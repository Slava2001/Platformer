#include <stdlib.h>
#include "button.h"
#include "debug.h"

ButtonList ButtonCreateButtonList(int size, float x, float y, float w, float h, float margin, char** text, void (*btnprc)(), ...)
{
	ButtonList* tmp = (ButtonList*)malloc(sizeof(ButtonList));

	tmp->size = size;
	tmp->button = (Button*)malloc(sizeof(Button) * size);

	void (**funk)(void) = &btnprc;

	for (int i = 0; i < size;i++)
	{
		tmp->button->text = text[i];
		tmp->button[i].pozX = x;
		tmp->button[i].pozY = y;
		tmp->button[i].sizX = w;
		tmp->button[i].sizY = h;
		tmp->button[i].buttonproc= funk[i];
		tmp->button[i].state = 0;
		y += h + margin;

	}
	return *tmp;
}
void ButtonUbdate(ButtonList* list)
{

	double CursorX = 0;
	double CursorY = 0;
	glfwGetCursorPos(window,&CursorX, &CursorY);


	CursorX = (CursorX / width)/zoom*2;
	CursorY = (CursorY / height)/zoom*2;

	DebugDraw(CursorX-0.1, CursorY - 0.1, 0.2, 0.2, 0, 0, 1);

	for (int x = 0; x < list->size; x++)
	{
		if (CursorX > list->button[x].pozX && CursorY > list->button[x].pozY
			&& CursorX < list->button[x].pozX + list->button[x].sizX
			&& CursorY < list->button[x].pozY + list->button[x].sizY)
		{
			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
			{
				if (list->button[x].state == 1)
				{
					list->button[x].state = 2;
					list->button[x].buttonproc();
				}
			}
			else
				list->button[x].state = 1;
		}
		else
			list->button[x].state = 0;
	}
}
void ButtonDraw(ButtonList* list)
{

	static GLuint cubeind[] = { 0,1,2,2,3,0 };
	static int cubeindcnt = sizeof(cubeind) / sizeof(GLuint);

	

	float cube[] = { 0, 0, list->button[0].sizX, 0, list->button[0].sizX, -list->button[0].sizY, 0, -list->button[0].sizY };

	static float Button1[] = { 0,0,1,0,1,0.25,0,0.25 };
	static float Button2[] = { 0,0.25,1,0.25,1,0.5,0,0.5 };
	

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, menuTextureId);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glPushMatrix();
	glTranslatef(-1, +1, 0);


	glScaled(zoom, zoom, zoom);

	glVertexPointer(2, GL_FLOAT, 0, cube);
	glColor3f(1, 1, 1);


	for (int x = 0; x < list->size; x++)
	{
		glPushMatrix();

		glTranslatef(list->button[x].pozX, -list->button[x].pozY, 0);

		if(!list->button[x].state)
			glTexCoordPointer(2, GL_FLOAT, 0, Button1);
		else
			glTexCoordPointer(2, GL_FLOAT, 0, Button2);

		glDrawElements(GL_TRIANGLES, cubeindcnt, GL_UNSIGNED_INT, cubeind);

		glPopMatrix();

	}
	

	
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();


}