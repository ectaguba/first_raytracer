//
//  firstraytracer.cpp
//
//  Created by Chris Taguba on 9/3/23.
//

#include <SDL2/SDL.h>
#include <cmath>
#include <limits>

#include "Vector3.h"
#include "RotationMatrix.h"
#include "SceneObject.h"
#include "Camera.h"
#include "Sphere.h"
#include "Light.h"
#include "AmbientLight.h"
#include "PointLight.h"
#include "DirectionalLight.h"

using namespace std;

// =============
// Global variables
// =============
float Cw = 1280;
float Ch = 720;
float Vw = 1.78;
float Vh = 1;
float projection_plane_z = 1;

const SDL_Color BACKGROUND_COLOR = {0, 0, 0, 255};

const SDL_Color RED = {255, 0, 0, 255};
const SDL_Color GREEN = {0, 255, 0, 255};
const SDL_Color BLUE = {0, 0, 255, 255};
const SDL_Color YELLOW = {255, 255, 0, 255};

const int OBJECT_NOT_SHINY = -1;

// Array of pointers to Sphere objects.
const int NUM_OF_SPHERES = 4;
Sphere* spheres[NUM_OF_SPHERES] = {
    new Sphere(Vector3(0, -1, 3), 1, RED, 500, 0.2),
    new Sphere(Vector3(2, 0, 4), 1, BLUE, 500, 0.3),
    new Sphere(Vector3(-2, 0, 4), 1, GREEN, 10, 0.4),
    new Sphere(Vector3(0, -5001, 0), 5000, YELLOW, 1000, 0.1)
};

// Array of pointers to Light objects.
const int NUM_OF_LIGHTS = 3;
Light* lights[NUM_OF_LIGHTS] = {
    new AmbientLight(0.2),
    new PointLight(0.6, Vector3(2, 1, 0)),
    new DirectionalLight(0.2, Vector3(1, 4, 4))
};

const float EPSILON = numeric_limits<float>::epsilon();
const float INFINITE = numeric_limits<float>::max();

// =============
// Methods
// =============

// Converts 2D canvas coordinates to 3D viewport coordinates
// IMPORTANT: Variables must be floats in order for direction vector to be correct
Vector3 CanvasToViewport(float x, float y) {
    return Vector3( (x) * (Vw/Cw), (y) * (Vh/Ch), projection_plane_z);
};

Vector3 MatrixMult(Vector3 v, RotationMatrix m) {
    float newX = m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z;
    float newY = m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z;
    float newZ = m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z;
    return Vector3(newX, newY, newZ);
};

SDL_Color MultiplyColor(SDL_Color color, float factor) {
    SDL_Color result;
    result.r = static_cast<float>(color.r) * factor;
    result.g = static_cast<float>(color.g) * factor;
    result.b = static_cast<float>(color.b) * factor;
    result.a = color.a; // preserve the alpha value
    return result;
}

SDL_Color AddColor(SDL_Color color1, SDL_Color color2) {
    SDL_Color result;
    result.r = static_cast<float>(color1.r) + static_cast<float>(color2.r);
    result.g = static_cast<float>(color1.g) + static_cast<float>(color2.g);
    result.b = static_cast<float>(color1.b) + static_cast<float>(color2.b);
    result.a = color1.a;
    
    if (result.r > 255) result.r = 255;
    if (result.g > 255) result.g = 255;
    if (result.b > 255) result.b = 255;
    
    return result;
}

void IntersectRaySphere(Vector3 origin, Vector3 direction, Sphere* sphere, float* t1, float* t2) {
    float r = sphere->radius;
    Vector3 CO = origin - sphere->position;
    
    float a = Vector3::Dot(direction, direction);
    float b = 2.0 * Vector3::Dot(CO, direction);
    float c = Vector3::Dot(CO, CO) - (r * r);
    
    float discriminant = (b * b) - (4.0 * a * c);
    if (discriminant < 0) {
        *t1 = INFINITE; // store value in pointer to address of t1
        *t2 = INFINITE; // store value in pointer to address of t2
        return;
    }
    
    *t1 = (-b + sqrt(discriminant)) / (2*a);
    *t2 = (-b - sqrt(discriminant)) / (2*a);
}

void ClosestIntersection(Vector3 origin, Vector3 direction, float t_min, float t_max, float* closest_t, Sphere** closest_sphere) {
    
    *closest_t = INFINITE;
    *closest_sphere = nullptr;
    
    for (int s = 0; s < NUM_OF_SPHERES; s++) {

        float t1, t2; // send addresses to method
        IntersectRaySphere(origin, direction, spheres[s], &t1, &t2);

        if ((t1 > t_min && t1 < t_max) && (t1 < *closest_t)) {
            *closest_t = t1; // store value in pointer pointing to address of closest_t
            *closest_sphere = spheres[s]; // store value in pointer pointing to address of closest_t
        }

        if ((t2 > t_min && t2 < t_max) && (t2 < *closest_t)) {
            *closest_t = t2;
            *closest_sphere = spheres[s];
        }
        
    };
}

float ComputeLighting(Vector3 point, Vector3 normal, Vector3 viewport, float specular) {
    
    float totalIntensity = 0.0;
    Vector3 lightRay;
    
    float t_max;
    
    for (int i = 0; i < NUM_OF_LIGHTS; i++) {
        
        Light* currLight = lights[i]; // save reference to lights array

        switch (currLight->type) {
            case AMBIENT:
                totalIntensity += currLight->intensity;
                continue;
            case POINT:
                lightRay = currLight->getVector() - point;
                t_max = 1.0;
                break;
                
            case DIRECTIONAL:
                lightRay = currLight->getVector();
                t_max = INFINITE;
                break;
        }
        
        // Shadow check
        float shadow_t;
        Sphere* shadow_sphere;
        ClosestIntersection(point, lightRay, 0.01 , t_max, &shadow_t, &shadow_sphere);
        if (shadow_sphere) {
            // if a shadow is in between the point and the light, skip it.
            continue;
        }
        
        // Diffuse
        float n_dot_l = Vector3::Dot(normal, lightRay);
        if (n_dot_l > 0) {
            totalIntensity += (currLight->intensity) * ( n_dot_l / (Vector3::Length(normal) * Vector3::Length(lightRay)) );
        }

        // Specular
        if (specular != OBJECT_NOT_SHINY) {
            Vector3 specRay = ((normal * 2) * Vector3::Dot(normal, lightRay)) - lightRay;
            float sr_dot_v = Vector3::Dot(specRay, viewport);
            if (sr_dot_v > 0) {
                totalIntensity += currLight->intensity * pow( sr_dot_v / (Vector3::Length(specRay) * Vector3::Length(viewport)), specular );
            }
        }
    }
    return totalIntensity;
};

Vector3 reflectRay(Vector3 ray, Vector3 normal) {
    return (normal * 2 * Vector3::Dot(normal, ray)) - ray;
}

SDL_Color TraceRay(Vector3 origin, Vector3 direction, float t_min, float t_max, float recursion_depth) {
    
    float closest_t;
    Sphere* closest_sphere;

    ClosestIntersection(origin, direction, t_min, t_max, &closest_t, &closest_sphere);

    if (!closest_sphere) {
        return BACKGROUND_COLOR;
    }
    
    Vector3 point = origin + (direction * closest_t); // compute intersection
    Vector3 normal = point - closest_sphere->position; // compute sphere normal at closest_t intersection
    normal = normal * pow(Vector3::Length(normal), -1); // normalize normal
    
    float lightIntensity = ComputeLighting(point, normal, direction * -1, closest_sphere->specular);
    if (lightIntensity > 1) lightIntensity = 1; // IMPORTANT: Values over 1 may darken spots.
    
    SDL_Color localColor = MultiplyColor(closest_sphere->color, lightIntensity);
    
    // recursive reflections
    float reflective = closest_sphere->reflective;
    
    // base case
    if (recursion_depth <= 0 || reflective <= 0) {
        return localColor;
    }

    // recursive case
    // TO-DO: Why do smaller values of t_min create bad, glitchy reflections
    Vector3 reflectedRay = reflectRay(direction * -1, normal);
    SDL_Color reflectedColor = TraceRay(point, reflectedRay, 0.1, INFINITE, recursion_depth - 1);

    SDL_Color totalColor;
    totalColor.r = (Uint8)(localColor.r * (1 - reflective) + reflectedColor.r * reflective);
    totalColor.g = (Uint8)(localColor.g * (1 - reflective) + reflectedColor.g * reflective);
    totalColor.b = (Uint8)(localColor.b * (1 - reflective) + reflectedColor.b * reflective);
    totalColor.a = 255;

    return totalColor;
};

int main(int argc, char* args[]) {

    // initialize SDL2
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return -1;
    }
    
    RotationMatrix rotationMatrix = RotationMatrix(0, 45, 0);
    Camera camera = Camera(Vector3(-5, 0, 0), rotationMatrix);
    
    float reflection_depth = 3;
    
    // create window
    SDL_Window* window = SDL_CreateWindow("Raytracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Cw, Ch, SDL_WINDOW_SHOWN);
    
    // create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    for (float x = -Cw/2; x < Cw/2; x++) {
        for (float y = -Ch/2; y < Ch/2; y++) {
            Vector3 direction = MatrixMult( CanvasToViewport(x, y), camera.rotation);
            SDL_Color color = TraceRay(camera.position, direction, 1, INFINITE, reflection_depth);

            // set color
            SDL_SetRenderDrawColor(renderer,
                                   static_cast<int>(color.r),
                                   static_cast<int>(color.g),
                                   static_cast<int>(color.b),
                                   SDL_ALPHA_OPAQUE);

            // draw color (convert from viewport to canvas again)
            SDL_RenderDrawPoint(renderer, ((Cw/2) + x), ((Ch/2) - y - 1));
        }
    }
    
    for (int i = 0; i < NUM_OF_LIGHTS; i++) {
        delete lights[i];
    }
    
    for (int i = 0; i < NUM_OF_SPHERES; i++) {
        delete spheres[i];
    }

    // update the display
    SDL_RenderPresent(renderer);

    // hack to get window to stay up
    SDL_Event e;
    bool quit = false;
    while( quit == false ) {
        while( SDL_PollEvent( &e ) ) {
            if( e.type == SDL_QUIT ) quit = true;
        }
    }
    
    // cleanup and quit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
};
