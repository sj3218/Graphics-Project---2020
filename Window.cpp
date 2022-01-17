/*
1. Park Sejeong
2. Project 2
3. CS250
4. Spring 2020
*/
#include "Window.h"

const Point O(0, 0, 0);
const Vector EX(1, 0, 0),
EY(0, 1, 0),
EZ(0, 0, 1);
const float PI = 4.0f * atan(1.0f);

Window::Window(int W, int H, Camera* camera) : width(W), height(H)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Failed to init SDL\n";
        return;
    }
    std::string programName = "CS250 Project 02 - s.park";
    mWindow = SDL_CreateWindow(programName.c_str(), SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

    if (!mWindow)
    {
        std::cout << "Unable to create window\n";
        CheckSDLError(__LINE__);
        return;
    }

    mContext = SDL_GL_CreateContext(mWindow);

    SetOpenGLAttributes();

    SDL_GL_SetSwapInterval(1);

    glewExperimental = GL_TRUE;
    glewInit();

    PrintSDL_GL_Attributes();
    cam = camera;
}

void Window::CheckSDLError(int line)
{
    std::string error = SDL_GetError();

    if (error != "")
    {
        std::cout << "SLD Error : " << error << std::endl;

        if (line != -1)
            std::cout << "\nLine : " << line << std::endl;

        SDL_ClearError();
    }
}

bool Window::SetOpenGLAttributes()
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    return true;
}

void Window::PrintSDL_GL_Attributes()
{
    int value = 0;
    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &value);
    std::cout << "SDL_GL_CONTEXT_MAJOR_VERSION : " << value << std::endl;

    SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &value);
    std::cout << "SDL_GL_CONTEXT_MINOR_VERSION: " << value << std::endl;
}

bool Window::IsDone()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            return true;

        const float dist_increment = 0.1f, zoom_increment = 0.95f;

        int currMouseX, currMouseY;
        
        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                return true;
                break;
            case SDLK_q:
                cam->GoUp(dist_increment);
                break;
            case SDLK_e:
                cam->GoUp(-dist_increment);
                break;
            case SDLK_UP:
                cam->Forward(dist_increment);
                break;
            case SDLK_DOWN:
                cam->Forward(-dist_increment);
                break;
            case SDLK_RIGHT:
                cam->GoRight(dist_increment);
                break;
            case SDLK_LEFT:
                cam->GoRight(-dist_increment);
                break;
            default:
                break;
            }
        }
        else if (event.type == SDL_MOUSEMOTION)
        {
            SDL_GetMouseState(&currMouseX, &currMouseY);
            
            if (canMouseMove)
            {
                Point diff(static_cast<float>(mouseX - currMouseX)/(width/2), static_cast<float>(mouseY - currMouseY)/ (height / 2));
                cam->ReadingInput(diff);
            }
            mouseX = currMouseX;
            mouseY = currMouseY;
        }
        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                if (canMouseMove == true)
                {
                    canMouseMove = false;
                }
                else
                {
                    canMouseMove = true;
                }
            }
        }
    }
    SDL_GL_SwapWindow(mWindow);
    return false;
}

void Window::Cleanup()
{
    SDL_GL_DeleteContext(mContext);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

Camera Window::GetCamera()
{
    return *cam;
}

