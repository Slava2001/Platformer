
#ifndef SoundTypedef
#define SoundTypedef
typedef enum
{
	SN_MAIN_SOUND,
	SN_BUTTON_CLICK_SOUND,
	SN_JUMP_SOUND,
	SN_WALK_SOUND,
	SN_LANDED_SOUND
}SoundType;
#endif SoundTypedef

void SoundInit();

void SoundPlay(SoundType st);
void SoundStop(SoundType st);
void SoundSetVolume(SoundType st,float volume);

