#ifndef _NODE_H_
#define _NODE_H_

template<class T>
struct Node
{
	T data;
	Node<T> *next;
};

#endif