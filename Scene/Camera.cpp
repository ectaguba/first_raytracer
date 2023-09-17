//
//  Camera.cpp
//  first-raytracer
//
//  Created by Chris Taguba on 9/17/23.
//
#include "Camera.h"

Camera::Camera() : rotation(RotationMatrix()) {
    position = Vector3(0, 0, 0);
}

Camera::Camera(Vector3 position) : rotation(RotationMatrix()) {
    this->position = position;
}

Camera::Camera(Vector3 position, RotationMatrix rotation) : rotation(rotation) {
    this->position = position;
}
