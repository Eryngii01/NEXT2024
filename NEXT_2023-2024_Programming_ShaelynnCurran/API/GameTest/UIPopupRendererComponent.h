#ifndef _UIPOPUPRENDERERCOMPONENT_H
#define _UIPOPUPRENDERERCOMPONENT_H

#include "UITextRendererComponent.h"

//*******************************************************************************************
// UIPopupRendererComponent
//*******************************************************************************************
/* A UITextRendererComponent subclass that renders floating text and disables after a
 * set time. Used as the enemy score popups.
 */

class UIPopupRendererComponent : public UITextRendererComponent {

public:
    UIPopupRendererComponent(int newID, bool isActive, int messageCount, Vector3 color,
        const std::vector<Vector2>& positions, const std::vector<std::string>& newMessages) :
        UITextRendererComponent(newID, isActive, messageCount, color, positions, newMessages), _timeCounter(0),
        _timeBeforeDisable(1500) {}

    void Render(GameObject& gameObject, bool debugMode) override;
    void Update(GameObject& gameObject, const float deltaTime) override;

    //===========================================================================================
    // Object Pooling
    //===========================================================================================
#pragma region Object Pooling

    // Used for updating the text content and resetting the popup timer
    void SetData(GameManager& gameManager, std::vector<std::string>& args) override;

    // Used for updating text positions
    void SetData(std::vector<Vector2>& args) override;

#pragma endregion

private:
    float _timeCounter, _timeBeforeDisable;
};
#endif
