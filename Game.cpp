//
// Created by ryousuke kaga on 2023/11/01.
//

#include "Game.h"


Game::Game(int width, int height):
    mWidth(width),
    mHeight(height),
    mIsRunning(true),
    mTicksCount(0) {}

bool Game::Initialize() {
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);

    if(sdlResult != 0) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow(
            "Game",
            100,
            100,
            mWidth,
            mHeight,
            0
            );

    if (!mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mRender = SDL_CreateRenderer(
            mWindow,
            -1,
            SDL_RENDERER_ACCELERATED
            );

    return true;
}

void Game::Shutdown() {
    SDL_DestroyWindow(mWindow);
    SDL_DestroyRenderer(mRender);
    SDL_Quit();
}

void Game::RunLoop() {
    while(mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        _ProcessInput(event);
    }
}
void Game::UpdateGame() {
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }

    _UpdateGame(deltaTime);

    mTicksCount = SDL_GetTicks();
}
void Game::GenerateOutput() {
    SDL_SetRenderDrawColor(
            mRender,
            220,
            220,
            220,
            255
    );
    SDL_RenderClear(mRender);

    _GenerateOutput();
    SDL_RenderPresent(mRender);
}