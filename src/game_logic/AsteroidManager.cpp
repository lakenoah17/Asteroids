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

void AsteroidManager::BreakAsteroid()
{
}

//Possibly unneeded
void AsteroidManager::UpdateAsteroidCount(unsigned int numAsteroids)
{
}

void AsteroidManager::GenerateAsteroids(unsigned int level)
{
	int screenWidth;
	int screenHeight;
	glfwGetWindowSize(currWindow, &screenWidth, &screenHeight);

	s_NumOfAsteroids = 5 + (level * 5);
	for (int i = 0; i < s_NumOfAsteroids; i++)
	{
		float xPos = (rand() - 5) * screenWidth;
		float yPos;
		if (xPos < -3 || xPos > screenWidth + 3)
		{
			yPos = (rand() - 5) * screenHeight;
		}
		else
		{
			yPos = rand() >= .5f ? -4 : screenHeight + 4;
		}
		s_ActiveAsteroids[i] = new Asteroid(&glm::vec2(xPos,yPos), glm::vec2(.5f), AsteroidSize::SMALL, 1, 10.0f);
	}
}

void AsteroidManager::ShiftAsteroids()
{
}
