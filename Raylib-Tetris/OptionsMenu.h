#pragma once
#include "Vec2.h"
#include "SoundManager.h"

class OptionsMenu
{
private:
	enum class KeyBinds {
		ROTATELEFT,
		ROTATERIGHT,
		RESET,
		SWAPPIECE,
		MENU,
		MOVERIGHT,
		MOVELEFT,
		HARDDROP,
		SOFTDROP,
		ALTERNATEROTATELEFT,
		ALTERNATEROTATERIGHT,
		ALTERNATERESET,
		ALTERNATESWAPPIECE,
		ALTERNATEMENU,
		ALTERNATEMOVERIGHT,
		ALTERNATEMOVELEFT,
		ALTERNATEHARDDROP,
		ALTERNATESOFTDROP
	};
public:
	OptionsMenu(SoundManager &sounds1, std::vector<std::vector<int>> &keyBindsList1);

	void LoadOptions();
	void SetLoaded(bool val);
	bool GetLoaded();
	void Tick();
	void Draw();

private:
	void ReturnButton();
	void ManageOptionsSelection();

	void ControlsButton();
	void ControlsSelection();
	void Controls();
	void VolumeSettings();

	void AudioAndGraphics();
	void AudioAndGraphicsSelection();
	void AudioAndGraphicsButton();
	void DrawControlsKeyBinds();
	KeyBinds SelectKeyBind();
	int SelectKey();
	void SaveKeysInSettings();
	void LoadKeysFromSettings();

	std::string KeyBindName(int key);

	std::vector<std::vector<int>>& keyBindsList;
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