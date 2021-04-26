#include "inputer.h"

#define MaxTextBoxLen 100

char** focusText;
int focusTextLen = 0;

void character_callback(GLFWwindow* window, unsigned int codepoint)
{
	if (!focusText)return;
	if (focusTextLen > MaxTextBoxLen-1)return;
	char cr;
	if (codepoint > 255)
		cr = codepoint - 1040 + 192;
	else
		cr = codepoint;


	(*focusText)[focusTextLen ] = cr;

	focusTextLen++;
	(*focusText)[focusTextLen] =0;
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (!focusText)return;
	if (focusTextLen < 1)return;
	if (action == GLFW_RELEASE)return;
	if (key == 259)
	{
		focusTextLen--;
		(*focusText)[focusTextLen] = 0;
	}
}
void inputerInit()
{
	glfwSetCharCallback(window, character_callback);
	glfwSetKeyCallback(window, key_callback);
}

void inputerAddTextBox(InputerList* ls,float x, float y, float w, float h)
{
	ls->ipr[ls->count].pozX = x;
	ls->ipr[ls->count].pozY = y;
	ls->ipr[ls->count].sizeX = w;
	ls->ipr[ls->count].sizeY = h;
	ls->ipr[ls->count].state = 0;
	ls->ipr[ls->count].type = IR_TEXTBOX;
	ls->ipr[ls->count].text = (char*)malloc(sizeof(char) * MaxTextBoxLen);
	ls->ipr[ls->count].text[0] = 0;
	ls->ipr[ls->count].text[1] = 0;
	ls->count++;
}
void inputerAddButton(InputerList* ls,float x, float y, float w, float h, char* text, void (*btnprc)())
{
	ls->ipr[ls->count].pozX = x;
	ls->ipr[ls->count].pozY = y;
	ls->ipr[ls->count].sizeX = w;
	ls->ipr[ls->count].sizeY = h;
	ls->ipr[ls->count].state = 0;
	ls->ipr[ls->count].type = IR_BUTTON;
	ls->ipr[ls->count].text = text;
	ls->ipr[ls->count].buttonproc = btnprc;
	ls->count++;
}
void inputerAddSlider(InputerList* ls,float x, float y, float w, float h,float vl,void(*sldprc)(float))
{
	ls->ipr[ls->count].pozX = x;
	ls->ipr[ls->count].pozY = y;
	ls->ipr[ls->count].sizeX = w;
	ls->ipr[ls->count].sizeY = h;
	ls->ipr[ls->count].state = 0;
	ls->ipr[ls->count].type = IR_SLIDER;
	ls->ipr[ls->count].text =NULL;
	ls->ipr[ls->count].value = vl;
	ls->ipr[ls->count].sliderproc = sldprc;
	ls->count++;
}

void inputerUpdate(InputerList* ls)
{
	double CursorX = 0;
	double CursorY = 0;
	glfwGetCursorPos(window, &CursorX, &CursorY);


	CursorX = (CursorX / width) / zoom * 2;
	CursorY = (CursorY / height) / zoom * 2;



	for (int i = 0; i < ls->count; i++)
	{
		if (CursorX >ls->ipr[i].pozX && CursorY > ls->ipr[i].pozY
			&& CursorX < ls->ipr[i].pozX + ls->ipr[i].sizeX
			&& CursorY < ls->ipr[i].pozY + ls->ipr[i].sizeY)
		{


			if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
			{
				if (ls->ipr[i].state == 1)
				{
					switch (ls->ipr[i].type)
					{
					case IR_BUTTON:
						ls->ipr[i].state = 2;
						SoundPlay(SN_BUTTON_CLICK_SOUND);
						if (ls->ipr[i].buttonproc)
							ls->ipr[i].buttonproc();
						break;
					case IR_SLIDER:
						ls->ipr[i].state = 1;
						ls->ipr[i].value = (CursorX - ls->ipr[i].pozX) / ls->ipr[i].sizeX;
						if (ls->ipr[i].sliderproc)
							ls->ipr[i].sliderproc(ls->ipr[i].value);
						break;
					case IR_TEXTBOX:
						focusText = &ls->ipr[i].text;
						focusTextLen = strlen(*focusText);
						ls->ipr[i].state = 3;
						break;
					}
				}
			}
			else
				if (ls->ipr[i].state != 3)
					ls->ipr[i].state = 1;

		}
		else
			if (ls->ipr[i].state != 3 || (ls->ipr[i].type == IR_SLIDER && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) != GLFW_PRESS))
				ls->ipr[i].state = 0;
			else if (ls->ipr[i].state == 3 && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
			{
				ls->ipr[i].state = 0;
				focusText = NULL;
			}
	}

}
void inputerDraw(InputerList* ls)
{
	glColor3f(0, 0, 0);
	
	for(int i=0;i<ls->count;i++)
	if(ls->ipr[i].text)
	Textout(ls->ipr[i].text, ls->ipr[i].pozX + 0.3, ls->ipr[i].pozY + ls->ipr[i].sizeY / 10, ls->ipr[i].sizeY / 1.25);

	glColor3f(1, 1, 1);


	static GLuint cubeind[] = { 0,1,2,2,3,0 };
	static int cubeindcnt = sizeof(cubeind) / sizeof(GLuint);

	static float Button1[] = { 0,0,1,0,1,0.25,0,0.25 };
	static float Button2[] = { 0,0.25,1,0.25,1,0.5,0,0.5 };
	static float Slider[]  = { 0,0.5,1,0.5,1,0.75,0,0.75 };
	static float SliderCursor[] = { 0,0.75,0.25,0.75,0.25,1,0,1 };





	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, menuTextureId);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glPushMatrix();
	glTranslatef(-1, +1, 0);


	glScaled(zoom, zoom, zoom);

	for (int i = 0; i < ls->count; i++)
	{

		float rect[] = { 0, 0, ls->ipr[i].sizeX , 0, ls->ipr[i].sizeX, -ls->ipr[i].sizeY, 0, -ls->ipr[i].sizeY };
		float currect[] = { 0, 0, ls->ipr[i].sizeY / 2 , 0, ls->ipr[i].sizeY / 2, -ls->ipr[i].sizeY, 0, -ls->ipr[i].sizeY };

		glVertexPointer(2, GL_FLOAT, 0, rect);
		glColor3f(1, 1, 1);

		//for (int x = 0; x < list->size; x++)
		//{
		glPushMatrix();

		glTranslatef(ls->ipr[i].pozX, -ls->ipr[i].pozY, 0);

		if (ls->ipr[i].type == IR_SLIDER)
		{
			glPushMatrix();
			glTranslatef(ls->ipr[i].value * ls->ipr[i].sizeX - ls->ipr[i].sizeY / 4, 0, 0);
			glVertexPointer(2, GL_FLOAT, 0, currect);
			glTexCoordPointer(2, GL_FLOAT, 0, SliderCursor);
			glDrawElements(GL_TRIANGLES, cubeindcnt, GL_UNSIGNED_INT, cubeind);
			glVertexPointer(2, GL_FLOAT, 0, rect);
			glPopMatrix();
		}



		if (ls->ipr[i].type == IR_SLIDER)
			glTexCoordPointer(2, GL_FLOAT, 0, Slider);
		else
			if (!ls->ipr[i].state)
				glTexCoordPointer(2, GL_FLOAT, 0, Button1);
			else
				glTexCoordPointer(2, GL_FLOAT, 0, Button2);



		glDrawElements(GL_TRIANGLES, cubeindcnt, GL_UNSIGNED_INT, cubeind);



		glPopMatrix();

		//}

	}

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();

}

InputerList* inputerCreateList(int listSize)
{
	InputerList* tmp = (InputerList*)malloc(sizeof(InputerList));
	if (!tmp)return NULL;

	tmp->count = 0;
	tmp->ipr = (inputer*)malloc(sizeof(inputer) * listSize);
	if (!tmp->ipr)
	{
		free(tmp);
		return NULL;
	}
	return tmp;
}