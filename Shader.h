/*
1. Park Sejeong
2. Project 2
3. CS250
4. Spring 2020
*/
#pragma once
#include <GL/glew.h>
#include <GL/GL.h>
#include "Affine.h"
#include <string>
#include <iostream>

enum vertexShader
{
    model,
    shadow
};

class Shader
{
public:
    Shader(vertexShader type);
    ~Shader();

    GLuint CompileShader(const char* shaderText, GLenum shaderType);
    void SetColor(const Hcoord& c);
    void ClearBuffers(const Hcoord& c);

    void UseProgam();
    void UnUseProgram();

    void SetUniformMatrix(const GLchar* location, Matrix matrix);
    void SetUniformVector(const GLchar* location, Vector vec);

    void EnableDepth();
    void DisableDepth();

private:
    vertexShader vertexShaderType;
    GLint program;
    GLint aposition;
    GLint ucolor;

};

