/*
 *  CSC 173 Project 1: Finite Automata
 *  Author: Thanh Pham
 */


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "dfa.h"
#include "nfa.h"
#include "subset_construction.h"
#include "questions.h"


//Exactly the string "happy"
DFA happy() {
	//Create DFA
	DFA happy = new_DFA(6);
	DFA_set_description(happy, "Exactly the string \"happy\"");
	DFA_set_accepting(happy, 5, true);

	DFA_set_transition(happy, 0, 'h', 1);
	DFA_set_transition(happy, 1, 'a', 2);
	DFA_set_transition(happy, 2, 'p', 3);
	DFA_set_transition(happy, 3, 'p', 4);
	DFA_set_transition(happy, 4, 'y', 5);

	return happy;
}

DFA start_39s() {
	//Create DFA
	DFA start_39s = new_DFA(4);
	DFA_set_description(start_39s, "Any string that starts with three 9s");
	DFA_set_accepting(start_39s, 3, true);

	DFA_set_transition(start_39s, 0, '9', 1);
	DFA_set_transition(start_39s, 1, '9', 2);
	DFA_set_transition(start_39s, 2, '9', 3);
	DFA_set_transition(start_39s, 0, '9', 1);
	DFA_set_transition_all(start_39s, 3, 3);

	return start_39s;
}

DFA even1() {
	//Create DFA
	DFA even1 = new_DFA(3);
	DFA_set_description(even1, "Binary input with an even number of 1s");
	DFA_set_accepting(even1, 2, true);

	DFA_set_transition(even1, 0, '0', 0);
	DFA_set_transition(even1, 0, '1', 1);
	DFA_set_transition(even1, 1, '0', 1);
	DFA_set_transition(even1, 1, '1', 2);
	DFA_set_transition(even1, 2, '0', 2);
	DFA_set_transition(even1, 2, '1', 1);

	return even1;
}

DFA odd0_even1() {
	//Create DFA
	DFA odd0_even1 = new_DFA(4);
	DFA_set_description(odd0_even1, "Binary input with an odd number of 0s and an even number of 1s");
	DFA_set_accepting(odd0_even1, 1, true);

	DFA_set_transition(odd0_even1, 0, '0', 1);
	DFA_set_transition(odd0_even1, 0, '1', 3);
	DFA_set_transition(odd0_even1, 1, '0', 0);
	DFA_set_transition(odd0_even1, 1, '1', 2);
	DFA_set_transition(odd0_even1, 2, '0', 3);
	DFA_set_transition(odd0_even1, 2, '1', 1);
	DFA_set_transition(odd0_even1, 3, '0', 2);
	DFA_set_transition(odd0_even1, 3, '1', 0);

	return odd0_even1;

}

DFA custom_dfa() {
	DFA custom_dfa = new_DFA(4);
	DFA_set_description(custom_dfa, "Custom DFA: Binary input that ends with 100");
	DFA_set_accepting(custom_dfa, 3, true);

	DFA_set_transition(custom_dfa, 0, '0', 0);
	DFA_set_transition(custom_dfa, 0, '1', 1);
	DFA_set_transition(custom_dfa, 1, '0', 2);
	DFA_set_transition(custom_dfa, 1, '1', 1);
	DFA_set_transition(custom_dfa, 2, '0', 3);
	DFA_set_transition(custom_dfa, 2, '1', 1);
	DFA_set_transition(custom_dfa, 3, '0', 0);
	DFA_set_transition(custom_dfa, 3, '1', 1);

	return custom_dfa;
}

NFA end_ing() {
	NFA end_ing = new_NFA(4);
	NFA_set_description(end_ing, "Strings ending in \"ing\"");
	NFA_set_accepting(end_ing, 3, true);

	NFA_add_transition_all(end_ing, 0, 0);
	NFA_add_transition(end_ing,  0, 'i', 1);
	NFA_add_transition(end_ing,  1, 'n', 2);
	NFA_add_transition(end_ing,  2, 'g', 3);

	return end_ing;
}

NFA contain_ing() {
	NFA contain_ing = new_NFA(6);
	NFA_set_description(contain_ing, "Strings containing \"ing\"");
	NFA_set_accepting(contain_ing, 3, true);

	NFA_add_transition_all(contain_ing, 0, 0);
	NFA_add_transition_all(contain_ing, 3, 3);
	NFA_add_transition(contain_ing,  0, 'i', 1);
	NFA_add_transition(contain_ing,  1, 'n', 2);
	NFA_add_transition(contain_ing,  2, 'g', 3);

	return contain_ing;
}

NFA washington() {
	NFA washington = new_NFA(12);
	NFA_set_description(washington, "Strings with more than 1 a, g, h, i, o, s, t, or w or more than 2 n's");

	NFA_set_accepting(washington, 11, true);

	NFA_add_transition_all(washington, 0, 0);
	NFA_add_transition_all(washington, 1, 1);
	NFA_add_transition_all(washington, 2, 2);
	NFA_add_transition_all(washington, 3, 3);
	NFA_add_transition_all(washington, 4, 4);
	NFA_add_transition_all(washington, 5, 5);
	NFA_add_transition_all(washington, 6, 6);
	NFA_add_transition_all(washington, 7, 7);
	NFA_add_transition_all(washington, 8, 8);
	NFA_add_transition_all(washington, 9, 9);
	NFA_add_transition_all(washington, 10, 10);
	NFA_add_transition_all(washington, 11, 11);

	//Transitions from state 0
	NFA_add_transition(washington, 0, 'a', 1);
	NFA_add_transition(washington, 0, 'g', 2);
	NFA_add_transition(washington, 0, 'h', 3);
	NFA_add_transition(washington, 0, 'i', 4);
	NFA_add_transition(washington, 0, 'n', 5);
	NFA_add_transition(washington, 5, 'n', 6); //second 'n'
	NFA_add_transition(washington, 0, 'o', 7);
	NFA_add_transition(washington, 0, 's', 8);
	NFA_add_transition(washington, 0, 't', 9);
	NFA_add_transition(washington, 0, 'w', 10);

	//Transitions to accepting state 11
	NFA_add_transition(washington, 1, 'a', 11);
	NFA_add_transition(washington, 2, 'g', 11);
	NFA_add_transition(washington, 3, 'h', 11);
	NFA_add_transition(washington, 4, 'i', 11);
	NFA_add_transition(washington, 6, 'n', 11);
	NFA_add_transition(washington, 7, 'o', 11);
	NFA_add_transition(washington, 8, 's', 11);
	NFA_add_transition(washington, 9, 't', 11);
	NFA_add_transition(washington, 10, 'w', 11);

	return washington;
}

NFA custom_nfa() {
	NFA custom_nfa = new_NFA(4);
	NFA_set_description(custom_nfa, "Custom NFA: Strings that start & end with \"n\", and have a \"t\" anywhere");
	NFA_set_accepting(custom_nfa, 3, true);

	NFA_add_transition_all(custom_nfa, 1, 1);
	NFA_add_transition_all(custom_nfa, 2, 2);
	NFA_add_transition_all(custom_nfa, 3, 2);
	NFA_add_transition(custom_nfa, 0, 'n', 1);
	NFA_add_transition(custom_nfa, 1, 't', 2);
	NFA_add_transition(custom_nfa, 2, 'n', 3);

	return custom_nfa;
}


