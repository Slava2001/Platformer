#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "TextureInit.h"
#include "textOut.h"
#pragma comment (lib, "glew32.lib" )
#pragma comment (lib, "OpenGL32.lib")

extern float zoom;
extern GLFWwindow* window;
extern const int width;
extern const int height;

typedef struct
{
	float pozX;
	float pozY;
	float sizX;
	float sizY;
	char* text;
	char state;
	void (*buttonproc)();
}Button;

typedef struct
{
	int size;
	Button* button;
}ButtonList;

ButtonList ButtonCreateButtonList(int size, float x, float y, float w, float h, float margin, char** text, void (*btnprc)(), ...);
void ButtonUbdate(ButtonList* list);
void ButtonDraw(ButtonList* list);
