#include "Controller.h"
#include <iostream>

/// <summary>
/// Constructs a Controller
/// </summary>
/// <param name="position">A pointer to the position vector of the parent</param>
/// <param name="colliderRect">A pointer to the collider rectangle of the parent</param>
/// <param name="rotation">A reference to the rotation (in radians) of the parent</param>
Controller::Controller(glm::vec2* position, glm::vec4* colliderRect, float& rotation)
	:parentPosition(position), parentColliderRect(colliderRect), parentRotation(&rotation)
{
	velocity = glm::vec2(0, 0);
	acceleration = glm::vec2(0, 0);
}

Controller::~Controller()
{
}

/// <summary>
/// Updates the velocity, acceleration, and position vectors
/// </summary>
void Controller::Update()
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
		TurnLeft();
	}
	//Rotates the object clockwise when the D key is pressed
	if (glfwGetKey(currWindow, GLFW_KEY_D))
	{
		TurnRight();
	}
	#pragma endregion

	#pragma region Move Obj forward
	//Moves the play forward when the W key is pressed
	if (glfwGetKey(currWindow, GLFW_KEY_W))
	{
		MoveForward();
	}
	else
	{
		//This condition stops the user after slowing down instead of kind of jiggling back and forth
		if (glm::length(acceleration) <= 0.015f || glm::length(acceleration) >= -0.015f)
		{
			acceleration = glm::vec2(0.0f);
		}

		//These conditions apply a "friction" to the object. They decide which way is 
		//opposite to the direction of motion and slow the object down over time
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

	parentColliderRect->x += velocity.x;
	parentColliderRect->y += velocity.y;
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
		FireProjectile();
		firstSpaceFrame = true;
	}
	else if(!glfwGetKey(currWindow, GLFW_KEY_SPACE))
	{
		firstSpaceFrame = false;
	}
}

/// <summary>
/// Increases the acceleration by the thrust magnitude in the direction of the parents rotation
/// </summary>
void Controller::MoveForward()
{
	acceleration.x += thrustMagnitude * glm::cos(*parentRotation);
	acceleration.y += thrustMagnitude * glm::sin(*parentRotation);
}

/// <summary>
/// Rotates the parent object counter-clockwise
/// </summary>
void Controller::TurnLeft()
{
	*parentRotation += .1f;
}

/// <summary>
/// Rotates the parent object clockwise
/// </summary>
void Controller::TurnRight()
{
	*parentRotation -= .1f;
}

/// <summary>
/// Fires a projectile
/// </summary>
void Controller::FireProjectile() {
	//No need to store a reference as the Projectile class handles everything itself
	new Projectile(parentPosition->x, parentPosition->y, 5, 5, *parentRotation);
}
