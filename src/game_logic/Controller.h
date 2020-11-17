#pragma once

#include "Projectile.h"
#include "GLFW/glfw3.h"


class Controller
{
public:
	static GLFWwindow* currWindow;

	Controller(GameObject* parent, glm::vec2* position, glm::vec4* colliderRect, float& rotation);
	~Controller();

	void Update();
	glm::vec2 GetVelocity() { return velocity; }

private:
	GameObject* parent;
	glm::vec2* parentPosition;
	glm::vec4* parentColliderRect;
	float* parentRotation;

	glm::vec2 velocity;
	glm::vec2 acceleration;
	const float thrustMagnitude = 0.005f;

	void MoveForward();
	void TurnLeft();
	void TurnRight();
	void FireProjectile();
};