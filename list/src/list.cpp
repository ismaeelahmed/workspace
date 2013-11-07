/*
 * list
 *
 *  Created on: Nov 1, 2013
 *      Author: mavrick
 */
#include <iostream>
#include "list_element.h"

using namespace std;

class list{
public:

	list():head(0), cursor(0){}
	//list(int s, list *p, list *q):d(s),head(p), cursor(q){}
	list(const int* arr, int n);
	list(const list& lst);//copy constructor
	void prepend(int n); //insert at front value n
	int get_element(){return cursor->d;}
	void advance(){ cursor= cursor-> next;}
	void print();

 ~list(); //delete

private:
  list_element * head;
  list_element* cursor;
 };

list::~list()
{
	 for( cursor = head; cursor != 0; )
	 { cursor = head->next;
	 delete head;
	 head = cursor;  
	 }

}

void list::prepend(int n)
 { if (head == 0)//empty list case
 cursor = head = new list_element(n,head);
 else//add to front -chain
 head = new list_element(n, head);
 }

list::list(const list& a)//copy constructor
{
	if(a.head==0)
	{	head=0;cursor=0;	}
	else
	{
	//add code here to print the first element of array aswell

	
		for(cursor=a.head ; cursor!=0; )
		{
		head=new list_element(cursor->d,head->next);
	//	cout << cursor->d<<endl;
		
		cursor=cursor->next;
		}cursor=head;
	}
}

void list:: print(){
 list_element* h = head;
 while(h != 0){//idiom for chaining
 cout << h->d << ", ";
 h = h -> next;
 }
 cout << "###" << endl;
 }

int main(void)
{
 list a, b;
 a.prepend(9); a.prepend(8);
 cout << " list a " << endl;
 a.print();
 
list c(a);
 cout << " Copied List "<<endl;
 c.print();


for (int i = 0; i < 40; ++i)
 b.prepend(i*i);
 cout << " list b " << endl;
 b.print();

 return(0);
}


