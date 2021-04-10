#include "menu.h"
#include "textOut.h"

GLFWwindow* window;



ButtonList mainMenuList;

/******ButtonFunctions******/
void Connecting();
void exitbtn();
/***************************/


void MenuInit()
{
	char* text[] = { "подкл","выход" };

	mainMenuList = ButtonCreateButtonList(2, 0, 0, 3, 1, 0.3,&text, Connecting, exitbtn);
}
void MenuUpdate()
{
	ButtonUbdate(&mainMenuList);
}
void MenuDraw()
{
	ButtonDraw(&mainMenuList);
	
}

void Connecting()
{
	printf("Game Started!\n");

	
	memcpy(pname, "SlaVik2001", 11);
	memcpy(ip_str, "127.0.0.1", 10);

	LanInit();
	if(connect)
	gamemenustate = 1;
}

void exitbtn()
{
	exit(0);
}