//
// Created by ryousuke kaga on 2023/11/18.
//

#include "Actor.h"


Actor::Actor(Game* game)
        :state(EActive)
        , position(Vector2(0, 0))
        , scale(1.0f)
        , rotation(0.0f)
        , mGame(game)
{
    mGame->AddActor(this);
}


Actor::~Actor()
{
    mGame->RemoveActor(this);
    // Need to delete components
    // Because ~Component calls RemoveComponent, need a different style loop
    while (!mComponents.empty())
    {
        delete mComponents.back();
    }
}

void Actor::Update(float deltaTime)
{
    if (state == EActive)
    {
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);
    }
}

void Actor::UpdateComponents(float deltaTime)
{
    for (auto comp : mComponents)
    {
        comp->Update(deltaTime);
    }
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::AddComponent(Component* component)
{
    // Find the insertion point in the sorted vector
    // (The first element with a order higher than me)
    int myOrder = component->updateOrder;
    auto iter = mComponents.begin();
    for (;
            iter != mComponents.end();
            ++iter)
    {
        if (myOrder < (*iter)->updateOrder)
        {
            break;
        }
    }

    // Inserts element before position of iterator
    mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component)
{
    auto iter = std::find(mComponents.begin(), mComponents.end(), component);
    if (iter != mComponents.end())
    {
        mComponents.erase(iter);
    }
}

Game *Actor::GetGame() {
    return mGame;
}
