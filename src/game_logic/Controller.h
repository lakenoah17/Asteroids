#pragma once

#include "GameObject.h"

class Controller
{
public:
	Controller(GameObject* parent, glm::vec2* position, float& rotation);
	~Controller();

	void Update();
	
private:
	GameObject* parent;
	glm::vec2* parentPosition;
	float& parentRotation;

	glm::vec2 velocity;
	glm::vec2 acceleration;
	const float thrustMagnitude = 0.2f;

	void MoveForward();
	void MoveLeft();
	void MoveRight();
	void MoveBackward();
};