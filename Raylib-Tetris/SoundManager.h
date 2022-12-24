#pragma once
#include <vector>
#include <string>
#include "raylibCpp.h"

class SoundManager
{
private:

	enum class Options {
		placeSound,
		invalidSound
	};
public:
	SoundManager();

	void PlaySoundFromName(std::string name);
	bool CheckMusicPlaying() const;
	void LoadMusic();
private:

	std::vector<Music> music;
	Sound placeSound;
	const int music_amount;

	Options ResolveOptions(std::string input);
};