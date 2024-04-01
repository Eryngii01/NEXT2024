#ifndef _MATHF_H
#define _MATHF_H

//*******************************************************************************************
// Mathf
//*******************************************************************************************
/* A class for handling standard math with floats. */
class Mathf {

public:
    static float Clamp(const float value, const float min, const float max) {
        return (value > max ? max : (value < min ? min : value));
    }

    static float Lerp(const float v1, const float v2, const float t) {
        return v1 * (1.0f - t) + v2 * t;
    }
};
#endif

