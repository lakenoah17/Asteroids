#pragma once
#include "Asteroid.h"

class AsteroidManager
{
public:
	AsteroidManager();
	~AsteroidManager();

	void UpdateAsteroids(float deltaTime);
	void BreakAsteroid();

	void UpdateAsteroidCount(unsigned int numAsteroids);

private:
	static unsigned int s_MAX_NUMBER_OF_ASTEROIDS;
	static Asteroid* s_ActiveAsteroids[100];
	static unsigned int s_NumOfAsteroids;
	
	void ShiftAsteroids();
};