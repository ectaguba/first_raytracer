//
//  Light.cpp
//  first-raytracer
//
//  Created by Chris Taguba on 9/17/23.
//

#include "Light.h"

Light::Light(float intensity, LightType type) {
    this->intensity = intensity;
    this->type = type;
}

Vector3 Light::getVector() const {
    return Vector3(0, 0, 0);
}
