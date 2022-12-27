#pragma once
#include <vector>
#include <string>
#include "raylibCpp.h"

class SoundManager
{
private:

	enum class Options {
		placeSound,
		menuSound,
		invalidSound
	};
public:
	SoundManager();

	void PlaySoundFromName(std::string name);
	bool CheckMusicPlaying() const;
	void PlayRandomMusic();
	void UpdateCurrentMusic();
	void CloseSound();
	void SetAllMusicVolume(float volume);
	float GetMusicVolume() const;

private:
	const std::vector<Music> music;
	const Sound placeSound;
	const Sound menuSound;
	const int music_amount;
	float musicVolume;
	int currentlyPlaying;

	Options ResolveOptions(std::string input);
};