//
//  Shape.cpp
//  first-raytracer
//
//  Created by Chris Taguba on 9/17/23.
//

#include "Shape.h"

Shape::Shape(ShapeType type) : SceneObject() {
    this->type = type;
};

Shape::Shape(ShapeType type, Vector3 newPos) : SceneObject(newPos) {
    this->type = type;
    color = {255, 255, 255, 255};
};

Shape::Shape(ShapeType type, Vector3 newPos, SDL_Color c) : SceneObject(newPos) {
    this->type = type;
    color = c;
};

Shape::Shape(ShapeType type, Vector3 newPos, SDL_Color c, float s) : SceneObject(newPos) {
    this->type = type;
    color = c;
    specular = s;
};

Shape::Shape(ShapeType type, Vector3 newPos, SDL_Color c, float s, float r) : SceneObject(newPos) {
    this->type = type;
    color = c;
    specular = s;
    reflective = r;
}

void Shape::printInfo() {};

void Shape::setColor(SDL_Color newColor) {
    color = newColor;
}

void Shape::setSpecular(float newSpecular) {
    specular = newSpecular;
}

void Shape::setReflective(float newReflective) {
    reflective = newReflective;
}
