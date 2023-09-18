//
//  Scene.cpp
//  first-raytracer
//
//  Created by Chris Taguba on 9/17/23.
//
#include "SceneObject.h"

SceneObject::SceneObject() {
    position = Vector3(0, 0, 0);
}

SceneObject::SceneObject(Vector3 newPos) {
    position = newPos;
}

void SceneObject::setPosition(Vector3 newPosition) {
    position = newPosition;
}
