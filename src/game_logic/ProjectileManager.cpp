#include "ProjectileManager.h"

GLFWwindow* ProjectileManager::currWindow;
unsigned int ProjectileManager::s_NumOfProjectiles;
const unsigned int ProjectileManager::MAX_NUMBER_OF_PROJECTILES;
Projectile* ProjectileManager::s_ActiveProjectiles[MAX_NUMBER_OF_PROJECTILES];

ProjectileManager::ProjectileManager(GLFWwindow* currWindow)
{
	ProjectileManager::currWindow = currWindow;
}

ProjectileManager::~ProjectileManager()
{
}

void ProjectileManager::FireNewProjectile(float x, float y, float angleToFireAt)
{
	if (s_NumOfProjectiles < MAX_NUMBER_OF_PROJECTILES)
	{
		s_ActiveProjectiles[s_NumOfProjectiles] = new Projectile(x, y, 5, 5, angleToFireAt);
		s_NumOfProjectiles++;
	}
}

void ProjectileManager::UpdateProjectiles(float deltaTime)
{
	int screenWidth;
	int screenHeight;
	glfwGetWindowSize(currWindow, &screenWidth, &screenHeight);

	for (int i = 0; i < s_NumOfProjectiles; i++)
	{
		while (s_ActiveProjectiles[i] == nullptr)
		{
			for (int j = 1; j < s_NumOfProjectiles; j++)
			{
				ShiftProjectile(j);
			}

			s_NumOfProjectiles--;
		}

		s_ActiveProjectiles[i]->Update(deltaTime);

		if (!CheckProjectileStatus(s_ActiveProjectiles[i], screenWidth, screenHeight))
		{
			delete s_ActiveProjectiles[i];
			s_ActiveProjectiles[i] = NULL;

			s_NumOfProjectiles--;
			for (int j = i + 1; j < s_NumOfProjectiles + i + 1 && j < MAX_NUMBER_OF_PROJECTILES; j++) {
				ShiftProjectile(j);
			}
			
			i--;
		}
	}
}

void ProjectileManager::DrawProjectiles()
{
	for (int i = 0; i < s_NumOfProjectiles; i++)
	{
		s_ActiveProjectiles[i]->Draw();
	}
}

/// <summary>
/// Shifts the projectiles as far left as it can be in the s_ActiveProjectiles array
/// </summary>
void ProjectileManager::ShiftProjectile(unsigned int projectileIndex)
{
	if (this && projectileIndex != 0 && s_ActiveProjectiles[projectileIndex] && projectileIndex < s_NumOfProjectiles)
	{
		s_ActiveProjectiles[projectileIndex - 1] = s_ActiveProjectiles[projectileIndex];
		s_ActiveProjectiles[projectileIndex] = nullptr;
	}
}

bool ProjectileManager::CheckProjectileStatus(Projectile* projectile, int screenWidth, int screenHeight)
{
	glm::vec2* projPosition = projectile->GetPosition();
	//Returns false if the Projectile is outside the bounds of the window 
	if (projPosition->x < -5 || projPosition->x > screenWidth + 5 || projPosition->y < -5 || projPosition->y > screenHeight + 5) {
		return false;
	}

	//TODO: Add a check for if the projectile collides with an asteroid

	return true;
}
