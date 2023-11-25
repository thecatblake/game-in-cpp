//
// Created by ryousuke kaga on 2023/11/25.
//

#ifndef GAME_IN_CPP_SPRITECOMPONENT_H
#define GAME_IN_CPP_SPRITECOMPONENT_H

#include "Component.h"

class Actor;

class SpriteComponent : public Component {
public:
    SpriteComponent(Actor* owner, int drawOrder = 100);
    ~SpriteComponent();
    virtual void Draw(SDL_Renderer* renderer);
    virtual void SetTexture(SDL_Texture* texture);

    int drawOrder;
    int textHeight;
    int textWidth;
protected:
    SDL_Texture* mTexture;
};


#endif //GAME_IN_CPP_SPRITECOMPONENT_H
