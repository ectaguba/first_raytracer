//
//  DirectionalLight.h
//  first-raytracer
//
//  Created by Chris Taguba on 9/17/23.
//

#ifndef DirectionalLight_h
#define DirectionalLight_h

#include "Light.h"
#include "Vector3.h"

class DirectionalLight : public Light {
public:
    Vector3 direction;

    DirectionalLight(float intensity, Vector3 direction);

    Vector3 getVector() const override;
};

#endif /* DirectionalLight_h */
