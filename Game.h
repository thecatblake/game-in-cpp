//
// Created by ryousuke kaga on 2023/11/01.
//

#ifndef GAME_GAME_H
#define GAME_GAME_H

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "Actor.h"
#include "SpriteComponent.h"
#include <unordered_map>
#include <algorithm>
#include <string>

class Game {
public:
    Game(int width, int height);
    bool Initialize();
    void RunLoop();
    void Shutdown();
    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);

    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(class SpriteComponent* sprite);
    SDL_Texture* GetTexture(const std::string& fileName);
protected:
    void ProcessInput();
    virtual void _ProcessInput(SDL_Event event) = 0;
    void UpdateGame();
    virtual void _UpdateGame(float deltaTime) = 0;
    void GenerateOutput();
    virtual void _GenerateOutput() = 0;

    virtual void LoadData();
    void UnloadData();

    SDL_Window* mWindow;
    SDL_Renderer* mRender;
    bool mIsRunning;
    int mWidth;
    int mHeight;
    Uint32 mTicksCount;

    std::vector<Actor*> mActors;
    std::vector<Actor*> mPendingActors;
    bool mUpdatingActors;
    std::vector<SpriteComponent*> mSprites;

    std::unordered_map<std::string, SDL_Texture*> mTextures;
};

#endif //GAME_GAME_H
