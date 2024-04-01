#ifndef _GAMEOBJECTFACTORY_H
#define _GAMEOBJECTFACTORY_H

//------------------------------------------------------------------------
#include <vector>
//------------------------------------------------------------------------
#include "Level.h"
#include "GameObject.h"
#include "ControllerComponent.h"
#include "PhysicsComponent.h"
#include "RendererComponent.h"
//------------------------------------------------------------------------

//*******************************************************************************************
// GameObjectFactory
//*******************************************************************************************
// A class for maintaining the instantiations of GameObject types, containing factory
// methods to instantiate various types of GameObjects that will appear during gameplay.
class GameObjectFactory {

public:

    //===========================================================================================
    // Decoration GameObjects
    //===========================================================================================
#pragma region Decoration GameObjects

    static void CreateBackground(int& gameObjectCounter,
        std::vector<GameObject>& gameObjects, std::vector<RendererComponent*>& renderers,
        Vector3 position, bool isActive = true);

    static void CreateLaneSelector(int& gameObjectCounter,
        std::vector<GameObject>& gameObjects, std::vector<RendererComponent*>& renderers,
        Vector3 position, bool isActive = true);

#pragma endregion

    //===========================================================================================
    // Actor GameObjects
    //===========================================================================================
#pragma region Actor GameObjects

    static void CreateProjectile(const GameManager& gameManager, int& gameObjectCounter, int& physicsCounter,
        std::vector<GameObject>& gameObjects, std::vector<int>& gameObjectPool, std::vector<PhysicsComponent*>& physics,
        std::vector<RendererComponent*>& renderers, Vector3 position, Vector2 scale, bool isActive = true);

    static void CreateEnemy(Level* level, const GameManager& gameManager, int& gameObjectCounter,
        int& physicsCounter, std::vector<GameObject>& gameObjects, std::vector<int>& gameObjectPool,
        std::vector<ControllerComponent*>& controllers, std::vector<PhysicsComponent*>& physics,
        std::vector<RendererComponent*>& renderers, Vector3 position, Vector2 scale, bool isActive = true);

    static void CreatePlayer(Level* level, int& gameObjectCounter, int& physicsCounter,
        std::vector<GameObject>& gameObjects, std::vector<ControllerComponent*>& controllers,
        std::vector<PhysicsComponent*>& physics, std::vector<RendererComponent*>& renderers,
        Vector3 position, Vector2 scale, bool isActive = true);

#pragma endregion

    //===========================================================================================
    // Utility GameObjects
    //===========================================================================================
#pragma region Utility GameObjects

    static void CreateUIController(Level* level, int& gameObjectCounter,
        std::vector<GameObject>& gameObjects, std::vector<ControllerComponent*>& controllers, bool isActive = true);

    static void CreateEnemySpawner(Level* level, int& gameObjectCounter,
        std::vector<GameObject>& gameObjects, std::vector<ControllerComponent*>& controllers, bool isActive = true);

#pragma endregion

    //===========================================================================================
    // UI GameObjects
    //===========================================================================================
#pragma region UI GameObjects

    static void CreateTextUI(int& gameObjectCounter, std::vector<GameObject>& gameObjects,
        std::vector<RendererComponent*>& renderers, int numMessages, Vector3 textColor,
        const std::vector<std::string>& messages, const std::vector<Vector2>& messagePositions, bool isActive = true);

    static void CreateTextPopupUI(int& gameObjectCounter, std::vector<GameObject>& gameObjects,
        std::vector<int>& gameObjectPool, std::vector<RendererComponent*>& renderers, int numMessages, Vector3 textColor,
        const std::vector<std::string>& messages, const std::vector<Vector2>& messagePositions, bool isActive = true);

    static void CreateRepeatedImageUI(int& gameObjectCounter, std::vector<GameObject>& gameObjects,
        std::vector<RendererComponent*>& renderers, Vector3 position, Vector2 spaceBetweenSprites,
        int spriteCount, bool isActive = true);

    static void CreateNextProjectileTypeUI(int& gameObjectCounter,
        std::vector<GameObject>& gameObjects, std::vector<RendererComponent*>& renderers,
        Vector3 position, float scale, bool isActive = true);

#pragma endregion

};
#endif

