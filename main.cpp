/*
1. Park Sejeong
2. Project 2
3. CS250
4. Spring 2020
*/
#include "Window.h"
#include "Shader.h"
#include "CubeObject.h"
#include "SnubObject.h"
#include "Camera.h"
#include "Projection.h"

const unsigned int WIDTH = 600;
const unsigned int HEIGHT = 600;

const Point O(0, 0, 0);
const Vector EX(1, 0, 0),
EY(0, 1, 0),
EZ(0, 0, 1);
const float PI = 4.0f * atan(1.0f);
const float PI10 = PI / 40;

const Vector BLUE(0, 0, 1),
YELLOW(1, 1, 0.2f),
LIGHTYELLOW(1, 1, 0.6f),
RED(1, 0, 0),
GREEN(0, 1, 0),
PINK(1, 0.226f, 0.906f),
LIGHTPINK(1, 0.68f, 0.906f),
DEEPPINK(1, 0, 0.43f),
SALMON(1, 0.453f, 0.453f),
SILVER(0.91f, 0.91f, 0.91f),
BROWN(0.6f, 0.4f, 0);

int main(int /*argc*/, char* /*argv*/[])
{
    Camera cam(Point(0, 1, 1), Point(0, 1, 0), EY,0.5f * PI, 1, 0.01f, 10);
    Vector lightPosition(0,30,-3);
    Window window(WIDTH, HEIGHT, &cam);
    Shader* shader = new Shader(model);
    Shader* shadowShader = new Shader(shadow);
    Matrix ndc;
    Matrix cameratoworld;
    Matrix shadowMatrix = BuildShadow(lightPosition);
    float degree = 0.f;

    CubeObject receiver(shader);
    receiver.SetTransform(Vector(0, 0, -0), 0, Vector(5, 0.05f, 5), EY);
    SnubObject snub(shader, shadowShader);
    snub.SetTransform(Vector(2, 4, -3), 0, Vector(0.25f, 0.25f, 0.25f), EY);
    SnubObject snub2(shader, shadowShader);
    snub2.SetTransform(Vector(-2, 4, -3), 0, Vector(0.25f, 0.25f, 0.25f), EY);
    SnubObject snub3(shader, shadowShader);
    snub3.SetTransform(Vector(2, 4, 0), 0, Vector(0.25f, 0.25f, 0.25f), EY);
    SnubObject snub4(shader, shadowShader);
    snub4.SetTransform(Vector(-2, 4, 0), 0, Vector(0.25f, 0.25f, 0.25f), EY);

    
    while (!window.IsDone())
    {
        shader->ClearBuffers(LIGHTPINK);
        lightPosition.x += std::cos(degree)*1.5f;
        lightPosition.z += std::sin(degree)*1.5f;
        degree += PI10;
        shadowMatrix = BuildShadow(lightPosition);

        shader->UseProgam();
        cameratoworld = CameraToWorld(cam);
        ndc = CameraToNDC(cam);

        receiver.SetUniforms(ndc, cameratoworld, lightPosition);
        receiver.SetColor(GREEN);
        receiver.DrawCubeObject();
        shader->UnUseProgram();

        shadowShader->UseProgam();
        snub.SetShadowUniforms(ndc, cameratoworld, lightPosition, shadowMatrix);
        snub.DrawShader();
        snub2.SetShadowUniforms(ndc, cameratoworld, lightPosition, shadowMatrix);
        snub2.DrawShader();
        snub3.SetShadowUniforms(ndc, cameratoworld, lightPosition, shadowMatrix);
        snub3.DrawShader();
        snub4.SetShadowUniforms(ndc, cameratoworld, lightPosition, shadowMatrix);
        snub4.DrawShader();
        shadowShader->UnUseProgram();

        shader->UseProgam();
        snub.SetUniforms(ndc, cameratoworld, lightPosition);
        snub.SetColor(LIGHTYELLOW);
        snub.DrawSnubObject();

        snub2.SetUniforms(ndc, cameratoworld, lightPosition);
        snub2.SetColor(RED);
        snub2.DrawSnubObject();

        snub3.SetUniforms(ndc, cameratoworld, lightPosition);
        snub3.SetColor(SALMON);
        snub3.DrawSnubObject();

        snub4.SetUniforms(ndc, cameratoworld, lightPosition);
        snub4.SetColor(DEEPPINK);
        snub4.DrawSnubObject();
        shader->UnUseProgram();
    }

    window.Cleanup();
    delete shader;
    delete shadowShader;
    return 0;
}