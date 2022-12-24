#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager():
	music({ LoadMusicStream("music_1.mp3") }),
	music_amount(music.size()),
	placeSound(LoadSound("place.wav")),
	musicPlayingId(0)
{
	SetSoundVolume(placeSound, 0.2f);
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
			std::cout << "\nMusic is playing for " << GetMusicTimePlayed(music[i]) << " seconds now";
			return true;
		}
	}
	return false;
}

void SoundManager::PlayRandomMusic()
{
	int toPlay = rand() % music_amount;
	SetMusicVolume(music[toPlay], 0.1f);
	PlayMusicStream(music[toPlay]);
	musicPlayingId = toPlay;
	std::cout << "\nPlay music " << GetMusicTimeLength(music[toPlay]);
}

void SoundManager::UpdateCurrentMusic()
{
	UpdateMusicStream(music[musicPlayingId]);
}

SoundManager::Options SoundManager::ResolveOptions(std::string input)
{
	if (input == "placeSound") return Options::placeSound;
	return Options::invalidSound;
}
