#ifndef _ENEMYCONTROLLERCOMPONENT_H
#define _ENEMYCONTROLLERCOMPONENT_H

#include "ControllerComponent.h"
#include "GameObject.h"

//*******************************************************************************************
// EnemyControllerComponent
//*******************************************************************************************
/* Handles enemy AI. */
class EnemyControllerComponent : public ControllerComponent {

public:
    explicit EnemyControllerComponent(int new_id, bool is_active) :
        ControllerComponent(new_id, is_active) {}

    void Update(GameObject& gameObject, GameManager& gameManager, float deltaTime) override;
};
#endif