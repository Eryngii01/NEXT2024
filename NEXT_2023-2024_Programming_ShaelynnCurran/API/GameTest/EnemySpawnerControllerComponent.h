#ifndef _ENEMYSPAWNERCONTROLLERCOMPONENT_H
#define _ENEMYSPAWNERCONTROLLERCOMPONENT_H

#include "ControllerComponent.h"
#include "GameObject.h"
#include "Level.h"

//*******************************************************************************************
// EnemySpawnerControllerComponent
//*******************************************************************************************
/* A controller component used to spawn enemies in certain increments of time. Adjusts the
 * increments of time according to the GameManager difficulty settings. */
class EnemySpawnerControllerComponent : public ControllerComponent {

public:
    explicit EnemySpawnerControllerComponent(int new_id, bool is_active, Level* level) :
        ControllerComponent(new_id, is_active), _level(level), _timeCounter(0.0f), _timeToSpawn(5000.0f) {}

    void Update(GameObject& gameObject, GameManager& gameManager, float deltaTime) override;

private:
    Level* _level;
    float _timeCounter, _timeToSpawn;
};
#endif