#include "stdafx.h"
#include "EnemyControllerComponent.h"

void EnemyControllerComponent::Update(GameObject& gameObject, GameManager& gameManager, float deltaTime) {
    if (!this->isEnabled) return;

    // TODO: Make more interesting behaviour w/ BTs
    // TODO: Maybe add BT to possibly make enemies be able to switch lanes, add more intricate movement behavior

    // For now, the enemy will just move to the left
    gameObject.input.x = -1.0f;
}
