/*
1. Park Sejeong
2. Project 2
3. CS250
4. Spring 2020
*/

#pragma once
#include <GL/glew.h>
#include <GL/GL.h>
#include "Shader.h"
#include "CubeMesh.h"

class CubeObject
{
public:
    CubeObject(Shader* s);
    ~CubeObject();

    void DrawCubeObject();
    void GenerateBuffer();
    void SetColor(const Hcoord& c);
    void SetUniforms(Matrix ndc, Matrix camera2world, Vector lightPos);

    Affine GetTransform();
    void SetTransform(Vector t, float r, Vector s, Vector axis);

private:
    Shader* shader;
    GLuint VAO;
    GLuint VBO[2];
    CubeMesh mesh;

    Affine transform;
};

