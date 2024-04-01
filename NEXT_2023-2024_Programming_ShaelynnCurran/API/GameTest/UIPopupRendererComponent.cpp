#include "stdafx.h"
#include "UIPopupRendererComponent.h"

void UIPopupRendererComponent::Render(GameObject& gameObject, bool debugMode) {
    UITextRendererComponent::Render(gameObject, debugMode);
}

void UIPopupRendererComponent::Update(GameObject& gameObject, const float deltaTime) {
    if (!this->isEnabled) return;

    _timeCounter += deltaTime;

    if (_timeCounter > _timeBeforeDisable) {
        gameObject.Disable();
        return;
    }

    for (Vector2& position : messagePositions) {
        position.y += 2.0f;
    }
}

void UIPopupRendererComponent::SetData(GameManager& gameManager, std::vector<std::string>& args) {
    UITextRendererComponent::SetData(gameManager, args);

    _timeCounter = 0.0f;
}

void UIPopupRendererComponent::SetData(std::vector<Vector2>& args) {
    // Sanitize inputs
    if (args.empty()) return;

    messagePositions[0] = args[0];
}
