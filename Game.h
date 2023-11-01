//
// Created by ryousuke kaga on 2023/11/01.
//

#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <SDL.h>

class Game {
public:
    Game(int width, int height);
    bool Initialize();
    void RunLoop();
    void Shutdown();
protected:
    void ProcessInput();
    virtual void _ProcessInput(SDL_Event event) = 0;
    void UpdateGame();
    virtual void _UpdateGame(float deltaTime) = 0;
    void GenerateOutput();
    virtual void _GenerateOutput() = 0;

    SDL_Window* mWindow;
    SDL_Renderer* mRender;
    bool mIsRunning;
    int mWidth;
    int mHeight;
    Uint32 mTicksCount;
};

#endif //GAME_GAME_H
