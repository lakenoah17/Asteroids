#pragma once
#include "Asteroid.h"
#include "GLFW/glfw3.h"

class AsteroidManager
{
public:
	AsteroidManager(GLFWwindow* window);
	~AsteroidManager();

	void UpdateAsteroids(float deltaTime);
	void DrawAsteroids();

	void GenerateAsteroids(unsigned int level);

	bool CheckForCollision(GameObject* objToCompareAgainst);
	void CheckForCollisions(GameObject* objsToCompareAgainst[], int numOfObjs);

	unsigned int GetNumOfAsteroids() { return s_NumOfAsteroids; }

private:
	static unsigned int s_MAX_NUMBER_OF_ASTEROIDS;
	static Asteroid* s_ActiveAsteroids[10000];
	static unsigned int s_NumOfAsteroids;
	static GLFWwindow* currWindow;
	
	void ShiftAsteroids();
};