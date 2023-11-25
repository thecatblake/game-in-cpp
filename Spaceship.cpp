//
// Created by ryousuke kaga on 2023/11/25.
//

#include "Game.h"

class Spaceship : public Game {
public:
    Spaceship(int width, int height);

private:
    void _GenerateOutput() override;

    void _ProcessInput(SDL_Event event) override;

    void _UpdateGame(float deltaTime) override;

    void LoadData() override;
};

Spaceship::Spaceship(int width, int height): Game(width, height) {
    auto ship = new Actor(this);
    auto shipSprite = new SpriteComponent(ship);
    std::string textFile = "/Users/ryousukekaga/repositories/game-in-cpp/Assets/Laser.png";
    SDL_Texture* texture = GetTexture(textFile);
    shipSprite->SetTexture(texture);
}

void Spaceship::_ProcessInput(SDL_Event event) {
    switch (event.type)
    {
    }
}

void Spaceship::_UpdateGame(float deltaTime) {
}

void Spaceship::_GenerateOutput() {
}

void Spaceship::LoadData() {
    Game::LoadData();
}

int main() {
    Spaceship game(1024, 769);
    bool success = game.Initialize();
    if(success)
        game.RunLoop();
    game.Shutdown();
}