/*
 * stack.h
 *
 *  Created on: Apr 9, 2017
 *      Author: mina
 */

#define default_value 100

template< class T > class Stack
{
    public:
	Stack(int = default_value);//default constructor
	~Stack()//destructor
	{delete [] values;}
	bool push( T );
	T pop();
	T peek();
	void print();
	bool isEmpty();
	bool isFull();

	int size;
	T *values;
	int index;

};

