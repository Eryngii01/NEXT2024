#include "stdafx.h"
#include "GameManager.h"

#include "App/app.h"

#pragma region Getters/Setters

int GameManager::EarnPoints(int amount) {
    this->score += amount;

    if (score > _nextScoreCap) IncreaseDifficulty();

    return score;
}

int GameManager::GetPlayerLives() const {
    return _playerLives;
}

int GameManager::LoseLife() {
    _playerLives--;

    return _playerLives;
}

Vector3 GameManager::GetColorByIndex(int index) const {
    if (index < 0 || index > _totalAvailableColors - 1) return _availableColors[0];

    return _availableColors[index];
}

int GameManager::GetProjectileColorIndex() const {
    return _nextProjectileColor;
}

Vector3 GameManager::GetProjectileColor() const {
    return _availableColors[_nextProjectileColor];
}

void GameManager::ReshuffleProjectileColor() const {
    _nextProjectileColor = rand() % (_maxColorIndex + 1 - 0) + 0;
}

int GameManager::GetEnemyColorIndex() const {
    return _nextEnemyColor;
}

Vector3 GameManager::GetEnemyColor() const {
    return _availableColors[_nextEnemyColor];
}

void GameManager::ReshuffleEnemyColor() const {
    _nextEnemyColor = rand() % (_maxColorIndex + 1 - 0) + 0;
}

#pragma endregion

void GameManager::IncreaseDifficulty() {
    const auto randChoice = rand() % (4 - 0) + 0;

    if (randChoice == 2 && _maxColorIndex < _totalAvailableColors - 1) {
        // Increase the color types available to spawn -> makes it harder to chain combos
        _maxColorIndex = min(_maxColorIndex + 1, _totalAvailableColors);
        _nextScoreCap += 20000;
        return;
    }

    // Otherwise, increase the enemy speed unless it is already maxed out
    currentEnemySpeed = min(currentEnemySpeed + 0.05f, maxEnemySpeed);
    _nextScoreCap += 15000;
}
