#include "raylib.h"
#include "asteroids.h"
#include "ctime"

#if defined(_WIN32)           
#define NOGDI             
#define NOUSER            
#endif

#if defined(_WIN32)
#include <Windows.h> 
#endif

#if defined(_WIN32)           
#undef near
#undef far
#endif

//#define DEBUG

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1360;
    const int screenHeight = 920;

    InitWindow(screenWidth, screenHeight, "Asteroids");
    InitAudioDevice();

    // TODO: Initialize all required variables and load all required data here!

    enum GameScreen currentScreen = GameScreen::TITLE;

    Asteroids asteroids(screenHeight, screenWidth, currentScreen);

    SetTargetFPS(60);               // Set desired framerate (frames-per-second)
    SetRandomSeed(time(0));
    HideCursor();

#ifndef DEBUG
    Music backgroundSound = LoadMusicStream("lunar.mp3");
    backgroundSound.looping = true;
    
    PlayMusicStream(backgroundSound);
#endif
    

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        switch (currentScreen)
        {
            case TITLE:
            {
                // TODO: Update TITLE screen variables here!

                // Press enter to change to GAMEPLAY screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    currentScreen = GameScreen::GAMEPLAY;
                }
            } break;
            case GAMEPLAY:
            {
                // TODO: Update GAMEPLAY screen variables here!

                asteroids.Update();

            } break;
            case LOST:
            {
                // TODO: Update ENDING screen variables here!

                // Press enter to return to TITLE screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    asteroids.ResetGame();
                }
            } break;
            case WON:
            {
                // TODO: Update ENDING screen variables here!

                // Press enter to return to TITLE screen
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    asteroids.ResetGame();
                }
            } break;
            default:
                break;
        }
#ifndef DEBUG
        UpdateMusicStream(backgroundSound);   // Update music buffer with new stream data
#endif 



        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        switch (currentScreen)
        {
            case TITLE:
            {
                // TODO: Draw TITLE screen here!
                //DrawRectangle(0, 0, screenWidth, screenHeight, RAYWHITE);
                DrawText("Asteroids", 20, 20, 40, RAYWHITE);
                DrawText("Press ENTER to start game", 120, 220, 20, RAYWHITE);

            } break;
            case GAMEPLAY:
            {
                // TODO: Draw GAMEPLAY screen here!

                asteroids.Draw();

            } break;
            case LOST:
            {
                // TODO: Draw ENDING screen here!
                DrawRectangle(0, 0, screenWidth, screenHeight, MAROON);
                DrawText("Game Over", 20, 20, 40, BLACK);
                DrawText("Press ENTER to start again", 120, 220, 20, BLACK);

            } break;
            case WON:
            {
                // TODO: Draw ENDING screen here!
                DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
                DrawText("You Won", 20, 20, 40, BLACK);
                DrawText("Press ENTER to start again", 120, 220, 20, BLACK);

            } break;
            default: 
                break;
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------

    // TODO: Unload all loaded data (textures, fonts, audio) here!
#ifndef DEBUG
    UnloadMusicStream(backgroundSound);
    CloseAudioDevice();
#endif
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

#if defined(_WIN32)   
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char* pCmdLine, int nCmdShow)
{
    main();

    return 0;
}
#endif