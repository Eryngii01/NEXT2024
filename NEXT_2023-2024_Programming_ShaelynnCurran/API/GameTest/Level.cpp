#include "stdafx.h"
#include "Level.h"

#include "GameObjectFactory.h"
#include "PhysicsEngine.h"

#pragma region Application Control Flow

LevelState Level::Update(float deltaTime) const {

    if (this->_state == LevelState::LEVEL_ACTIVE) {

        // Process Player Input and AI.
        for (const auto controllerComp : _controllerComponents) {
            controllerComp->Update(this->_gameObjects[controllerComp->ID], this->_gameManager, deltaTime);
        }

        // Update physics
        // First, update the static physics components that won't need to resolve collisions
        int index = 0;
        for (int i = 0; i < this->_numStaticPhysicsComponents; i++) {
            index++;
            const auto physicsComp = this->_physicsComponents[i];

            physicsComp->Update(this->_gameObjects[physicsComp->ID], this->_gameManager, deltaTime);
        }

        // Then, update the physics components that must resolve collisions between others by checking backwards to
        // avoid repeated checks
        for (int i = index; i < this->_numPhysicsComponents; i++) {
            const auto physicsComp = this->_physicsComponents[i];
            GameObject& gameObject = this->_gameObjects[physicsComp->ID];

            physicsComp->Update(gameObject, this->_gameManager, deltaTime);
            PhysicsEngine::ResolveCollisions(_gameObjects, gameObject, physicsComp, _physicsComponents, i);
        }

        // Update animations
        for (const auto rendererComp : _rendererComponents) {
            rendererComp->Update(this->_gameObjects[rendererComp->ID], deltaTime);
        }

    }
    else {
        // Only process UI controller input
        for (const auto controllerComp : _controllerComponents) {
            if (controllerComp->ID != _uiControllerID) continue;

            controllerComp->Update(this->_gameObjects[_uiControllerID], this->_gameManager, deltaTime);
        }

        // Update graphics
        for (const auto rendererComp : _rendererComponents) {
            rendererComp->Update(this->_gameObjects[rendererComp->ID], deltaTime);
        }
    }

    return _state;
}

void Level::Render() const {

    for (const auto rendererComp : _rendererComponents) {
        rendererComp->Render(this->_gameObjects[rendererComp->ID], this->_isDebugMode);
    }
}

#pragma endregion

#pragma region Exposed Object Pooling Methods

void Level::TakeEnemyFromPool(const Vector3 position, int lane, const float movementSpeed, ColorTag color) const {

    for (const auto gameObjID : _enemyPool) {
        GameObject& gameObject = _gameObjects[gameObjID];

        // Find an inactive GameObject to set active with new data
        if (gameObject.numActiveComponents > 0) continue;

        // Reset the position and update movementSpeed of the enemy
        gameObject.transform.position = position;
        std::vector<int> laneNum = { lane };
        std::vector<float> speed = { movementSpeed };

        gameObject.Enable();

        const auto physics = gameObject.physicsComp;
        physics->SetData(_gameManager, laneNum, speed);

        // NOTE: This is absolutely horrendous for DE&I and sprites themselves should be distinguishable;
        // differences should not only rely on a change of color, but for lack of time...I'm sorry :(

        // Set enemy color
        const auto renderer = gameObject.rendererComp;

        if (color != ColorTag::NONE) {
            std::vector<int> colorType = { static_cast<int>(color) };
            physics->SetData(_gameManager, colorType);
            renderer->SetData(_gameManager, colorType);
        }
        else {
            physics->SetData(_gameManager);
            renderer->SetData(_gameManager);
            _gameManager.ReshuffleEnemyColor();
        }

        gameObject.numActiveComponents = 3;
        return;
    }
}

void Level::TakeProjectileFromPool(const Vector3 position, const float velocityY) const {

    for (const auto gameObjID : _projectilePool) {
        GameObject& gameObject = _gameObjects[gameObjID];

        // Find an inactive GameObject to set active with new data
        if (gameObject.numActiveComponents > 0) continue;

        // Reset the position and update velocity of the projectile
        gameObject.transform.position = position;
        std::vector<float> velocity = { velocityY };

        gameObject.Enable();

        const auto physics = gameObject.physicsComp;
        physics->SetData(_gameManager, velocity);

        // NOTE: This is absolutely horrendous for DE&I and sprites themselves should be distinguishable;
        // differences should not only rely on a change of color, but for lack of time...I'm sorry :(

        // Set projectile color
        std::vector<Vector3> color = { _gameManager.GetProjectileColor() };

        const auto renderer = gameObject.rendererComp;
        renderer->SetData(_gameManager);

        gameObject.numActiveComponents = 2;

        // Update the projectile UI to reflect the newly selected projectile color
        _gameManager.ReshuffleProjectileColor();
        _gameObjects[_uiProjectileID].rendererComp->SetData(_gameManager);

        return;
    }
}

void Level::TakeScorePopupFromPool(const Vector3 position, const int score) const {

    for (const auto gameObjID : _scorePopupPool) {
        GameObject& gameObject = _gameObjects[gameObjID];

        // Find an inactive GameObject to set active with new data
        if (gameObject.numActiveComponents > 0) continue;

        gameObject.Enable();

        // Reset the position of the popup text
        std::vector<Vector2> newPosition = { Vector2(position.x, position.y) };
        std::vector<std::string> pointsEarned = { std::to_string(score) };

        // Set the popup text
        const auto renderer = gameObject.rendererComp;
        renderer->SetData(_gameManager, pointsEarned);
        renderer->SetData(newPosition);

        gameObject.numActiveComponents = 1;

        return;
    }
}

#pragma endregion

#pragma region Game State

void Level::SwitchLanes(int directionalChange) const {

    auto lane = _gameManager.currentLane + directionalChange;
    lane = lane < 0 ? 2 : lane;
    lane = lane % 3;

    _gameManager.currentLane = lane;

    // Directly manipulate the position of the lane highlighter based on the lane number
    const auto rendererComp = _rendererComponents[1];
    const auto id = rendererComp->ID;

    _gameObjects[id].transform.position.y = 64.0f * (lane + 1);

    // Mark the rendererComp dirty to update itself
    _gameObjects[id].isDirty = true;
}

void Level::LoseLife() {
    const auto remainingLives = _gameManager.LoseLife();
    const auto livesRenderer = _gameObjects[_livesID].rendererComp;

    std::vector<int> lives = { remainingLives };
    livesRenderer->SetData(_gameManager, lives);

    if (remainingLives > 0) return;

    // Once the player has lost all lives, invoke game over
    LoseLevel();
}

void Level::DefeatEnemy(const PhysicsComponent* enemyCollider, int ID, int pointMultiplier) const {
    // Calculate the points earned and update corresponding UI
    const auto pointsEarned = 100 * pointMultiplier;
    const auto score = _gameManager.EarnPoints(pointsEarned);
    const auto scoreRenderer = _gameObjects[_scoreID].rendererComp;

    std::vector<std::string> currentScore = { std::to_string(score) };
    scoreRenderer->SetData(_gameManager, currentScore);

    const GameObject& defeatedEnemy = _gameObjects[ID];

    // Spawn score popup
    const auto defeatedEnemyPos = defeatedEnemy.transform.position;
    const auto popupPosition = Vector3(defeatedEnemyPos.x, defeatedEnemyPos.y + 20.0f, 0.0f);
    TakeScorePopupFromPool(popupPosition, pointsEarned);

    // Check for other enemies to defeat
    PhysicsEngine::ChainEnemyCollisions(pointMultiplier, defeatedEnemy, enemyCollider, _gameObjects, _physicsComponents);
}

#pragma endregion

#pragma region Level Sequencing

void Level::LoseLevel() {

    this->_state = LevelState::LEVEL_OVER;

    // Enable the UI controller
    _gameObjects[_uiControllerID].Enable();

    for (auto gameObject : _gameObjects) {
        gameObject.DisableRenderer();
    }

    // -> Create game over UI text
    const std::vector<std::string> messages = { "GAME OVER", "FINAL SCORE", std::to_string(_gameManager.score) };
    const std::vector<Vector2> messagePositions = { Vector2(APP_VIRTUAL_WIDTH * 0.450f, APP_VIRTUAL_HEIGHT * 0.6f),
                                                    Vector2(APP_VIRTUAL_WIDTH * 0.443f, APP_VIRTUAL_HEIGHT * 0.5f),
                                                    Vector2(APP_VIRTUAL_WIDTH * 0.46f, APP_VIRTUAL_HEIGHT * 0.45f) };
    GameObjectFactory::CreateTextUI(_numGameObjects, _gameObjects, _rendererComponents,
        3, Vector3(1.0f, 1.0f, 1.0f), messages, messagePositions);
}

void Level::NextLevel() {
    this->_state = LevelState::LEVEL_DESTROY;
}

#pragma endregion

#pragma region Level Building

LevelState Level::LoadTitle() {

    // -> Create UI text and corresponding positions for the title screen
    const std::vector<std::string> messages = { "SLIME WARS", "Press A to Begin" };
    const std::vector<Vector2> messagePositions = { Vector2(APP_VIRTUAL_WIDTH * 0.440f, APP_VIRTUAL_HEIGHT * 0.7f),
                                                    Vector2(APP_VIRTUAL_WIDTH * 0.43f, APP_VIRTUAL_HEIGHT * 0.5f) };
    GameObjectFactory::CreateTextUI(_numGameObjects, _gameObjects, _rendererComponents,
        2, Vector3(1.0f, 1.0f, 1.0f), messages, messagePositions);

    // -> Level sequence controller
    GameObjectFactory::CreateUIController(this, _numGameObjects, _gameObjects,
        _controllerComponents, true);

    _state = LevelState::LEVEL_ACTIVE;
    return this->_state;
}

LevelState Level::LoadCredits() {

    // -> Create UI text and corresponding positions for the credits screen
    const std::vector<std::string> messages = { "Thank You for Playing!",
        "I hope you enjoyed it! :)", "The credits for the artwork I used can be found in the documentation!" };
    const std::vector<Vector2> messagePositions = { Vector2(APP_VIRTUAL_WIDTH * 0.42f, APP_VIRTUAL_HEIGHT * 0.6f),
                                                    Vector2(APP_VIRTUAL_WIDTH * 0.415f, APP_VIRTUAL_HEIGHT * 0.5f),
                                                    Vector2(APP_VIRTUAL_WIDTH * 0.25f, APP_VIRTUAL_HEIGHT * 0.4f) };
    GameObjectFactory::CreateTextUI(_numGameObjects, _gameObjects, _rendererComponents,
        3, Vector3(1.0f, 1.0f, 1.0f), messages, messagePositions);

    // -> Level sequence controller
    GameObjectFactory::CreateUIController(this, _numGameObjects, _gameObjects,
        _controllerComponents, true);

    _state = LevelState::LEVEL_ACTIVE;
    return this->_state;
}

LevelState Level::LoadLevel() {
    // Create the level background -> This will exist for as long as the level exists
    GameObjectFactory::CreateBackground(_numGameObjects, _gameObjects, _rendererComponents,
        Vector3(APP_VIRTUAL_WIDTH / 2, APP_VIRTUAL_HEIGHT / 2, 0));

    // Create the lane selector -> TODO: this is a static collider for projectiles to hit
    GameObjectFactory::CreateLaneSelector(_numGameObjects,
        _gameObjects, _rendererComponents,
        Vector3(620.f, 128.0f, 0));

    // NOTE: These will be pooled for reuse

    // -> Create projectiles; max of 10 on the screen at any given time
    for (int i = 0; i < 10; i++) {
        GameObjectFactory::CreateProjectile(_gameManager, _numGameObjects,
            _numStaticPhysicsComponents, _gameObjects, _projectilePool, _physicsComponents, _rendererComponents,
            Vector3(0.f, 0.f, 0.f), Vector2(15.0f, 15.0f), false);
    }

    // Here begins the GameObjects (with physics components) that will resolve collisions between the previous ones
    // NOTE: Projectiles are not "static" but the enemies will take care of their collision resolution
    _numPhysicsComponents = _numStaticPhysicsComponents;

    // -> Create AI-powered enemies; max of 100 in the scene at any given time
    for (int i = 0; i < 100; i++) {
        GameObjectFactory::CreateEnemy(this, _gameManager, _numGameObjects, _numPhysicsComponents,
            _gameObjects, _enemyPool, _controllerComponents, _physicsComponents, _rendererComponents,
            Vector3(0.0f, 0.0f, 0.0f), Vector2(30, 30), false);
    }

    // Lastly (for non-utility GameObjects), create the player to ensure that the PlayerPhysicsComponent will be
    // handling the final collision detection after all other GameObjects have been updated
    /* This is slightly nuanced where in cases in which the enemy collides with both the projectile and player, the
    * collision between the projectile and enemy will be handled first
    */
    _playerID = _numGameObjects;

    GameObjectFactory::CreatePlayer(this, _numGameObjects, _numPhysicsComponents,
        _gameObjects, _controllerComponents, _physicsComponents, _rendererComponents,
        Vector3(APP_VIRTUAL_WIDTH / 16, APP_VIRTUAL_HEIGHT / 5, _gameManager.targetZPos[1]),
        Vector2(20, 140));

    // Here begins the construction of utility GameObjects to run the game

    _uiControllerID = _numGameObjects;

    // -> Level sequence controller
    GameObjectFactory::CreateUIController(this, _numGameObjects, _gameObjects,
        _controllerComponents, false);

    // -> Create spawners
    GameObjectFactory::CreateEnemySpawner(this, _numGameObjects, _gameObjects, _controllerComponents);

    // Create UI last to be rendered over everything else

    // -> Create text UI popups to be pooled for use upon enemy deaths. About 30 should do
    for (int i = 0; i < 30; i++) {
        const std::vector<std::string> popupMessages = { "0" };
        const std::vector<Vector2> popupMessagePositions = { Vector2(0.0f, 0.0f) };
        GameObjectFactory::CreateTextPopupUI(_numGameObjects, _gameObjects, _scorePopupPool,
            _rendererComponents, 1, Vector3(0.0f, 0.0f, 0.0f),
            popupMessages, popupMessagePositions, false);
    }

    // -> Create text UI for the game
    // Create UI text and corresponding positions
    const std::vector<std::string> messages = { "Score: ", "Next: " };
    const std::vector<Vector2> messagePositions = { Vector2(APP_VIRTUAL_WIDTH * 0.75f, APP_VIRTUAL_HEIGHT * 0.93f),
                                                    Vector2(APP_VIRTUAL_WIDTH * 0.02f, APP_VIRTUAL_HEIGHT * 0.03f) };
    GameObjectFactory::CreateTextUI(_numGameObjects, _gameObjects, _rendererComponents,
        2, Vector3(0.0f, 0.0f, 0.0f), messages, messagePositions);

    _livesID = _numGameObjects;

    // -> Create lives UI
    GameObjectFactory::CreateRepeatedImageUI(_numGameObjects, _gameObjects, _rendererComponents,
        Vector3(APP_VIRTUAL_WIDTH * 0.05f, APP_VIRTUAL_HEIGHT * 0.93f, 0.0f),
        Vector2(APP_VIRTUAL_WIDTH * 0.08f, 0.0f), _gameManager.GetPlayerLives());

    _scoreID = _numGameObjects;

    // -> Create score UI
    const std::vector<std::string> score = { "0" };
    const std::vector<Vector2> scorePosition = { Vector2(APP_VIRTUAL_WIDTH * 0.9f, APP_VIRTUAL_HEIGHT * 0.93f) };

    GameObjectFactory::CreateTextUI(_numGameObjects, _gameObjects, _rendererComponents,
        1, Vector3(0.0f, 0.0f, 0.0f), score, scorePosition);

    // -> Create the next projectile UI sprite
    _uiProjectileID = _numGameObjects;

    GameObjectFactory::CreateNextProjectileTypeUI(_numGameObjects, _gameObjects, _rendererComponents,
        Vector3(APP_VIRTUAL_WIDTH * 0.11f, APP_VIRTUAL_HEIGHT * 0.038f, 0.0f), 2.0);

    _state = LevelState::LEVEL_ACTIVE;
    return this->_state;
}

#pragma endregion
