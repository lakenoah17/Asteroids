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
        "C:/Windows/Fonts/AGENCYR.ttf",
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

    error = FT_Set_Pixel_Sizes(
        fontFace,
        0,
        128
    );
    #pragma endregion

    //Getting the size of the window to allow for screen wrapping
    int windowWidth;
    int windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    #pragma region Game Logic Intializations
    int levelNum = 1;
    Controller::currWindow = window;

    ProjectileManager* projManager = new ProjectileManager(window);

    AsteroidManager* am = new AsteroidManager(window);
    am->GenerateAsteroids(levelNum);

    Player* player = new Player();

    int numLives = 3;
    int score = 0;
    unsigned int oldNumAsts;

    float oldTime = clock();
    float deltaTime = 0.0f;
    float newTime;

    TextRenderer* text = new TextRenderer(&fontFace);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    #pragma endregion

    while (!glfwWindowShouldClose(window) && s_GameState != -1)
    {
        Renderer::Clear();
        
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

            text->DrawText(325, 400, "Asteroids!", 1, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
            text->DrawText(1350, 250, "Press Enter to start", .3, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

            break;
        #pragma endregion

        case 1:
        #pragma region GameState

            //Calculates the deltaTime between loops
            newTime = clock();
            //Changes deltaTime to be in seconds
            deltaTime = (newTime - oldTime) / 1000;
            oldTime = newTime;

            oldNumAsts = am->GetNumOfAsteroids();

            am->CheckForCollisions((GameObject**)ProjectileManager::s_ActiveProjectiles, projManager->GetNumOfProjectiles());

            //Keeps track of score system
            if (am->GetNumOfAsteroids() > oldNumAsts)
            {
                score += ((oldNumAsts + 2) - am->GetNumOfAsteroids()) * 100;
            }
            else if (am->GetNumOfAsteroids() < oldNumAsts)
            {
                score += (oldNumAsts - am->GetNumOfAsteroids()) * 100;
            }
            
            text->DrawText(25, windowHeight * 4 - 125, "Score: " + std::to_string(score), .25, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

            if (player)
            {
                player->Update(deltaTime);
                player->Draw();
            }
            else
            {
                numLives--;

                if (numLives == -1)
                {
                    s_GameState = 2;
                }
                else
                {
                    player = new Player();
                }
                continue;
            }

            //Draws the visual for lives left to the screen
            for (int i = 0; i < numLives; i++)
            {
                Renderer::Draw(player->GetPlayerRenderable(), GL_LINES, 20 + i * 28, windowHeight - 75);
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
            text->DrawText(315, 400, "Game Over!", 1, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
            text->DrawText(1500, 475, "Final Score: " + std::to_string(score), .3, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
            text->DrawText(1150, 250, "Press enter to return to menu", .3, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

            if (glfwGetKey(window, GLFW_KEY_ENTER))
            {
                s_GameState = 0;

                levelNum = 1;
                Controller::currWindow = window;

                delete projManager;
                delete am;
                if (player)
                {
                    delete player;
                }

                projManager = new ProjectileManager(window);

                am = new AsteroidManager(window);
                am->GenerateAsteroids(levelNum);

                player = new Player();

                oldTime = clock();
                deltaTime = 0.0f;

                score = 0;
            }
            break;
        #pragma endregion

        default:
            break;
        }
        
        GLCall(glfwSwapBuffers(window));

        GLCall(glfwPollEvents());

        if (glfwGetKey(window, GLFW_KEY_ESCAPE)){
            s_GameState = -1;
        }
    }

    if (player)
    {
        delete player;
    }
    
    FT_Done_Face(fontFace);
    FT_Done_FreeType(library);
    glfwTerminate();
    return 0;
}