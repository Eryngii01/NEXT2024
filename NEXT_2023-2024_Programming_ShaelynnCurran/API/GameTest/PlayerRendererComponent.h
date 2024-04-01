#ifndef _PLAYERRENDERERCOMPONENT_H
#define _PLAYERRENDERERCOMPONENT_H

#include<string>
#include "GameObject.h"
#include "RendererComponent.h"

//*******************************************************************************************
// PlayerRendererComponent
//*******************************************************************************************
// Implementation of RendererComponent for the player GameObject

class PlayerRendererComponent : public RendererComponent {

public:
	PlayerRendererComponent(int newID, bool isActive,
		const std::vector<std::string>& spriteFiles, float xOffset, float yOffset, Vector3 position) :
		RendererComponent(newID, isActive, spriteFiles, xOffset, yOffset, position), deg_2_rad_(PI / 180)
	{
		// Correct sprites positions with offsets
		for (const auto sprite : sprites)
		{
			sprite->SetPosition(position.x + spriteOffset.x, position.y + spriteOffset.y);
		}
	}

	void Render(GameObject& gameObject, bool debugMode) override;
	void Update(GameObject& gameObject, const float deltaTime) override;

private:
	float deg_2_rad_;
};
#endif
