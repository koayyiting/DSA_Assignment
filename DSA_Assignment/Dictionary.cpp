#include "Dictionary.h"
using namespace std;

//Default constructor
Dictionary::Dictionary()
{
	for (int i = 0; i < MAX_SIZE; i++)
	{
		items[i] = NULL;
	}
	size = 0;
};

//Destructor
Dictionary::~Dictionary()
{
	//need to release all pointers that references the heap
	for (int i = 0; i < MAX_SIZE; i++)
	{
		items[i] = NULL;
	}
};

int Dictionary::getLength()
{
	return size;
}

int charvalue(char c)
{
	if (isalpha(c))
	{
		if (isupper(c))
		{
			return (int)c - (int)'A';
		}
		else
		{
			return (int)c - (int)'a' + 26;
		}
	}
	else { return -1; }
}

int Dictionary::hash(KeyType newkey)
{
	string addName = newkey;
	char firstChar = addName[0];
	char rkey = charvalue(firstChar);
	int h = rkey % MAX_SIZE; //% gives the reminder when rkey divide by 101
	return h;
}

//check if the stack is empty
bool Dictionary::isEmpty()
{
	if (size == 0)
	{
		return true;
	}
	return false;
};

bool Dictionary::add(KeyType newkey, ItemType newitem)
{
	int index = hash(newkey);

	if (items[index] == NULL) // space is empty - start new list
	{
		items[index] = new Node;
		items[index]->key = newkey;
		items[index]->item = newitem;
		items[index]->next = NULL;

		//OR
		//Node* newNode = new Node;
		//newNode->key = newkey;
		//newNode->item = newitem;
		//newNode->next = NULL;
		//items[index] = newNode;
	}
	else
	{
		Node* current = items[index];

		if (current->key == newkey) { return false; }

		while (current->next != NULL)
		{
			current = current->next;
			if (current->key == newkey) // duplicate key
				return false;
		}

		//Add new node to end of list
		Node* newNode = new Node;
		newNode->key = newkey;
		newNode->item = newitem;
		newNode->next = NULL;
		current->next = newNode;
	}
	size++;
	return true;
}

void Dictionary::remove(KeyType key)
{
	int index = hash(key);
	if (items[index] != NULL)
	{
		Node* temp = items[index];
		Node* oneNodeb4 = items[index];
		while (temp->key != key)
		{
			oneNodeb4 = temp;
			temp = temp->next;
		}
		oneNodeb4->next = temp->next;
		delete temp;
		size--;
	}
}

ItemType Dictionary::get(KeyType key)
{
	int index = hash(key);
	if (items[index] != NULL)
	{
		Node* temp = items[index];
		return temp->item;
	}
};

void Dictionary::print()
{
	if (!isEmpty())
	{
		cout << "\nPhone List:" << endl;
		for (int i = 0; i < MAX_SIZE; i++)
		{
			Node* temp = items[i];
			if (temp != NULL)
			{
				cout << temp->key << ", " << temp->item << endl;
				while (temp->next != NULL)
				{
					temp = temp->next;
					cout << temp->key << ", " << temp->item << endl;
				}
			}
		}
	}
};


