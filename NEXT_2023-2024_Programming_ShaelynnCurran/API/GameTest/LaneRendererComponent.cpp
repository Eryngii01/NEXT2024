#include "stdafx.h"
#include "LaneRendererComponent.h"

void LaneRendererComponent::Update(GameObject& gameObject, const float deltaTime) {
    if (!this->isEnabled) return;

    for (const auto sprite : sprites) {
        sprite->Update(deltaTime);

        // Only update the position of this sprite if the renderer component is "dirty"
        if (!gameObject.isDirty) continue;

        const auto position = gameObject.transform.position;
        sprite->SetPosition(position.x, position.y);
    }
}