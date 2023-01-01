#pragma once
#include "Vec2.h"
#include "SoundManager.h"

class OptionsMenu
{
public:
	OptionsMenu(SoundManager &sounds1);

	void LoadOptions();
	void SetLoaded(bool val);
	bool GetLoaded();
	void Tick();
	void Draw();

private:
	void VolumeSettings();
	void ReturnButton();

	bool optionsLoaded;

	bool mouseOverMusicVolumeSlider;
	bool mouseClickedMusicVolumeSlider;

	bool mouseOverSFXVolumeSlider;
	bool mouseClickedSFXVolumeSlider;
	float volume;

	int returnButtonCounter;
	bool mouseOverReturnButton;

	SoundManager &sounds;
	Color volumeSliderTint;
};