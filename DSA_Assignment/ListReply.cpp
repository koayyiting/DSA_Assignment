// List.cpp - Implementation of List ADT using Array
#include "ListReply.h"  // header file
#include "Reply.h"

// constructor
ListReply::ListReply() { size = 0; }

// add an item to the back of the list (append)
bool ListReply::add(Reply item)
{
	Node* newNode = new Node;
	newNode->item = item;
	newNode->next = NULL;

	if (size == 0)
	{
		firstNode = newNode;
	}
	else
	{
		Node* current = firstNode;
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = newNode;
	}
	size++;
	return true;
}

// add an item at a specified position in the list (insert)
bool ListReply::add(int index, Reply item)
{
	if (index < size && index >= 0)
	{
		Node* newNode = new Node;
		newNode->item = item;
		newNode->next = NULL;

		if (index == 0)
		{
			newNode->next = firstNode; //idk crrt or wrong
			firstNode = newNode;
		}
		else
		{
			Node* current = firstNode;
			for (int i = 0; i < index - 1; i++)
			{
				current = current->next;
			}
			newNode->next = current->next;
			current->next = newNode;
		}
		size++;
		return true;
	}
	else { return false; }
}

// remove an item at a specified position in the list
void ListReply::remove(int index)
{
	if (index < size && index >= 0)
	{
		if (index == 0)
		{
			firstNode = firstNode->next;
		}
		else
		{
			Node* current = firstNode;
			for (int i = 0; i < index - 1; i++)
			{
				current = current->next;
			}
			if (current->next != NULL) {
				current->next = current->next->next;
			}
		}
		size--;
	}
}

// get an item at a specified position of the list (retrieve)
Reply ListReply::get(int index)
{
	if (index < size && index >= 0)
	{
		Node* current = firstNode;
		for (int i = 0; i < index; i++)
		{
			current = current->next;
		}
		return current->item;
	}
}

// check if the list is empty
bool ListReply::isEmpty() { return size == 0; }

// check the size of the list
int ListReply::getLength() { return size; }

// display the items in the list
void ListReply::print()
{
	Node* temp = firstNode;
	if (temp == NULL) {
		cout << "List is Empty" << endl;
	}
	else {
		while (temp != NULL) {
			//cout << temp->item.getTopicTitle() << endl;
			temp = temp->next;
		}
	}
}


// replace the  item in the specified index in the list
//void List::replace(int index, ItemType item)
//{
//
//}