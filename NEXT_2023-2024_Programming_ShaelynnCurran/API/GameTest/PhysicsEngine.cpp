#include "stdafx.h"
#include "PhysicsEngine.h"

void PhysicsEngine::ResolveCollisions(std::vector<GameObject>& gameObjects, GameObject& curObject,
    PhysicsComponent* collider, const std::vector<PhysicsComponent*>& otherColliders, int curIndex) {

    // Abort if the current component/collider is disabled
    if (!collider->IsEnabled()) return;

    // Get the GameObject associated with the current physics component
    const auto transform = curObject.transform;

    // Traverse the vector backwards
    for (int i = curIndex - 1; i > -1; i--) {
        const auto other = otherColliders[i];

        // Need to check if the other component/collider is enabled to avoid wasting time on calculations
        if (!other->IsEnabled()) continue;

        GameObject& otherObject = gameObjects[other->ID];

        if (!ResolveLayerMasking(curObject, collider, otherObject, other)) continue;

        if (CheckAABBCollision(transform, gameObjects[other->ID].transform)) {
            // Notify both components/colliders of the collision
            other->OnCollision(otherObject, curObject.tag, collider->GetTag());
            collider->OnCollision(curObject, otherObject.tag, other->GetTag());
        }
    }
}

bool PhysicsEngine::ResolveLayerMasking(const GameObject& curObject, const PhysicsComponent* curCollider,
    const GameObject& otherObject, const PhysicsComponent* otherCollider) {

    const auto curTag = curObject.tag;

    if (curTag == ObjectType::PLAYER && otherObject.tag == ObjectType::ENEMY) {
        // The player only collides with enemies
        return true;
    }

    if (curTag == ObjectType::ENEMY && otherObject.tag == ObjectType::PROJECTILE &&
        curCollider->currentLane == otherCollider->currentLane) {
        // Enemies only collide with the projectiles that are targeting the same lane
        // (player collision with enemies is handled by the player)

        return true;
    }

    // DECORATION and NONE do not collide with anything
    // Projectiles do collide with enemies, but this case is handled by the enemy components
    return false;
}

bool PhysicsEngine::CheckAABBCollision(const Transform& c1, const Transform& c2) {
    const Vector3 c1Pos = c1.position, c2Pos = c2.position;
    const Vector2 c1Scale = c1.scale, c2Scale = c2.scale;

    /* This collision does not account for rotation... */

    // Search for x-axis collision
    // C1 min < C2 max; C1 max > C2 min
    if (!(c1Pos.x - c1Scale.x < c2Pos.x + c2Scale.x && c1Pos.x + c1Scale.x > c2Pos.x - c2Scale.x)) return false;

    // Search for y-axis collision
    // C1 min < C2 max; C1 max > C2 min
    // If both axes overlap, notify the GameObject of the collision and act accordingly
    return (c1Pos.y - c1Scale.y < c2Pos.y + c2Scale.y && c1Pos.y + c1Scale.y > c2Pos.y - c2Scale.y);
}

void PhysicsEngine::ChainEnemyCollisions(int pointMultiplier, const GameObject& curObject, const PhysicsComponent* curCollider,
    std::vector<GameObject>& gameObjects, const std::vector<PhysicsComponent*>& otherColliders) {

    const auto position = curObject.transform.position;
    std::vector<int> adjacentEnemies;

    int gameObjIndex = 0;
    for (GameObject& otherObject : gameObjects) {
        gameObjIndex++;

        if (otherObject.tag != ObjectType::ENEMY) continue;
        if (!otherObject.isPhysicsActive) continue;

        // Compare the distance only if the object is an enemy and has an active collider/physics component
        if (CompareDistance(position, otherObject.transform.position, 68.0f)) {
            // To preserve the logic of increasing the combo score multiplier as the units get farther from the
            // original enemy that was destroyed (e.g. x1->x2->x4->x8), batch the collision events
            adjacentEnemies.push_back(gameObjIndex - 1);

            // Disable the physics components before calling OnCollision so that all the enemies adjacent to the
            // destroyed enemy will be "defeated" before entering the next combo multiplier stage
            otherObject.DisablePhysics();
        }
    }

    // Set the current multiplier data for the enemy to be defeated
    std::vector<int> scoreMultiplier = { pointMultiplier };

    // Call the batched OnCollision(s) to chain the next enemy collision
    for (const auto otherCollider : otherColliders) {

        for (const auto adjacentEnemyIndex : adjacentEnemies) {
            GameObject& adjacentEnemy = gameObjects[adjacentEnemyIndex];
            const auto defeatedEnemyID = adjacentEnemy.ID;

            if (otherCollider->ID != defeatedEnemyID) continue;

            otherCollider->SetData(scoreMultiplier);
            otherCollider->OnCollision(adjacentEnemy, curObject.tag, curCollider->GetTag());
        }
    }
}

bool PhysicsEngine::CompareDistance(Vector3 v1, Vector3 v2, float distanceThreshold) {

    const auto displacementVec = v2 - v1;
    return displacementVec.Get2DMagnitude() < distanceThreshold;
}
