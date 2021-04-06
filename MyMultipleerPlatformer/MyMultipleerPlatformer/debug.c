#include "debug.h"

void DebugDraw(float x, float y, float w, float h, float r, float g, float b)
{

	glPushMatrix();

	glTranslatef(-1, +1, 0);
	glScaled(zoom, zoom, zoom);

	glBegin(GL_LINE_LOOP);
	glColor3f(r, g, b);
	glVertex2d(x, -y);
	glVertex2d(x + w, -y);
	glVertex2d(x + w, -y - h);
	glVertex2d(x, -y - h);
	glVertex2d(x + w, -y);
	glVertex2d(x + w, -y - h);
	glVertex2d(x, -y);
	glVertex2d(x, -y - h);
	glEnd();

	glPopMatrix();
}