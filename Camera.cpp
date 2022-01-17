/*
1. Park Sejeong
2. Project 2
3. CS250
4. Spring 2020
*/

#include "Camera.h"

const float PI = 4.0f * atan(1.0f);
Camera::Camera(void)
{
    eye = Point(0.f, 0.f, 0.f);
    right = Vector(1.f, 0.f, 0.f);
    up = Vector(0.f, 1.f, 0.f);
    back = Vector(0.f, 0.f, -1.f);

    width = 2.f * static_cast<float>(distance * std::tan(45.f));
    height = width;

    near = 0.1f;
    far = 10.f;
    distance = near;
}

Camera::Camera(Point e, Point t, Vector globalUP, float fov, float aspect, float near, float far)
{
    eye = e;
    target = t;
    this->globalUP = globalUP;
    up = globalUP;
    
    look = normalize(target - eye);
    spheicalCoord = Point(1, std::asin(look.y), std::atan(look.x / look.z)+PI);

    back = -look;
    right = normalize(cross(globalUP,back));

    distance = near;
    width = 2.f * static_cast<float>(distance * std::tan(fov / 2.0f));
    height = width / aspect;

    this->near = near;
    this->far = far;
}

void Camera::ReadingInput(Point newTarget)
{
    spheicalCoord.z += newTarget.x; //beta
    spheicalCoord.y += newTarget.y;  //alpha

    UpdateVector();
    UpdateTarget();
}

void Camera::UpdateVector()
{
    look.x = std::cos(spheicalCoord.y) * std::sin(spheicalCoord.z);
    look.y = std::sin(spheicalCoord.y);
    look.z = std::cos(spheicalCoord.y) * std::cos(spheicalCoord.z);

    look = normalize(look);
    back = -look;
    right = normalize(cross(globalUP, back));
    up = normalize(cross(back, right));
}

void Camera::UpdateEye(bool front)
{
    Hcoord newEye;

    if (front)
    {
        newEye = speed * look;
    }
    else
    {
        newEye = -speed * look;
    }

    eye.x += newEye.x;
    eye.y += newEye.y;
    eye.z += newEye.z;
}

void Camera::UpdateTarget()
{
    target = eye + look;
}

Camera& Camera::GoRight(float distance_increment)
{
    Affine translation = translate(distance_increment * right);
    eye = translation * eye;

    return *this;
}

Camera& Camera::GoUp(float distance_increment)
{
    Affine translation = translate(distance_increment * up);
    eye = translation * eye;

    return *this;
}

Camera::Camera(const Point& E, const Vector& look, const Vector& vp, float fov, float aspect, float near, float far)
{
    eye = E;
    back = -normalize(look);
    right = normalize(cross(vp, back));
    up = normalize(cross(back, right));

    distance = near;
    width = 2.f * static_cast<float>(distance * std::tan(fov / 2.0f));
    height = width / aspect;

    this->near = near;
    this->far = far;
}

Point Camera::Eye(void) const
{
    return eye;
}

Vector Camera::Right(void) const
{
    return right;
}

Vector Camera::Up(void) const
{
    return up;
}

Vector Camera::Back(void) const
{
    return back;
}

Vector Camera::ViewportGeometry(void) const
{
    return Vector(width, height, distance);
}

float Camera::NearDistance(void) const
{
    return near;
}

float Camera::FarDistance(void) const
{
    return far;
}

Camera& Camera::Zoom(float factor)
{
    width *= factor;
    height *= factor;
    return *this;
}

Camera& Camera::Forward(float distance_increment)
{
    Affine translation = translate(-distance_increment * back);
    eye = translation * eye;

    return *this;
}

Camera& Camera::Yaw(float angle)
{
    Affine rotateMatrix = rotate(angle, up);
    right = rotateMatrix * right;
    back = rotateMatrix * back;
    return *this;
}

Camera& Camera::Pitch(float angle)
{
    Affine rotateMatrix = rotate(angle, right);
    up = rotateMatrix * up;
    back = rotateMatrix * back;
    return *this;
}

Camera& Camera::Roll(float angle)
{
    Affine rotateMatrix = rotate(angle, back);
    up = rotateMatrix * up;
    right = rotateMatrix * right;
    return *this;
}
