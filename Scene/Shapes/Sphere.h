//
//  Sphere.h
//  first-raytracer
//
//  Created by Chris Taguba on 9/17/23.
//

#ifndef Sphere_h
#define Sphere_h

#include "SceneObject.h"
#include <SDL2/SDL.h>

class Sphere : public SceneObject {
public:
    float radius;
    SDL_Color color;
    float specular;
    float reflective;

    Sphere();
    Sphere(Vector3 newPos, float radius);
    Sphere(Vector3 newPos, float radius, SDL_Color color);
    Sphere(Vector3 newPos, float radius, SDL_Color color, float specular, float reflective);
};

#endif /* Sphere_h */
