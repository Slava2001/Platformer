#include <Windows.h>
#include "sound.h"
#include <bass.h>



//
//OutputStreamPtr GetSoundByType(SoundType st)
//{
//	switch (st)
//	{
//	case SN_MAIN_SOUND:
//		return mainSound;
//		break;
//	case SN_BUTTON_CLICK_SOUND:
//		return BtnCLkSound;
//		break;
//	case SN_JUMP_SOUND:
//		return jumpSound;
//		break;
//	case SN_WALK_SOUND:
//		return walkSound;
//	case SN_LANDED_SOUND:
//		return walkSound;
//		break;
//	}
//	return mainSound;
//}


 
HSAMPLE mainSound;
HSAMPLE BtnCLkSound;
HSAMPLE jumpSound;
HSAMPLE walkSound;
HSAMPLE landSound;

HCHANNEL mainChannel;
HCHANNEL BtnCLkChannel;
HCHANNEL jumpChannel;
HCHANNEL walkChannel;
HCHANNEL landChannel;

HSAMPLE* GetSoundByType(SoundType st)
{
	switch (st)
	{
	case SN_MAIN_SOUND:
		return &mainSound;
		break;
	case SN_BUTTON_CLICK_SOUND:
		return &BtnCLkSound;
		break;
	case SN_JUMP_SOUND:
		return &jumpSound;
		break;
	case SN_WALK_SOUND:
		return &walkSound;
	case SN_LANDED_SOUND:
		return &landSound;
		break;
	}
	return &mainSound;
}
HCHANNEL* GetChanelByType(SoundType st)
{
	switch (st)
	{
	case SN_MAIN_SOUND:
		return &mainChannel;
		break;
	case SN_BUTTON_CLICK_SOUND:
		return &BtnCLkChannel;
		break;
	case SN_JUMP_SOUND:
		return &jumpChannel;
		break;
	case SN_WALK_SOUND:
		return &walkChannel;
	case SN_LANDED_SOUND:
		return &landChannel;
		break;
	}
	return &mainChannel;
}

void SoundInit()
{
    if(!BASS_Init(-1, 44100, 0, 0, NULL))
    {
        printf("BASS_ERROR!\h");
        getchar();
        return;
    }


	mainSound = BASS_SampleLoad(0, "sound/main.ogg", 0, 0, 1, BASS_SAMPLE_MONO | BASS_SAMPLE_LOOP);
	BtnCLkSound = BASS_SampleLoad(0, "sound/btnClk.wav", 0, 0, 1, BASS_SAMPLE_MONO);
	jumpSound = BASS_SampleLoad(0, "sound/jump.wav", 0, 0, 1, BASS_SAMPLE_MONO);
	walkSound = BASS_SampleLoad(0, "sound/btnClk.wav", 0, 0, 1, BASS_SAMPLE_MONO);
	landSound = BASS_SampleLoad(0, "sound/btnClk.wav", 0, 0, 1, BASS_SAMPLE_MONO);


}
void SoundDeInit()
{
    BASS_Free();
}

void SoundPlay(SoundType st)
{
    BASS_ChannelStop(*GetChanelByType(st),0);
	*GetChanelByType(st) = BASS_SampleGetChannel(*GetSoundByType(st), FALSE);
    BASS_ChannelPlay(*GetChanelByType(st), FALSE);
}
void SoundStop(SoundType st)
{
	
}
void SoundSetVolume(SoundType st, float volume)
{
	BASS_ChannelSetAttribute(*GetChanelByType(st), BASS_ATTRIB_VOL, volume);

	BASS_SAMPLE info;
	BASS_SampleGetInfo(*GetSoundByType(st), &info);
	info.volume = volume; 
	BASS_SampleSetInfo(*GetSoundByType(st), &info); 

}



//#include <Windows.h>
//#include <iostream>
//#include "audiere.h" 
//
//using namespace std;
//using namespace audiere;
//
//#ifndef SoundTypedef
//#define SoundTypedef
//typedef enum
//{
//	SN_MAIN_SOUND,
//	SN_BUTTON_CLICK_SOUND,
//	SN_JUMP_SOUND,
//	SN_WALK_SOUND,
//	SN_LANDED_SOUND
//}SoundType;
//#endif SoundTypedef
//
//
//AudioDevicePtr device;
//
//OutputStreamPtr mainSound;
//OutputStreamPtr BtnCLkSound;
//OutputStreamPtr jumpSound;
//OutputStreamPtr walkSound;
//OutputStreamPtr landSound;
//
//OutputStreamPtr GetSoundByType(SoundType st)
//{
//	switch (st)
//	{
//	case SN_MAIN_SOUND:
//		return mainSound;
//		break;
//	case SN_BUTTON_CLICK_SOUND:
//		return BtnCLkSound;
//		break;
//	case SN_JUMP_SOUND:
//		return jumpSound;
//		break;
//	case SN_WALK_SOUND:
//		return walkSound;
//	case SN_LANDED_SOUND:
//		return walkSound;
//		break;
//	}
//	return mainSound;
//}
//
//extern "C" void SoundInit()
//{
//	 device = OpenDevice();  
//	 mainSound = OpenSound(device, "sound/main.ogg", false);
//	 BtnCLkSound = OpenSound(device, "sound/btnClk.wav", false);
//	 jumpSound = OpenSound(device, "sound/jump.wav", false);
//	 walkSound = OpenSound(device, "sound/btnClick.ogg", false);
//	 landSound = OpenSound(device, "sound/btnClick.ogg", false);
//
//	 mainSound->setRepeat(true);
//}
//extern "C" void SoundPlay(SoundType st)
//{
//	if (GetSoundByType(st)->isPlaying())
//		GetSoundByType(st)->reset();
//	GetSoundByType(st)->play();
//}
//extern "C" void SoundStop(SoundType st)
//{
//	GetSoundByType(st)->stop();
//}
//extern "C" void SoundSetVolume(SoundType st, float volume)
//{
//	GetSoundByType(st)->setVolume(volume);
//}
