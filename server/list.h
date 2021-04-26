
typedef struct
{
	int id;
	void* data;
	struct Node* next;
}Node;
extern int CountOfItems;

Node* ListGetItem(int index, Node** head_of_list);
int ListGetItemIndexbyID(int id, Node** head_of_list);
Node* ListAddItem(void* data, Node** head_of_list);
void ListDeleteItem(int ItemID, Node** head_of_list);
void ListDeleteFirstItem(Node** head_of_list);
