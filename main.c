/*
 *  CSC 173 Project 1: Finite Automata
 *  Author: Thanh Pham
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "nfa.h"
#include "dfa.h"
#include <math.h>
#include "LinkedList.h"
#include "BitSet.h"
#include "questions.h"
#include "subset_construction.h"


void REPL_DFA(DFA dfa) {
	printf("%s\n", DFA_get_description(dfa));
	char input[100];
	do {

		printf("Enter an input(\"quit\" to quit): ");
		scanf(" %s", input);

		if (strcmp("quit",input) == 0) {
			break;
		}

		printf("Result for input \"%s\": %s\n", input, DFA_execute(dfa, input)?"true":"false");
		printf("\n");

	} while (strcmp("quit",input) != 0);

	printf("--------------------\n");
//	DFA_free(dfa);
}

void REPL_NFA(NFA nfa) {
	printf("%s\n", NFA_get_description(nfa));
	char input[100];
	do {

		printf("Enter an input(\"quit\" to quit): ");
		scanf(" %s", input);

		if (strcmp("quit",input) == 0) {
			break;
		}

		printf("Result for input \"%s\": %s\n", input, NFA_execute(nfa, input)?"true":"false");
		printf("\n");

	} while (strcmp("quit",input) != 0);

	printf("--------------------\n");
//	NFA_free(nfa);

}

int main(int argc, char *argv[]) {
	printf("\nCSC173 Project 1 by Thanh Pham \n");

	printf("----------PROBLEM 1: DFA----------\n");
	REPL_DFA(happy());
	REPL_DFA(start_39s());
	REPL_DFA(even1());
	REPL_DFA(odd0_even1());
	REPL_DFA(custom_dfa());

	printf("----------PROBLEM 2: NFA----------\n");
	REPL_NFA(end_ing());
	REPL_NFA(contain_ing());
	REPL_NFA(washington());
	REPL_NFA(custom_nfa());

	printf("----------PROBLEM 3: NFA To DFA----------\n");
	DFA end_ing_dfa = NFA_to_DFA(end_ing());
	printf("States in the new DFA: %d\n", DFA_get_size(end_ing_dfa));
	REPL_DFA(end_ing_dfa);

	DFA contain_ing_dfa = NFA_to_DFA(contain_ing());
	printf("States in the new DFA: %d\n", DFA_get_size(contain_ing_dfa));
	REPL_DFA(contain_ing_dfa);

	DFA wash_dfa = NFA_to_DFA(washington());
	printf("States in the new DFA: %d\n", DFA_get_size(wash_dfa));
	REPL_DFA(wash_dfa);

	DFA custom_nfa_to_dfa = NFA_to_DFA(custom_nfa());
	printf("States in the new DFA: %d\n", DFA_get_size(custom_nfa_to_dfa));
	REPL_DFA(custom_nfa_to_dfa);

}
