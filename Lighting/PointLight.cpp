//
//  PointLight.cpp
//  first-raytracer
//
//  Created by Chris Taguba on 9/17/23.
//

#include "PointLight.h"

PointLight::PointLight(float intensity, Vector3 position) : Light(intensity, POINT), position(position) {}

Vector3 PointLight::getVector() const {
    return position;
}
