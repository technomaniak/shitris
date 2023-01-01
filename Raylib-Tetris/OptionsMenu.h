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
	void ControlsButton();
	void AudioAndGraphicsButton();
	void ManageOptionsSelection();
	void Controls();
	void GraphicsAndAudio();

	bool optionsLoaded;
	int whatOptionPart;

	bool mouseOverMusicVolumeSlider;
	bool mouseClickedMusicVolumeSlider;

	bool mouseOverSFXVolumeSlider;
	bool mouseClickedSFXVolumeSlider;
	float volume;

	int returnButtonCounter;
	bool mouseOverReturnButton;

	int controlsButtonCounter;
	bool mouseOverControlsButton;

	int audioAndGraphicsButtonCounter;
	bool mouseOverAudioAndGraphicsButton;

	SoundManager &sounds;
	Color volumeSliderTint;
};