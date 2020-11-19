#pragma once
#include "GameObject.h"
#include <GLFW\glfw3.h>

class Projectile : public GameObject
{
private:
	glm::vec2 velocity;

public:
	Projectile(float x, float y, float width, float height, float angleToFireAt);
	~Projectile();
	void Update(float deltaTime) override;
	void Draw() override;

};