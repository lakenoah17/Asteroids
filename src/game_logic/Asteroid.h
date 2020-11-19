#pragma once
#include "GameObject.h"

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
	Asteroid(glm::vec2 position, glm::vec2 velocity, AsteroidSize size, float rotation);
	~Asteroid();

	void Update(float deltaTime) override;
	void Draw() override;

private:
	glm::vec2 velocity;
	float rotation;

};