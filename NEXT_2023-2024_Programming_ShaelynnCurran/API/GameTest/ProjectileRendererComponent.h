#ifndef _PROJECTILERENDERERCOMPONENT_H
#define _PROJECTILERENDERERCOMPONENT_H

#include<string>
#include "RendererComponent.h"

//*******************************************************************************************
// ProjectileRendererComponent
//*******************************************************************************************
/* Implementation of RendererComponent for the projectile GameObject that constantly rotates
 * and adjusts scale based on its z-position
 */

class ProjectileRendererComponent : public RendererComponent {

public:
    ProjectileRendererComponent(int newID, bool isActive, const std::vector<std::string>& spriteFiles,
        const float size, const float maxSize, const float zRange, float xOffset, float yOffset, Vector3 position) :
        RendererComponent(newID, isActive, spriteFiles, xOffset, yOffset, position), _totalZRange(zRange) {
        _minSize = size;
        _maxSize = maxSize;
        sprites[0]->SetScale(size);
    }

    void Render(GameObject& gameObject, bool debugMode) override;
    void Update(GameObject& gameObject, const float deltaTime) override;

    //===========================================================================================
    // Object Pooling
    //===========================================================================================
#pragma region Object Pooling

    // For changing the projectile sprite's color via the GameManager upon spawns
    void SetData(GameManager& gameManager) override;

#pragma endregion

private:
    float _minSize, _maxSize, _totalZRange;
};
#endif
