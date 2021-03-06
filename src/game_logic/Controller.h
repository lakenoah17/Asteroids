#pragma once

#include "ProjectileManager.h"
#include "GLFW/glfw3.h"


class Controller
{
public:
	static GLFWwindow* currWindow;
	static float hyperSpaceCooldown;

	Controller(glm::vec2* position, glm::vec4 colliderRect, float& rotation);
	~Controller();

	void Update(float deltaTime);
	glm::vec2 GetVelocity() { return velocity; }

private:
	glm::vec2* parentPosition;
	glm::vec4* parentColliderRect;
	float* parentRotation;
	ProjectileManager* pm;

	glm::vec2 velocity;
	glm::vec2 acceleration;
	const float thrustMagnitude = 0.5f;
	const float rotationalSpeed = 5.0f;
	const float frictionMagnitude = 2.0f;

	//Used to decide the first frame the space key is pressed
	bool firstSpaceFrame = false;
	bool firstFrameF = false;
};