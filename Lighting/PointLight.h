
//
//  PointLight.h
//  first-raytracer
//
//  Created by Chris Taguba on 9/17/23.
//

#ifndef PointLight_h
#define PointLight_h

#include "Light.h"
#include "Vector3.h"

class PointLight : public Light {
public:
    Vector3 position;

    PointLight(float intensity, Vector3 position);

    Vector3 getVector() const override;
};

#endif /* PointLight_h */
