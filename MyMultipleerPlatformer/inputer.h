#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "TextureInit.h"
#include "textOut.h"
#pragma comment (lib, "glew32.lib" )
#pragma comment (lib, "OpenGL32.lib")
#include "sound.h"
#include <string.h>


#ifndef  inputerStruct
#define inputerStruct


typedef enum
{
	IR_BUTTON,
	IR_TEXTBOX,
	IR_SLIDER,

}inputerType;

typedef struct
{
	float pozX;
	float pozY;
	float sizeX;
	float sizeY;
	char state;
	char* text;
	inputerType type;
	union {
		void (*buttonproc)();
		void (*sliderproc)(float);
	};
	float value;
}inputer;

typedef struct
{
	inputer* ipr;
	int count;
}InputerList;


#endif //  inputerStruct


extern float zoom;
extern GLFWwindow* window;
extern int width;
extern int height;

InputerList* inputerCreateList(int listSize);
void inputerInit();
void inputerUpdate(InputerList * ls);
void inputerDraw(InputerList * ls);
void inputerAddButton(InputerList* ls,float x, float y, float w, float h, char* text, void (*btnprc)());
void inputerAddSlider(InputerList* ls,float x, float y, float w, float h, float vl, void(*sldprc)(float));
void inputerAddTextBox(InputerList* ls,float x, float y, float w, float h);