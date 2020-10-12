/*
 *  CSC 173 Project 1: Finite Automata
 *  Author: Thanh Pham
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "dfa.h"

typedef struct DFA* DFA;
typedef struct DFA_State* DFA_State;

DFA_State new_DFA_State() {
	DFA_State this = (DFA_State)malloc(sizeof(struct DFA_State));
	this->trans = (int*)malloc(128*sizeof(int));
	for (int i = 0; i < 128; i++) {
		this->trans[i] = -1;
	}
	this->accept = false;
	return this;
}

/**
 * Allocate and return a new DFA containing the given number of states.
 */
DFA new_DFA(int nstates) {
	DFA this = (DFA)malloc(sizeof(struct DFA));
	if (this == NULL) {
		return NULL;
	}
	this->nstates = nstates;
	this->current_state = 0;

	this->states = (DFA_State*)malloc(nstates*sizeof(DFA_State));
	for (int i = 0; i < nstates; i++) {
		this->states[i] = new_DFA_State();
	}
	return this;
}

/**
 * Free the given DFA.
 */
void DFA_free(DFA dfa) {
//	for (int i = 0; i < dfa->nstates; i++) {
//		free(dfa->states[i]);
//	}
	free(dfa->states);
	free(dfa);
}

/**
 * Return the number of states in the given DFA.
 */
int DFA_get_size(DFA dfa) {
	return dfa->nstates;
}

char* DFA_get_description(DFA dfa) {
	return dfa->desc;
}

void DFA_set_description(DFA dfa, char* str) {
	dfa->desc = str;
}

/**
 * Return the state specified by the given DFA's transition function from
 * state src on input symbol sym.
 */
int DFA_get_transition(DFA dfa, int src, char sym) {
	return dfa->states[src]->trans[sym];
}

/**
 * For the given DFA, set the transition from state src on input symbol
 * sym to be the state dst.
 */
void DFA_set_transition(DFA dfa, int src, char sym, int dst) {
	dfa->states[src]->trans[sym] = dst;
}

/**
 * Set the transitions of the given DFA for each symbol in the given str.
 * This is a nice shortcut when you have multiple labels on an edge between
 * two states.
 */
void DFA_set_transition_str(DFA dfa, int src, char *str, int dst) {
	for (int i = 0; i < strlen(str); i++) {
		dfa->states[src]->trans[str[i]] = dst;
	}
}

/**
 * Set the transitions of the given DFA for all input symbols.
 * Another shortcut method.
 */
void DFA_set_transition_all(DFA dfa, int src, int dst) {
	for (int i = 0; i < 128; i++) {
		dfa->states[src]->trans[i] = dst;
	}
}

/**
 * Set whether the given DFA's state is accepting or not.
 */
void DFA_set_accepting(DFA dfa, int state, bool value) {
	dfa->states[state]->accept = value;
}

/**
 * Return true if the given DFA's state is an accepting state.
 */
bool DFA_get_accepting(DFA dfa, int state) {
	return dfa->states[state]->accept;
}

/**
 * Run the given DFA on the given input string, and return true if it accepts
 * the input, otherwise false.
 */
bool DFA_execute(DFA dfa, char *input) {
	dfa->current_state = 0;
	for (int i = 0; i < strlen(input); i++) {
		dfa->current_state = DFA_get_transition(dfa, dfa->current_state, input[i]);
		if (dfa->current_state == -1) {
			return false;
		}
	}
	return DFA_get_accepting(dfa, dfa->current_state);
}

/**
 * Print the given DFA to System.out.
 * Print each state of the DFA, whether it's accepting
 */
void DFA_print(DFA dfa) {
	//Iterate through each state, check its transitions
	for (int i = 0; i < DFA_get_size(dfa); i++) {
		printf("\nState %d -", i);
		if (dfa->states[i]->accept) {
			printf(" Accepting: True, ");
		} else {
			printf(" Accepting: False, ");
		}

		int count = 0;
		for (int j = 0; j < 128; j++) {
			if (dfa->states[i]->trans[j] != -1) {
				count++;
			}
		}

		if (count >= 128) {
			printf("Transitions: All character.");
		} else {
			printf("Transitions: ");
			for (int k = 0; k < 128; k++) {
				if (dfa->states[i]->trans[k] != -1) {
					if (k != '\200') {
						printf("%c", k);
					}
				}
			}
		}
		printf("\n");
	}
}

