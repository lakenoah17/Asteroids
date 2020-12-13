#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "graphics/Renderer.h"
#include "graphics/VertexBufferLayout.h"

#include "game_logic/GameObject.h"
#include "game_logic/Controller.h"
#include "game_logic/Player.h"
#include "game_logic/Asteroid.h"
#include "game_logic/ProjectileManager.h"
#include "game_logic/AsteroidManager.h"

#include "graphics/TextRenderer.h"

#include <thread>

//-1 = Stop execution
//0 = Menu state
//1 = Game state
//2 = Game Over state
static int s_GameState = 0;

GLFWwindow* Controller::currWindow;

FT_Library library;

int main()
{
    #pragma region GLFWInit
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1080, 760, "Asteroids by Noah Shields", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //Sets framerate to Vsync
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cout << "Error" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));

    #pragma endregion

    #pragma region FreeTypeInit
    FT_Error error = FT_Init_FreeType(&library);
    FT_Face fontFace;

    if (error)
    {
        std::cout << "An error has occured with the FreeType library"<<std::endl;
    }
    
    error = FT_New_Face(library,
        "C:/Windows/Fonts/Arial.ttf",
        0,
        &fontFace);

    if (error == FT_Err_Unknown_File_Format)
    {
        std::cout << "Font format not supported" << std::endl;
    }
    else if (error)
    {
        std::cout << "Font broken or can't be read" << std::endl;
    }

    error = FT_Set_Char_Size(
        fontFace,    /* handle to face object           */
        0,       /* char_width in 1/64th of points  */
        16 * 64,   /* char_height in 1/64th of points */
        300,     /* horizontal device resolution    */
        300);   /* vertical device resolution      */
    #pragma endregion

    int levelNum = 1;
    Controller::currWindow = window;

    ProjectileManager* projManager = new ProjectileManager(window);

    AsteroidManager* am = new AsteroidManager(window);
    am->GenerateAsteroids(levelNum);

    Player* player = new Player();

    float oldTime = clock();
    float deltaTime = 0.0f;
    float newTime;

    TextRenderer* text = new TextRenderer(&fontFace);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(window) && s_GameState != -1)
    {
        Renderer::Clear();
        

        text->DrawText(0, 0, "Hello", 5);
        switch (s_GameState)
        {
        case -1:
            break;

        case 0:
        #pragma region MenuState
            if (glfwGetKey(window, GLFW_KEY_ENTER))
            {
                s_GameState = 1;
            }

            break;
        #pragma endregion

        case 1:
        #pragma region GameState
            //Calculates the deltaTime between loops
            newTime = clock();
            //Changes deltaTime to be in seconds
            deltaTime = (newTime - oldTime) / 1000;
            oldTime = newTime;

            am->CheckForCollisions((GameObject**)ProjectileManager::s_ActiveProjectiles, projManager->GetNumOfProjectiles());

            if (player)
            {
                player->Update(deltaTime);
                player->Draw();
            }
            else
            {
                s_GameState = 2;
                continue;
            }

            //Checks for collision between player and asteroids
            if (am->CheckForCollision(player))
            {
                player = nullptr;
            }

            projManager->UpdateProjectiles(deltaTime);
            projManager->DrawProjectiles();

            am->UpdateAsteroids(deltaTime);
            am->DrawAsteroids();

            if (am->GetNumOfAsteroids() == 0)
            {
                levelNum++;
                am->GenerateAsteroids(levelNum);
            }

            break;
        #pragma endregion

        case 2:
        #pragma region GameOverState
            if (glfwGetKey(window, GLFW_KEY_ENTER))
            {
                s_GameState = 0;
            }
            break;
        #pragma endregion

        default:
            break;
        }
        
        GLCall(glfwSwapBuffers(window));

        GLCall(glfwPollEvents());

        if (glfwGetKey(window, GLFW_KEY_ESCAPE))
        {
            s_GameState = -1;
        }
    }

    if (player)
    {
        delete player;
    }
    
    glfwTerminate();
    return 0;
}