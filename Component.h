//
// Created by ryousuke kaga on 2023/11/18.
//

#ifndef GAME_IN_CPP_COMPONENT_H
#define GAME_IN_CPP_COMPONENT_H

#include <SDL2/SDL.h>

class Actor;

class Component {
public:
    Component(Actor* owner, int updateOrder=100);
    virtual ~Component();

    virtual void Update(float deltaTime);
    int updateOrder;
protected:
    Actor* mOwner;
};


#endif //GAME_IN_CPP_COMPONENT_H
