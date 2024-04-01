#ifndef _LANERENDERERCOMPONENT_H
#define _LANERENDERERCOMPONENT_H

#include "BasicRendererComponent.h"

//*******************************************************************************************
// LaneRendererComponent
//*******************************************************************************************
/* Handles the rendering of a sprite used to communicate the target lane selected for
 * firing projectiles.
 */
class LaneRendererComponent : public BasicRendererComponent {

public:
    LaneRendererComponent(int newID, bool isActive, const std::vector<std::string>& spriteFiles,
        float xOffset, float yOffset, Vector3 position) :
        BasicRendererComponent(newID, isActive, spriteFiles, xOffset, yOffset, position) {}

    void Update(GameObject& gameObject, const float deltaTime) override;
};
#endif
