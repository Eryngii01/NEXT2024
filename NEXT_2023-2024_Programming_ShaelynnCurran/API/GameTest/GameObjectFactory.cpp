#include "stdafx.h"
#include "GameObjectFactory.h"

#include "BasicRendererComponent.h"
#include "EnemyControllerComponent.h"
#include "EnemyPhysicsComponent.h"
#include "EnemyRendererComponent.h"
#include "EnemySpawnerControllerComponent.h"
#include "LaneRendererComponent.h"
#include "PlayerControllerComponent.h"
#include "PlayerPhysicsComponent.h"
#include "PlayerRendererComponent.h"
#include "ProjectilePhysicsComponent.h"
#include "ProjectileRendererComponent.h"
#include "RepeatRendererComponent.h"
#include "UIControllerComponent.h"
#include "UIPopupRendererComponent.h"
#include "UITextRendererComponent.h"

#pragma region Decoration GameObjects

void GameObjectFactory::CreateBackground(int& gameObjectCounter, std::vector<GameObject>& gameObjects,
    std::vector<RendererComponent*>& renderers, Vector3 position, bool isActive) {

    const std::vector<std::string> spriteFiles = { R"(.\Assets\Art\Background\background.bmp)" };
    RendererComponent* rendererComp = new BasicRendererComponent(gameObjectCounter, isActive,
        spriteFiles, 0.f, 0.f, position);
    renderers.push_back(rendererComp);

    gameObjects.emplace_back(gameObjectCounter, isActive ? 1 : 0,
        false, false, true, ObjectType::DECORATION,
        position, Vector2(0.f, 0.f), rendererComp);

    gameObjectCounter++;
}

void GameObjectFactory::CreateLaneSelector(int& gameObjectCounter, std::vector<GameObject>& gameObjects,
    std::vector<RendererComponent*>& renderers, Vector3 position, bool isActive) {

    const std::vector<std::string> spriteFiles = { R"(.\Assets\Art\Background\lane_highlighter.bmp)" };
    RendererComponent* rendererComp = new LaneRendererComponent(gameObjectCounter, isActive, spriteFiles,
        0.f, 0.f, position);
    renderers.push_back(rendererComp);

    gameObjects.emplace_back(gameObjectCounter, isActive ? 1 : 0,
        false, false, true, ObjectType::DECORATION,
        position, Vector2(0.f, 0.f), rendererComp);

    gameObjectCounter++;
}

#pragma endregion

#pragma region Actor GameObjects

void GameObjectFactory::CreateProjectile(const GameManager& gameManager, int& gameObjectCounter, int& physicsCounter,
    std::vector<GameObject>& gameObjects, std::vector<int>& gameObjectPool, std::vector<PhysicsComponent*>& physics,
    std::vector<RendererComponent*>& renderers, Vector3 position, Vector2 scale, bool isActive) {

    PhysicsComponent* physicsComp = new ProjectilePhysicsComponent(gameObjectCounter, isActive, ColorTag::GREEN,
        0.004f, 7.0f, scale, Vector2(55.f, 55.f));
    physics.push_back(physicsComp);

    const auto zRange = abs(gameManager.targetZPos[2] - gameManager.targetZPos[0]);
    const std::vector<std::string> spriteFiles = { R"(.\Assets\Art\Projectiles\projectile.bmp)" };
    RendererComponent* rendererComp = new ProjectileRendererComponent(gameObjectCounter, isActive,
        spriteFiles, 0.5f, 1.3f, zRange, 0.f, 0.f, position);
    renderers.push_back(rendererComp);

    gameObjects.emplace_back(gameObjectCounter, isActive ? 2 : 0,
        false, true, true, ObjectType::PROJECTILE,
        position, scale, rendererComp, physicsComp);
    gameObjectPool.push_back(gameObjectCounter);

    gameObjectCounter++;
    physicsCounter++;
}

void GameObjectFactory::CreateEnemy(Level* level, const GameManager& gameManager, int& gameObjectCounter, int& physicsCounter,
    std::vector<GameObject>& gameObjects, std::vector<int>& gameObjectPool,
    std::vector<ControllerComponent*>& controllers, std::vector<PhysicsComponent*>& physics,
    std::vector<RendererComponent*>& renderers, Vector3 position, Vector2 scale, bool isActive) {

    ControllerComponent* controllerComp = new EnemyControllerComponent(gameObjectCounter, isActive);
    controllers.push_back(controllerComp);

    PhysicsComponent* physicsComp = new EnemyPhysicsComponent(gameObjectCounter, isActive, ColorTag::GREEN, level);
    physics.push_back(physicsComp);

    const auto zRange = abs(gameManager.targetZPos[2] - gameManager.targetZPos[0]);
    const std::vector<std::string> spriteFiles = { R"(.\Assets\Art\Enemies\slime_spritesheet_calciumtrice.bmp)" };
    RendererComponent* rendererComp = new EnemyRendererComponent(gameObjectCounter, isActive,
        spriteFiles, 0.5f, 1.3f, zRange, 0.0f, 20.0f, position);
    renderers.push_back(rendererComp);

    gameObjects.emplace_back(gameObjectCounter, isActive ? 3 : 0,
        true, true, true, ObjectType::ENEMY,
        position, scale, rendererComp, physicsComp, controllerComp);
    gameObjectPool.push_back(gameObjectCounter);

    gameObjectCounter++;
    physicsCounter++;
}

void GameObjectFactory::CreatePlayer(Level* level, int& gameObjectCounter, int& physicsCounter,
    std::vector<GameObject>& gameObjects, std::vector<ControllerComponent*>& controllers,
    std::vector<PhysicsComponent*>& physics, std::vector<RendererComponent*>& renderers,
    Vector3 position, Vector2 scale, bool isActive) {

    ControllerComponent* controllerComp = new PlayerControllerComponent(gameObjectCounter, isActive, level);
    controllers.push_back(controllerComp);

    PhysicsComponent* physicsComp = new PlayerPhysicsComponent(gameObjectCounter, isActive, ColorTag::NONE, level);
    physics.push_back(physicsComp);

    const std::vector<std::string> spriteFiles = { R"(.\Assets\Art\Player\cannon.bmp)", R"(.\Assets\Art\Player\cannon_wheel.bmp)" };
    RendererComponent* rendererComp = new PlayerRendererComponent(gameObjectCounter, isActive,
        spriteFiles, 40.f, -5.0f, position);
    renderers.push_back(rendererComp);

    gameObjects.emplace_back(gameObjectCounter, isActive ? 3 : 0,
        true, true, true, ObjectType::PLAYER,
        position, scale, rendererComp, physicsComp, controllerComp);

    gameObjectCounter++;
    physicsCounter++;
}

#pragma endregion

#pragma region Utility GameObjects

void GameObjectFactory::CreateUIController(Level* level, int& gameObjectCounter,
    std::vector<GameObject>& gameObjects, std::vector<ControllerComponent*>& controllers, bool isActive) {

    ControllerComponent* controllerComp = new UIControllerComponent(gameObjectCounter, isActive, level);
    controllers.push_back(controllerComp);

    gameObjects.emplace_back(gameObjectCounter, isActive ? 3 : 0,
        true, false, false, ObjectType::NONE, Vector3(0.0f, 0.0f, 0.0f),
        Vector2(0.0f, 0.0f), nullptr, nullptr, controllerComp);

    gameObjectCounter++;
}

void GameObjectFactory::CreateEnemySpawner(Level* level, int& gameObjectCounter, std::vector<GameObject>& gameObjects,
    std::vector<ControllerComponent*>& controllers, bool isActive) {

    ControllerComponent* controllerComp = new EnemySpawnerControllerComponent(gameObjectCounter, isActive, level);
    controllers.push_back(controllerComp);

    gameObjects.emplace_back(gameObjectCounter, isActive ? 1 : 0,
        true, false, false, ObjectType::NONE,
        Vector3(0.0f, 0.0f, 0.0f), Vector2(0.0f, 0.0f),
        nullptr, nullptr, controllerComp);

    gameObjectCounter++;
}

#pragma endregion

#pragma region UI GameObjects

void GameObjectFactory::CreateTextUI(int& gameObjectCounter, std::vector<GameObject>& gameObjects,
    std::vector<RendererComponent*>& renderers, int numMessages, Vector3 textColor,
    const std::vector<std::string>& messages, const std::vector<Vector2>& messagePositions, bool isActive) {

    RendererComponent* rendererComp = new UITextRendererComponent(gameObjectCounter, isActive,
        numMessages, textColor, messagePositions, messages);
    renderers.push_back(rendererComp);

    gameObjects.emplace_back(gameObjectCounter, isActive ? 1 : 0,
        false, false, true, ObjectType::UI,
        Vector3(0.0f, 0.0f, 0.0f), Vector2(0.f, 0.f), rendererComp);

    gameObjectCounter++;
}

void GameObjectFactory::CreateTextPopupUI(int& gameObjectCounter, std::vector<GameObject>& gameObjects,
    std::vector<int>& gameObjectPool, std::vector<RendererComponent*>& renderers, int numMessages, Vector3 textColor,
    const std::vector<std::string>& messages, const std::vector<Vector2>& messagePositions, bool isActive) {

    RendererComponent* rendererComp = new UIPopupRendererComponent(gameObjectCounter, isActive,
        numMessages, textColor, messagePositions, messages);
    renderers.push_back(rendererComp);

    gameObjects.emplace_back(gameObjectCounter, isActive ? 1 : 0,
        false, false, true, ObjectType::UI,
        Vector3(0.0f, 0.0f, 0.0f), Vector2(0.f, 0.f), rendererComp);
    gameObjectPool.push_back(gameObjectCounter);

    gameObjectCounter++;
}

void GameObjectFactory::CreateRepeatedImageUI(int& gameObjectCounter, std::vector<GameObject>& gameObjects,
    std::vector<RendererComponent*>& renderers, Vector3 position, Vector2 spaceBetweenSprites, int spriteCount, bool isActive) {

    const std::string spriteFile = R"(.\Assets\Art\UI\heart-pixel-art-64x64.bmp)";
    RendererComponent* rendererComp = new RepeatRendererComponent(gameObjectCounter, isActive,
        spriteFile, position, spriteCount, spaceBetweenSprites, 0.0f, 0.0f, 1.0f);
    renderers.push_back(rendererComp);

    gameObjects.emplace_back(gameObjectCounter, isActive ? 1 : 0,
        false, false, true, ObjectType::UI,
        position, Vector2(0.f, 0.f), rendererComp);

    gameObjectCounter++;
}

void GameObjectFactory::CreateNextProjectileTypeUI(int& gameObjectCounter, std::vector<GameObject>& gameObjects,
    std::vector<RendererComponent*>& renderers, Vector3 position, float scale, bool isActive) {

    const std::vector<std::string> spriteFiles = { R"(.\Assets\Art\Projectiles\projectile.bmp)" };
    RendererComponent* rendererComp = new BasicRendererComponent(gameObjectCounter, isActive,
        spriteFiles, 0.f, 0.f, position, scale);
    renderers.push_back(rendererComp);

    gameObjects.emplace_back(gameObjectCounter, isActive ? 1 : 0,
        false, false, true, ObjectType::UI,
        position, Vector2(0.f, 0.f), rendererComp);

    gameObjectCounter++;
}

#pragma endregion
