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

    RotationMatrix();
    RotationMatrix(float angleX, float angleY, float angleZ);

    const float* operator[](int i) const;
};

#endif /* RotationMatrix_h */
