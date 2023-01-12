#include "CreditsMenu.h"
#include "Vec2.h"
#include <vector>
#include "raylibCpp.h"
#include "Settings.h"

CreditsMenu::CreditsMenu(SoundManager& sounds1) :
	menuLoaded(false),
	returnButtonCounter(0),
	mouseOverReturnButton(false),
	sounds(sounds1)
{
}

void CreditsMenu::Tick()
{
	Draw();
	ReturnButton();
}

void CreditsMenu::LoadCreditsMenu()
{
	menuLoaded = true;
}

bool CreditsMenu::GetMenuLoaded()
{
	return menuLoaded;
}

void CreditsMenu::SetLoaded(bool val)
{
	menuLoaded = val;
}

void CreditsMenu::DrawText()
{
	raycpp::DrawText("DEVELOPER: Cherry <3#8150 A.K.A. technomaniak on github\n------------------------------------------------------------\nMUSIC: also Cherry\n------------------------------------------------------------\nGRAPHICS: You get the point\n------------------------------------------------------------\nSFX: M0~ oh wait, no it's still me, Cherry\n------------------------------------------------------------\nMENTAL HELP: Adam, Metallica, Slipknot & Imagine Dragons", { 200, 200 }, 50, Color{ 200, 200, 255, 255 });
}

void CreditsMenu::Draw()
{
	ClearBackground(BLACK);
	DrawText();
	raycpp::DrawText("RETURN", settings::returnButtonTextPos - Vec2<int>{ (settings::minReturnTextSize - settings::returnTextSize) * -2,
		((settings::minReturnTextSize - settings::returnTextSize) / 2) * -1}, settings::returnTextSize, RAYWHITE);
}

void CreditsMenu::ReturnButton()
{
	if (raycpp::GetMousePos() > settings::verticalDividerPos2 - Vec2<int>{ 0, 25 }
	&& raycpp::GetMousePos() < Vec2<int>{ settings::screenWidth, settings::verticalDividerLength2 } - Vec2<int>{ 0, 25 })
	{
		if (mouseOverReturnButton != true)
		{
			sounds.PlaySoundFromName("menuSound");
			mouseOverReturnButton = true;
		}
	}
	else
	{
		if (settings::returnTextSize > settings::minReturnTextSize)
		{
			returnButtonCounter++;
			if (returnButtonCounter > 0)
			{
				settings::returnTextSize -= 5;
				returnButtonCounter = 0;
			}
		}
		mouseOverReturnButton = false;
	}
	if (mouseOverReturnButton)
	{
		if (settings::returnTextSize < settings::maxReturnTextSize)
		{
			returnButtonCounter++;
			if (returnButtonCounter > 0)
			{
				settings::returnTextSize += 5;
				returnButtonCounter = 0;
			}
		}
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			sounds.PlaySoundFromName("menuSound");
			SetLoaded(false);
		}
	}
}
