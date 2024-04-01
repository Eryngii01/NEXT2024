#include "stdafx.h"
#include "RepeatRendererComponent.h"

void RepeatRendererComponent::Update(GameObject& gameObject, const float deltaTime) {
    if (!this->isEnabled) return;

    for (int i = 0; i < _activeSpriteCount; i++) {
        sprites[i]->Update(deltaTime);
    }
}

void RepeatRendererComponent::Render(GameObject& gameObject, bool debugMode) {
    if (!this->isEnabled) return;

    for (int i = 0; i < _activeSpriteCount; i++) {
        sprites[i]->Draw();
    }
}

void RepeatRendererComponent::SetData(GameManager& gameManager, std::vector<int>& args) {
    // Sanitize inputs; ensure that there are enough arguments to successfully set this component's movement speed
    if (args.empty()) return;

    _activeSpriteCount = args[0];
}
