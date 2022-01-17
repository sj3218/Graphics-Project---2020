/*
1. Park Sejeong
2. Project 2
3. CS250
4. Spring 2020
*/

#include "Projection.h"

Affine CameraToWorld(const Camera& cam)
{
    return Affine(cam.Right(), cam.Up(), cam.Back(), cam.Eye());
}

Affine WorldToCamera(const Camera& cam)
{
    return inverse(CameraToWorld(cam));
}

Matrix CameraToNDC(const Camera& cam)
{
    Matrix ndc;
    Vector viewport = cam.ViewportGeometry();
    float viewportWidth = viewport.x;
    float viewportHeight = viewport.y;
    float viewportDistanceTwice = viewport.z * 2.f;

    float nearPlane = cam.NearDistance();
    float farPlane = cam.FarDistance();

    ndc[0].x = viewportDistanceTwice / viewportWidth;
    ndc[1].y = viewportDistanceTwice / viewportHeight;
    ndc[2].z = (nearPlane + farPlane) / (nearPlane - farPlane);
    ndc[2].w = (2 * nearPlane * farPlane) / (nearPlane - farPlane);
    ndc[3].z = -1.f;

    return ndc;

}
