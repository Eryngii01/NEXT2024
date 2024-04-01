#include "stdafx.h"
#include "ProjectileRendererComponent.h"

#include "Mathf.h"

void ProjectileRendererComponent::Update(GameObject& gameObject, const float deltaTime) {
    if (!this->isEnabled) return;

    const auto position = gameObject.transform.position;

    // Simulate the "forward" vector by scaling (lerp based on z-position) objects as they come closer to the screen
    const auto newSize = Mathf::Lerp(_minSize, _maxSize, position.z / _totalZRange);

    for (const auto sprite : sprites) {
        sprite->Update(deltaTime);
        sprite->SetPosition(position.x, position.y);
        sprite->SetScale(newSize);
    }
}

void ProjectileRendererComponent::Render(GameObject& gameObject, bool debugMode) {
    if (!this->isEnabled) return;

    for (const auto sprite : sprites) {
        sprite->Draw();
    }

    if (debugMode) {
        const Transform transform = gameObject.transform;

        DrawCollider(transform);
    }
}

void ProjectileRendererComponent::SetData(GameManager& gameManager) {
    // Set the projectile sprite's color
    const auto color = gameManager.GetProjectileColor();
    sprites[0]->SetColor(color.x, color.y, color.z);
}