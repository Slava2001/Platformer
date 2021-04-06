#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#pragma comment( lib, "glew32.lib" )
#pragma comment (lib, "OpenGL32.lib")
#include "TextureInit.h"
#include "Player.h"
#include "map.h"
#include "Lan.h"
#include <time.h>
#include "menu.h"


const int width = 800;
const int height = 600;


float zoom = 0.1;

char gamemenustate = 0;//0-MainMenu 1-game 2-subMenu

GLFWwindow* window;
int main(int argc, char* argv[])
{


	
	#pragma omp parallel sections num_threads(2)
	{
		#pragma omp section
		{
			while(!connected)
			LanUpdateBots();
		}
		#pragma omp section
		{
			//printf("Game Started!\n");
		
			glfwInit();
			window = glfwCreateWindow(width, height, "Platformer", NULL, NULL);
			glfwMakeContextCurrent(window);
			glewInit();
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glEnable(GL_ALPHA_TEST);
			glAlphaFunc(GL_GREATER, 0.3);


			MenuInit();
			TextureInit();
			MapInit();


			float tps =0;
			int counter = 0;
			static clock_t start = 0, end;
			
			while (!glfwWindowShouldClose(window))
			{
				end = clock(NULL);
				tps += difftime(end, start)/CLOCKS_PER_SEC;
				counter++;
				if (counter > 9)
				{
					printf("\rFPS:%d     ", (int)(10/tps));
					counter = 0;
					tps = 0;
				}start = end;




				glClearColor(117 / 255., 193 / 255., 1, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


				if (gamemenustate == 0)
				{
					MenuUpdate();
					MenuDraw();
				}
				else
				{
					PlayerUpdate();

					PlayerDraw();
					MapDraw();
					LanDrawBots();
				}

				glfwSwapBuffers(window);
				glfwPollEvents();

			}
			glfwTerminate();
			LanDisconnect();
		}
	}



	return 0;
}

