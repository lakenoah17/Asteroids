#include "Controller.h"

Controller::Controller(GameObject* parent, glm::vec2* position, glm::vec4* colliderRect, float& rotation)
	:parent(parent), parentPosition(position), parentColliderRect(colliderRect), parentRotation(&rotation)
{
	velocity = glm::vec3(0,0,0);
	acceleration = glm::vec2(0, 0);
}

Controller::~Controller()
{
}

void Controller::Update()
{
	velocity.x += acceleration.x;
	velocity.y += acceleration.y;

	if (glfwGetKey(currWindow, GLFW_KEY_W))
	{
		MoveForward();
	}
	else
	{
		

		if (velocity.x < 0.06f && velocity.x > -0.06f)
		{
			acceleration.x = 0;
			velocity.x = 0;
		}

		if(velocity.y < 0.05f && velocity.y > -0.05f)
		{
			acceleration.y = 0;
			velocity.y = 0;
		}

		if (velocity.y > 0 || velocity.x > 0)
		{
			acceleration -= .05f;
		}
	}

	parentPosition->x += velocity.x;
	parentPosition->y += velocity.y;

	parentColliderRect->x += velocity.x;
	parentColliderRect->y += velocity.y;

	parent->GetDrawData()->model = glm::translate(glm::mat4(1.0f), glm::vec3(parentPosition->x, parentPosition->y, 0));

	if (glfwGetKey(currWindow, GLFW_KEY_A))
	{
		TurnLeft();
	}

	if (glfwGetKey(currWindow, GLFW_KEY_D))
	{
		TurnRight();
	}
	
	parent->GetDrawData()->model = glm::rotate(parent->GetDrawData()->model, *parentRotation - glm::half_pi<float>(), glm::vec3(0, 0, 1));
}

void Controller::MoveForward()
{
	acceleration.x += thrustMagnitude * cos(*parentRotation);
	acceleration.y += thrustMagnitude * sin(*parentRotation);
}

void Controller::TurnLeft()
{
	*parentRotation += .05f;
}

void Controller::TurnRight()
{
	*parentRotation -= .05f;
}

void Controller::MoveBackward()
{
	acceleration[0] -= thrustMagnitude * acceleration[0] * cos(*parentRotation);
	acceleration[1] -= thrustMagnitude * acceleration[1] * sin(*parentRotation);
}
