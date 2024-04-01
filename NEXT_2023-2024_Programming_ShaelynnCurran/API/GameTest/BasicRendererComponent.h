#ifndef _BASICRENDERERCOMPONENT_H
#define _BASICRENDERERCOMPONENT_H

#include "RendererComponent.h"

//*******************************************************************************************
// BasicRendererComponent
//*******************************************************************************************
/* A Renderer Component subclass that can be used to render multiple sprites associated
 * with a generic GameObject.
 */

class BasicRendererComponent : public RendererComponent {

public:
	BasicRendererComponent(int newID, bool isActive, const std::vector<std::string>& spriteFiles,
		float xOffset, float yOffset, Vector3 position, float scale = 1.0f) :
		RendererComponent(newID, isActive, spriteFiles, xOffset, yOffset, position) {

		for (const auto sprite : sprites) {
			sprite->SetScale(scale);
		}
	}

	void Render(GameObject& gameObject, bool debugMode) override;
	void Update(GameObject& gameObject, const float deltaTime) override;

	// Used to update the sprites' colors
	void SetData(GameManager& gameManager) override;
};
#endif
