#ifndef _PLAYERPHYSICSCOMPONENT_H
#define _PLAYERPHYSICSCOMPONENT_H

#include "Level.h"
#include "PhysicsComponent.h"

//*******************************************************************************************
// PlayerPhysicsComponent
//*******************************************************************************************
// Implementation of PhysicsComponent for the player GameObject
class PlayerPhysicsComponent : public PhysicsComponent {

public:
	explicit PlayerPhysicsComponent(int newID, bool isActive, ColorTag newTag, Level* level) :
		PhysicsComponent(newID, isActive, newTag), _level(level) {}

	void Update(GameObject& gameObject, GameManager& gameManager, const float deltaTime) override;

	void OnCollision(GameObject& gameObject, ObjectType otherTag, ColorTag otherColor) override;

private:
	Level* _level;

};
#endif
