#ifndef _ENEMYPHYSICSCOMPONENT_H
#define _ENEMYPHYSICSCOMPONENT_H

#include "Level.h"
#include "PhysicsComponent.h"

//*******************************************************************************************
// EnemyPhysicsComponent
//*******************************************************************************************
// Implementation of PhysicsComponent for the enemy GameObject

class EnemyPhysicsComponent : public PhysicsComponent {

public:
    explicit EnemyPhysicsComponent(int newID, bool isActive, ColorTag newTag, Level* level) :
        PhysicsComponent(newID, isActive, newTag), _movementSpeed(0), _zPos(0), _onZPosChanged(false),
        _comboMultiplier(1), _level(level) {}

    void Update(GameObject& gameObject, GameManager& gameManager, const float deltaTime) override;
    void OnCollision(GameObject& gameObject, ObjectType otherTag, ColorTag otherColor) override;

    //===========================================================================================
    // Object Pooling
    //===========================================================================================
#pragma region Object Pooling

    // For setting combo multipliers
    void SetData(std::vector<int>& args) override;
    // For getting the color associated with this enemy from the GameManager; Used for when enemies get newly spawned
    void SetData(GameManager& gameManager) override;
    // For getting the color associated with this enemy; Used for when a projectile "turns" into an enemy
    void SetData(GameManager& gameManager, std::vector<int>& args) override;
    // For resetting movement bookkeeping when an enemy is newly spawned
    void SetData(GameManager& gameManager, std::vector<int>& intArgs, std::vector<float>& floatArgs) override;

#pragma endregion

private:
    float _movementSpeed;
    float _zPos;
    bool _onZPosChanged;

    int _comboMultiplier;

    Level* _level;

};
#endif
