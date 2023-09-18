//
//  Plane.cpp
//  first-raytracer
//
//  Created by Chris Taguba on 9/17/23.
//

#include <cmath>
#include "Plane.h"

Plane::Plane() : Shape(PLANE) {
    normal = Vector3(0, 1, 0);
}

Plane::Plane(const Vector3 p, const Vector3 n) : Shape(PLANE, p)  {
    normal = n;
    color = {255, 255, 255, 255};
    specular = 0;
    reflective = 0;
}

Plane::Plane(const Vector3 p, const Vector3 n, const SDL_Color c, const float s, const float r) : Shape(PLANE, p) {
    normal = n;
    color = c;
    specular = s;
    reflective = s;
}
