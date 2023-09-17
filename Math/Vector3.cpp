//
//  Vector3.cpp
//  first-raytracer
//
//  Created by Chris Taguba on 9/17/23.
//

#include "Vector3.h"

Vector3::Vector3() : x(0.0f), y(0.0f), z(0.0f) {}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3 Vector3::operator+(const Vector3& other) const {
    return Vector3(x + other.x, y + other.y, z + other.z);
}

Vector3 Vector3::operator-(const Vector3& other) const {
    return Vector3(x - other.x, y - other.y, z - other.z);
}

Vector3 Vector3::operator*(float scalar) const {
    return Vector3(x * scalar, y * scalar, z * scalar);
}

bool Vector3::operator==(const Vector3& other) const {
    return (x == other.x) && (y == other.y) && (z == other.z);
}

float Vector3::Dot(const Vector3& v1, const Vector3& v2) {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

float Vector3::Length(const Vector3& v) {
    return std::sqrt(Dot(v, v));
}

void Vector3::printCoords() {
    std::cout << "(" << x << "," << y << "," << z << ")" << std::endl;
}
