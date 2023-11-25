//
// Created by ryousuke kaga on 2023/11/18.
//

#include "Component.h"
#include "Actor.h"

Component::Component(Actor *owner, int updateOrder): mOwner(owner), updateOrder(updateOrder) {
    mOwner->AddComponent(this);
}

Component::~Component()
{
    mOwner->RemoveComponent(this);
}

void Component::Update(float deltaTime) {

}
