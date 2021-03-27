#include "stack.h"
template<class T>
stack<T>::stack()
{
	Top = NULL;
}
template<class T>
void stack<T>::pop()
{
	if(Top==NULL)return ;
	Node<T>*p=new Node<T>;
	p=Top;
	Top=Top->next;
	delete p;
 } 
template<class T>
T stack<T>::top()
{
	return Top->data;
}
template<class T>
void stack<T>::push(T x)
{
	Node<T>*a=new Node<T>;
	a->data=x;
	a->next=Top;
	Top=a;
}
template<class T>
bool stack<T>::empty()
{
	return Top==NULL;
}
template<class T>
stack<T>::~stack()
{
	Node<T>*p=new Node<T>;
	p=Top;
	while(p){
		Node<T>*s = new Node<T>;
		s=p;
		p=p->next;
		delete s;
	}
	Top = NULL;
}
template<class T>
int stack<T>::size()
{
	int i=0;
	Node<T> *p = Top;
	while(p) {
		i++;
		p = p->next;
	}	
	return i;
}
