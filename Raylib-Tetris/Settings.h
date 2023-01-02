#pragma once
#include "Vec2.h"
#include <vector>

namespace settings
{
    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

    // Window settings
        inline constexpr int screenWidth = 1920;
        inline constexpr int screenHeight = 1080;
        inline constexpr int fps = 60;

    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

    // Board settings
        inline constexpr int cellSize = 45;
        inline constexpr int padding = 5;
        inline constexpr Vec2<int> boardPosition { 300, 100 };  // 250 70
        inline Vec2<int> boardWidthHeight { 10, 20 };

    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

    // Score/Level settings
        inline constexpr Vec2<int> scoreCounterPosition{ 1220, 100 };
        inline constexpr int scoreCounterSize = 92;
        inline constexpr Vec2<int> levelCounterPosition{ 1220, 375 };
        inline constexpr int levelCounterSize = 80;
        inline constexpr Vec2<int> linesCounterPosition{ 1220, 625 };
        inline constexpr int linesCounterSize = 80;

    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

    // Main Menu 

        // Play Button
            inline constexpr Vec2<int> playButtonSize{ 500, 150 };
            inline constexpr int minPlayButtonTextSize = 80;
            inline constexpr int maxPlayButtonTextSize = 100;
            inline int playButtonTextSize = 100;
            inline constexpr Vec2<int> playButtonPos{ (screenWidth / 2) - (playButtonSize.GetX() / 2), ((screenHeight / 5) * 3) };
            inline Vec2<int> playButtonTextPos{ playButtonPos.GetX(), playButtonPos.GetY() };


        // Main Text
            inline int mainTextSize = 300;

        // Settings Button
            inline constexpr Vec2<int> settingsButtonSize{ 110, 110 };
            inline constexpr float maxSettingsButtonTextureSize = 0.1853125f;
            inline constexpr float minSettingsButtonTextureSize = 0.1353125f;
            inline float settingsButtonTextureSize = 0.1853125f;
            inline constexpr Vec2<int> settingsButtonPos{ 75, 75 };
            inline Vec2<int> settingsButtonTexturePos = settingsButtonPos + Vec2<int>{ 6, 6 };

        // Quit Game Button
            inline constexpr Vec2<int> quitGameButtonSize{ 500, 150 };
            inline constexpr int minQuitGameButtonTextSize = 80;
            inline constexpr int maxQuitGameButtonTextSize = 100;
            inline int quitGameButtonTextSize = 100;
            inline constexpr Vec2<int> quitGameButtonPos = playButtonPos + Vec2<int>{ 0, 200 };
            inline Vec2<int> quitGameButtonTextPos{ quitGameButtonPos.GetX(), quitGameButtonPos.GetY() };

    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

    // Setting Menu

        // Options Selection
            
            // Dividers

                // Vertical
                    inline constexpr Vec2<int> verticalDividerPos{ 570, 0 };
                    inline constexpr int verticalDividerLength = 175;

                    inline constexpr Vec2<int> verticalDividerPos2{ screenWidth - 570, 0 };
                    inline constexpr int verticalDividerLength2 = 175;
    
                // Horizontal
                    inline constexpr Vec2<int> horizontalDividerPos{ 0, 175 };
                    inline constexpr int horizontalDividerLength = screenWidth;

            // Controls
                
                // Text
                    inline constexpr Vec2<int> controlsTextPos{ 115, 63 };
                    inline int controlsTextSize = 60;
                    inline constexpr int minControlsTextSize = 60;
                    inline constexpr int maxControlsTextSize = 75;

                // Key Positions
                    
                    // Rotate Right
                        inline constexpr Vec2<int> rotateRightKeyTextPos{ 100, 200 };
                        inline constexpr int rotateRightKeyTextSize = 60;
                        inline constexpr int minRotateRightKeyTextSize = 60;
                        inline constexpr int maxRotateRightKeyTextSize = 70;
                        inline constexpr Vec2<int> rotateRightKeyButtonTextPos{ 700, 200 };
                        inline constexpr Vec2<int> alternateRotateRightKeyButtonTextPos{ 1200, 200 };
                
                    // Rotate Left
                        inline constexpr Vec2<int> rotateLeftKeyTextPos{ 100, 300 };
                        inline constexpr int rotateLeftKeyTextSize = 60;
                        inline constexpr int minRotateLeftKeyTextSize = 60;
                        inline constexpr int maxRotateLeftKeyTextSize = 70;
                        inline constexpr Vec2<int> rotateLeftKeyButtonTextPos{ 700, 300 };
                        inline constexpr Vec2<int> alternateRotateLeftKeyButtonTextPos{ 1200, 300 };
                
                    // Swap
                        inline constexpr Vec2<int> swapKeyTextPos{ 100, 400 };
                        inline constexpr int swapKeyTextSize = 60;
                        inline constexpr int minSwapKeyTextSize = 60;
                        inline constexpr int maxSwapKeyTextSize = 70;
                        inline constexpr Vec2<int> swapKeyButtonTextPos{ 700, 400 };
                        inline constexpr Vec2<int> alternateSwapKeyButtonTextPos{ 1200, 400 };
                
                    // Move Right
                        inline constexpr Vec2<int> moveRightKeyTextPos{ 100, 500 };
                        inline constexpr int moveRightKeyTextSize = 60;
                        inline constexpr int minMoveRightKeyTextSize = 60;
                        inline constexpr int maxMoveRightKeyTextSize = 70;
                        inline constexpr Vec2<int> moveRightKeyButtonTextPos{ 700, 500 };
                        inline constexpr Vec2<int> alternateMoveRightKeyButtonTextPos{ 1200, 500 };
                
                    // Move Left
                        inline constexpr Vec2<int> moveLeftKeyTextPos{ 100, 600 };
                        inline constexpr int moveLeftKeyTextSize = 60;
                        inline constexpr int minMoveLeftKeyTextSize = 60;
                        inline constexpr int maxMoveLeftKeyTextSize = 70;
                        inline constexpr Vec2<int> moveLeftKeyButtonTextPos{ 700, 600 };
                        inline constexpr Vec2<int> alternateMoveLeftKeyButtonTextPos{ 1200, 600 };
                
                    // Reset
                        inline constexpr Vec2<int> resetKeyTextPos{ 100, 700 };
                        inline constexpr int resetKeyTextSize = 60;
                        inline constexpr int minResetKeyTextSize = 60;
                        inline constexpr int maxResetKeyTextSize = 70;
                        inline constexpr Vec2<int> resetKeyButtonTextPos{ 700, 700 };
                        inline constexpr Vec2<int> alternateResetKeyButtonTextPos{ 1200, 700 };
                
                    // Menu
                        inline constexpr Vec2<int> menuKeyTextPos{ 100, 800 };
                        inline constexpr int menuKeyTextSize = 60;
                        inline constexpr int minMenuKeyTextSize = 60;
                        inline constexpr int maxMenuKeyTextSize = 70;
                        inline constexpr Vec2<int> menuKeyButtonTextPos{ 700, 800 };
                        inline constexpr Vec2<int> alternateMenuKeyButtonTextPos{ 1200, 800 };
                
                    // Soft Drop
                        inline constexpr Vec2<int> softDropKeyTextPos{ 100, 900 };
                        inline constexpr int softDropKeyTextSize = 60;
                        inline constexpr int minSoftDropKeyTextSize = 60;
                        inline constexpr int maxSoftDropKeyTextSize = 70;
                        inline constexpr Vec2<int> softDropKeyButtonTextPos{ 700, 900 };
                        inline constexpr Vec2<int> alternateSoftDropKeyButtonTextPos{ 1200, 900 };

                    // Hard Drop
                        inline constexpr Vec2<int> hardDropKeyTextPos{ 100, 1000 };
                        inline constexpr int hardDropKeyTextSize = 60;
                        inline constexpr int minhardDropKeyTextSize = 60;
                        inline constexpr int maxhardDropKeyTextSize = 70;
                        inline constexpr Vec2<int> hardDropKeyButtonTextPos{ 700, 1000 };
                        inline constexpr Vec2<int> alternateHardDropKeyButtonTextPos{ 1200, 1000 };
                
            // Audio And Graphic
                // Text
                    inline constexpr Vec2<int> audioAndGraphicsTextPos{ 660, 63 };
                    inline int audioAndGraphicsTextSize = 60;
                    inline constexpr int minAudioAndGraphicsTextSize = 60;
                    inline constexpr int maxAudioAndGraphicsTextSize = 75;

                // Volume Slider
                    inline constexpr Vec2<int> volumeSliderBorderSize{ 50, 610 };
                    inline constexpr Vec2<int> volumeSliderBorderPos{ screenWidth - volumeSliderBorderSize.GetX() * 5, screenHeight - (int)(volumeSliderBorderSize.GetY() * 1.25) };
                    inline Vec2<int> volumeSliderSize = volumeSliderBorderSize - 10;
                    inline constexpr Vec2<int> volumeSliderPos = volumeSliderBorderPos + 5;

            // Return 
                inline constexpr Vec2<int> returnButtonTextPos{ screenWidth - 445, 63 };
                inline int returnTextSize = 60;
                inline constexpr int minReturnTextSize = 60;
                inline constexpr int maxReturnTextSize = 75;

    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

    // Game Over Screen
    
        // Text
            inline constexpr Vec2<int> gameOverTextPosition{ levelCounterPosition.GetX() - 400, 300 };
            inline constexpr Vec2<int> newBestTextPosition = gameOverTextPosition - Vec2<int>{ 0, -300 };
            inline constexpr int gameOverAllRegularTextsSize = 92;
    
        // Restart Button
            inline constexpr Vec2<int> restartButtonPos = gameOverTextPosition + Vec2<int>{ 0, 250 };
            inline constexpr Vec2<int> restartButtonSize{ 257, 75 };
            inline constexpr int minRestartButtonTextSize = 30;
            inline constexpr int maxRestartButtonTextSize = 35;
            inline int restartButtonTextSize = 35;

        // Main Menu Button
            inline constexpr Vec2<int> mainMenuButtonPos = restartButtonPos + Vec2<int>{ 0, 100 };
            inline constexpr Vec2<int> mainMenuButtonSize{ 257, 75 };
            inline constexpr int minMainMenuButtonTextSize = 30;
            inline constexpr int maxMainMenuButtonTextSize = 35;
            inline int mainMenuButtonTextSize = 35;

        // Reuses Options Button From Below

    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

    // In Game Pause Menu

        // Reuses Restart Button and Main Menu Button

        // Options Button Pos
            inline constexpr Vec2<int> optionsButtonPos = mainMenuButtonPos + Vec2<int>{ 0, 100 };
            inline constexpr Vec2<int> optionsButtonSize{ 257, 75 };
            inline constexpr int minOptionsButtonTextSize = 30;
            inline constexpr int maxOptionsButtonTextSize = 35;
            inline int optionsButtonTextSize = 35;

    //--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
}