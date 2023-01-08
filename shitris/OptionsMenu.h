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
		ALTERNATESOFTDROP,
		NONE
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
	bool MoveRightKeyBind();
	bool MoveLeftKeyBind();
	bool RotateRightKeyBind();
	bool RotateLeftKeyBind();
	bool ResetKeyBind();
	bool MenuKeyBind();
	bool HardDropKeyBind();
	bool SoftDropKeyBind();
	bool SwapKeyBind();
	bool AlternateMoveRightKeyBind();
	bool AlternateMoveLeftKeyBind();
	bool AlternateRotateRightKeyBind();
	bool AlternateRotateLeftKeyBind();
	bool AlternateResetKeyBind();
	bool AlternateMenuKeyBind();
	bool AlternateHardDropKeyBind();
	bool AlternateSoftDropKeyBind();
	bool AlternateSwapKeyBind();

	void AudioAndGraphics();
	void AudioAndGraphicsSelection();
	void AudioAndGraphicsButton();
	void DrawControlsKeyBinds();
	KeyBinds SelectKeyBind();
	void SelectKey(KeyBinds selection);
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

	int moveRightCounter;
	bool mouseOverMoveRight;
	int alternateMoveRightCounter;
	bool alternateMouseOverMoveRight;

	int moveLeftCounter;
	bool mouseOverMoveLeft;
	int alternateMoveLeftCounter;
	bool alternateMouseOverMoveLeft;

	int rotateRightCounter;
	bool mouseOverRotateRight;
	int alternateRotateRightCounter;
	bool alternateMouseOverRotateRight;

	int rotateLeftCounter;
	bool mouseOverRotateLeft;
	int alternateRotateLeftCounter;
	bool alternateMouseOverRotateLeft;

	int resetCounter;
	bool mouseOverReset;
	int alternateResetCounter;
	bool alternateMouseOverReset;

	int menuCounter;
	bool mouseOverMenu;
	int alternateMenuCounter;
	bool alternateMouseOverMenu;

	int hardDropCounter;
	bool mouseOverHardDrop;
	int alternateHardDropCounter;
	bool alternateMouseOverHardDrop;

	int softDropCounter;
	bool mouseOverSoftDrop;
	int alternateSoftDropCounter;
	bool alternateMouseOverSoftDrop;

	int swapCounter;
	bool mouseOverSwap;
	int alternateSwapCounter;
	bool alternateMouseOverSwap;
	
	int keyPressed;
	bool justFoundKey;
	KeyBinds waitingForInput;

	SoundManager &sounds;
	Color volumeSliderTint;
};