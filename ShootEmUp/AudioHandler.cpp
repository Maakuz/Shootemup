#include"AudioHandler.h"
AudioHandler::AudioHandler()
{
	loadFiles();

	this->volume = 15;

	initializeSounds();

	this->bgmPlayingIntro = false;
	this->victoryPlaying = false;
	this->bgmPlaying = false;
}

AudioHandler::~AudioHandler()
{}

void AudioHandler::loadFiles()
{
	this->selectSoundBuffer.loadFromFile("../Sfx/cursor.wav");
	this->shootSoundBuffer.loadFromFile("../Sfx/zap.wav");
	this->buySoundBuffer.loadFromFile("../Sfx/buy.wav");
	this->hitSoundBuffer.loadFromFile("../Sfx/hit.wav");
	this->bgmIntro.openFromFile("../Sfx/bgmIntro.wav");
	this->victory.openFromFile("../Sfx/victory.wav");
	this->bgm.openFromFile("../Sfx/bgm.wav");
}

void AudioHandler::initializeSounds()
{
	this->selectSound.setBuffer(this->selectSoundBuffer);
	this->shootSound.setBuffer(this->shootSoundBuffer);
	this->buySound.setBuffer(this->buySoundBuffer);
	this->hitSound.setBuffer(this->hitSoundBuffer);

	this->selectSound.setVolume(this->volume);
	this->shootSound.setVolume(this->volume);
	this->buySound.setVolume(this->volume);
	this->hitSound.setVolume(this->volume);
	this->victory.setVolume(this->volume);

	this->bgm.setLoop(true);
}

void AudioHandler::update()
{
	if (this->bgmIntro.getPlayingOffset().asMilliseconds() >= 2994 && !this->bgmPlaying)
	{
		this->bgmPlaying = true;
		this->bgm.play();
	}

	if (this->bgmIntro.getPlayingOffset().asMilliseconds() >= 3500)
	{
		this->bgm.setVolume(this->volume);
		this->bgmIntro.setVolume(0);
		this->bgmPlayingIntro = false;
	}
}

void AudioHandler::stopBgm()
{
	if (this->bgmPlaying || this->bgmPlayingIntro)
	{
		this->bgmPlaying = false;
		this->bgmPlayingIntro = false;
		this->bgm.stop();
		this->bgmIntro.stop();
	}
}

void AudioHandler::startBgm()
{
	if (!bgmPlayingIntro && !this->bgmPlaying)
	{
		this->bgmPlayingIntro = true;
		this->bgmIntro.play();
		this->bgmIntro.setVolume(this->volume);
		this->bgm.setVolume(0);
	}
}

void AudioHandler::playVictory()
{
	if (!victoryPlaying)
	{
		this->shootSound.setVolume(0);
		this->victoryPlaying = true;
		this->victory.play();
	}
}

void AudioHandler::playHitSound()
{
	this->hitSound.play();
}

void AudioHandler::playBuySound()
{
	this->buySound.play();
}

float AudioHandler::getVictoryPos()
{
	return this->victory.getPlayingOffset().asMilliseconds();
}

void AudioHandler::playShootSound()
{
	this->shootSound.play();
}

void AudioHandler::playSelecetSound()
{
	this->selectSound.play();
}
