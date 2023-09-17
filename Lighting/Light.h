//
//  Light.h
//  first-raytracer
//
//  Created by Chris Taguba on 9/17/23.
//

#ifndef Light_h
#define Light_h

#include "Vector3.h"

enum LightType {
    AMBIENT,
    POINT,
    DIRECTIONAL
};

class Light {
public:
    float intensity;
    LightType type;

    Light(float intensity, LightType type);
    virtual Vector3 getVector() const;
};

#endif /* Light_h */
