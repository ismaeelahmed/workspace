/*
 * list_element.h
 *
 *  Created on: Nov 2, 2013
 *      Author: mavrick
 */

#ifndef LIST_ELEMENT_H_
#define LIST_ELEMENT_H_

class list_element
{
public:
	list_element(int data=0, list_element * ptr= 0): d(data),next(ptr){}
	int d;
	list_element * next;
	//friend class list;

};

#endif /* LIST_ELEMENT_H_ */
