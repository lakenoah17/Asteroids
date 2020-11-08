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

void Draw();
void Update();

int main()
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Learning OpenGL", NULL, NULL);
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

    //Scopes the draw call so there is no infinite loop from the index 
    //buffer not being destroyed before glfw is terminated causing the 
    //error checker to loop infinetly because it doesn't have a valid context
    {

        //TODO: Code for later to use for mvp matricies

        //Sets up all of the matrices for a Model View Projection Matrix hardcoded atm
        //proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        //view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
        //model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
        //mvp = &(proj * view * model);



        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));

        GameObject temp1(200, 200, 200, 200);
        GameObject temp2(0, 0, 200, 200);

        while (!glfwWindowShouldClose(window))
        {
            temp1.Draw();

            temp2.Draw();

            GLCall(glfwSwapBuffers(window));

            GLCall(glfwPollEvents());
        }
    }

    glfwTerminate();
    return 0;
}

void Draw() {

}

void Update() {

}