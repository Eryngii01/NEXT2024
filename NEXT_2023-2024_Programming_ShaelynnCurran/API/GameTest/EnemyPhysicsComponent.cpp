#include "stdafx.h"
#include "EnemyPhysicsComponent.h"

void EnemyPhysicsComponent::Update(GameObject& gameObject, GameManager& gameManager, const float deltaTime) {
    if (!this->isEnabled) return;

    // Fetch the player input and move accordingly
    const Vector2 inputCoord = gameObject.input;
    Vector3& position = gameObject.transform.position;

    // Update the horizontal position of the object
    position.x += inputCoord.x * _movementSpeed;

    if (!_onZPosChanged) return;

    // Update the gameObject's zPos
    position.z = _zPos;
    _onZPosChanged = false;
}

void EnemyPhysicsComponent::OnCollision(GameObject& gameObject, ObjectType otherTag, ColorTag otherColor) {
    if (otherTag == ObjectType::PROJECTILE) {
        // Enemies collide with projectiles and assume different behaviour based on whether the colors match or not
        // Colors match: Destroy enemy and earn points; Don't match: Projectile turns into a new "enemy"
        if (tag != otherColor) {
            const auto position = gameObject.transform.position;

            _level->TakeEnemyFromPool(Vector3(position.x - 20.0f, position.y, position.z),
                currentLane, _movementSpeed, otherColor);

            return;
        }

        // Set this component inactive so that the adjacent enemy to be destroyed will not count this enemy
        gameObject.DisablePhysics();

        _level->DefeatEnemy(this, ID, _comboMultiplier);
        gameObject.Disable();

    }
    else if (otherTag == ObjectType::ENEMY) {
        // Chained enemy deaths only work if the enemies are of the same color
        if (tag != otherColor) {
            // Reset the combo multiplier and resume operation of the physics component
            gameObject.EnablePhysics();
            _comboMultiplier = 1;
            return;
        }

        // Sort of recursively chain enemy deaths
        // Set this component inactive so that the adjacent enemy to be destroyed will not count this enemy
        gameObject.DisablePhysics();

        _level->DefeatEnemy(this, ID, _comboMultiplier * 2);
        gameObject.Disable();

    }
    else if (otherTag == ObjectType::PLAYER) {
        // Enemies die upon contact with the player; an eye for an eye
        gameObject.Disable();
    }
}

void EnemyPhysicsComponent::SetData(std::vector<int>& args) {
    // Sanitize inputs
    if (args.empty()) return;

    _comboMultiplier = args[0];
}

void EnemyPhysicsComponent::SetData(GameManager& gameManager) {
    tag = static_cast<ColorTag>(gameManager.GetEnemyColorIndex());
}

void EnemyPhysicsComponent::SetData(GameManager& gameManager, std::vector<int>& args) {
    if (args.empty()) return;

    tag = static_cast<ColorTag>(args[0]);
}

void EnemyPhysicsComponent::SetData(GameManager& gameManager, std::vector<int>& intArgs, std::vector<float>& floatArgs) {
    // Sanitize inputs; ensure that there are enough arguments to successfully set this component's movement speed
    if (intArgs.empty() || floatArgs.empty()) return;

    const auto targetLane = gameManager.currentLane;

    currentLane = intArgs[0];
    _movementSpeed = floatArgs[0];
    _zPos = gameManager.targetZPos[targetLane];

    _comboMultiplier = 1;
}

