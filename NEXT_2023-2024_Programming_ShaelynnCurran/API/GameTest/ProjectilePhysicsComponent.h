#ifndef _PROJECTILEPHYSICSCOMPONENT_H
#define _PROJECTILEPHYSICSCOMPONENT_H

#include "PhysicsComponent.h"
#include "Level.h"

//*******************************************************************************************
// ProjectilePhysicsComponent
//*******************************************************************************************
/* Implementation to simulate a projectile physics object that moves in the direction
 * of a set velocity upon spawning. */
class ProjectilePhysicsComponent : public PhysicsComponent {

public:
    explicit ProjectilePhysicsComponent(int newID, bool isActive, ColorTag newTag,
        float gravityScale, float speedMultiplier, const Vector2 newScale, const Vector2 maxScale) :
        PhysicsComponent(newID, isActive, newTag), _gravity(GRAVITY* gravityScale), _speed(speedMultiplier),
        _isTicking(false), _targetZPos(0.0f), _timeCounter(0.0f), _timeToTargetZ(3000.0f) {

        _speed = speedMultiplier;

        _minScale.x = newScale.x;
        _minScale.y = newScale.y;
        _maxScale.x = maxScale.x;
        _maxScale.y = maxScale.y;
    }

    void Update(GameObject& gameObject, GameManager& gameManager, const float deltaTime) override;
    void OnCollision(GameObject& gameObject, ObjectType otherTag, ColorTag otherColor) override;

    //===========================================================================================
    // Object Pooling
    //===========================================================================================
#pragma region Object Pooling

    // For changing the projectile's color tag via the GameManager upon spawns
    void SetData(GameManager& gameManager, std::vector<float>& args) override;

#pragma endregion

private:
    float _gravity, _speed;

    bool _isTicking;
    float _targetZPos, _timeCounter, _timeToTargetZ;
    Vector2 _minScale, _maxScale;
};
#endif
