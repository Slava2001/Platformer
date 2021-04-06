#include <stdio.h> 
#include <stdlib.h> 
#include <WinSock2.h>
#pragma comment(lib, "WS2_32.lib")
#include "list.h"

typedef struct
{
	float x;
	float y;
	byte state;
	byte lookDir;
}Player;

typedef struct
{
	SOCKET socket;
	SOCKADDR_IN addres;
	int client_addr_size;
	Player* player;
	byte pname[64];
}Client;


extern Player MePlayer;
void LanInit();
void LanDisconnectBots(Node * client);
