#include "map.h"
#include "TextureInit.h"
#include "Player.h"
#include <time.h>
#include <math.h>
#include "Lan.h"
#include "debug.h"
#include "sound.h"



extern float zoom;

float animationSpeed = 0.1;
int state = 3; //0-idl 1-atk 2-jmp 3-walk
int lookDir = 0;//0-left 1-right
char w_isprsd;
char isSit = 0;
//PhysiñVars
/////////////////////////////////
double playerX = 1, playerY = 1;
const float frictionForce = 20, maxAcsel = 20, maxSpeedX = 4, jmpFors = 5, gravity = 10;
float speedX, speedY, acsel;
int PlayerOnGroung = 1;
/////////////////////////////////



extern GLFWwindow* window;

void PlayerUpdate()
{



	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		if (isSit == 0)
		{
			isSit = 1;
			playerY += PlayerSizeY / 2;
		}
	}
	else
	{
		if (isSit == 1)
		{
			isSit = 0;
			playerY -= PlayerSizeY / 2;
		}
	}




	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		if (state<3 || lookDir!=0)
		{
			acsel = -maxAcsel;
			lookDir = 0;
			state = 3;
		}
		
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		if (state < 3 || lookDir != 1)
		{
			acsel = maxAcsel;
			lookDir = 1;
			state = 3;
		}
		
	}
	else
	{
		acsel = 0;
		if(state!=2)
		state = 0;
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{

		if (state != 1)
		{
			state = 1;
		}

	}

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		if (state!=2 && PlayerOnGroung)
		{
			speedY = -jmpFors;
			state = 2;
			PlayerOnGroung =0;
			SoundPlay(SN_JUMP_SOUND);
		}

	}

	

	PlayerPhysiñUpdate();

	MePlayer.x = playerX;
	MePlayer.y = playerY;
	MePlayer.isSit = isSit;
	MePlayer.lookDir = lookDir;
	MePlayer.state = state;

}

void PlayerPhysiñUpdate()
{
	float time;
	static clock_t start = 0, end;
	end = clock(NULL);
	time = difftime(end, start) / CLOCKS_PER_SEC;
	if (time > 0.1)time = 0.1;
	start = end;
	
	if(((speedX < maxSpeedX) && (lookDir==1))||((speedX>-maxSpeedX)&&(lookDir==0)))
	speedX += acsel * time;

	if (!acsel)
	 speedX = abs(speedX)> 0.01? speedX - (speedX / abs(speedX)) * frictionForce * time : 0;

	
	speedY += gravity*time;
	if (speedY > 5)speedY = 5;

	playerX += speedX * time;
	Collision(1);

	playerY += speedY * time;
	Collision(0);



	DebugDraw(playerX, playerY, PlayerSizeX, isSit ? PlayerSizeY / 2 : PlayerSizeY,0,0,1);
}



void Collision(int collisDir)// 1-test by x 0- test by y
{
	for (int ix = playerX; ix < (playerX + PlayerSizeX); ix++)
	{
		for (int iy = playerY; iy < (playerY + (isSit ? PlayerSizeY / 2 : PlayerSizeY)); iy++)
		{
			char tile = MapGetTile(ix, iy);
			if (tile > 58)
			{
				if (collisDir)
				{
					if (speedX > 0)
					{
						playerX = ix-PlayerSizeX;
					}
					else if (speedX < 0)
					{
						playerX = ix+1;
					}
					speedX = 0;
				}
				else
				{
					if (speedY < 0)
					{
						playerY = iy+1;
					}
					else if (speedY > 0)
					{
						playerY = iy- (isSit ? PlayerSizeY / 2 : PlayerSizeY);
					//	if(PlayerOnGroung==0)
						//	SoundPlay(SN_LANDED_SOUND);
						PlayerOnGroung = 1;
					}
					speedY = 0;
					
				}


				//DebugDraw(ix, iy, 1, 1, 1, 0, 0);
			}
			
		}
	}
	
	for (int ix = playerX; ix < (playerX + PlayerSizeX); ix++)
	{
		for (int iy = playerY+0.5; iy < (int)(playerY + 0.5 + (isSit ? PlayerSizeY / 2 : PlayerSizeY)); iy++)
		{
			char tile = MapGetTile(ix, iy);

			if (tile > '0' && tile < '9')
				PlayerReSpawn();

			DebugDraw(ix, iy, 1, 1, 0, 1, 0);
		}
	}
}
void PlayerReSpawn()
{
	playerX = 1;
	playerY = 1;
	state = 0; //0-idl 1-atk 2-jmp 3-walk
	lookDir = 0;//0-left 1-right
	speedX = 0;
	speedY = 0;
	acsel = 0;
	PlayerOnGroung = 1;
	/////////////////////////////////

}




void PlayerDraw()
{
	static GLuint cubeind[] = { 0,1,2,2,3,0 };

	static int cubeindcnt = sizeof(cubeind) / sizeof(GLuint);

	static float player_frame_right[] = { 0, 0, PlayerSizeX, 0, PlayerSizeX, -PlayerSizeY, 0, -PlayerSizeY };
	static float player_frame_left[] =  { PlayerSizeX, 0, 0, 0, 0, -PlayerSizeY, PlayerSizeX, -PlayerSizeY };

	static float player_sit_frame_right[] = { 0, 0, PlayerSizeX, 0, PlayerSizeX, -PlayerSizeY/2, 0, -PlayerSizeY/2 };
	static float player_sit_frame_left[] = { PlayerSizeX, 0, 0, 0, 0, -PlayerSizeY/2, PlayerSizeX, -PlayerSizeY/2 };

	static float player_idl[] =   { 0 * 0.25 ,0 * 0.5, 1 * 0.25,0 * 0.5, 1 * 0.25,1 * 0.5, 0 * 0.25 ,1 * 0.5 };
	static float player_atack[] = { 1 * 0.25 ,0 * 0.5, 2 * 0.25,0 * 0.5, 2 * 0.25,1 * 0.5, 1 * 0.25 ,1 * 0.5 };
	static float player_jmp[] =	  { 2 * 0.25 ,0 * 0.5, 3 * 0.25,0 * 0.5, 3 * 0.25,1 * 0.5, 2 * 0.25 ,1 * 0.5 };

	static float player_walk1[] = { 0 * 0.25 ,1 * 0.5, 1 * 0.25,1 * 0.5, 1 * 0.25,2 * 0.5, 0 * 0.25 ,2 * 0.5 };
	static float player_walk2[] = { 1 * 0.25 ,1 * 0.5, 2 * 0.25,1 * 0.5, 2 * 0.25,2 * 0.5, 1 * 0.25 ,2 * 0.5 };
	static float player_walk3[] = { 2 * 0.25 ,1 * 0.5, 3 * 0.25,1 * 0.5, 3 * 0.25,2 * 0.5, 2 * 0.25 ,2 * 0.5 };
	static float player_walk4[] = { 3 * 0.25 ,1 * 0.5, 4 * 0.25,1 * 0.5, 4 * 0.25,2 * 0.5, 3 * 0.25 ,2 * 0.5 };


	static clock_t start=0, end;
	end = clock(NULL);
	if (difftime(end, start) > animationSpeed*CLOCKS_PER_SEC)
	{
		start = end;
		if (state == 2)
		{
			state = 0;
		}
		if (state == 1)
			state = 0;
		if (state > 2 && state < 7)
		{
			state++;
			if (state > 6)
				state = 3;
		}
	}




	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, playertextureId);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glPushMatrix();


	glTranslatef(-1, +1, 0);

	glScaled(zoom, zoom, zoom);

	glTranslatef(playerX, -playerY, 0);


	if(!isSit)
		lookDir?glVertexPointer(2, GL_FLOAT, 0, player_frame_right):
		glVertexPointer(2, GL_FLOAT, 0, player_frame_left);
	else
		lookDir ? glVertexPointer(2, GL_FLOAT, 0, player_sit_frame_right) :
		glVertexPointer(2, GL_FLOAT, 0, player_sit_frame_left);

	glColor3f(1, 1, 1);


	switch (state)
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

