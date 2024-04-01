#ifndef _LEVEL_H
#define _LEVEL_H

//------------------------------------------------------------------------
#include <vector>
//------------------------------------------------------------------------
#include "GameObject.h"
#include "ControllerComponent.h"
#include "PhysicsComponent.h"
#include "RendererComponent.h"

// Represents the current state of the level
enum class LevelState {
    LEVEL_LOADING,
    LEVEL_LOAD_FAILED,
    LEVEL_ACTIVE,
    LEVEL_OVER,
    LEVEL_DESTROY
};

//*******************************************************************************************
// Level
//*******************************************************************************************
/* Represents a single level within a game. Holds and manages all the GameObjects and
 * their components, handling the delegation of application update() and render()
 * functions to apply to the GameObjects to bring the game to life. Also communicates
 * its state to the World class on update to facilitate level loads (for parsing).
* Takes care of all deallocation of GameObjects via deletion of the World class.
*/
class Level {

public:
    explicit Level(const int levelType, const char* filename = "") :
        _state(LevelState::LEVEL_LOADING), _gameManager(0.0f, 100.0f, 200.0f),
        _numGameObjects(0), _playerID(0), _uiControllerID(0), _uiProjectileID(0), _livesID(0), _scoreID(0),
        _numStaticPhysicsComponents(0), _numPhysicsComponents(0) {

        switch (levelType) {
        case 0:
            // Title screen
            this->_state = this->LoadTitle();
            break;
        case 1:
            // A regular level type
            this->_state = this->LoadLevel();
            break;
        case 2:
            // Generate the credits screen
            this->_state = this->LoadCredits();
            break;
        default:
            // A regular level type
            this->_state = this->LoadLevel();
            break;
        }
    }

    ~Level() {
        // Manually deallocate vector elements
        for (const auto rendererComp : _rendererComponents) {
            delete rendererComp;
        }

        for (const auto physicsComp : _physicsComponents) {
            delete physicsComp;
        }

        for (const auto controllerComp : _controllerComponents) {
            delete controllerComp;
        }
    }

    //===========================================================================================
    // Application Control Flow
    //===========================================================================================
    /* Methods for handling delegated application tasks, such as updating and rendering
    * GameObjects.
    */
#pragma region Application Control Flow

    LevelState Update(const float deltaTime) const;
    void Render() const;

#pragma endregion

    //===========================================================================================
    // Getters/Setters
    //===========================================================================================
    /* Method declarations are also included here for ease of readability and since these are
    * concise.
    */
#pragma region Getters/Setters

    LevelState GetState() const {
        return this->_state;
    }

    void SetDebugMode(const bool value) const {
        this->_isDebugMode = value;
    }

#pragma endregion

    //===========================================================================================
    // Exposed Object Pooling Methods
    //===========================================================================================
    /* Methods for handling delegated application tasks, such as updating and rendering
    * GameObjects.
    */
#pragma region Exposed Object Pooling Methods

    void TakeEnemyFromPool(const Vector3 position, int lane, const float movementSpeed, ColorTag color = ColorTag::NONE) const;
    void TakeProjectileFromPool(const Vector3 position, const float velocityY) const;
    void TakeScorePopupFromPool(const Vector3 position, const int score) const;

#pragma endregion

    //===========================================================================================
    // Game State
    //===========================================================================================
#pragma region Game State

    void SwitchLanes(int directionalChange) const;
    void LoseLife();
    void DefeatEnemy(const PhysicsComponent* enemyCollider, int ID, int pointMultiplier) const;

#pragma endregion

private:
    mutable bool _isDebugMode;

    //===========================================================================================
    // Level Sequencing
    //===========================================================================================
    /* Works closely with Application Control Flow to provide levels with a state, supporting
    * winning and losing conditions and level statuses to communicate to World when a level
    * should be restarted or progressed.
    */
#pragma region Level Sequencing

    LevelState _state;

public:
    void NextLevel();

private:
    void LoseLevel();

#pragma endregion

    //===========================================================================================
    // GameObject/Component Bookkeeping
    //===========================================================================================
    /* Stores and manages all GameObjects and their components associated with this particular
    * in-game level to pass to the Application Control Flow member functions for updates.
    * GameObject components that must be updated every frame will be stored contiguously to
    * optimize performance (avoid CPU thrashing).
    */
#pragma region GameObject/Component Bookkeeping

    mutable GameManager _gameManager;

    mutable std::vector<GameObject> _gameObjects;

    /* Support polymorphism flexibility at the cost of data locality */
    std::vector<ControllerComponent*> _controllerComponents;
    std::vector<PhysicsComponent*> _physicsComponents;
    std::vector<RendererComponent*> _rendererComponents;

    // Used for issuing newly instantiated gameObjects their unique ID number to link their associated components as
    // a loose, but single package
    int _numGameObjects;
    int _playerID, _uiControllerID, _uiProjectileID, _livesID, _scoreID;

    // Physics system will handled by separating the update logic of the physics components
    int _numStaticPhysicsComponents, _numPhysicsComponents;

#pragma endregion

    //===========================================================================================
    // Object Pooling
    //===========================================================================================
#pragma region Object Pooling

    // Pools are used to collect the ids of gameObjects to make GameObject search easy. Should be
    // fairly cheap since random access for vectors is a O(1) operation

    // NOTE: Here the IDs will all be in sequential order because of the static initialization process,
    // but if this game were to be read from a file, they wouldn't necessarily be in order

    std::vector<int> _projectilePool, _enemyPool, _scorePopupPool;

#pragma endregion

    //===========================================================================================
    // Level Building
    //===========================================================================================
    /* Handles the creation of all level GameObjects from file parsing to completed GameObjects
    * of various types (i.e. UI, Physics-based, Controller-based via player input or AI, etc.)
    */
#pragma region Level Building

    LevelState LoadTitle();
    LevelState LoadCredits();
    LevelState LoadLevel();

#pragma endregion

};
#endif

