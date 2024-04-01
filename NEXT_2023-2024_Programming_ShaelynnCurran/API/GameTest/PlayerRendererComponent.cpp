#include "stdafx.h"
#include "PlayerRendererComponent.h"

#include "Mathf.h"

void PlayerRendererComponent::Update(GameObject& gameObject, const float deltaTime) {
	if (!this->isEnabled) return;

	for (const auto sprite : sprites) {
		sprite->Update(deltaTime);
	}

	const auto cannon = sprites[0];
	const auto inputCoord = gameObject.aimInput;
	const auto position = gameObject.transform.position;
	// For now, only y-input will dictate the angle of projectile firing without adjustments to velocity, but later
	// maybe change this to adjust the x-axis velocity according to x-input
	// const auto inputX = Mathf::Clamp(inputCoord.x, 0, 1);
	const auto inputY = Mathf::Clamp(inputCoord.y, 0, 1);

	cannon->SetAngle(Mathf::Lerp(0.f, 90.f * deg_2_rad_, inputY));

	// Correct position according to cannon sprite rotation
	cannon->SetPosition(position.x + spriteOffset.x + Mathf::Lerp(0.f, -35.f, inputY),
		position.y + spriteOffset.y + Mathf::Lerp(0.f, 30.f, inputY));
}

void PlayerRendererComponent::Render(GameObject& gameObject, bool debugMode) {
	if (!this->isEnabled) return;

	for (const auto sprite : sprites) {
		sprite->Draw();
	}

	if (debugMode) {
		const Transform transform = gameObject.transform;
		const Vector3 position = transform.position;

		DrawCollider(transform);

		// Fetch the player aim input to draw a trajectory path
		const Vector2 inputCoord = gameObject.aimInput;

		const float x2 = position.x + (100 * inputCoord.x);
		const float y2 = position.y + (100 * inputCoord.y);

		// Hard to see when the line is drawn green, so even though it signifies the y-axis coordinate it will
		// be drawn in blue contrary to the gizmo representation
		App::DrawLine(position.x, position.y, x2, y2,
			0.0f, 0.0f, Mathf::Clamp(inputCoord.y, 0.0f, 1.0f));
	}
}
