#include "queue.h"
template <class T>
queue<T>::queue()
{
	Node<T> *s=new Node<T>;
	s->next=NULL;
	fro=rear=s;
}

template <class T>
void queue<T>::push(T x)
{
	Node<T> *s=new Node<T>;
	s->data=x;
	s->next=NULL;
	rear->next=s;
	rear=s;
}

template <class T>
void queue<T>::pop()
{
	if(rear==fro) 
	return ;
	Node<T> *p=fro->next;
	T x=p->data;
	fro->next=p->next;
	if(p->next==NULL)
	rear=fro;
	delete p;
}

template<class T>
T queue<T>::front(){
	Node<T> *p;
	T x;
	p=fro->next;
	x=p->data;
	return x;
}

template <class T>
bool queue<T>::empty()
{
	return fro == rear;
}

template <class T>
queue<T>::~queue()
{
	Node<T>*p;
	p=fro;
	while(p){
		Node<T>*s;
		s=p;
		p=p->next;
		delete s;
	}
	fro=NULL;
}

template <class T>
int queue<T>::size()
{
	int i=0;
	Node<T>*p=fro->next;
	while(p){
		i++;
		p=p->next;
	}
	return i;
}
