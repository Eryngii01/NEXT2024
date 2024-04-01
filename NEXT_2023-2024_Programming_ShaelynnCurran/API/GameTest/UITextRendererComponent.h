#ifndef _UITEXTRENDERERCOMPONENT_H
#define _UITEXTRENDERERCOMPONENT_H

#include "RendererComponent.h"

//*******************************************************************************************
// UITextRendererComponent
//*******************************************************************************************
/* Renders a series of text at a set of provided positions. */

class UITextRendererComponent : public RendererComponent {

public:
    UITextRendererComponent(int newID, bool isActive, int messageCount, Vector3 color,
        const std::vector<Vector2>& positions, const std::vector<std::string>& newMessages) :
        RendererComponent(newID, isActive, newMessages, 0.0f, 0.0f,
            Vector3(0.0f, 0.0f, 0.0f), true),
        numMessages(messageCount), textColor(color) {

        for (int i = 0; i < numMessages; i++) {
            messages.emplace_back(newMessages[i]);
            messagePositions.emplace_back(positions[i]);
        }
    }

    void Render(GameObject& gameObject, bool debugMode) override;

    // No sprites to update
    void Update(GameObject& gameObject, const float deltaTime) override {}

    //===========================================================================================
    // Object Pooling
    //===========================================================================================
#pragma region Object Pooling

    // Used for updating the text to render
    void SetData(GameManager& gameManager, std::vector<std::string>& args) override;

#pragma endregion

protected:
    int numMessages;
    std::vector<Vector2> messagePositions;
    std::vector<std::string> messages;
    Vector3 textColor;
};
#endif
