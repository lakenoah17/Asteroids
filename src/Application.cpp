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
    window = glfwCreateWindow(1080, 760, "Learning OpenGL", NULL, NULL);
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

    Renderer renderer;

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));

    #pragma endregion

    Controller::currWindow = window;

    std::list<GameObject> gameObjects;

    GameObject temp2(100, 100, 50, 100);
    GameObject temp1(0, 0, 200, 200);
    Player player;

    gameObjects.push_back(temp1);
    gameObjects.push_back(temp2);

    Projectile proj(10.0f, 10.0f, 10.0f, 10.0f, 45.0f);

    while (!glfwWindowShouldClose(window) && s_GameState != -1)
    {
        renderer.Clear();

        player.Update();
        player.GetDrawData()->BindRenderable();
        renderer.Draw(player.GetDrawData(), GL_LINES);

        proj.Update();
        proj.GetDrawData()->BindRenderable();
        renderer.Draw(proj.GetDrawData());
        

        GLCall(glfwSwapBuffers(window));

        GLCall(glfwPollEvents());

        if (glfwGetKey(window, GLFW_KEY_ESCAPE))
        {
            s_GameState = -1;
        }
    }

    glfwTerminate();
    return 0;
}