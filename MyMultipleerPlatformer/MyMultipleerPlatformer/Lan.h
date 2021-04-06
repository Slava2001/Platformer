#include <stdio.h> 
#include <stdlib.h> 
#include <WinSock2.h>
#pragma comment(lib, "WS2_32.lib")
#include "TextureInit.h"


#ifndef strct
#define strct

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

#endif // !strct



extern Player MePlayer;
extern char flag;
extern byte pname[64];
extern byte ip_str[17];
extern char connected;

void LanInit();
void LanDrawBots();
void LanDisconnect();