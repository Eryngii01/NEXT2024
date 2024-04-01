#include "stdafx.h"
#include "EnemySpawnerControllerComponent.h"

#include "Mathf.h"

void EnemySpawnerControllerComponent::Update(GameObject& gameObject, GameManager& gameManager, float deltaTime) {
    if (!this->isEnabled) return;

    _timeCounter += deltaTime;

    if (_timeCounter > _timeToSpawn) {
        // Spawn an entire row at once
        for (int i = 0; i < 3; i++) {
            _level->TakeEnemyFromPool(Vector3(APP_VIRTUAL_WIDTH + 30.0f, 64.0f * (i + 1),
                gameManager.targetZPos[i]), i, gameManager.currentEnemySpeed);
        }

        _timeCounter = 0.0f;

        // Adjust timer according to the enemy speed
        _timeToSpawn = 2800.0f - Mathf::Lerp(0.0f, 2600.0f, gameManager.currentEnemySpeed / gameManager.maxEnemySpeed);
    }
}
