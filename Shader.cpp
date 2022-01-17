/*
1. Park Sejeong
2. Project 2
3. CS250
4. Spring 2020
*/
#include "Shader.h"

namespace
{
    const char* vertex_shader_text =
        R"(
            #version 330

	    layout(location = 0) in vec4 position;
	    layout(location = 1) in vec3 aNormal;

            uniform mat4 transform;
            uniform mat4 NdcMatrix;
            uniform mat4 cameraMatrix;

            out vec3 Normal;
            out vec3 FragPos;
            
	    void main()
	    {
                FragPos = vec3(transform * position);
	        gl_Position = transpose(NdcMatrix) * transpose(inverse(cameraMatrix)) * transform * position;
                Normal = aNormal;
	    }
    )";

    const char* fragment_shader_text =
        R"(
        #version 330 core
        
        in vec3 Normal;
        in vec3 FragPos;

        out vec4 FragColor;
        uniform vec3 color;
        uniform vec3 lightPos;

        void main()
        {
            vec3 norm = normalize(Normal);
            vec3 lightDir = normalize(lightPos - FragPos);
            float diff = max(dot(norm, lightDir), 0.0);
            vec3 diffuse = diff * color;
            FragColor = vec4(diffuse, 1);
        }
)";

    const char* vertex_shadow_shader_text =
        R"(
            #version 330

	    layout(location = 0) in vec4 position;

            uniform mat4 transform;
            uniform mat4 NdcMatrix;
            uniform mat4 cameraMatrix;
            uniform mat4 shadowMatrix;
            
	    void main()
	    {
	        gl_Position = transpose(NdcMatrix) * transpose(inverse(cameraMatrix)) * transpose(shadowMatrix)* transform * position;
	    }
    )";

    const char* fragment_shadow_shader_text =
        R"(
        #version 330 core

        out vec4 FragColor;
        uniform vec3 color;

        void main()
        {
            FragColor = vec4(0,0,0, 1);
        }
)";
}

Shader::Shader(vertexShader type)
{
    vertexShaderType = type;

    GLint errorCheck;
    GLuint vertexShader;
    GLuint fragmentShader;

    if (vertexShaderType == model)
    {
        vertexShader = CompileShader(vertex_shader_text, GL_VERTEX_SHADER);
        fragmentShader = CompileShader(fragment_shader_text, GL_FRAGMENT_SHADER);
    }
    else
    {
        vertexShader = CompileShader(vertex_shadow_shader_text, GL_VERTEX_SHADER);
        fragmentShader = CompileShader(fragment_shadow_shader_text, GL_FRAGMENT_SHADER);
    }

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &errorCheck);

    if (errorCheck != GL_TRUE)
    {
        GLint length = 0;
        GLchar* message = new GLchar[length];

        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
        glGetProgramInfoLog(program, length, &length, message);

        std::cerr << "fail to link\n" << message << "\n";
        delete[] message;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    aposition = glGetAttribLocation(program, "position");
    ucolor = glGetUniformLocation(program, "color");
    
    EnableDepth();
}

Shader::~Shader()
{
    glDeleteProgram(program);
}

GLuint Shader::CompileShader(const char* shaderText, GLenum shaderType)
{
    GLint errorCheck;

    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderText, NULL);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &errorCheck);

    if (errorCheck != GL_TRUE)
    {
        std::string error;
        if (shaderType == GL_VERTEX_SHADER)
            error += "fail to Vertex shader compile\n";
        else if (shaderType == GL_FRAGMENT_SHADER)
            error += "fail to Fragment shader compile\n";

        GLint length = 0;
        GLchar* message = new GLchar[length];
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        glGetShaderInfoLog(shader, length, &length, message);

        std::cout << error << message << "\n";
        delete[] message;
    }
    return shader;
}

void Shader::SetColor(const Hcoord& c)
{
    glUniform3f(ucolor, c.x, c.y, c.z);
}

void Shader::ClearBuffers(const Hcoord& c)
{
    glClearColor(c.x, c.y, c.z, c.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Shader::UseProgam()
{
    glUseProgram(program);
}

void Shader::UnUseProgram()
{
    glUseProgram(0);
}

void Shader::SetUniformMatrix(const GLchar* location, Matrix matrix)
{
    GLint uniformLocation = glGetUniformLocation(program, location);

    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &matrix.row->x);
}

void Shader::SetUniformVector(const GLchar* location, Vector vec)
{
    GLint uniformLocation = glGetUniformLocation(program, location);
    glUniform3f(uniformLocation, vec.x, vec.y, vec.z);
}

void Shader::EnableDepth()
{
    glEnable(GL_DEPTH_TEST);
}

void Shader::DisableDepth()
{
    glDisable(GL_DEPTH_TEST);
}
