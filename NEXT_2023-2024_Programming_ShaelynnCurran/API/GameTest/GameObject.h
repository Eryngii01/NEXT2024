#ifndef _GAMEOBJECT_H
#define _GAMEOBJECT_H

// Macros can be bug-prone as they are just copy-pasted (expanded) into the code when used, so must be careful
// when using it
#define GRAVITY (-9.81f)

#include "ObjectType.h"
#include "Component.h"

/* Stores positional and scale data for the GameObject. A watered-down transformation matrix... */
class Transform {

public:
    Transform(Vector3 position, Vector2 scale) : position(position), scale(scale) {}

    Vector3 position;
    Vector2 scale;
};

enum class ControllerState {
    STATE_PLAYING,
    STATE_LEVEL_OVER
};

//*******************************************************************************************
// GameObject
//*******************************************************************************************
/* A sack of data used to loosely bind respective components as a single entity; used for
 * sharing data and linking IDs to actively enable/disable components for object pooling
 */
class GameObject {

public:
    explicit GameObject(int newID, int activeComponents, bool activeController, bool activePhysics, bool activeRenderer,
        ObjectType newTag, Vector3 position, Vector2 scale, Component* renderer = nullptr, Component* physics = nullptr,
        Component* controller = nullptr) :
        ID(newID), numActiveComponents(activeComponents), isDirty(false), tag(newTag), transform(position, scale),
        input(0, 0), aimInput(0, 0), inputState(ControllerState::STATE_PLAYING), controllerComp(controller),
        physicsComp(physics), rendererComp(renderer), isControllerActive(activeController), isPhysicsActive(activePhysics),
        isRendererActive(activeRenderer) {}

    //===========================================================================================
    // Enable/Disable
    //===========================================================================================
#pragma region Enable/Disable

    // Accessible to all components to enable the entire gameObject associated with them
    void Enable() {
        if (controllerComp) {
            controllerComp->SetActivity(true);
            isControllerActive = true;
            numActiveComponents++;
        }

        if (physicsComp) {
            physicsComp->SetActivity(true);
            isPhysicsActive = true;
            numActiveComponents++;
        }

        if (rendererComp) {
            rendererComp->SetActivity(true);
            isRendererActive = true;
            numActiveComponents++;
        }
    }

    void EnableController() {
        if (controllerComp) controllerComp->SetActivity(true);

        isControllerActive = true;
        numActiveComponents++;
    }

    void EnablePhysics() {
        if (physicsComp) physicsComp->SetActivity(true);

        isPhysicsActive = true;
        numActiveComponents++;
    }

    void EnableRenderer() {
        if (rendererComp) rendererComp->SetActivity(true);

        isRendererActive = true;
        numActiveComponents++;
    }

    // Accessible to all components to disable the entire gameObject associated with them
    void Disable() {
        if (controllerComp) controllerComp->SetActivity(false);
        if (physicsComp) physicsComp->SetActivity(false);
        if (rendererComp) rendererComp->SetActivity(false);

        isControllerActive = isPhysicsActive = isRendererActive = false;
        numActiveComponents = 0;
    }

    void DisableController() {
        if (controllerComp) controllerComp->SetActivity(false);

        isControllerActive = false;
        numActiveComponents--;
    }

    void DisablePhysics() {
        if (physicsComp) physicsComp->SetActivity(false);

        isPhysicsActive = false;
        numActiveComponents--;
    }

    void DisableRenderer() {
        if (rendererComp) rendererComp->SetActivity(false);

        isRendererActive = false;
        numActiveComponents--;
    }

#pragma endregion

    // When enabling objects taken from the pool, the data can be reset via the GameObject to be used by the components
    int ID;
    int numActiveComponents;
    bool isDirty;
    ObjectType tag;
    Transform transform;

    Vector2 input, aimInput;
    ControllerState inputState;

    // To avoid cyclic dependencies, the GameObject will only be able to enable/disable component types (polymorphism)
    // Memory cleanup of these components is handled by Level
    Component* controllerComp, * physicsComp, * rendererComp;
    bool isControllerActive, isPhysicsActive, isRendererActive;
};
#endif

