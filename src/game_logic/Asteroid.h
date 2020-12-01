#pragma once
#include "GameObject.h"

/// <summary>
/// Enum used for storing all of the possible sizes of an asteroid
/// </summary>
enum class AsteroidSize {
    SMALL = 0,
    MEDIUM = 1,
    LARGE = 2,
    XLARGE = 3
};

class Asteroid : public GameObject
{
public:
	Asteroid();
	Asteroid(glm::vec2* position, glm::vec2 velocity, AsteroidSize size, float rotation, float timeToSpawn);
	~Asteroid();

	void Update(float deltaTime) override;
	void Draw() override;
	std::tuple<Asteroid*, Asteroid*> SplitAsteroid();

private:
	glm::vec2 velocity;
	float rotation;
	AsteroidSize size;
	float timeToSpawn;

};