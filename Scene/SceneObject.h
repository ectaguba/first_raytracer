//
//  Scene.h
//  first-raytracer
//
//  Created by Chris Taguba on 9/17/23.
//

#ifndef Scene_h
#define Scene_h

#include "Vector3.h"
#include "RotationMatrix.h"

class SceneObject {
public:
    
    Vector3 position;
    
    SceneObject();
    SceneObject(Vector3 newPos);

    void setPosition(Vector3 newPosition);
};

#endif /* Scene_h */
