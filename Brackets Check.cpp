#include <bits/stdc++.h>

using namespace std;
//Allow brackets like [[]]/([])[{}]
#define ignore_level 0
//Maxnium length of the equation
#define max_length 1000

template <class T>
class element{
	public:
	T data;
	class element* next;
	class element* prev;
	element<T>()
	{
		this->next = NULL;
		this->prev = NULL;
	}
	element<T>(T* input)
	{
		data = *input;
		this->next = NULL;
		this->prev = NULL;
	}
};

template <class T>
class stk{
	private:
	element<T>* _top;
	element<T>* _head;
	int size;
	public:
	stk()
	{
		_top = NULL;
		_head = NULL;
		size = 0;
	}
	void push(element<T>* src)
	{
		if(src)
		{
			//If already has element in stack
			if(_head)
			{
				size++;
				this->_top->next = src;
				src->prev = _top;
				this->_top = src;
			}
			else
			{
				size++;
				this->_head = src;
				this->_top = src;
				this->_top->prev = NULL;
			}
		}
	}
	void pop()
	{
		if(size > 0)
		{
			element<T> *temp = _top->prev;
			delete _top;
			_top = temp;
			//If this is the last element
			if(!_top)
			_head = NULL;
			size-=1;
		}
	}
	element<T>* top(){return this->_top;}
	T topdata(){if(_top) return this->_top->data; else return *(new T);}
	element<T>* head(){return this->_head;}
	T headata(){if (_head) return this->_head->data; else return *(new T);}
	int getsize(){return size;}
};

int getlevel(char input)
{
	switch(input)
		{
			case '{':
			return 3;
			case '(':
			return 1;
			case '[':
			return 2;
			default:
			//If input is NULL means allow all the brackets
			return INT_MAX;
		}
	return INT_MAX;
}

							
int main()
{
	char input[max_length];
	int current_level = 0;
l2:	
	cout << "Please enter the equation:\n";
	while(cin >> input)
	{
		stk<char> *s = new stk<char>();
		bool unmatch = 0;
		for(int i = 0; i < strlen(input) ;i ++)
		{
			if(input[i] == '(' || input[i] == '[' || input[i] == '{')
			{
				if(ignore_level == 0)
				{
					if(getlevel(input[i]) == 3 ? getlevel(input[i]) > getlevel(s->topdata()) : getlevel(input[i]) >= getlevel(s->topdata()))
					{
						unmatch = 1;
						goto l1;
					}
				}
				s->push(new element<char>(&input[i]));
			}

			else
			if(input[i] == ')' || input[i] == ']' || input[i] == '}')
			{
				if(!s->getsize())
				{
					unmatch = 1;
					goto l1;
				}
				char temp = s->topdata();
				s->pop();
				switch (temp)
				{
					case '(' :
					{
						if (input[i] == ')')
						{
							continue;
						}
						else
						{
							unmatch = 1;
							break;
						}
					};
					case '[' : 
					{
						if (input[i] == ']')
						{
							continue;
						}
						else
						{
							unmatch = 1;
							break;
						};
					};
					case '{' : 
					{
						if (input[i] == '}')
						{
							continue;
						}
						else
						{
							unmatch = 1;
							break;
						};
					};
					default:
					{
						unmatch = 1;
						break;	
					};
				};
			};
		};
		
	l1:
		if(unmatch || s->getsize())
		cout << "The equation has problem.\n";
		else
		cout << "The equation is currently good.\n";
		goto l2;
	}
	return 0;
}
