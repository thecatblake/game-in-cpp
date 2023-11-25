//
// Created by ryousuke kaga on 2023/11/01.
//

#include "Game.h"
#include "SpriteComponent.h"


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

    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
        return false;
    }

    LoadData();

    return true;
}

void Game::Shutdown() {
    UnloadData();
    IMG_Quit();
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
        switch (event.type)
            case SDL_QUIT:
                mIsRunning = false;
                break;

        _ProcessInput(event);
    }
}
void Game::UpdateGame() {
    while(!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }

    mUpdatingActors = true;
    for(auto & actor : mActors) {
        actor->Update(deltaTime);
    }
    mUpdatingActors = false;
    for(auto & pending: mPendingActors) {
        mActors.push_back(pending);
    }
    mPendingActors.clear();

    std::vector<Actor*> deadActors;

    for(auto actor : mActors) {
        if(actor->state == Actor::EDead) {
            deadActors.push_back(actor);
        }
    }

    for(auto & actor : deadActors) {
        delete actor;
    }

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

void Game::AddActor(Actor *actor) {
    if(mUpdatingActors)
        mPendingActors.push_back(actor);
    else
        mActors.push_back(actor);
}

SDL_Texture* Game::GetTexture(const std::string& fileName)
{
    SDL_Texture* tex = nullptr;
    // Is the texture already in the map?
    auto iter = mTextures.find(fileName);
    if (iter != mTextures.end())
    {
        tex = iter->second;
    }
    else
    {
        // Load from file
        SDL_Surface* surf = IMG_Load(fileName.c_str());
        if (!surf)
        {
            SDL_Log("Failed to load texture file %s", fileName.c_str());
            return nullptr;
        }

        // Create texture from surface
        tex = SDL_CreateTextureFromSurface(mRender, surf);
        SDL_FreeSurface(surf);
        if (!tex)
        {
            SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
            return nullptr;
        }

        mTextures.emplace(fileName.c_str(), tex);
    }
    return tex;
}
void Game::RemoveActor(Actor* actor)
{
    // Is it in pending actors?
    auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
    if (iter != mPendingActors.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }

    // Is it in actors?
    iter = std::find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end())
    {
        // Swap to end of vector and pop off (avoid erase copies)
        std::iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
    }
}

void Game::AddSprite(SpriteComponent* sprite)
{
    // Find the insertion point in the sorted vector
    // (The first element with a higher draw order than me)
    int myDrawOrder = sprite->drawOrder;
    auto iter = mSprites.begin();
    for ( ;
            iter != mSprites.end();
            ++iter)
    {
        if (myDrawOrder < (*iter)->drawOrder)
        {
            break;
        }
    }

    // Inserts element before position of iterator
    mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite)
{
    // (We can't swap because it ruins ordering)
    auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(iter);
}

void Game::LoadData() {

}

void Game::UnloadData() {
    while (!mActors.empty())
    {
        delete mActors.back();
    }

    // Destroy textures
    for (auto i : mTextures)
    {
        SDL_DestroyTexture(i.second);
    }
    mTextures.clear();
}

