#pragma once
#include "GameObject.h"
#include <GLFW\glfw3.h>

class Projectile : public GameObject
{
private:
	glm::vec2 velocity;
	unsigned int projectileIndex;

public:
	static GLFWwindow* currWindow;
	static const unsigned int MAX_NUMBER_OF_PROJECTILES = 10;

	Projectile(float x, float y, float width, float height, float angleToFireAt);
	~Projectile();
	void Update() override;
	static Projectile* s_ActiveProjectiles[MAX_NUMBER_OF_PROJECTILES];
	static unsigned int s_NumOfProjectiles;

	void ShiftProjectile();

};