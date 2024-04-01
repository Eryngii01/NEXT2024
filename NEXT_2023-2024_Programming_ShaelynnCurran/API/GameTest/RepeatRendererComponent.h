#ifndef _REPEATRENDERERCOMPONENT_H
#define _REPEATRENDERERCOMPONENT_H

#include "RendererComponent.h"

//*******************************************************************************************
// RepeatRendererComponent
//*******************************************************************************************
/* Repeats the rendering of a single sprite as many times as provided with spacing control.
 * Used to render player lives and count them down visually as they deplete.
 */
class RepeatRendererComponent : public RendererComponent {

public:
    RepeatRendererComponent(int newID, bool isActive, const std::string& spriteFile, Vector3 position, int numRepeat,
        Vector2 spaceBetweenSprites, float xOffset, float yOffset, float scale) :
        RendererComponent(newID, isActive, std::vector<std::string>(), xOffset, yOffset, position,
            true), _activeSpriteCount(numRepeat) {

        for (int i = 0; i < numRepeat; i++) {
            const auto sprite = App::CreateSprite(spriteFile.c_str(), 1, 1);
            sprite->SetPosition(position.x + spriteOffset.x + i * spaceBetweenSprites.x,
                position.y + spriteOffset.y + i * spaceBetweenSprites.y);
            sprite->SetScale(scale);

            sprites.push_back(sprite);
        }
    }

    void Render(GameObject& gameObject, bool debugMode) override;
    void Update(GameObject& gameObject, const float deltaTime) override;

    // Used for decreasing the number of repeated sprites to render
    void SetData(GameManager& gameManager, std::vector<int>& args) override;

private:
    int _activeSpriteCount;
};
#endif
