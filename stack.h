#ifndef _STACK_H_
#define _STACK_H_

#include "node.h"
#include<iostream>
using namespace std;

template<class T>
class stack
{
	Node<T>* Top;
	public:
		stack();
		~stack();
		void push(T x);
		void pop();
		T top();
		int size();
		bool empty();		 
};
#endif
