//
//  Scene.h
//  first-raytracer
//
//  Created by Chris Taguba on 9/17/23.
//

#ifndef Scene_h
#define Scene_h

#include "Vector3.h"

class SceneObject {
public:
    Vector3 position;

    SceneObject();
    SceneObject(Vector3 newPos);
};

#endif /* Scene_h */
