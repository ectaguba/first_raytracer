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
    cosX = cos(radX);
    sinX = sin(radX);
    cosY = cos(radY);
    sinY = sin(radY);
    cosZ = cos(radZ);
    sinZ = sin(radZ);

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

void RotationMatrix::rotateX(float angleX) {
    float radX = angleX * M_PI / 180.0;
    
    cosX = cos(radX);
    sinX = sin(radX);
    
    matrix[0][1] = -cosX * sinZ + sinX * sinY * cosZ;
    matrix[0][2] = sinX * sinZ + cosX * sinY * cosZ;
    
    matrix[1][1] = cosX * cosZ + sinX * sinY * sinZ;
    matrix[1][2] = -sinX * cosZ + cosX * sinY * sinZ;
    
    matrix[2][1] = sinX * cosY;
    matrix[2][2] = cosX * cosY;
}

void RotationMatrix::rotateY(float angleY) {
    float radY = angleY * M_PI / 180.0;
    
    cosY = cos(radY);
    sinY = sin(radY);
    
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

void RotationMatrix::rotateZ(float angleZ) {
    float radZ = angleZ * M_PI / 180.0;
    
    cosZ = cos(radZ);
    sinZ = sin(radZ);
    
    matrix[0][0] = cosY * cosZ;
    matrix[0][1] = -cosX * sinZ + sinX * sinY * cosZ;
    matrix[0][2] = sinX * sinZ + cosX * sinY * cosZ;

    matrix[1][0] = cosY * sinZ;
    matrix[1][1] = cosX * cosZ + sinX * sinY * sinZ;
    matrix[1][2] = -sinX * cosZ + cosX * sinY * sinZ;
}

