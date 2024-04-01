#include "stdafx.h"
#include "PlayerPhysicsComponent.h"

void PlayerPhysicsComponent::Update(GameObject& gameObject, GameManager& gameManager, const float deltaTime) {
	if (!this->isEnabled) return;

	// Should the player do anything other than fire projectiles?
}

void PlayerPhysicsComponent::OnCollision(GameObject& gameObject, ObjectType otherTag, ColorTag otherColor) {
	// The player only collides with enemies
	_level->LoseLife();
}
