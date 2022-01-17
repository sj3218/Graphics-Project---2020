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
#include "SnubDodecMesh.h"

class SnubObject
{
public:
    SnubObject(Shader* s, Shader* shadowS);
    ~SnubObject();

    void DrawSnubObject();
    void GenerateBuffer();
    void SetColor(const Hcoord& c);
    void SetUniforms(Matrix ndc, Matrix camera2world, Vector lightPos);
    void SetShadowUniforms(Matrix ndc, Matrix camera2world, Vector lightPos, Matrix shadowMatix);

    Affine GetTransform();
    void SetTransform(Vector t, float r, Vector s, Vector axis);
    void SetTransform(Affine m);

    void SetShadowMatrixUniform(Matrix m);
    void DrawShader();

private:
    Shader* shader;
    Shader* shadowShader;

    GLuint VAO;
    GLuint VBO[2];
    SnubDodecMesh mesh;

    Affine transform;
    Affine shadowMatrix;
};

