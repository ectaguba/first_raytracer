//
//  DirectionalLight.cpp
//  first-raytracer
//
//  Created by Chris Taguba on 9/17/23.
//

#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(float intensity, Vector3 direction) : Light(intensity, DIRECTIONAL), direction(direction) {}

Vector3 DirectionalLight::getVector() const {
    return direction;
}
