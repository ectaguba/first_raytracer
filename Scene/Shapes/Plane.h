//
//  Plane.h
//  first-raytracer
//
//  Created by Chris Taguba on 9/17/23.
//

#ifndef Plane_h
#define Plane_h

#include <SDL2/SDL.h>
#include "Vector3.h"
#include "Shape.h"

class Plane : public Shape {
public:
    // Plane position is point on plane.
    Vector3 normal;
    SDL_Color color;
    float specular;
    float reflective;

    Plane();
    Plane(const Vector3 p, const Vector3 n);
    Plane(const Vector3 p, const Vector3 n, const SDL_Color c, const float s, const float r);
};

#endif /* Plane_h */
