#ifndef _CONTROLLERCOMPONENT_H
#define _CONTROLLERCOMPONENT_H

#include "GameObject.h"

//*******************************************************************************************
// ControllerComponent
//*******************************************************************************************
/* Interface of a component for managing AI and player input. Also used as a medium for
 * utility components, such as spawners.
 */
class ControllerComponent : public Component {

public:
	ControllerComponent(int newID, bool isActive) : Component(newID, isActive) {}

	~ControllerComponent() override = default;

	virtual void Update(GameObject& gameObject, GameManager& gameManager, float deltaTime) = 0;
};
#endif

