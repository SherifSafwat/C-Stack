//============================================================================
// Name        : a3.cpp
// Author      : mina
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <sstream>
#include <stdlib.h>
#include <typeinfo>
#include <iomanip>
#include "stack.h"

using namespace std;

const char * expressionToParse;
Stack <float> *s_numbers;
Stack <char> *s_ops;

fstream outFile1;
int ii =0;

/////////////////////////////////////////////////////////////////////////
////////// Stack
/////////////////////////////////////////////////////////////////////////

template< class T > Stack<T>::Stack(int x):
    size(x),//ctor
    values(new T[size]),
    index(-1)
{ /*empty*/  }

template<class T> bool Stack<T>::isEmpty()
{
    if( index  == -1 )//is empty
    	return 1;
    else
    	return 0; //is not empty
}

template< class T > bool Stack<T>::isFull()
{
    if((index + 1) == size )
    	return 1;
    else
    	return 0;
}

template< class T > bool Stack<T>::push(T x)
{
    bool b = 0;
    if(!Stack<T>::isFull())
    {
    	index += 1;
    	values[index] = x;
    	b = 1;
    }
    return b;
}

template< class T > T Stack<T>::peek( )
{
    T val = -1;
    if(!Stack<T>::isEmpty())
    {
    	val = values[index];
    }
    else
    {
    	val = 0;
        //cout << "Stack is Empty : ";
    }
    return val;
}

template< class T > T Stack<T>::pop()
{
    T val = -1;
    if(!Stack<T>::isEmpty())
    {
    	val = values[index];
		index -=  1;
    }
    else
    {
    	val = 0;
    	//cout << "Stack is Empty : ";
    }
    return val;

}

template< class T > void Stack<T>::print()
{
	int i=0;
    //fstream outFile;    outFile.open ("test.txt", std::ofstream::out | std::ofstream::app);

    while(i <= index) //!Stack<T>::isEmpty())
    {
    	//outFile << values[index] << "Y";
    	outFile1 << values[i] << " ";
		i++;
    }

    //outFile.close();

}

/////////////////////////////////////////////////////////////////////////
////////// Functions
/////////////////////////////////////////////////////////////////////////

char get()
{
    return *expressionToParse++;
}

char peek()
{
    return *expressionToParse;
}

char last()
{
    return *expressionToParse--;
}

int number()
{
    int result = get() - '0';

    while (peek() >= '0' && peek() <= '9')
    {
        result = 10*result + get() - '0';
    }
    return result;
}

int check(char new_op)
{

	if( ( new_op == 'x' || new_op == '/' ) && ( s_ops->peek() == '/' || s_ops->peek() == 'x') )
	{
		return 1;
	}


	if( ( new_op == '+' || new_op == '-' ) && ( s_ops->peek() == '+' || s_ops->peek() == '-') )
	{
		return 1;
	}


	if ( (new_op == '+' || new_op == '-') && (s_ops->peek() == '/' || s_ops->peek() == 'x') )
	{
		return 1;
	}

	return 0;

}

int calc1()
{

	outFile1 << endl << endl << "--------------------  GO  --------------------------------" << endl ;
	outFile1 << "NU: "; s_numbers->print(); outFile1 << endl;
	outFile1 << "OP: "; s_ops->print(); outFile1 << endl;

	float re = 0;


	if (not peek() && s_ops-> index >s_numbers->index )
	{
		outFile1 << endl << "Invalid Expression Last" << endl;
		return -2;
	}

	if (s_numbers->index > 0 )
	{
		if (s_ops->peek() == 'x')
		{
			re = s_numbers->pop() * s_numbers->pop();
			s_numbers->push(re);
			s_ops->pop();

			outFile1 << "FU: x: " << re << endl;
		}
		else if (s_ops->peek() == '/')
		{
			re = s_numbers->pop();

			if(re == 0)
			{
				outFile1 << "divide Zero" << endl;
				return -1;
			}

			re = s_numbers->pop() / re;
			s_numbers->push(re);
			s_ops->pop();

			outFile1 << "FU: /: " << re << endl;
		}
		else if (s_ops->peek() == '+')
		{
			re = s_numbers->pop() + s_numbers->pop();
			s_numbers->push(re);
			s_ops->pop();

			outFile1 << "FU: +: " << re << endl;
		}
		else if (s_ops->peek() == '-')
		{
			re = s_numbers->pop();
			re = s_numbers->pop() - re;
			s_numbers->push(re);
			s_ops->pop();

			outFile1 << "FU: -: " << re << endl;
		}
	}
	else
	{
		outFile1 << endl << "Invalid Expression Numbers" << endl;
		return -2;
	}



	outFile1 << "NU: "; s_numbers->print(); outFile1 << endl;
	outFile1 << "OP: "; s_ops->print(); outFile1 << endl;
	outFile1 << "--------------------  CL  --------------------------------" << endl ;


	return 0;
}

int Parse()
{
	outFile1 << endl << "--------------------  NEW  --------------------------------" << endl ;
	outFile1 << expressionToParse << endl;

	int mi = 1;
	char p_last = 'O';

	while(peek())
	{ //ii++; if(ii > 80) { outFile1 << endl << "lllllllllooooooopppppppp" << endl; break; } // test


		if (peek() >= '0' && peek() <= '9')
		{

			if (mi == -1)
			{
				s_numbers->push(number()*mi);
				mi = 1;
			}
			else
			{
				s_numbers->push(number()*mi);
			}

			p_last = 'N';

			outFile1 << endl << "CH: "<< s_numbers->peek();
		}
		else if (peek() == '-' || peek() == '+' || peek() == 'x' || peek() == '/')
		{


			if (p_last == 'O' && peek() == '-')
			{
				mi = -1;
				get();
			}
			else if (p_last == 'O' && peek() == '+')
			{
				mi = 1;
				get();
			}
			else
			{

				while (check(peek()))
				{
					if(calc1() == -2)
					{
						cout << "Invalid Expression";
						return -1;
					}
				}

				s_ops->push(get());

				outFile1 << endl << "CH: "<< s_ops->peek();

			}

			p_last = 'O';

		}
		else if (peek() == '(')
		{
			if ( p_last == 'N' )
			{
				cout << "Invalid Expression";
				return -1;
			}

			s_ops->push(get());
			outFile1 << endl << "CH: "<< s_ops->peek();
		}
		else if (peek() == ')')
		{

			outFile1 << endl << "CH: "<< peek();
			//s_ops->push(get());
			get();

			while (s_ops->peek() != '(')
			{ //ii++; if(ii > 80) { outFile1 << endl << "lllllllllooooooopppppppp" << endl; break; } // test
				outFile1 << endl << "FU: exp:" << endl;
				if(calc1() == -2)
				{
					cout << "Invalid Expression";
					return -1;
				}

			}

			if(not peek() && s_ops->peek() == '(' && s_ops->index > 0 )
			{
				cout << "Invalid Expression";
				return -1;
			}
			else
			{
				s_ops->pop();
			}
		}
		else
		{
			cout << "Invalid Expression";
			return -1;
		}

	}


	if (not peek() && not s_ops->peek())
	{
		cout << std::fixed << std::setprecision(2) << s_numbers->peek() ;
		outFile1 << endl <<  std::fixed << std::setprecision(2) << s_numbers->peek() ;
		outFile1 << endl << "--------------------  END  --------------------------------" << endl ;
	}



	return 0;

}

int main(int argc,char *argv[])
{

	outFile1.open ("test1.txt", std::ofstream::out | std::ofstream::app);

	if (argc < 2)
	{
		cout << "0.00" ;
		return 0;
	}


	if ( (strcmp(argv[1], " ") == 0 ) || (argc < 2) )
	{
		cout << "0.00" ;
		return 0;
	}

	if (argc > 2 )
	{
		cout << "Invalid Expression";
		return 0;
	}

	if ( not ( (argv[1][0] >= '0' && argv[1][0] <= '9') || (argv[1][0] == '+') || (argv[1][0] == '-') || (argv[1][0] == '(') ) )
	{
		cout << "Invalid Expression";
		return 0;
	}

	s_numbers = new Stack <float>(100);
	s_ops = new Stack <char>(100);

	string s1;
	s1 = "(" + string(argv[1]) + ")";
	expressionToParse = s1.c_str();

	Parse();

	delete s_numbers;
	delete s_ops;
	return 0;
}
