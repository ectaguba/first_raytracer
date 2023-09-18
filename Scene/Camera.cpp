//
//  Camera.cpp
//  first-raytracer
//
//  Created by Chris Taguba on 9/17/23.
//
#include "Camera.h"

// Default position and rotation
Camera::Camera() : SceneObject(Vector3(0, 0, 0)) {}

// Given position w/ default rotation
Camera::Camera(Vector3 position) : SceneObject(position) {}

// Given position and rotation
Camera::Camera(Vector3 position, RotationMatrix rotation) : SceneObject(position) {
    this->rotation = rotation;
}
