#ifndef _RENDERERCOMPONENT_H
#define _RENDERERCOMPONENT_H

#include "GameObject.h"
#include "app\app.h"

//*******************************************************************************************
// RendererComponent
//*******************************************************************************************
// Interface of a component for managing graphics for a GameObject.
class RendererComponent : public Component {

public:
    explicit RendererComponent(int newID, bool isActive, const std::vector<std::string>& spriteFiles,
        const float xOffset, const float yOffset, Vector3 position, bool ignoreSpriteConstruction = false) :
        Component(newID, isActive) {

        spriteOffset = Vector2(xOffset, yOffset);

        if (ignoreSpriteConstruction) return;

        for (const auto& filename : spriteFiles) {
            const auto sprite = App::CreateSprite(filename.c_str(), 1, 1);
            sprite->SetPosition(position.x + spriteOffset.x, position.y + spriteOffset.y);
            sprite->SetScale(1.0f);

            sprites.push_back(sprite);
        }
    }

    virtual ~RendererComponent() override = default;

    // Render and update functions to be called every frame
    virtual void Render(GameObject& gameObject, bool debugMode) = 0;
    virtual void Update(GameObject& gameObject, const float deltaTime) = 0;

protected:

    // Support the rendering of multiple sprites per component
    std::vector<CSimpleSprite*> sprites;
    Vector2 spriteOffset;

    //===========================================================================================
    // Debug Rendering
    //===========================================================================================
#pragma region Debug Rendering

    static void DrawCollider(const Transform& transform) {
        const Vector3 position = transform.position;

        // Draw transform position gizmo
        App::DrawLine(position.x, position.y, position.x + 25.f, position.y, 1.0f, 0.0f, 0.0f);
        App::DrawLine(position.x, position.y, position.x, position.y + 25.f, 0.f, 1.0f, 0.f);
        App::DrawLine(position.x, position.y, position.x, position.y - 5.f, 0.f, 0.f, 1.0f);

        // Draw the physics colliders

        // Fetch the current player position
        const float width = transform.scale.x, height = transform.scale.y;

        // Bottom left corner of collider
        const float x = position.x - width;
        const float y = position.y - height;

        // Top right corner of collider
        const float x2 = position.x + width;
        const float y2 = position.y + height;

        // Draw the top
        App::DrawLine(x, y2, x2, y2, 1.0f, 1.0f, 1.0f);
        // Draw the left
        App::DrawLine(x, y, x, y2, 1.0f, 1.0f, 1.0f);
        // Draw the right
        App::DrawLine(x2, y, x2, y2, 1.0f, 1.0f, 1.0f);
        // Draw the bottom
        App::DrawLine(x, y, x2, y, 1.0f, 1.0f, 1.0f);
    }

#pragma endregion

};
#endif
