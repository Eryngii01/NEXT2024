#include "stdafx.h"
#include "ProjectilePhysicsComponent.h"

#include "Mathf.h"

void ProjectilePhysicsComponent::Update(GameObject& gameObject, GameManager& gameManager, const float deltaTime) {
    if (!this->isEnabled) return;

    const auto position = gameObject.transform.position;
    velocity.y += _gravity;

    // Movement through a set velocity
    gameObject.transform.position.x += _speed;
    gameObject.transform.position.y += velocity.y * _speed;

    if (position.y < -12.0f) {
        // The gameObject fell out of bounds; disable it to add it back into the pool
        gameObject.Disable();
        return;
    }

    if (!_isTicking) return;

    _timeCounter += deltaTime;

    // Only run the timer once until this gameObject is enabled again
    if (_timeCounter > _timeToTargetZ) {
        _timeCounter = _timeToTargetZ;
        _isTicking = false;
    }

    // Scroll directly down
    const auto zPos = Mathf::Lerp(position.z, _targetZPos, _timeCounter / _timeToTargetZ);
    gameObject.transform.position.z = zPos;
}

void ProjectilePhysicsComponent::OnCollision(GameObject& gameObject, ObjectType otherTag, ColorTag otherColor) {
    // Projectiles collide with enemies only and destroy themselves regardless of the outcome upon contact
    gameObject.Disable();
}

void ProjectilePhysicsComponent::SetData(GameManager& gameManager, std::vector<float>& args) {

    // Sanitize inputs; ensure that there are enough arguments to successfully set this component's velocity
    if (args.empty()) return;

    // Cache the current lane being targeting, since this can possibly change the next frame and we don't want
    // projectiles suddenly changing trajectory
    const auto targetLane = gameManager.currentLane;
    currentLane = targetLane;

    tag = static_cast<ColorTag>(gameManager.GetProjectileColorIndex());
    this->velocity.y = args[0] * 2.5f;
    this->_targetZPos = gameManager.targetZPos[targetLane];
    this->_isTicking = true;
    this->_timeCounter = 0.0f;
}
