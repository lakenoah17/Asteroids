#pragma once
#include "Projectile.h"

class ProjectileManager
{
public:
	ProjectileManager(GLFWwindow* currWindow);
	~ProjectileManager();

	void FireNewProjectile(float x, float y, float angleToFireAt);

	void UpdateProjectiles(float deltaTime);
	void DrawProjectiles();

private:
	static const unsigned int MAX_NUMBER_OF_PROJECTILES = 10;
	static unsigned int s_NumOfProjectiles;
	static Projectile* s_ActiveProjectiles[MAX_NUMBER_OF_PROJECTILES];
	static GLFWwindow* currWindow;

	void ShiftProjectile(unsigned int projectileIndex);
	bool CheckProjectileStatus(Projectile* projectile, int screenWidth, int screenHeight);
};