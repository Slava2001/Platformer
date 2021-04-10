#include "textOut.h"
#define charSize 0.0625




void Textout(char* Text, float pozX, float pozY, float size)
{
	GLfloat rectCoord[] = {0,0,1,0,1,-1,0,-1};
	GLfloat rectTex[] = {0,0,1,0,1,1,0,1};
	struct {float l, r, t, b;} rct;
	float w;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, FontTextureId);
	glPushMatrix();
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);


		glVertexPointer(2, GL_FLOAT, 0, rectCoord);
		glTexCoordPointer(2, GL_FLOAT, 0, rectTex);

		glTranslatef(-1, +1, 0);
	
		glScaled(zoom, zoom, zoom);
		glTranslatef(pozX,  - pozY, 0);
		glScaled(size, size, 0);

		while (*Text) 
		{
			w =  charwidth[(unsigned char)Text];
			int x = *Text & 15, y = *Text >> 4;
			rct.l = x * charSize;
			rct.r = rct.l + w* charSize;
			rct.t = (y + 1) * charSize;
			rct.b = rct.t - charSize;
			rectTex[0] = rectTex[6] = rct.l;
			rectTex[2] = rectTex[4] = rct.r;
			rectTex[1] = rectTex[3] = rct.b;
			rectTex[5] = rectTex[7] = rct.t;
			rectCoord[2] = rectCoord[4] = w;
		//	glColor3f(0, 0, 0);
			glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
			glTranslatef(w, 0, 0);
			Text++;
		}


		

		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);



}