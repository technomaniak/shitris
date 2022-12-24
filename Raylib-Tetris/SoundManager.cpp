#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager():
	music({ LoadMusicStream("music_1.mp3") }),
	music_amount(music.size()),
	placeSound(LoadSound("place.wav"))
{
}

void SoundManager::PlaySoundFromName(std::string name)
{
	switch (ResolveOptions(name))
	{
	case Options::placeSound:
		PlaySound(placeSound);
		return;
	case Options::invalidSound:
		std::cout << "\n WRONG SOUND FILE\n";
		return;
	}
}

bool SoundManager::CheckMusicPlaying() const
{
	for (int i = 0; i < music_amount; i++)
	{
		if (IsMusicStreamPlaying(music[i]))
		{
			std::cout << "\nMusic is playing for " << GetMusicTimePlayed(music[i]) << " now";
			return true;
		}
	}
	return false;
}

void SoundManager::LoadMusic()
{
	int toPlay = rand() % music_amount;
	PlayMusicStream(music[toPlay]);
	std::cout << "\nPlay music " << GetMusicTimeLength(music[toPlay]);
}

SoundManager::Options SoundManager::ResolveOptions(std::string input)
{
	if (input == "placeSound") return Options::placeSound;
	return Options::invalidSound;
}
