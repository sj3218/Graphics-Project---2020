/*
1. Park Sejeong
2. Project 2
3. CS250
4. Spring 2020
*/

#pragma once
#include "Affine.h"

class Camera {
public:
    Camera(void);
    Camera(Point e, Point t, Vector globalUP, float fov, float aspect, float near, float far);
    
    void ReadingInput(Point newTarget);
    void UpdateVector();
    void UpdateEye(bool front);
    void UpdateTarget();
    
    Camera& GoRight(float distance_increment);
    Camera& GoUp(float distance_increment);

    Camera(const Point& E, const Vector& look, const Vector& vp,
        float fov, float aspect, float near, float far);
    Point Eye(void) const;
    Vector Right(void) const;
    Vector Up(void) const;
    Vector Back(void) const;
    Vector ViewportGeometry(void) const;
    float NearDistance(void) const;
    float FarDistance(void) const;
    Camera& Zoom(float factor);
    Camera& Forward(float distance_increment);
    Camera& Yaw(float angle);
    Camera& Pitch(float angle);
    Camera& Roll(float angle);

private:
    Point eye; //position
    Point target;
    Point spheicalCoord;//(1, alpha, beta)
    Vector look;
    float speed = 0.05f;
    Vector globalUP;

    Vector right, up, back;
    float width, height, distance,
        near, far;
};