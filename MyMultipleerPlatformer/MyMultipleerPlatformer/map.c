
#include "map.h"
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "TextureInit.h"
#pragma comment (lib, "glew32.lib" )
#pragma comment (lib, "OpenGL32.lib")

int MAP_X=20;
int MAP_Y=20;

int textureId;
extern float zoom;

char *map={		
				"gggggggggggggggggggg"
				"g.......gg........gg"
				"g..................g"
				"g..gg........gg....g"
				"g....g.........g...g"
				"g..............gg..g"
				"g..................g"
				"g.................gg"
				"g..........5....gggg"
				"ggggggg..ggggggggggg"
				"g.43......g........g"
				"g..........g.......g"
				"g.......gg..g.....gg"
				"g..gg........gg....g"
				"g..............g...g"
				"g....gg..g.....  ..g"
				"g..................g"
				"g......5..........gg"
				"g.....gggg.....5gggg"
				"gggggggggggggggggggg"
};

void MapInit()
{
	

}


char MapGetTile(int x, int y)
{
	if (x < 0 || y<0 || x>MAP_X - 1 || y>MAP_Y - 1)
		return '.';
	return map[y * MAP_X + x];
}


void MapDraw()
{
	
	
	
	
	static GLuint cubeind[] = { 0,1,2,2,3,0};

	static int cubeindcnt = sizeof(cubeind) / sizeof(GLuint);

	static float cube[] = { 0,0, 1,0, 1,-1, 0,-1};


	
	static float grasAngle[] = { 0 * 0.25 ,0 * 0.25, 1 * 0.25,0 * 0.25, 1 * 0.25,1 * 0.25, 0 * 0.25 ,1 * 0.25 };
	static float gras[]		 = { 1 * 0.25 ,0 * 0.25, 2 * 0.25,0 * 0.25, 2 * 0.25,1 * 0.25, 1 * 0.25 ,1 * 0.25 };
	static float snowAngle[] = { 2 * 0.25 ,0 * 0.25, 3 * 0.25,0 * 0.25, 3 * 0.25,1 * 0.25, 2 * 0.25 ,1 * 0.25 };

	static float grasAngler[] = { 1 * 0.25,0 * 0.25, 0 * 0.25 ,0 * 0.25,  0 * 0.25 ,1 * 0.25, 1 * 0.25,1 * 0.25 };
	static float snowAngler[] = { 3 * 0.25,0 * 0.25, 2 * 0.25 ,0 * 0.25,  2 * 0.25 ,1 * 0.25, 3 * 0.25,1 * 0.25 };
	
	static float snow[]		 = { 3 * 0.25 ,0 * 0.25, 4 * 0.25,0 * 0.25, 4 * 0.25,1 * 0.25, 3 * 0.25 ,1 * 0.25 };
	
	static float grasMiddel[] = { 0 * 0.25 ,1 * 0.25, 1 * 0.25,1 * 0.25, 1 * 0.25,2 * 0.25, 0 * 0.25 ,2 * 0.25 };
	static float snowMiddel[] = { 1 * 0.25 ,1 * 0.25, 2 * 0.25,1 * 0.25, 2 * 0.25,2 * 0.25, 1 * 0.25 ,2 * 0.25 };
	static float picesaw1[] = { 2 * 0.25, 1 * 0.25, 3 * 0.25, 1 * 0.25, 3 * 0.25, 2 * 0.25, 2 * 0.25, 2 * 0.25 };
	static float picesaw2[] = { 2 * 0.25, 2 * 0.25, 2 * 0.25, 1 * 0.25, 3 * 0.25, 1 * 0.25, 3 * 0.25, 2 * 0.25 };
	static float picesaw3[] = { 3 * 0.25, 2 * 0.25, 2 * 0.25, 2 * 0.25, 2 * 0.25, 1 * 0.25, 3 * 0.25, 1 * 0.25 };
	static float picesaw4[] = { 3 * 0.25, 1 * 0.25, 3 * 0.25, 2 * 0.25, 2 * 0.25, 2 * 0.25, 2 * 0.25, 1 * 0.25 };
	static float shipi[] = { 3 * 0.25 ,1 * 0.25, 4 * 0.25,1 * 0.25, 4 * 0.25,2 * 0.25, 3 * 0.25 ,2 * 0.25 };

	static float buttun[] = { 0 * 0.25 ,2 * 0.25, 1 * 0.25,2 * 0.25, 1 * 0.25,3 * 0.25, 0 * 0.25 ,3 * 0.25 };
	static float richag[] = { 1 * 0.25 ,2 * 0.25, 2 * 0.25,2 * 0.25, 2 * 0.25,3 * 0.25, 1 * 0.25 ,3 * 0.25 };
	static float box[] =    { 2 * 0.25 ,2 * 0.25, 3 * 0.25,2 * 0.25, 3 * 0.25,3 * 0.25, 2 * 0.25 ,3 * 0.25 };
	static float saw[] =	{ 3 * 0.25 ,2 * 0.25, 4 * 0.25,2 * 0.25, 4 * 0.25,3 * 0.25, 3 * 0.25 ,3 * 0.25 };

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glPushMatrix();
	glTranslatef(-1, +1,0);


	glScaled(zoom, zoom, zoom);

	glVertexPointer(2, GL_FLOAT, 0, cube);
	glColor3f(1, 1, 1);
	

	for (int y = 0; y < MAP_Y; y++)
	{
		glPushMatrix();
		for (int x = 0; x < MAP_X; x++)
		{
			glPushMatrix();


				switch (map[y * MAP_X + x])
				{
				case 'g':
					glTexCoordPointer(2, GL_FLOAT, 0, gras);
					break;
				case 'a':
					glTexCoordPointer(2, GL_FLOAT, 0, grasAngle);
					break;
				case 'S':
					glTexCoordPointer(2, GL_FLOAT, 0, snowAngle);
					break;
				case 'A':
					glTexCoordPointer(2, GL_FLOAT, 0, snow);
					break;
				case 'M':
					glTexCoordPointer(2, GL_FLOAT, 0, snowMiddel);
					break;
				case 'm':
					glTexCoordPointer(2, GL_FLOAT, 0, grasMiddel);
					break;
				case '2':
					glTexCoordPointer(2, GL_FLOAT, 0, picesaw1);
					break;
				case '1':
					glTexCoordPointer(2, GL_FLOAT, 0, picesaw4);
					break;
				case '4':
					glTexCoordPointer(2, GL_FLOAT, 0, picesaw3);
					break;
				case '3':
					glTexCoordPointer(2, GL_FLOAT, 0, picesaw2);
					break;
				case '5':
					glTexCoordPointer(2, GL_FLOAT, 0, shipi);
					break;
				case '6':
					glTexCoordPointer(2, GL_FLOAT, 0, buttun);
					break;
				case '7':
					glTexCoordPointer(2, GL_FLOAT, 0, richag);
					break;
				case 'b':
					glTexCoordPointer(2, GL_FLOAT, 0, box);
					break;
				case '8':
					glTexCoordPointer(2, GL_FLOAT, 0, saw);
					break;
				case 'q':
					glTexCoordPointer(2, GL_FLOAT, 0, grasAngler);
					break;
				case 'w':
					glTexCoordPointer(2, GL_FLOAT, 0, snowAngler);
					break;
				default:
					goto skip;
				}
				glDrawElements(GL_TRIANGLES, cubeindcnt, GL_UNSIGNED_INT, cubeind);
			skip:

		

			glPopMatrix();

			 glTranslatef(1, 0, 0);
		}
		glPopMatrix();
	glTranslatef(0, -1, 0);
	}
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}
