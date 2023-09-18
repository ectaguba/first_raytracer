//
//  RotationMatrix.h
//  first-raytracer
//
//  Created by Chris Taguba on 9/17/23.
//

#ifndef RotationMatrix_h
#define RotationMatrix_h

#include <cmath>

class RotationMatrix {
public:
    
    float matrix[3][3];
    
    float cosX;
    float sinX;
    float cosY;
    float sinY;
    float cosZ;
    float sinZ;

    RotationMatrix();
    RotationMatrix(float angleX, float angleY, float angleZ);

    const float* operator[](int i) const;
    
    void rotateX(float angleX);
    void rotateY(float angleY);
    void rotateZ(float angleZ);
};

#endif /* RotationMatrix_h */
