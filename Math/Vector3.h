//
//  Vector3.h
//  first-raytracer
//
//  Created by Chris Taguba on 9/17/23.
//

#ifndef Vector3_h
#define Vector3_h

#include <cmath>
#include <iostream>

class Vector3 {
public:
    float x;
    float y;
    float z;

    Vector3();
    Vector3(float x, float y, float z);

    Vector3 operator+(const Vector3& other) const;
    Vector3 operator-(const Vector3& other) const;
    Vector3 operator*(float scalar) const;
    bool operator==(const Vector3& other) const;

    static float Dot(const Vector3& v1, const Vector3& v2);
    static float Length(const Vector3& v);

    void printCoords();
};

#endif /* Vector3_h */
