//
//  AmbientLight.h
//  first-raytracer
//
//  Created by Chris Taguba on 9/17/23.
//

#ifndef AmbientLight_h
#define AmbientLight_h

#include "Light.h"

class AmbientLight : public Light {
public:
    AmbientLight(float intensity);
};

#endif /* AmbientLight_h */
