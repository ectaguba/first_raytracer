//
//  firstraytracer.cpp
//
//  Created by Chris Taguba on 9/3/23.
//

#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

// =============
// Classes
// =============
class Vector3 {
    public:
        double x;
        double y;
        double z;
        
        Vector3() {}
        
        Vector3(double x, double y, double z) {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        
        // Vector addition
        Vector3 operator+(const Vector3& other) const {
            return Vector3(x + other.x, y + other.y, z + other.z);
        }

        // Vector subtraction
        Vector3 operator-(const Vector3& other) const {
            return Vector3(x - other.x, y - other.y, z - other.z);
        }

        // Scalar multiplication
        Vector3 operator*(double scalar) const {
            return Vector3(x * scalar, y * scalar, z * scalar);
        }
    
        bool operator==(const Vector3& other) const {
            return (x == other.x) && (y == other.y) && (z == other.z);
        }

        // Dot product
        static double Dot(const Vector3& v1, const Vector3& v2) {
            return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
        }

        // Vector length
        static double Length(const Vector3& v) {
            return sqrt(Dot(v, v));
        }
};

class SceneObject {
    public:
        Vector3 position;
        SceneObject() {
            this->position = Vector3(0, 0, 0);
        }
        
        SceneObject(Vector3 newPos) {
            this->position = newPos;
        }
};

class Sphere : public SceneObject {
    public:
        double radius;
        SDL_Color color; // struct
        int specular;
    
        Sphere() {
            this->position = Vector3(0, 0, 0);
            
            this->radius = 1;
            
            this->color.r = 255;
            this->color.g = 255;
            this->color.b = 255;
            this->color.a = 255;
        }
        // no color
        Sphere(Vector3 newPos, double radius) {
            this->position = newPos;
            
            this->radius = radius;
            
            this->color.r = 255;
            this->color.g = 255;
            this->color.b = 255;
            this->color.a = 255;
        }
        
        // SDL_Color
        Sphere(Vector3 newPos, double radius, SDL_Color color) {
            this->position = newPos;
            this->radius = radius;
            this->color = color;
        }
    
        // SDL_Color + light
        Sphere(Vector3 newPos, double radius, SDL_Color color, int specular) {
            this->position = newPos;
            this->radius = radius;
            this->color = color;
            this->specular = specular;
        }
};

// Polymorphic base Light class
// Important for calculating light at some point in the scene
enum LightType {
    AMBIENT,
    POINT,
    DIRECTIONAL
};

class Light {
public:
    double intensity;
    LightType type;
    
    Light(double intensity, LightType type) : intensity(intensity), type(type) {}
    
    virtual Vector3 getVector() const {
        return Vector3(0, 0, 0);
    }
};

class AmbientLight : public Light {
public:
    AmbientLight(double intensity) : Light(intensity, AMBIENT) {}
};

class PointLight : public Light {
public:
    Vector3 position;

    PointLight(double intensity, Vector3 position) : Light(intensity, POINT), position(position) {}
    
    Vector3 getVector() const override {
        // Calculate the direction from the light to the position.
        return position;
    }
};

class DirectionalLight : public Light {
public:
    Vector3 direction;
    
    DirectionalLight(double intensity, Vector3 direction) : Light(intensity, DIRECTIONAL), direction(direction) {}
    
    Vector3 getVector() const override {
        // Directional lights have a fixed direction.
        return direction;
    }
};


// =============
// Global variables
// =============
double Cw = 720;
double Ch = 720;
double Vw = 1;
double Vh = 1;
double projection_plane_z = 1;

const SDL_Color BACKGROUND_COLOR = {255, 255, 255, 255}; // white

const SDL_Color RED = {255, 0, 0, 255};
const SDL_Color GREEN = {0, 255, 0, 255};
const SDL_Color BLUE = {0, 0, 255, 255};
const SDL_Color YELLOW = {255, 255, 0, 255};

const int OBJECT_NOT_SHINY = -1;

const int NUM_OF_SPHERES = 4;
Sphere* spheres[NUM_OF_SPHERES] = {
    new Sphere(Vector3(0, -1, 3), 1, RED, 500),
    new Sphere(Vector3(2, 0, 4), 1, BLUE, 500),
    new Sphere(Vector3(-2, 0, 4), 1, GREEN, 10),
    new Sphere(Vector3(0, -5001, 0), 5000, YELLOW, 1000)
};


const int NUM_OF_LIGHTS = 3;
Light* lights[] = {
    new AmbientLight(0.2),
    new PointLight(0.6, Vector3(2, 1, 0)),
    new DirectionalLight(0.2, Vector3(1, 4, 4))
};

const double INFINITE = numeric_limits<double>::max();

// =============
// Methods
// =============

// Converts 2D canvas coordinates to 3D viewport coordinates
// IMPORTANT: Variables must be doubles in order for direction vector to be correct
Vector3 CanvasToViewport(double x, double y) {
    return Vector3( (x) * (Vw/Cw), (y) * (Vh/Ch), projection_plane_z);
};

// TO-DO: Fix specular lighting
double ComputeLighting(Vector3 point, Vector3 normal, Vector3 viewport, int specular) {
    double totalIntensity = 0.0;
    Vector3 lightRay;
    for (int i = 0; i < NUM_OF_LIGHTS; i++) {
        
        Light* currLight = lights[i]; // save reference to lights array

        switch (currLight->type) {
            case AMBIENT:
                totalIntensity += currLight->intensity;
                break;
            case POINT:
                lightRay = currLight->getVector() - point;
                break;
            case DIRECTIONAL:
                lightRay = currLight->getVector();
                break;
        }
        
        // Diffuse
        double n_dot_l = Vector3::Dot(normal, lightRay);
        if (n_dot_l > 0) {
            totalIntensity += (currLight->intensity) * ( n_dot_l / (Vector3::Length(normal) * Vector3::Length(lightRay)) );
        }

//        // Specular
//        if (specular != OBJECT_NOT_SHINY) {
//            Vector3 specRay = (normal * 2 * Vector3::Dot(normal, viewport)) - lightRay ;
//            double sr_dot_v = Vector3::Dot(specRay, viewport);
//            if (sr_dot_v > 0) {
//                totalIntensity += currLight->intensity * pow( sr_dot_v / (Vector3::Length(specRay) * Vector3::Length(viewport)), specular );
//            }
//        }
    }
    return totalIntensity;
};

void IntersectRaySphere(Vector3 origin, Vector3 direction, Sphere* sphere, double* t1, double* t2) {
    double r = sphere->radius;
    Vector3 CO = origin - sphere->position;
    
    double a = Vector3::Dot(direction, direction);
    double b = 2.0 * Vector3::Dot(CO, direction);
    double c = Vector3::Dot(CO, CO) - (r * r);
    
    double discriminant = (b * b) - (4.0 * a * c);
    if (discriminant < 0) {
        *t1 = INFINITE; // Store value in pointer pointing to address of t1
        *t2 = INFINITE; // Store value in pointer pointing to address of t2
        return;
    }
    
    *t1 = (-b + sqrt(discriminant)) / (2*a);
    *t2 = (-b - sqrt(discriminant)) / (2*a);
}

SDL_Color MultiplyColor(SDL_Color color, double factor) {
    SDL_Color result;
    result.r = static_cast<Uint8>(color.r * factor);
    result.g = static_cast<Uint8>(color.g * factor);
    result.b = static_cast<Uint8>(color.b * factor);
    result.a = color.a; // Preserve the alpha value
    return result;
}

SDL_Color TraceRay(Vector3 origin, Vector3 direction, double t_min, double t_max) {
    
    double closest_t = t_max;
    Sphere* closest_sphere = nullptr;

    for (int s = 0; s < NUM_OF_SPHERES; s++) {
        
        double t1, t2; // Send addresses
        IntersectRaySphere(origin, direction, spheres[s], &t1, &t2);
        
        if ((t1 > t_min && t1 < t_max) && (t1 < closest_t)) {
            closest_t = t1;
            closest_sphere = spheres[s];
        }

        if ((t2 > t_min && t2 < t_max) && (t2 < closest_t)) {
            closest_t = t2;
            closest_sphere = spheres[s];
        }
    }; // End for loop

    if (!closest_sphere) {
        return BACKGROUND_COLOR;
    }
    
    Vector3 point = origin + (direction * closest_t); // compute intersection
    Vector3 normal = point - closest_sphere->position; // compute sphere normal at closest_t intersection
    normal = normal * pow(Vector3::Length(normal), -1); // normalize normal
    
    // Parameter viewport is Vector3 V from object to camera
    // Vector3 D points from camera to object
    // Therefore, V = -D
    double lightIntensity = ComputeLighting(point, normal, direction * -1, closest_sphere->specular);
    
    // Multiply the color with the intensity
    SDL_Color modifiedColor = MultiplyColor(closest_sphere->color, lightIntensity);
    
    return modifiedColor;
};


int main(int argc, char* args[]) {
    
    // Initialize SDL2
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return -1;
    }
    
    SceneObject camera = SceneObject(Vector3(0, 0, 0));
    
    // Create window
    SDL_Window* window = SDL_CreateWindow("Raytracer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Cw, Ch, SDL_WINDOW_SHOWN);
    
    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    for (double x = -Cw/2; x < Cw/2; x++) {
        for (double y = -Ch/2; y < Ch/2; y++) {
            Vector3 direction = CanvasToViewport(x, y);
            SDL_Color color = TraceRay(camera.position, direction, 1, INFINITE);

            // Set color
            SDL_SetRenderDrawColor(renderer,
                                   static_cast<int>(color.r),
                                   static_cast<int>(color.g),
                                   static_cast<int>(color.b),
                                   SDL_ALPHA_OPAQUE);

            // Draw color (convert from viewport to canvas again)
            SDL_RenderDrawPoint(renderer, ((Cw/2) + x), ((Ch/2) - y - 1));
        }
    }
    
    for (int i = 0; i < NUM_OF_LIGHTS; i++) {
        delete lights[i];
    }
    
    for (int i = 0; i < NUM_OF_SPHERES; i++) {
        delete spheres[i];
    }

    // Update the display
    SDL_RenderPresent(renderer);

    // Hack to get window to stay up
    SDL_Event e;
    bool quit = false;
    while( quit == false ) {
        while( SDL_PollEvent( &e ) ) {
            if( e.type == SDL_QUIT ) quit = true;
        }
    }
    
    // Cleanup and quit
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
};
