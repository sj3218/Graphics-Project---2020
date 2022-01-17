/*
1. Park Sejeong
2. Project 2
3. CS250
4. Spring 2020
*/
#include "SnubObject.h"

SnubObject::SnubObject(Shader* s, Shader* shadowS)
{
    GenerateBuffer();
    shader = s;
    shadowShader = shadowS;
}

SnubObject::~SnubObject()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(2, VBO);
}

void SnubObject::DrawSnubObject()
{
    glBindVertexArray(VAO);
    shader->SetUniformMatrix("transform", transform);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>((mesh.GetBuffers().size())));
}

void SnubObject::GenerateBuffer()
{
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
    glBufferData(GL_ARRAY_BUFFER, mesh.GetBuffers().size() * sizeof(GL_FLOAT), &mesh.GetBuffers().at(0), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(0);

    glGenBuffers(1, &VBO[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
    glBufferData(GL_ARRAY_BUFFER, mesh.GetNormal().size() * sizeof(GL_FLOAT), &mesh.GetNormal().at(0), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glEnableVertexAttribArray(1);
}

void SnubObject::SetColor(const Hcoord& c)
{
    shader->SetColor(c);
}

void SnubObject::SetUniforms(Matrix ndc, Matrix camera2world, Vector lightPos)
{
    shader->SetUniformMatrix("NdcMatrix", ndc);
    shader->SetUniformMatrix("cameraMatrix", camera2world);
    shader->SetUniformVector("lightPos", lightPos);
}

void SnubObject::SetShadowUniforms(Matrix ndc, Matrix camera2world, Vector lightPos, Matrix shadowMatix)
{   
    shadowShader->SetUniformMatrix("transform", transform);
    shadowShader->SetUniformMatrix("NdcMatrix", ndc);
    shadowShader->SetUniformMatrix("cameraMatrix", camera2world);
    shadowShader->SetUniformVector("lightPos", lightPos);
    SetShadowMatrixUniform(shadowMatix);
}

Affine SnubObject::GetTransform()
{
    return transform;
}

void SnubObject::SetTransform(Vector t, float r, Vector s, Vector axis)
{
    transform = transpose(translate(t)) * transpose(rotate(r, axis)) * scale(s.x, s.y, s.z);
    shader->SetUniformMatrix("transform", transform);
}

void SnubObject::SetTransform(Affine m)
{
    transform = m;
}

void SnubObject::SetShadowMatrixUniform(Matrix m)
{
    shadowShader->SetUniformMatrix("shadowMatrix", m);
}

void SnubObject::DrawShader()
{
    glBindVertexArray(VAO);
    shadowShader->DisableDepth();
    shadowShader->SetUniformMatrix("transform", transform);
    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>((mesh.GetBuffers().size())));
    shadowShader->EnableDepth();
}
