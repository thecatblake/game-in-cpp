//
// Created by ryousuke kaga on 2023/11/25.
//

#include "SpriteComponent.h"
#include "Actor.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
        :Component(owner)
        ,mTexture(nullptr)
        ,drawOrder(drawOrder)
        ,textWidth(0)
        ,textHeight(0)
{
    mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
    mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::SetTexture(SDL_Texture *texture) {
    mTexture = texture;
    SDL_QueryTexture(texture, nullptr, nullptr, &textWidth, &textHeight);
}

void SpriteComponent::Draw(SDL_Renderer *renderer) {
    if(mTexture) {
        SDL_Rect r;
        r.w = static_cast<int>(textWidth * mOwner->scale);
        r.h = static_cast<int>(textHeight * mOwner->scale);
        r.x = static_cast<int>(mOwner->position.x - r.w / 2);
        r.y = static_cast<int>(mOwner->position.y - r.h / 2);

        SDL_RenderCopyEx(renderer,
                         mTexture,
                         nullptr,
                         &r,
                         -Math::ToDegrees(mOwner->rotation),
                         nullptr,
                         SDL_FLIP_NONE);
    }
}
