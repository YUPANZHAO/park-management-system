#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "node.h"
#include<iostream>
using namespace std;

template <class T>
class queue
{
	Node<T>*fro,*rear;
	public:
		queue();
		~queue();
		void push(T x);
		void pop();
		T front();
		int size();
		bool empty();
};

#endif