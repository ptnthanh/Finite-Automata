/*
 *  CSC 173 Project 1: Finite Automata
 *  Author: Thanh Pham
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include "dfa.h"
#include "nfa.h"
#include "BitSet.h"
#include "LinkedList.h"
#include "subset_construction.h"


DFA NFA_to_DFA(NFA nfa ) {
	LinkedList states = new_LinkedList();
	LinkedList sets = new_LinkedList();

	DFA_State s0 = new_DFA_State();
	LinkedList_add_at_front(states, s0);

	BitSet start = new_BitSet();
	BitSet_insert(start, 0);
	LinkedList_add_at_front(sets, start);

	int nstates = 1;
	int index = -1;
	LinkedListIterator states_it = LinkedList_iterator(states);
	LinkedListIterator sets_it = LinkedList_iterator(sets);

	//Iterate through each state in the list
	while (LinkedListIterator_hasNext(states_it)) {
		index++;
		DFA_State cur_state = LinkedList_elementAt(states, index);
		BitSet cur_set = LinkedList_elementAt(sets, index);

		//Use nfa transition function to find all possible destination for each symbol
		for (int sym = 0; sym < 128; sym++) {

			BitSet dst = new_BitSet();
			BitSetIterator cur_set_it = BitSet_iterator(cur_set);
			while (BitSetIterator_hasNext(cur_set_it)) {
				int temp = BitSetIterator_next(cur_set_it);
				BitSet_union(dst, NFA_get_transitions(nfa, temp, sym));

				//set current state to accepting if one of the state in set is accepting
				if (NFA_get_accepting(nfa, temp)) {
					cur_state->accept = true;
				}
			}
			free(cur_set_it);

			//Add set to list if not already in
			int check = -1;
			int inter = 0;
			LinkedListIterator check_it = LinkedList_iterator(sets);
			while (LinkedListIterator_hasNext(check_it)) {

				BitSet tempbs = LinkedListIterator_next(check_it);
				if (BitSet_equals(tempbs, dst)) {
					check = inter;
				}
				inter++;
			}
			free(check_it);


			if (check < 0 && (!BitSet_isEmpty(dst))) {
				DFA_State sk = new_DFA_State();
				cur_state->trans[sym] = nstates;
				LinkedList_add_at_end(states, sk);
				LinkedList_add_at_end(sets, dst);
				nstates++;
			} else if (!BitSet_isEmpty(dst)) {
				cur_state->trans[sym] = check;

			}
		}
		DFA_State next_state = LinkedListIterator_next(states_it);
		BitSet next_set = LinkedListIterator_next(sets_it);
	}

	//Create dfa, copy states from list
	DFA dfa = new_DFA(nstates);
	DFA_set_description(dfa, NFA_get_description(nfa));
	LinkedListIterator accept_it = LinkedList_iterator(states);
	for (int a = 0; a < nstates; a++) {
		DFA_State sta = LinkedListIterator_next(accept_it);
		dfa->states[a] = sta;
	}
	free(accept_it);
	free(states_it);
	free(sets_it);
	return dfa;
}

