#include "stdafx.h"
#include "PlayerControllerComponent.h"

void PlayerControllerComponent::Update(GameObject& gameObject, GameManager& gameManager, float deltaTime) {
	if (!this->isEnabled) return;

	// Toggle Debug Mode
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_B, true)) {
		_level->SetDebugMode(true);
	}
	else if (App::GetController().CheckButton(XINPUT_GAMEPAD_Y, true)) {
		_level->SetDebugMode(false);
	}

	// Switch lanes to aim at
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_LEFT_SHOULDER, true)) {
		_level->SwitchLanes(1);
	}
	else if (App::GetController().CheckButton(XINPUT_GAMEPAD_RIGHT_SHOULDER, true)) {
		_level->SwitchLanes(-1);
	}

	// Get the input vector to aim projectiles
	const float aimX = App::GetController().GetLeftThumbStickX();
	const float aimY = App::GetController().GetLeftThumbStickY();
	gameObject.aimInput.x = aimX;
	gameObject.aimInput.y = aimY;

	// Shoot a projectile
	if (App::GetController().CheckButton(XINPUT_GAMEPAD_A, true)) {
		_level->TakeProjectileFromPool(gameObject.transform.position, aimY);
		App::PlaySound(".\\TestData\\Test.wav");
	}
}
