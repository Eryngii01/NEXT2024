#ifndef _PHYSICSENGINE_H
#define _PHYSICSENGINE_H

#include <vector>
#include "PhysicsComponent.h"

//*******************************************************************************************
// PhysicsEngine
//*******************************************************************************************
/* Oversees the collision resolution between all physics colliders within the scene */

class PhysicsEngine {
    // Physics resolutions will only be exposed to the Level class 
    friend class Level;

private:
    static void ResolveCollisions(std::vector<GameObject>& gameObjects, GameObject& curObject,
        PhysicsComponent* curCollider, const std::vector<PhysicsComponent*>& otherColliders, int curIndex);

    static bool ResolveLayerMasking(const GameObject& curObject, const PhysicsComponent* curCollider,
        const GameObject& otherObject, const PhysicsComponent* otherCollider);

    static bool CheckAABBCollision(const Transform& c1, const Transform& c2);

    static void ChainEnemyCollisions(int pointMultiplier, const GameObject& curObject, const PhysicsComponent* curCollider,
        std::vector<GameObject>& gameObjects, const std::vector<PhysicsComponent*>& otherColliders);

    static bool CompareDistance(Vector3 v1, Vector3 v2, float distanceThreshold);
};
#endif

