#include "menu.h"
#include "textOut.h"
#include "inputer.h"
#include "sound.h"
#include "Player.h"

GLFWwindow* window;



char Menustate = 0; //0-main, 1-connect, 2-settings, 3-ingamemenu
char prevstate = 0;
InputerList** Menu;

/******ButtonFunctions******/
void Connecting();
void Disconnecting();
void exitbtn();
void SingleGame();
void MenuStateSettings();
void MenuStateMain();
void MenuStateConnect();
void MenuStateNull();
void MenuBack();
void MainSoundVoluem(float vl);
void SFXSoundVolue(float vl);
/***************************/
extern inputer ipt;

void MenuInit()
{
	//soundPlay(MainSound);

	char* text[] = { "подключится","выход","музыка","" };
//	mainMenuList = ButtonCreateButtonList(4, 1/zoom-2.5, 5, 5, 1, 0.2,&text, Connecting, exitbtn, Playsound, NULL);

	SoundSetVolume(SN_MAIN_SOUND, 0.2f);
	SoundPlay(SN_MAIN_SOUND);



	inputerInit();

	Menu = (InputerList**)malloc(sizeof(InputerList*) * 4);
	Menu[0] = inputerCreateList(3);
	inputerAddButton(Menu[0], 1 / zoom - 2.5, 5, 5, 1, "Одиночная игра", SingleGame);
	inputerAddButton(Menu[0], 1 / zoom - 2.5, 6.25, 5, 1, "Подключится", MenuStateConnect);// MenuStateConnect);
	inputerAddButton(Menu[0], 1 / zoom - 2.5, 7.5, 5, 1, "Настройки", MenuStateSettings);
	inputerAddButton(Menu[0], 1 / zoom - 2.5, 8.75, 5, 1, "Выход", exitbtn);

	Menu[1] = inputerCreateList(4);
	inputerAddTextBox(Menu[1], 1 / zoom - 2.5, 5, 5, 1);
		memcpy(Menu[1]->ipr[0].text, "SlaVik", 7);
	inputerAddTextBox(Menu[1], 1 / zoom - 2.5, 6.25, 5, 1);
		memcpy(Menu[1]->ipr[1].text, "127.0.0.1", 10);
	inputerAddButton(Menu[1], 1 / zoom - 2.5, 7.5, 5, 1, "Подключится", Connecting);
	inputerAddButton(Menu[1], 1 / zoom - 2.5, 8.75, 5, 1, "Назад", MenuBack);

	Menu[2] = inputerCreateList(3);
	inputerAddSlider(Menu[2], 1 / zoom - 2.5, 5, 5, 1, 0.2, MainSoundVoluem);
	inputerAddSlider(Menu[2], 1 / zoom - 2.5, 6.25, 5, 1, 0.2, SFXSoundVolue);
	inputerAddButton(Menu[2], 1 / zoom - 2.5, 7.5, 5, 1, "Назад", MenuBack);

	Menu[3] = inputerCreateList(3);
	inputerAddButton(Menu[3], 1 / zoom - 2.5, 5, 5, 1, "Продолжить", MenuStateNull);// MenuStateConnect);
	inputerAddButton(Menu[3], 1 / zoom - 2.5, 6.25, 5, 1, "Настройки", MenuStateSettings);
	inputerAddButton(Menu[3], 1 / zoom - 2.5, 7.5, 5, 1, "Отключится", Disconnecting);
}

char EscCheckPress = 0;

void MenuUpdate()
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE))
	{
		if (!EscCheckPress)
		{
			EscCheckPress = 1;
			if(Menustate == -1 || Menustate == 3)
			Menustate = Menustate == -1 ? 3 : -1;
			//printf("Menu state:%d\n", Menustate);
		}
	}
	else EscCheckPress = 0;

	if(Menustate!=-1)
	inputerUpdate(Menu[Menustate]);
}

void MenuDraw()
{
	if (Menustate != -1)
	inputerDraw(Menu[Menustate]);
}
void Disconnecting()
{
	prevstate = Menustate = 0;
	LanDisconnect();
	gamemenustate = 0;
}
void MenuStateNull()
{
	prevstate = Menustate;
	Menustate = -1;
}
void Connecting()							
{
	printf("Game Started!\n");

	
	memcpy(pname, Menu[1]->ipr[0].text, strlen(Menu[1]->ipr[0].text));
	memcpy(ip_str, Menu[1]->ipr[1].text, strlen(Menu[1]->ipr[1].text));

	LanInit();
	if(connected)
	gamemenustate = 1;
	Menustate = -1;

	PlayerReSpawn();

}
void exitbtn()									
{
	exit(0);
}
void MenuStateSettings()			
{
	prevstate = Menustate;
	Menustate = 2;
}
void MenuStateMain()					
{
	prevstate = Menustate;
	Menustate = 0;
}
void MenuStateConnect()				
{
	prevstate = Menustate;
	Menustate = 1;
}
void MenuBack()
{
	Menustate=prevstate;
}
void SingleGame()
{
	gamemenustate = 1;
	Menustate = -1;

	PlayerReSpawn();
}
void MainSoundVoluem(float vl)	
{
	SoundSetVolume(SN_MAIN_SOUND, vl*vl);
}
void SFXSoundVolue(float vl)	
{
	SoundSetVolume(SN_BUTTON_CLICK_SOUND, vl * vl);
}

