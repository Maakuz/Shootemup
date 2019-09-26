#ifndef AUDIOHANDLER_H
#define AUDIOHANDLER_H
#include"SFML/Audio.hpp"
using namespace sf;

//Handles all the music and sound effects
class AudioHandler 
{
private:
	SoundBuffer selectSoundBuffer;
	SoundBuffer shootSoundBuffer;
	SoundBuffer buySoundBuffer;
	SoundBuffer hitSoundBuffer;

	Sound selectSound;
	Sound shootSound;
	Sound buySound;
	Sound hitSound;

	Music bgmIntro;
	Music victory;
	Music bgm;

	bool bgmPlayingIntro;
	bool victoryPlaying;
	bool bgmPlaying;

	int volume;

	void loadFiles();
	void initializeSounds();
public:
	AudioHandler();
	virtual ~AudioHandler();

	void update();
	void stopBgm();
	void startBgm();
	void playVictory();
	void playHitSound();
	void playBuySound();
	float getVictoryPos();
	void playShootSound();
	void playSelecetSound();
};

#endif