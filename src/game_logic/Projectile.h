#pragma once
#include "GameObject.h"
#include <GLFW\glfw3.h>

class Projectile : public GameObject
{
public:
	static GLFWwindow* currWindow;

	Projectile(float x, float y, float width, float height, float angleToFireAt);
	~Projectile();
	void Update() override;
	static Projectile* s_ActiveProjectiles[2];
	static unsigned int s_NumOfProjectiles;

private:
	glm::vec3 velocity;
	unsigned int projectileIndex;

};