#include "stdafx.h"
#include "BasicRendererComponent.h"

void BasicRendererComponent::Update(GameObject& gameObject, const float deltaTime) {
	if (!this->isEnabled) return;

	for (const auto sprite : sprites) {
		sprite->Update(deltaTime);
	}
}

void BasicRendererComponent::Render(GameObject& gameObject, bool debugMode) {
	if (!this->isEnabled) return;

	for (const auto sprite : sprites) {
		sprite->Draw();
	}
}

void BasicRendererComponent::SetData(GameManager& gameManager) {
	const auto color = gameManager.GetProjectileColor();

	for (const auto sprite : sprites) {
		sprite->SetColor(color.x, color.y, color.z);
	}

}
