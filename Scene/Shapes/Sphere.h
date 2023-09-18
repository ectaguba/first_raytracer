//
//  Sphere.h
//  first-raytracer
//
//  Created by Chris Taguba on 9/17/23.
//

#ifndef Sphere_h
#define Sphere_h

#include "Shape.h"
#include <SDL2/SDL.h>

class Sphere : public Shape {
public:
    float radius;

    Sphere();
    Sphere(float radius);
    Sphere(float radius, Vector3 newPos);
    Sphere(float radius, Vector3 newPos, SDL_Color color);
    Sphere(float radius, Vector3 newPos, SDL_Color color, float specular);
    Sphere(float radius, Vector3 newPos, SDL_Color color, float specular, float reflective);
    
    void setRadius(float radius);
};

#endif /* Sphere_h */
