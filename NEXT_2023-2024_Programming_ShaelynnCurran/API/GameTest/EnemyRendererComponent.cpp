#include "stdafx.h"
#include "EnemyRendererComponent.h"

#include "Mathf.h"

void EnemyRendererComponent::Update(GameObject& gameObject, const float deltaTime) {
	if (!this->isEnabled) return;

	const auto position = gameObject.transform.position;
	const auto newSize = Mathf::Lerp(_minSize, _maxSize, position.z / _totalZRange);

	for (const auto sprite : sprites) {
		sprite->Update(deltaTime);
		sprite->SetPosition(position.x + spriteOffset.x, position.y + spriteOffset.y + (position.z / _totalZRange * 40.0f));
		sprite->SetScale(newSize);
	}
}

void EnemyRendererComponent::Render(GameObject& gameObject, bool debugMode) {
	if (!this->isEnabled) return;

	for (const auto sprite : sprites) {
		sprite->Draw();
	}

	if (debugMode) {
		DrawCollider(gameObject.transform);
	}
}

void EnemyRendererComponent::SetData(GameManager& gameManager) {
	// Set the enemy sprite's color
	const auto color = gameManager.GetEnemyColor();
	sprites[0]->SetColor(color.x, color.y, color.z);
}

void EnemyRendererComponent::SetData(GameManager& gameManager, std::vector<int>& args) {
	if (args.empty()) return;

	// Set the enemy sprite's color
	const auto color = gameManager.GetColorByIndex(args[0]);
	sprites[0]->SetColor(color.x, color.y, color.z);
}
