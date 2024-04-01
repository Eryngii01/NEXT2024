#include "stdafx.h"
#include "UITextRendererComponent.h"

void UITextRendererComponent::Render(GameObject& gameObject, bool debugMode) {
    if (!this->isEnabled) return;

    for (int i = 0; i < numMessages; i++) {
        const auto position = messagePositions[i];
        App::Print(position.x, position.y, messages[i].c_str(), textColor.x, textColor.y, textColor.z);
    }
}

void UITextRendererComponent::SetData(GameManager& gameManager, std::vector<std::string>& args) {

    for (std::vector<std::string>::size_type i = 0; i < args.size(); i++) {
        // Set as many messages as possible
        if (i > numMessages - 1) break;

        messages[i] = args[i];
    }
}

