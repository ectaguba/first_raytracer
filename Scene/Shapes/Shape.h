//
//  Shape.h
//  first-raytracer
//
//  Created by Chris Taguba on 9/17/23.
//

#ifndef Shape_h
#define Shape_h

#include <SDL2/SDL.h>
#include "SceneObject.h"

enum ShapeType {
    SPHERE,
    PLANE
};
    
class Shape : public SceneObject {
public:
    
    ShapeType type;
    SDL_Color color;
    float specular;
    float reflective;
    
    Shape(ShapeType type);
    
    Shape(ShapeType type, Vector3 newPos);

    Shape(ShapeType type, Vector3 newPos, SDL_Color c);
    
    Shape(ShapeType type, Vector3 newPos, SDL_Color c, float s);
    
    Shape(ShapeType type, Vector3 newPos, SDL_Color c, float s, float r);
    
    virtual void printInfo();
    
    void setColor(SDL_Color newColor);

    void setSpecular(float newSpecular);

    void setReflective(float newReflective);
    
};

#endif /* Shape_h */
