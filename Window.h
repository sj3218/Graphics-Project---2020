/*
1. Park Sejeong
2. Project 2
3. CS250
4. Spring 2020
*/
#pragma once
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <vector>

#include "Camera.h"


class Window
{
public:
    Window(int W, int H, Camera* camera);
    void CheckSDLError(int line = -1);
    bool SetOpenGLAttributes();
    void PrintSDL_GL_Attributes();
    bool IsDone();
    void Cleanup();

    Camera GetCamera();

private:
    int width;
    int height;

    bool canMouseMove = false;
    int mouseX = 0;
    int mouseY = 0;

    Camera* cam;
    SDL_Window* mWindow;
    SDL_GLContext mContext;

};