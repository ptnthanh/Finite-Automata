/*
 *  CSC 173 Project 1: Finite Automata
 *  Author: Thanh Pham
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include "nfa.h"
#include "BitSet.h"


struct NFA {
	int nstates;
	BitSet current_state;
	BitSet** trans;
	bool* accept;
	char* desc;
};
typedef struct NFA *NFA;

NFA new_NFA(int nstates) {
	NFA nfa = (NFA)malloc(sizeof(struct NFA));
	nfa->nstates = nstates;
//	BitSet start = new_BitSet();
//	BitSet_insert(start, 0);
//	nfa->current_state = start;

	//Transition table
	nfa->trans = (BitSet**)malloc(nstates * sizeof(BitSet*));
	for (int i = 0; i < nstates; i++){
	    nfa->trans[i] = (BitSet *)malloc(128 * sizeof(BitSet));
	}

	for(int i = 0; i < nstates; i++){
		for(int j = 0; j < 128; j++){
	      nfa->trans[i][j] = new_BitSet();
		}
	}

	//Acceptance table
	nfa->accept = (bool*)malloc(nstates * sizeof(bool));
	for(int i=0; i<nstates; i++){
		nfa->accept[i] = false;
	  }

	return nfa;
}

void NFA_free(NFA nfa) {
	for (int i = 0; i < nfa->nstates; i++) {
//		for(int j=0; j<128; j++){
//			BitSet_free(nfa->trans[i][j]);
//	    }
//	    free(nfa->trans[i]);
	  }
	  free(nfa->trans);
	  BitSet_free(nfa->current_state);
	  free(nfa->accept);
	  free(nfa);
}

int NFA_get_size(NFA nfa) {
	return nfa->nstates;
}

void NFA_set_description(NFA nfa, char* str) {
	nfa->desc = str;
}

char* NFA_get_description(NFA nfa) {
	return nfa->desc;
}

BitSet NFA_get_transitions(NFA nfa, int state, char sym) {
	return nfa->trans[state][sym];
}

void NFA_add_transition(NFA nfa, int src, char sym, int dst) {
	if (!BitSet_lookup(nfa->trans[src][sym], dst)) {
		BitSet_insert(nfa->trans[src][sym], dst);
	}
}

void NFA_add_transition_str(NFA nfa, int src, char *str, int dst) {
	for (int i = 0; i < strlen(str); i++) {
		int sym = str[i];
		if (!BitSet_lookup(nfa->trans[src][sym], dst)) {
			BitSet_insert(nfa->trans[src][sym], dst);
		}
	}
}

void NFA_add_transition_all(NFA nfa,  int src, int dst) {
	for (int i = 0; i < 128; i++) {
		if (!BitSet_lookup(nfa->trans[src][i], dst)) {
			BitSet_insert(nfa->trans[src][i], dst);
		}
	}
}

void NFA_set_accepting(NFA nfa, int state, bool value) {
	nfa->accept[state] = value;
}

bool NFA_get_accepting(NFA nfa, int state) {
	return nfa->accept[state];
}

bool NFA_execute(NFA nfa, char* input) {
	//Reset NFA
	if (nfa->current_state != NULL) {
		BitSet_free(nfa->current_state);
	}
	BitSet start = new_BitSet();
	BitSet_insert(start, 0);
	nfa->current_state = start;

	for (int i = 0; i < strlen(input); i++) {
		BitSet temp = new_BitSet();
		BitSetIterator it = BitSet_iterator(nfa->current_state);

		while(BitSetIterator_hasNext(it)) {
			int st = BitSetIterator_next(it);
			BitSet_union(temp, NFA_get_transitions(nfa, st, input[i]));
		}
		free(it);
		BitSet_free(nfa->current_state);

		nfa->current_state = temp;
		BitSet_union(nfa->current_state, temp);
	}
	bool accepted = false;
	BitSetIterator accept_it = BitSet_iterator(nfa->current_state);
	while (BitSetIterator_hasNext(accept_it)) {
		int cur = BitSetIterator_next(accept_it);
		if (nfa->accept[cur] == true) {
			accepted = true;
		}
	}
	free(accept_it);
	return accepted;
}

void NFA_print(NFA nfa) {
	for (int i = 0; i < NFA_get_size(nfa); i++) {
		printf("\nState %d - ", i);
		if (nfa->accept[i]) {
			printf("Accepting: True, ");
		} else {
			printf("Accepting: False, ");
		}
		printf("Transitions: ");
		for (int j = 0; j < 128; j++) {
			if (!BitSet_isEmpty(nfa->trans[i][j])) {
				printf("%c", j);
			}
		}
		printf("\n");
	}
}
