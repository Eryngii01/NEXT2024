#ifndef _OBJECTTYPE_H
#define _OBJECTTYPE_H

//*******************************************************************************************
// ObjectType
//*******************************************************************************************
/* Used to mark the GameObject type primarily for layer masking collisions. */
enum class ObjectType {
    DECORATION, // An object without a physics or input functionality; only contains a sprite
    PROJECTILE, // An object the player can fire; affected by gravity
    PLAYER, // The player gameObject
    ENEMY, // An enemy gameObject with AI controllers
    UI, // Rendered above all the others
    NONE
};
#endif