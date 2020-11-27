#include "AsteroidManager.h"

unsigned int AsteroidManager::s_MAX_NUMBER_OF_ASTEROIDS;
Asteroid* AsteroidManager::s_ActiveAsteroids[100];
unsigned int AsteroidManager::s_NumOfAsteroids;
GLFWwindow* AsteroidManager::currWindow;

AsteroidManager::AsteroidManager(GLFWwindow* window)
{
	AsteroidManager::currWindow = window;
}

AsteroidManager::~AsteroidManager()
{
}

void AsteroidManager::UpdateAsteroids(float deltaTime)
{
	for (int i = 0; i < s_NumOfAsteroids; i++)
	{
		s_ActiveAsteroids[i]->Update(deltaTime);
	}


}

void AsteroidManager::DrawAsteroids()
{
	for (int i = 0; i < s_NumOfAsteroids; i++)
	{
		s_ActiveAsteroids[i]->Draw();
	}
}

void AsteroidManager::GenerateAsteroids(unsigned int level)
{
	int screenWidth;
	int screenHeight;
	glfwGetWindowSize(currWindow, &screenWidth, &screenHeight);

	s_NumOfAsteroids = 5 + (level * 5);
	for (int i = 0; i < s_NumOfAsteroids; i++)
	{
		float xPos = ((((float)rand()) / RAND_MAX) * screenWidth ) - 5;
		float yPos;
		if (xPos < -3 || xPos > screenWidth + 3)
		{
			yPos = ((((float)rand()) / RAND_MAX) * screenHeight) - 10;
		}
		else
		{
			yPos = (((float)rand()) / RAND_MAX) >= .5f ? -4 : screenHeight - 10;
		}

		float rotation = ((((float)rand()) / RAND_MAX) * 2 * glm::pi<float>());
		s_ActiveAsteroids[i] = new Asteroid(new glm::vec2(xPos, yPos), glm::vec2(40.0f), AsteroidSize::MEDIUM, rotation, 10.0f);
	}
}

/// <summary>
/// Shifts all of the asteroids to fill space in the array
/// </summary>
void AsteroidManager::ShiftAsteroids()
{
	for (int i = 1; i < s_NumOfAsteroids; i++)
	{
		if (this != nullptr)
		{
			s_ActiveAsteroids[i - 1] = s_ActiveAsteroids[i];
			s_ActiveAsteroids[i] = NULL;
		}
	}
}
