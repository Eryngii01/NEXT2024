#include "stdafx.h"
#include "World.h"

#pragma region Application Delegation

void World::Update(const float deltaTime) {

    const LevelState levelStatus = this->_level->Update(deltaTime);

    // The level has finished, fetch the next one if there are anymore.
    const auto currentLevel = this->_currentLevel;
    const auto levelCount = this->_totalLevels;

    if (levelStatus == LevelState::LEVEL_DESTROY || levelStatus == LevelState::LEVEL_LOAD_FAILED) {
        delete this->_level;

        if (currentLevel > levelCount - 1) {
            // Load the credits level if all the available levels have been parsed
            LoadCreditsLevel();
        }
        else if (currentLevel < 0) {
            // Allow the game to be replayed; once the credits level has been loaded, the title screen will be loaded again.

            // _isOnReplay will prevent the "failed" levels from being loaded again to save time and recreate the same 
            // gameplay experience (If one happens to add new level files while the application is running).
            this->_isOnReplay = true;
            this->_totalLevels = this->_totalLoadedLevels;
            LoadTitleLevel();
        }
        else {
            LoadLevel();
        }
    }
}

void World::Render() const {

    this->_level->Render();
}

#pragma endregion

#pragma region Level Sequencing/Bookkeeping

void World::LoadTitleLevel() {

    this->_level = new Level(0);
    this->_currentLevel = 0;
}

void World::LoadCreditsLevel() {

    this->_level = new Level(2);
    this->_currentLevel = -1;
}

void World::LoadLevel() {

    this->_level = new Level(1);
    this->_currentLevel++;
}

// Deprecated; for loading a sequence of levels by file
void World::LoadNextLevel() {

    const auto currentLevel = this->_currentLevel;
    auto nextLevelNum = this->_currentLevel + 1;
    auto registerOnLevelLoad = true;

    if (this->_isOnReplay) {
        registerOnLevelLoad = false;
        nextLevelNum = _levelIndexes[currentLevel];
    }

    const std::string filename = R"(.\Assets\LevelData\Level)" + std::to_string(nextLevelNum) + ".txt";
    this->_level = new Level(1, filename.c_str());

    // If the level load has failed, then try again the next frame
    if (this->_level->GetState() == LevelState::LEVEL_LOAD_FAILED && registerOnLevelLoad) {
        this->_totalLoadedLevels--;
    }
    else if (registerOnLevelLoad) {
        this->_levelIndexes[currentLevel] = nextLevelNum;
    }

    this->_currentLevel++;
}

#pragma endregion
