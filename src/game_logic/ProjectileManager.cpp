#include "ProjectileManager.h"

GLFWwindow* ProjectileManager::currWindow;
unsigned int ProjectileManager::s_NumOfProjectiles;
const unsigned int ProjectileManager::MAX_NUMBER_OF_PROJECTILES;
Projectile* ProjectileManager::s_ActiveProjectiles[MAX_NUMBER_OF_PROJECTILES];

/// <summary>
/// Initializes a new Projectile Manager
/// </summary>
/// <param name="currWindow">The window the program is using</param>
ProjectileManager::ProjectileManager(GLFWwindow* currWindow)
{
	ProjectileManager::currWindow = currWindow;
}

ProjectileManager::~ProjectileManager()
{
}

/// <summary>
/// Creates a new Projectile
/// </summary>
/// <param name="x">the x position to create it at</param>
/// <param name="y">the y position to create it at </param>
/// <param name="angleToFireAt">the angle the projectile will travel at</param>
void ProjectileManager::FireNewProjectile(float x, float y, float angleToFireAt)
{
	//Makes sure the new projectile wouldn't exceed the maximum amount of projectiles
	if (s_NumOfProjectiles < MAX_NUMBER_OF_PROJECTILES)
	{
		s_ActiveProjectiles[s_NumOfProjectiles] = new Projectile(x, y, 5, 5, angleToFireAt);
		s_NumOfProjectiles++;
	}
}

/// <summary>
/// Updates all of the projectiles
/// </summary>
/// <param name="deltaTime">The time between this and the last frame</param>
void ProjectileManager::UpdateProjectiles(float deltaTime)
{
	int screenWidth;
	int screenHeight;
	glfwGetWindowSize(currWindow, &screenWidth, &screenHeight);

	for (int i = 0; i < s_NumOfProjectiles; i++)
	{
		//Shifts all of the Projectiles making sure none of them have been destroyed
		while (s_ActiveProjectiles[i] == nullptr && s_NumOfProjectiles)
		{
			//Shifts the Projectiles to the left
			for (int j = 1; j < s_NumOfProjectiles; j++)
			{
				ShiftProjectile(j);
			}

			s_NumOfProjectiles--;
		}

		//If there are existing projectiles update them
		if (s_NumOfProjectiles)
		{
			s_ActiveProjectiles[i]->Update(deltaTime);

			//Checks to see if the porojectile is still on the screen
			if (!CheckProjectileStatus(s_ActiveProjectiles[i], screenWidth, screenHeight))
			{
				delete s_ActiveProjectiles[i];
				s_ActiveProjectiles[i] = NULL;

				for (int j = i + 1; j < s_NumOfProjectiles + i + 1 && j < MAX_NUMBER_OF_PROJECTILES; j++) {
					ShiftProjectile(j);
				}

				s_NumOfProjectiles--;

				i--;
			}
		}
	}
}

/// <summary>
/// Draws all of the valid projectiles to the screen
/// </summary>
void ProjectileManager::DrawProjectiles()
{
	for (int i = 0; i < s_NumOfProjectiles; i++)
	{
		//Checks to see if the proectile is valid
		while (s_ActiveProjectiles[i] == nullptr && s_NumOfProjectiles)
		{
			for (int j = 1; j < s_NumOfProjectiles; j++)
			{
				ShiftProjectile(j);
			}

			s_NumOfProjectiles--;
		}

		s_ActiveProjectiles[i]->Draw();
	}
}

/// <summary>
/// Shifts the projectiles as far left as it can be in the s_ActiveProjectiles array
/// </summary>
/// <param name="projectileIndex">The index of the projectile to check</param>
void ProjectileManager::ShiftProjectile(unsigned int projectileIndex)
{
	if (projectileIndex != 0 && s_ActiveProjectiles[projectileIndex] && projectileIndex < s_NumOfProjectiles)
	{
		s_ActiveProjectiles[projectileIndex - 1] = s_ActiveProjectiles[projectileIndex];
		s_ActiveProjectiles[projectileIndex] = nullptr;
	}
}

/// <summary>
/// Checks to see if the projectile is still valid
/// </summary>
/// <param name="projectile">Projectile to check</param>
/// <param name="screenWidth">The width of the window</param>
/// <param name="screenHeight">The height of the window</param>
/// <returns>Whether the Projectile is still valid or not</returns>
bool ProjectileManager::CheckProjectileStatus(Projectile* projectile, int screenWidth, int screenHeight)
{
	glm::vec2* projPosition = projectile->GetPosition();
	//Returns false if the Projectile is outside the bounds of the window 
	if (projPosition->x < -5 || projPosition->x > screenWidth + 5 || projPosition->y < -5 || projPosition->y > screenHeight + 5) {
		return false;
	}

	return true;
}
