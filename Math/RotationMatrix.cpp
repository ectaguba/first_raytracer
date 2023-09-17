//
//  RotationMatrix.cpp
//  first-raytracer
//
//  Created by Chris Taguba on 9/17/23.
//

#include "RotationMatrix.h"

RotationMatrix::RotationMatrix() {
    matrix[0][0] = 1;
    matrix[0][1] = 0;
    matrix[0][2] = 0;

    matrix[1][0] = 0;
    matrix[1][1] = 1;
    matrix[1][2] = 0;

    matrix[2][0] = 0;
    matrix[2][1] = 0;
    matrix[2][2] = 1;
}

RotationMatrix::RotationMatrix(float angleX, float angleY, float angleZ) {
    // Convert angles from degrees to radians
    float radX = angleX * M_PI / 180.0;
    float radY = angleY * M_PI / 180.0;
    float radZ = angleZ * M_PI / 180.0;

    // Compute individual rotation matrices
    float cosX = cos(radX);
    float sinX = sin(radX);
    float cosY = cos(radY);
    float sinY = sin(radY);
    float cosZ = cos(radZ);
    float sinZ = sin(radZ);

    matrix[0][0] = cosY * cosZ;
    matrix[0][1] = -cosX * sinZ + sinX * sinY * cosZ;
    matrix[0][2] = sinX * sinZ + cosX * sinY * cosZ;

    matrix[1][0] = cosY * sinZ;
    matrix[1][1] = cosX * cosZ + sinX * sinY * sinZ;
    matrix[1][2] = -sinX * cosZ + cosX * sinY * sinZ;

    matrix[2][0] = -sinY;
    matrix[2][1] = sinX * cosY;
    matrix[2][2] = cosX * cosY;
}

const float* RotationMatrix::operator[](int i) const {
    return matrix[i];
}

