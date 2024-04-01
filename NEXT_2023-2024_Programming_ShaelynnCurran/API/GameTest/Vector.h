#include <cmath>

#ifndef _VECTOR_H
#define _VECTOR_H

//*******************************************************************************************
// Vector3
//*******************************************************************************************
/* Container to represent a mathematical vector in 3D space */
class Vector3 {

public:
    explicit Vector3(const float newX = 0, const float newY = 0, const float newZ = 0) : x(newX), y(newY), z(newZ) {}

    Vector3 operator+(const Vector3& other) const {
        return Vector3(this->x + other.x, this->y + other.y, this->z + other.z);
    }

    Vector3 operator-(const Vector3& other) const {
        return Vector3(this->x - other.x, this->y - other.y, this->z - other.z);
    }

    void SetVector(const float newX, const float newY, const float newZ) {
        this->x = newX;
        this->y = newY;
        this->z = newZ;
    }

    float Get2DMagnitude() const {
        return std::sqrt(x * x + y * y);
    }

    float x, y, z;
};

//*******************************************************************************************
// Vector2
//*******************************************************************************************
/* Container to represent a mathematical vector in 2D space */
class Vector2 {

public:
    explicit Vector2(const float newX = 0, const float newY = 0) : x(newX), y(newY) {}

    Vector2 operator+(const Vector2& other) const {
        return Vector2(this->x + other.x, this->y + other.y);
    }

    Vector2 operator-(const Vector2& other) const {
        return Vector2(this->x - other.x, this->y - other.y);
    }

    void SetVector(const float newX, const float newY) {
        this->x = newX;
        this->y = newY;
    }

    float x, y;
};
#endif

