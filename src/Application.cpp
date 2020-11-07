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

int main(void)
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

        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));


        Renderer renderer;

        float spaceshipVertPos[] = {
             0.0f,  100.0f, 0.0f, 0.0f,
           -75.0f, -100.0f, 1.0f, 0.0f,
             0.0f,  -50.0f, 1.0f, 1.0f,
            75.0f, -100.0f, 0.0f, 1.0f
        };

        unsigned int spaceShipIndicies[] = {
            0, 1, 
            1, 2, 
            2, 3,
            3, 0
        };

        Shader *spaceshipShader = new Shader("res/shaders/Spaceship.shader");

        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));
        glm::mat4 mvp = proj * view * model;
        spaceshipShader->Bind();
        spaceshipShader->SetUniformMat4f("u_MVP", mvp);
        spaceshipShader->SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

        VertexBuffer *vb = new VertexBuffer(spaceshipVertPos, 4 * 4 * sizeof(float));

        VertexArray *vao = new VertexArray();

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);

        vao->AddBuffer(*vb, layout);

        IndexBuffer ib(spaceShipIndicies, 2 * 4);

        spaceshipShader->Bind();


        while (!glfwWindowShouldClose(window))
        {
            renderer.Clear();

            renderer.Draw(*vao, ib, *spaceshipShader, GL_LINES);

            GLCall(glfwSwapBuffers(window));

            GLCall(glfwPollEvents());
        }
    }

    glfwTerminate();
    return 0;
}