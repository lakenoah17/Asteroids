#pragma once
#include "Projectile.h"

class ProjectileManager
{
private:
	static const unsigned int MAX_NUMBER_OF_PROJECTILES = 10;
	static unsigned int s_NumOfProjectiles;
	static GLFWwindow* currWindow;

	void ShiftProjectile(unsigned int projectileIndex);
	bool CheckProjectileStatus(Projectile* projectile, int screenWidth, int screenHeight);

public:
	static Projectile* s_ActiveProjectiles[MAX_NUMBER_OF_PROJECTILES];

	ProjectileManager(GLFWwindow* currWindow);
	~ProjectileManager();

	void FireNewProjectile(float x, float y, float angleToFireAt);

	void UpdateProjectiles(float deltaTime);
	void DrawProjectiles();

	int GetNumOfProjectiles() { return s_NumOfProjectiles; }
};