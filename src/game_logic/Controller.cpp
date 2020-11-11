#include "Controller.h"

Controller::Controller(GameObject* parent, glm::vec2* position, glm::vec4* colliderRect, float& rotation)
	:parent(parent), parentPosition(position), parentColliderRect(colliderRect), parentRotation(rotation)
{
	velocity = glm::vec3(0,0,0);
	acceleration = glm::vec2(0, 0);
}

Controller::~Controller()
{
}

void Controller::Update()
{
	if (glfwGetKey(currWindow, GLFW_KEY_W))
	{
		MoveForward();
	}
	else
	{
		if (acceleration.x <= 0 || acceleration.y <= 0)
		{
			acceleration.x = 0;
			acceleration.y = 0;
			velocity.x = 0;
			velocity.y = 0;
		}
		else
		{
			acceleration -= .05f;
		}
	}

	if (glfwGetKey(currWindow, GLFW_KEY_A))
	{
		MoveLeft();
	}

	if (glfwGetKey(currWindow, GLFW_KEY_D))
	{
		MoveRight();
	}

	velocity.x += acceleration.x;
	velocity.y += acceleration.y;

	parentPosition->x += velocity.x;
	parentPosition->y += velocity.y;

	parentColliderRect->x += velocity.x;
	parentColliderRect->y += velocity.y;
}

void Controller::MoveForward()
{
	acceleration[0] += thrustMagnitude * cos(parentRotation);
	acceleration[1] += thrustMagnitude * sin(parentRotation);
}

void Controller::MoveLeft()
{
	parentRotation += .2f;
	/*acceleration[0] *= cos(parentRotation);
	acceleration[1] *= sin(parentRotation);*/
}

void Controller::MoveRight()
{
	parentRotation -= .2f;

	/*acceleration[0] *= cos(parentRotation);
	acceleration[1] *= sin(parentRotation);*/

	
}

void Controller::MoveBackward()
{
	acceleration[0] -= thrustMagnitude * acceleration[0] * cos(parentRotation);
	acceleration[1] -= thrustMagnitude * acceleration[1] * sin(parentRotation);
}
