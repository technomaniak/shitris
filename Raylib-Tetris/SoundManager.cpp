#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager():
	music({ LoadMusicStream("music_1.mp3"), LoadMusicStream("music_2.mp3") }),
	music_amount(music.size()),
	placeSound(LoadSound("placeSound.wav")),
	menuSound(LoadSound("menuSound.wav")),
	musicVolume(0.2f),
	currentlyPlaying(0)
{
	SetSoundVolume(placeSound, musicVolume);
	SetSoundVolume(menuSound, musicVolume);
}

void SoundManager::PlaySoundFromName(std::string name)
{
	switch (ResolveOptions(name))
	{
	case Options::placeSound:
		PlaySound(placeSound);
		return;
	case Options::menuSound:
		PlaySound(menuSound);
		return;
	case Options::invalidSound:
		std::cout << "\n WRONG SOUND FILE\n";
		return;
	}
}

bool SoundManager::CheckMusicPlaying()
{
	for (int i = 0; i < music_amount; i++)
	{
		if (IsMusicStreamPlaying(music[i]))
		{
			currentlyPlaying = i;
			return true;
		}
	}
	return false;
}

void SoundManager::PlayRandomMusic()
{
	srand((int)time(NULL));
	currentlyPlaying = rand() % music_amount;
	SetMusicVolume(music[currentlyPlaying], musicVolume);
	PlayMusicStream(music[currentlyPlaying]);
	std::cout << "\nPlay music " << GetMusicTimeLength(music[currentlyPlaying]);
}

void SoundManager::UpdateCurrentMusic()
{
	UpdateMusicStream(music[currentlyPlaying]);
}

void SoundManager::CloseSound()
{
	for (int i = 0; i < music_amount; i++)
	{
		UnloadMusicStream(music[i]);
	}
	UnloadSound(placeSound);
}

void SoundManager::SetAllMusicVolume(float volume)
{
	musicVolume = volume;
	SetMusicVolume(music[currentlyPlaying], musicVolume);
	SetSoundVolume(placeSound, musicVolume);
	SetSoundVolume(menuSound, musicVolume);
}

float SoundManager::GetMusicVolume() const
{
	return musicVolume;
}

SoundManager::Options SoundManager::ResolveOptions(std::string input)
{
	if (input == "placeSound") return Options::placeSound;
	if (input == "menuSound") return Options::menuSound;
	return Options::invalidSound;
}
