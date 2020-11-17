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

	if (velocity.x > 7.5f || velocity.x < -7.5f)
	{
		acceleration.x = 0;
	}

	if (velocity.y > 7.5f || velocity.y < -7.5f)
	{
		acceleration.y = 0;
	}

	if (glfwGetKey(currWindow, GLFW_KEY_W))
	{
		MoveForward();
	}
	else
	{
		if (acceleration.x <= 0.02f && acceleration.x >= -0.02f)
		{
			acceleration.x = 0;
		}

		if(acceleration.y <= 0.02f && acceleration.y >= -0.02f)
		{
			acceleration.y = 0;
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

	

	parentPosition->x += velocity.x;
	parentPosition->y += velocity.y;

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

	if (glfwGetKey(currWindow, GLFW_KEY_SPACE))
	{
		FireProjectile();
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
	*parentRotation += .1f;
}

void Controller::TurnRight()
{
	*parentRotation -= .1f;
}

void Controller::FireProjectile() {
	if (Projectile::s_NumOfProjectiles < 2)
	{
		new Projectile(parentPosition->x, parentPosition->y, 5, 5, *parentRotation);
	}
}
