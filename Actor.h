//
// Created by ryousuke kaga on 2023/11/18.
//

#ifndef GAME_IN_CPP_ACTOR_H
#define GAME_IN_CPP_ACTOR_H

#include "Vector2.h"
#include "Math.h"
#include "Game.h"
#include "Component.h"

class Game;

class Actor {
public:;
    enum State {
        EActive,
        EPaused,
        EDead
    };

    Actor(Game* game);
    virtual ~Actor();

    void Update(float deltaTime);
    void UpdateComponents(float deltaTime);
    virtual void UpdateActor(float deltaTime);

    void AddComponent(Component* component);
    void RemoveComponent(Component* component);

    Game* GetGame();

    State state;

    Vector2 position;
    float scale;
    float rotation;
protected:
    std::vector<Component*> mComponents;
    Game* mGame;
};


#endif //GAME_IN_CPP_ACTOR_H
