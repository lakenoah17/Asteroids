#include "Controller.h"
#include <iostream>

Controller::Controller(GameObject* parent, glm::vec2* position, glm::vec4* colliderRect, float& rotation)
	:parent(parent), parentPosition(position), parentColliderRect(colliderRect), parentRotation(&rotation)
{
	velocity = glm::vec2(0, 0);
	acceleration = glm::vec2(0, 0);
}

Controller::~Controller()
{
}

void Controller::Update()
{
	if (glm::length(velocity) > 5.0f  || glm::length(velocity) < -5.0f)
	{
		acceleration = glm::vec2(0.0f);
	}

	if (glfwGetKey(currWindow, GLFW_KEY_W))
	{
		MoveForward();
	}
	else
	{
		if (glm::length(acceleration) <= 0.015f || glm::length(acceleration) >= -0.015f)
		{
			acceleration = glm::vec2(0.0f);
		}

		if (velocity.y > 0)
		{
			acceleration.y -= .02f;
		}
		if (velocity.x > 0)
		{
			acceleration.x -= .02f;
		}

		if (velocity.y < 0)
		{
			acceleration.y += .02f;
		}
		if (velocity.x < 0)
		{
			acceleration.x += .02f;
		}
	}

	velocity += acceleration;

	*parentPosition += velocity;

	int screenWidth;
	int screenHeight;
	glfwGetWindowSize(currWindow, &screenWidth, &screenHeight);

	if (parentPosition->x < -5) {
		parentPosition->x = screenWidth + 2.5f;
	}
	if (parentPosition->x > screenWidth + 5) {
		parentPosition->x = -2.5f;
	}

	if (parentPosition->y < -5) {
		parentPosition->y = screenHeight + 2.5f;
	}
	if (parentPosition->y > screenHeight + 5) {
		parentPosition->y = -2.5f;
	}

	if (glfwGetKey(currWindow, GLFW_KEY_A))
	{
		TurnLeft();
	}

	if (glfwGetKey(currWindow, GLFW_KEY_D))
	{
		TurnRight();
	}

	if (glfwGetKey(currWindow, GLFW_KEY_SPACE))
	{
		FireProjectile();
	}

	parentColliderRect->x += velocity.x;
	parentColliderRect->y += velocity.y;
}

void Controller::MoveForward()
{
	acceleration.x += thrustMagnitude * glm::cos(*parentRotation);
	acceleration.y += thrustMagnitude * glm::sin(*parentRotation);
}

void Controller::TurnLeft()
{
	*parentRotation += .1f;
}

void Controller::TurnRight()
{
	*parentRotation -= .1f;
}

void Controller::FireProjectile() {
	new Projectile(parentPosition->x, parentPosition->y, 5, 5, *parentRotation);
}
