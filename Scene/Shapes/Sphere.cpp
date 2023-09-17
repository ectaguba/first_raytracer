//
//  Sphere.cpp
//  first-raytracer
//
//  Created by Chris Taguba on 9/17/23.
//

#include "Sphere.h"

Sphere::Sphere() : radius(1), color({255, 255, 255, 255}), specular(0), reflective(0) {
    position = Vector3(0, 0, 0);
}

Sphere::Sphere(Vector3 newPos, float radius) : radius(radius), color({255, 255, 255, 255}), specular(0), reflective(0) {
    position = newPos;
}

Sphere::Sphere(Vector3 newPos, float radius, SDL_Color color) : radius(radius), color(color), specular(0), reflective(0) {
    position = newPos;
}

Sphere::Sphere(Vector3 newPos, float radius, SDL_Color color, float specular, float reflective)
    : radius(radius), color(color), specular(specular), reflective(reflective) {
    position = newPos;
}

