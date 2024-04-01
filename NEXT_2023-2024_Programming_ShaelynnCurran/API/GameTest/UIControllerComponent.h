#ifndef _UICONTROLLERCOMPONENT_H
#define _UICONTROLLERCOMPONENT_H

#include "ControllerComponent.h"
#include "GameObject.h"
#include "Level.h"

//*******************************************************************************************
// UIControllerComponent
//*******************************************************************************************
/* Accepts player input on an application level after the game has ended. Used for letting
 * the player switch/progress through levels.
 */
class UIControllerComponent : public ControllerComponent {

public:
    explicit UIControllerComponent(int new_id, bool is_active, Level* level) :
        ControllerComponent(new_id, is_active), _level(level) {}

    void Update(GameObject& gameObject, GameManager& gameManager, float deltaTime) override;

private:
    Level* _level;
};
#endif