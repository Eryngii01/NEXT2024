#ifndef _ENEMYRENDERERCOMPONENT_H
#define _ENEMYRENDERERCOMPONENT_H

#include<string>
#include "GameObject.h"
#include "RendererComponent.h"

enum EnemyAnim {
    ANIM_ROLLING,
    ANIM_DYING
};

//*******************************************************************************************
// EnemyRendererComponent
//*******************************************************************************************
/* Implementation of RendererComponent for the enemy GameObject */

class EnemyRendererComponent : public RendererComponent {

public:
    EnemyRendererComponent(int newID, bool isActive,
        const std::vector<std::string>& spriteFiles, const float size, const float maxSize, const float zRange,
        float xOffset, float yOffset, Vector3 position) :
        RendererComponent(newID, isActive, spriteFiles, xOffset, yOffset, position, true), _totalZRange(zRange) {

        _minSize = size;
        _maxSize = maxSize;

        // Set up special sprite for enemies
        const auto sprite = App::CreateSprite(spriteFiles[0].c_str(), 5, 5);
        sprite->SetPosition(position.x + spriteOffset.x, position.y + spriteOffset.y);
        sprite->SetScale(1.0f);
        sprite->SetScale(size);

        constexpr float speed = 1.0f / 15.0f;
        sprite->CreateAnimation(ANIM_ROLLING, speed, { 0,1,2,3,4,5,6,7, 8, 9, 10 });
        sprite->CreateAnimation(ANIM_ROLLING, speed, { 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 });
        sprite->SetAnimation(ANIM_ROLLING);

        sprites.push_back(sprite);
    }

    void Render(GameObject& gameObject, bool debugMode) override;
    void Update(GameObject& gameObject, const float deltaTime) override;

    //===========================================================================================
    // Object Pooling
    //===========================================================================================
#pragma region Object Pooling

    // For setting the sprite color via GameManager; Used when enemy is newly spawned
    void SetData(GameManager& gameManager) override;
    // For directly setting the sprite color; Used when the enemy is spawned from a projectile-enemy collision
    void SetData(GameManager& gameManager, std::vector<int>& args) override;

#pragma endregion

#pragma endregion

private:
    float _minSize, _maxSize, _totalZRange;

};
#endif
