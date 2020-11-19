#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

#include <thread>

//-1 = Stop execution
//0 = Menu state
//1 = Game state
//2 = Game Over state
static int s_GameState = 0;

GLFWwindow* Controller::currWindow;

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

    Controller::currWindow = window;

    ProjectileManager* projManager = new ProjectileManager(window);

    Player* player = new Player();

    float oldTime = clock();
    float deltaTime = 0.0f;

    Asteroid asteroid;

    while (!glfwWindowShouldClose(window) && s_GameState != -1)
    {
        //Calculates the deltaTime between loops
        float newTime = clock();
        //Changes deltaTime to be in seconds
        deltaTime = (newTime - oldTime) / 1000;
        oldTime = newTime;

        Renderer::Clear();

        projManager->UpdateProjectiles(deltaTime);
        projManager->DrawProjectiles();

        asteroid.Update(deltaTime);
        asteroid.Draw();
        
        player->Update(deltaTime);
        player->Draw();

        GLCall(glfwSwapBuffers(window));

        GLCall(glfwPollEvents());

        if (glfwGetKey(window, GLFW_KEY_ESCAPE))
        {
            s_GameState = -1;
        }
    }
    delete player;

    glfwTerminate();
    return 0;
}