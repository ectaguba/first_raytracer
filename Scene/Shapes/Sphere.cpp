//
//  Sphere.cpp
//  first-raytracer
//
//  Created by Chris Taguba on 9/17/23.
//

#include "Sphere.h"

Sphere::Sphere() : Shape(SPHERE) {
    radius = 1;
}

Sphere::Sphere(float radius) : Shape(SPHERE) {
    this->radius = radius;
}

Sphere::Sphere(float radius, Vector3 newPos) : Shape(SPHERE, newPos) {
    this->radius = radius;
}

Sphere::Sphere(float radius, Vector3 newPos, SDL_Color color) : Shape(SPHERE, newPos, color) {
    this->radius = radius;
}

Sphere::Sphere(float radius, Vector3 newPos, SDL_Color color, float specular) : Shape(SPHERE, newPos, color, specular) {
    this->radius = radius;
}

Sphere::Sphere(float radius, Vector3 newPos, SDL_Color color, float specular, float reflective)
    : Shape(SPHERE, newPos, color, specular, reflective) {
        this->radius = radius;
}

void Sphere::setRadius(float newRadius) {
    radius = newRadius;
}

