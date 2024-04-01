#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

#include <vector>

#include "Vector.h"

//*******************************************************************************************
// GameManager
//*******************************************************************************************
/* Data storage to communicate/update the state of the game to all components and Level. */

class GameManager {

public:
    GameManager(float backZPos, float centralZPos, float frontZPos) : score(0), currentLane(1),
        currentEnemySpeed(0.2f), maxEnemySpeed(3.0f), targetZPos({ frontZPos, centralZPos, backZPos }),
        _nextProjectileColor(0), _nextEnemyColor(0), _playerLives(3), _nextScoreCap(15000),
        _maxColorIndex(2), _totalAvailableColors(5) {

        _availableColors = {
            Vector3(1.0f, 1.0f, 1.0f), // Green
            Vector3(1.0f, 0.3f, 0.3f), // Red
            Vector3(0.3f, 0.3f, 1.0f), // Blue
            Vector3(1.0f, 0.3f, 1.0f), // Purple
            Vector3(0.3f, 0.3f, 0.3f) // Grey
        };
    }

    //===========================================================================================
    // Getters/Setters
    //===========================================================================================
#pragma region Getters/Setters

    int EarnPoints(int amount);

    int GetPlayerLives() const;

    int LoseLife();

    Vector3 GetColorByIndex(int index) const;

    int GetProjectileColorIndex() const;
    Vector3 GetProjectileColor() const;
    void ReshuffleProjectileColor() const;

    int GetEnemyColorIndex() const;
    Vector3 GetEnemyColor() const;
    void ReshuffleEnemyColor() const;

#pragma endregion

    int score, currentLane;
    float currentEnemySpeed, maxEnemySpeed;

    std::vector<float> targetZPos;

    mutable int _nextProjectileColor, _nextEnemyColor;

private:
    void IncreaseDifficulty();

    int _playerLives;
    int _nextScoreCap;

    // Begin with two max projectile colors
    int _maxColorIndex, _totalAvailableColors;
    std::vector<Vector3> _availableColors;
};
#endif
