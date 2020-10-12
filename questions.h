/*
 *  CSC 173 Project 1: Finite Automata
 *  Author: Thanh Pham
 */


#ifndef QUESTIONS_H_
#define QUESTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dfa.h"
#include "nfa.h"

extern DFA happy();
extern DFA start_39s();
extern DFA even1();
extern DFA odd0_even1();
extern DFA custom_dfa();

extern NFA end_ing();
extern NFA contain_ing();
extern NFA washington();
extern NFA custom_nfa();

#endif /* QUESTIONS_H_ */
