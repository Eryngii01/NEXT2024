#include "stdafx.h"
#include "UIControllerComponent.h"

void UIControllerComponent::Update(GameObject& gameObject, GameManager& gameManager, float deltaTime) {
    if (!this->isEnabled) return;

    if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true)) {
        _level->NextLevel();
    }
}
