#ifndef _PHYSICSCOMPONENT_H
#define _PHYSICSCOMPONENT_H

#include "GameObject.h"

class World;
class InputComponent;

enum class ColorTag {
    GREEN,
    RED,
    BLUE,
    PURPLE,
    GREY,
    NONE
};

//*******************************************************************************************
// PhysicsComponent
//*******************************************************************************************
/* Interface of a component for managing the physics of a GameObject. This includes data
 * on the position in the world, the velocity of objects, collision detection, and
 * collision detection.
 */
class PhysicsComponent : public Component {

public:
    explicit PhysicsComponent(int newID, bool isActive, ColorTag newTag) :
        Component(newID, isActive), velocity(0.0f, 0.0f), tag(newTag), currentLane(0) {}

    virtual ~PhysicsComponent() override = default;

    // Exposed for the sharing of color tags during collision resolution
    ColorTag GetTag() const {
        return this->tag;
    }

    virtual void Update(GameObject& gameObject, GameManager& gameManager, const float deltaTime) = 0;
    virtual void OnCollision(GameObject& gameObject, ObjectType otherTag, ColorTag otherColor) = 0;

    Vector2 velocity;
    ColorTag tag;

    int currentLane;
};
#endif

