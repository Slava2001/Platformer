#define _CRT_SECURE_NO_WARNINGS 1
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <time.h>
#include "Lan.h"
#include <math.h>
#include "Player.h"

extern float zoom;

#define maxp 10



Player MePlayer;


char flag=1;
char connected = 0;

Player **Playersmass = NULL;

int PlayerCount = 0;

WSADATA ws;

SOCKET s;

SOCKADDR_IN sa;

byte pname[64];
byte ip_str[17] = { 0 };

void LanPlayerAcceptor();

void LanInit()
{
	
	Playersmass = (Player**)malloc(sizeof(Player) * maxp);
	if (!Playersmass)exit(-1);

	WSAStartup(MAKEWORD(2, 2), &ws);

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (!s) { printf("create socket err!"); getchar(); return -1; }

	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(9595);


		
	//	printf("Enter IP: ");
		/*if (scanf("%s", ip_str)==1)
			memcpy(ip_str, "127.0.0.1", 10);
			*/
		//scanf("%s", ip_str);

		sa.sin_addr.S_un.S_addr = inet_addr(ip_str);
		connect(s, &sa, sizeof(sa));

	//	printf("Enter Name :");
		//if(!scanf("%s", pname))exit(-1);
		//srand(clock(NULL));
		/*pname[0] = 'p';
		pname[1] = 'l';
		for(int i=2;i<10;i++)
		pname[i] = rand()%('Z'-'A')+'A';
		pname[10] = 0;*/
		if (send(s, pname, sizeof(pname), 0) == SOCKET_ERROR)
		{
			printf("SocketErr!!!\n");
		}
		else
		{
			connected = 1;
		}
}



void LanDrawBots()
{


	for (int i = 0; i < PlayerCount; i++) 
	{
		static GLuint cubeind[] = { 0,1,2,2,3,0 };

		static int cubeindcnt = sizeof(cubeind) / sizeof(GLuint);


		static float player_frame_right[] = { 0, 0, PlayerSizeX, 0, PlayerSizeX, -PlayerSizeY, 0, -PlayerSizeY };
		static float player_frame_left[] = { PlayerSizeX, 0, 0, 0, 0, -PlayerSizeY, PlayerSizeX, -PlayerSizeY };

		static float player_idl[] = { 0 * 0.25 ,0 * 0.5, 1 * 0.25,0 * 0.5, 1 * 0.25,1 * 0.5, 0 * 0.25 ,1 * 0.5 };
		static float player_atack[] = { 1 * 0.25 ,0 * 0.5, 2 * 0.25,0 * 0.5, 2 * 0.25,1 * 0.5, 1 * 0.25 ,1 * 0.5 };
		static float player_jmp[] = { 2 * 0.25 ,0 * 0.5, 3 * 0.25,0 * 0.5, 3 * 0.25,1 * 0.5, 2 * 0.25 ,1 * 0.5 };

		static float player_walk1[] = { 0 * 0.25 ,1 * 0.5, 1 * 0.25,1 * 0.5, 1 * 0.25,2 * 0.5, 0 * 0.25 ,2 * 0.5 };
		static float player_walk2[] = { 1 * 0.25 ,1 * 0.5, 2 * 0.25,1 * 0.5, 2 * 0.25,2 * 0.5, 1 * 0.25 ,2 * 0.5 };
		static float player_walk3[] = { 2 * 0.25 ,1 * 0.5, 3 * 0.25,1 * 0.5, 3 * 0.25,2 * 0.5, 2 * 0.25 ,2 * 0.5 };
		static float player_walk4[] = { 3 * 0.25 ,1 * 0.5, 4 * 0.25,1 * 0.5, 4 * 0.25,2 * 0.5, 3 * 0.25 ,2 * 0.5 };


		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, playertextureId);
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glPushMatrix();


		glTranslatef(-1, +1, 0);

		glScaled(zoom, zoom, zoom);



		glTranslatef(Playersmass[i]->x,  -Playersmass[i]->y, 0);

		/*plpoz[i] += (4 * time)*((plpoz[i] - Playersmass[i]->x) / abs(plpoz[i] - Playersmass[i]->x));
		plpoz[i+1] += (4 * time)*((plpoz[i+1] - Playersmass[i+1]->x) / abs(plpoz[i+1] - Playersmass[i+1]->x));


		glTranslatef(plpoz[i], -plpoz[i+1], 0);*/

		 

		Playersmass[i]->lookDir ? glVertexPointer(2, GL_FLOAT, 0, player_frame_right) :
			glVertexPointer(2, GL_FLOAT, 0, player_frame_left);




		glColor3f(1, 1, 1);


		switch (Playersmass[i]->state)
		{
		case 0:
			glTexCoordPointer(2, GL_FLOAT, 0, player_idl);
			break;
		case 1:
			glTexCoordPointer(2, GL_FLOAT, 0, player_atack);
			break;
		case 2:
			glTexCoordPointer(2, GL_FLOAT, 0, player_jmp);
			break;
		case 3:
			glTexCoordPointer(2, GL_FLOAT, 0, player_walk1);
			break;
		case 4:
			glTexCoordPointer(2, GL_FLOAT, 0, player_walk2);
			break;
		case 5:
			glTexCoordPointer(2, GL_FLOAT, 0, player_walk3);
			break;
		case 6:
			glTexCoordPointer(2, GL_FLOAT, 0, player_walk4);
			break;
		default:
			break;
		}

		glDrawElements(GL_TRIANGLES, cubeindcnt, GL_UNSIGNED_INT, cubeind);

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisable(GL_TEXTURE_2D);

		glPopMatrix();

	}
}


void LanUpdateBots()
{
		byte buff[256];
		int tmp;
		while (SOCKET_ERROR != recv(s, buff, 1, 0))
		{



			tmp = buff[0];

			
			if (tmp != PlayerCount)
			{
				if (tmp < PlayerCount)
					for (int i = tmp; i < PlayerCount; i++)
						free(Playersmass[i]);

				Player** tmppl = (Player**)realloc(Playersmass, sizeof(Player) * tmp);
				
				if(tmp>PlayerCount)
				for (int i = PlayerCount; i < tmp; i++)
					tmppl[i] = (Player*)malloc(sizeof(Player));



					PlayerCount = tmp;
					Playersmass = tmppl;
			//plpoz = (float*)realloc(plpoz, sizeof(float) * 2 * PlayerCount);
			}


			if(PlayerCount!=0)
			for (int i = 0; i < PlayerCount; i++)
			{
				//printf("%d\n", PlayerCount);
				recv(s, Playersmass[i], sizeof(Player), 0);
			}



			send(s, &MePlayer, sizeof(Player), 0);
			
		}
}

void LanDisconnect()
{
	byte buf[256];

	shutdown(s, SD_BOTH);
	while (recv(s, buf, sizeof(buf), 0) != -1);
	closesocket(s);
}