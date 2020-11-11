#include "Controller.h"

Controller::Controller(GameObject* parent, glm::vec2* position, float& rotation)
	:parent(parent), parentPosition(position), parentRotation(rotation)
{
}

Controller::~Controller()
{
}

void Controller::Update()
{
	
}

void Controller::MoveForward()
{
	acceleration[0] += thrustMagnitude * acceleration[0] * cos(parentRotation);
	acceleration[1] += thrustMagnitude * acceleration[1] * sin(parentRotation);
	velocity += acceleration;
}

void Controller::MoveLeft()
{
	parentRotation += .2f;
	acceleration[0] = acceleration[0] * cos(parentRotation);
	acceleration[1] = acceleration[1] * sin(parentRotation);

	velocity += acceleration;
}

void Controller::MoveRight()
{
	parentRotation -= .2f;

	acceleration[0] = acceleration[0] * cos(parentRotation);
	acceleration[1] = acceleration[1] * sin(parentRotation);

	velocity += acceleration;
}

void Controller::MoveBackward()
{
	acceleration[0] -= thrustMagnitude * acceleration[0] * cos(parentRotation);
	acceleration[1] -= thrustMagnitude * acceleration[1] * sin(parentRotation);
	velocity += acceleration;
}
