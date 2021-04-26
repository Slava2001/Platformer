#define _CRT_SECURE_NO_WARNINGS 1
#define _WINSOCK_DEPRECATED_NO_WARNINGS


#include "Lan.h"

extern float zoom;

#define maxp 10



Node* ClientsList = NULL;


WSADATA ws;

SOCKET s;

SOCKADDR_IN sa;

void LanPlayerAcceptor();

void LanInit()
{
	WSAStartup(MAKEWORD(2, 2), &ws);

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (!s) { printf("create socket err!"); getchar(); return -1; }

	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(9595);

	printf("Server started\n");

}

void LanPlayerAcceptor()
{
	bind(s, &sa, sizeof(sa));
	listen(s, 100);

	SOCKET client_soc;
	SOCKADDR_IN client_addr;
	int client_addr_size = sizeof(client_addr);


	while(1)
	{

		client_soc = accept(s, &client_addr, &client_addr_size);

		

		Client* tmp = (Client*)malloc(sizeof(Client));
		if (!tmp)exit(-1);

		recv(client_soc, tmp->pname, sizeof(tmp->pname), 0);
	


		tmp->socket = client_soc;
		tmp->addres = client_addr;
		
		tmp->player = (Player*)malloc(sizeof(Player));
		if (!tmp->player)exit(-1);


		tmp->player->x = 0;
		tmp->player->y = 0;
		tmp->player->lookDir = 0;
		tmp->player->state = 0;


		

		printf("%s connected! #%d   id:%d\n", tmp->pname, CountOfItems, ListAddItem(tmp, &ClientsList)->id);
		

	}
}



void LanUpdateBots()
{
		byte buff[256];
		
	while (1) {
		
	
		
		printf(" \r");

			Node* tmpNode = ClientsList;
			if(CountOfItems!=0)
			for (int i = 0; i < CountOfItems; i++)
			{
				
				buff[0] = CountOfItems-1;
				//printf("%d\n", CountOfItems);
				send(((Client*)tmpNode->data)->socket, buff, 1, 0);
				
				Node* tmpNode2 = ClientsList;
				for (int j = 0; j < CountOfItems; j++)
				{
					if(tmpNode->id!=tmpNode2->id)
						send(((Client*)tmpNode->data)->socket, ((Client*)tmpNode2->data)->player, sizeof(Player), 0);
						tmpNode2 = tmpNode2->next;
				}

			

				//printf("%d\n", CountOfItems);
				
				if (SOCKET_ERROR == recv(((Client*)tmpNode->data)->socket, ((Client*)tmpNode->data)->player, sizeof(Player), 0))
				{
					Node*t= tmpNode->next;
					LanDisconnectBots(tmpNode);
					tmpNode = t;
				}else
				tmpNode = tmpNode->next;

				//printf("%d\n", CountOfItems);

			}

	}
}

void LanDisconnectBots(Node * client)
{
	printf("%s discconected( #%d  id:%d\n",((Client*)client->data)->pname,CountOfItems-1, (Client*)client->id);
	ListDeleteItem(client->id, &ClientsList);
}