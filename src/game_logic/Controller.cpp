#include "Controller.h"
#include <iostream>

float Controller::hyperSpaceCooldown;

/// <summary>
/// Constructs a Controller
/// </summary>
/// <param name="position">A pointer to the position vector of the parent</param>
/// <param name="colliderRect">A pointer to the collider rectangle of the parent</param>
/// <param name="rotation">A reference to the rotation (in radians) of the parent</param>
Controller::Controller(glm::vec2* position, glm::vec4 colliderRect, float& rotation)
	:parentPosition(position), parentColliderRect(&colliderRect), parentRotation(&rotation)
{
	velocity = glm::vec2(0, 0);
	acceleration = glm::vec2(0, 0);
	hyperSpaceCooldown = 0.0f;
}

Controller::~Controller()
{
}

/// <summary>
/// Updates the velocity, acceleration, and position vectors
/// </summary>
/// <param name="deltaTime">The time between this frame and the last frame</param>
void Controller::Update(float deltaTime)
{
	//This maxes out the velocity at a little over 5.0f making it so the player can't go too fast
	if (glm::length(velocity) > 5.0f  || glm::length(velocity) < -5.0f)
	{
		acceleration = glm::vec2(0.0f);
	}

	#pragma region Rotate Obj
	//Rotates the object counter-clockwise when the A key is pressed
	if (glfwGetKey(currWindow, GLFW_KEY_A))
	{
		*parentRotation += rotationalSpeed * deltaTime;
	}
	//Rotates the object clockwise when the D key is pressed
	if (glfwGetKey(currWindow, GLFW_KEY_D))
	{
		*parentRotation -= rotationalSpeed * deltaTime;
	}
	#pragma endregion

	#pragma region Move Obj forward
	//Moves the play forward when the W key is pressed
	if (glfwGetKey(currWindow, GLFW_KEY_W))
	{
		acceleration.x += thrustMagnitude * glm::cos(*parentRotation) * deltaTime;
		acceleration.y += thrustMagnitude * glm::sin(*parentRotation) * deltaTime;
	}
	else
	{
		//This condition stops the user after slowing down instead of kind of jiggling back and forth
		if (glm::length(acceleration) <= 0.015f || glm::length(acceleration) >= -0.015f)
		{
			acceleration = glm::vec2(0.0f);
		}

		if (glm::length(velocity) >= 0.01f || glm::length(velocity) <= -0.01f) {
			//These conditions apply a "friction" to the object. They decide which way is 
			//opposite to the direction of motion and slow the object down over time
			if (velocity.y > 0)
			{
				acceleration.y -= frictionMagnitude * deltaTime;
			}
			if (velocity.x > 0)
			{
				acceleration.x -= frictionMagnitude * deltaTime;
			}

			if (velocity.y < 0)
			{
				acceleration.y += frictionMagnitude * deltaTime;
			}
			if (velocity.x < 0)
			{
				acceleration.x += frictionMagnitude * deltaTime;
			}
		}
	}

	velocity += acceleration;
	*parentPosition += velocity;

	if (glfwGetKey(currWindow, GLFW_KEY_F) && !hyperSpaceCooldown)
	{
		(*parentPosition).x += 75 * cos(*parentRotation);
		(*parentPosition).y += 75 * sin(*parentRotation);

		hyperSpaceCooldown = 5.0f;
	}
	
	if (hyperSpaceCooldown > 0)
	{
		hyperSpaceCooldown -= deltaTime;

		if (hyperSpaceCooldown < 0)
		{
			hyperSpaceCooldown = 0;
		}
	}

	#pragma endregion

	#pragma region Screen Wrapping
	//Getting the size of the window to allow for screen wrapping
	int windowWidth;
	int windowHeight;
	glfwGetWindowSize(currWindow, &windowWidth, &windowHeight);

	//Wraps the object from the left side to the right side
	if (parentPosition->x < -2.5) {
		parentPosition->x = windowWidth - 3.0f;
	}
	//Wraps the object from the left side to the right side
	if (parentPosition->x > windowWidth) {
		parentPosition->x = -2.5f;
	}

	//Wraps the object from the bottom to the top (OpenGL uses Left-Bottom coordinate system)
	if (parentPosition->y < -2.0) {
		parentPosition->y = windowHeight - 5.0f;
	}
	//Wraps the object from the top to the bottom (OpenGL uses Left-Bottom coordinate system)
	if (parentPosition->y > windowHeight - 5.0f) {
		parentPosition->y = -2.0f;
	}

	#pragma endregion

	//Fires a projectile when the Space key is pressed. 
	//The key needs to be released to allow for another projectile to be fired
	if (glfwGetKey(currWindow, GLFW_KEY_SPACE) && !firstSpaceFrame)
	{
		pm->FireNewProjectile(parentPosition->x, parentPosition->y, *parentRotation);

		firstSpaceFrame = true;
	}
	else if(!glfwGetKey(currWindow, GLFW_KEY_SPACE))
	{
		firstSpaceFrame = false;
	}
}
