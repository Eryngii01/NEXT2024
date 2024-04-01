#ifndef _PLAYERCONTROLLERCOMPONENT_H
#define _PLAYERCONTROLLERCOMPONENT_H

#include "ControllerComponent.h"
#include "GameObject.h"
#include "Level.h"

//*******************************************************************************************
// EnemyControllerComponent
//*******************************************************************************************
/* Implements the controller component to handle player input. */
class PlayerControllerComponent : public ControllerComponent {

public:
    explicit PlayerControllerComponent(int new_id, bool is_active, Level* level) :
        ControllerComponent(new_id, is_active), _level(level) {}

    void Update(GameObject& gameObject, GameManager& gameManager, float deltaTime) override;

private:
    Level* _level;
};
#endif