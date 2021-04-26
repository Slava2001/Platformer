#include <stdlib.h> 
#include "list.h"

int CountOfItems = 0;

Node* ListGetItem(int index, Node** head_of_list)
{
	Node* tmp;
	tmp = *head_of_list;
	for (int i = 0; i < index && tmp->next; i++)
	{
		tmp = tmp->next;
	}
	return tmp;
}
int ListGetItemIndexbyID(int id, Node** head_of_list)
{
	Node* tmp;
	tmp = *head_of_list;

	for (int i = 0; i < CountOfItems; i++)
	{
		if (tmp->id == id)
			return i;

		tmp = tmp->next;
	}
	return -1;
}

Node* ListAddItem(void* data, Node** head_of_list)
{

	Node* temp = (Node*)malloc(sizeof(Node));
	if (!temp)exit(-1);


	temp->id = rand();
	
	temp->data = data;


	if (!CountOfItems)
	{
		temp->next = *head_of_list;
		*head_of_list = temp;
	}
	else
	{
		Node* tmphead = ListGetItem(CountOfItems-1,head_of_list);

		temp->next = tmphead->next;
		tmphead->next = temp;
	}
	CountOfItems++;
	return temp;
}

void ListDeleteItem(int ItemID, Node** head_of_list)
{
	
	Node* temp = NULL;

	int n = ListGetItemIndexbyID(ItemID,head_of_list);
	if (n == -1)return;

	if (n == 0)
	{
		temp = *head_of_list;
		*head_of_list = temp->next;
	}
	else if (n > 0)
	{
		Node* temp2 = ListGetItem(n - 1, head_of_list);
		if (temp2->next)
		{
			temp = temp2->next;
			temp2->next = temp->next;
		}
	}

	free(temp);
	CountOfItems--;
}

void ListDeleteFirstItem(Node** head_of_list)
{
	Node* temp = *head_of_list;
	*head_of_list = temp->next;
	free(temp);
}