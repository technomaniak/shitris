#pragma once
#include "SoundManager.h"

class CreditsMenu
{
public:
	CreditsMenu(SoundManager& sounds1);

	void Tick();
	void LoadCreditsMenu();
	bool GetMenuLoaded();
	void SetLoaded(bool val);
private:
	void DrawText();
	void Draw();
	void ReturnButton();

	bool menuLoaded;
	bool mouseOverReturnButton;
	int returnButtonCounter;
	SoundManager& sounds;
};