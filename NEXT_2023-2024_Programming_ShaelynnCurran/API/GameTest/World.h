#ifndef _WORLD_H
#define _WORLD_H

#include "Level.h"

//*******************************************************************************************
// World
//*******************************************************************************************
/* The World class oversees the entire game process, storing and managing all the Levels
 * within the game, delegating the application update() and render() functions to the
 * individual levels to manage their gameObject data.
 * Cycles through Levels like a flipbook.
 */

class World {

public:
    explicit World() : _currentLevel(0), _totalLevels(1), _totalLoadedLevels(1), _isOnReplay(false) {
        // TODO: Change this to load the title level
        this->LoadTitleLevel();
    }

    ~World() {
        delete this->_level;
    }

    // TODO: Define a copy constructor, copy assignment operator, etc. depending on whether or not I will
    // come to need any of these in the future...

    //===========================================================================================
    // Application Delegation
    //===========================================================================================
#pragma region Application Delegation

    // A method to delegate the update functionality for all the gameObjects to the current active level.
    void Update(const float deltaTime);

    // A method to delegate the render functionality for all the existing gameObjects to the current active
    // level.
    void Render() const;

#pragma endregion

private:
    //===========================================================================================
    // Level Sequencing/Bookkeeping
    //===========================================================================================
#pragma region Level Sequencing/Bookkeeping

    // Keep only one level in memory at a time to prevent a waste of memory

    // The max levels can be defined by the macro MAX_LEVELS, dictating how many levels can be created
    // by parsing the Level<#>.txt files found in the project Assets folder. 
    Level* _level;

    int _levelIndexes[1];
    // Metadata to ensure correct traversal to find the level design assets.
    int _currentLevel, _totalLevels, _totalLoadedLevels;
    bool _isOnReplay;

    void LoadTitleLevel();

    void LoadCreditsLevel();

    void LoadLevel();

    // A method to be called from the application initialization function. Initializes all the level classes
    // and stores them as metadata before beginning the game.
    void LoadNextLevel();

#pragma endregion

};
#endif

