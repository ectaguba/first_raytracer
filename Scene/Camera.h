//
//  Camera.h
//  first-raytracer
//
//  Created by Chris Taguba on 9/17/23.
//

#ifndef Camera_h
#define Camera_h

#include "SceneObject.h"
#include "RotationMatrix.h"

class Camera : public SceneObject {
public:
    RotationMatrix rotation;

    Camera();
    Camera(Vector3 position);
    Camera(Vector3 position, RotationMatrix rotation);
};

#endif /* Camera_h */
