#include "Projectile.h"

GLFWwindow* Projectile::currWindow;
unsigned int Projectile::s_NumOfProjectiles;
const unsigned int Projectile::MAX_NUMBER_OF_PROJECTILES;
Projectile* Projectile::s_ActiveProjectiles[MAX_NUMBER_OF_PROJECTILES];

/// <summary>
/// Initializes a Projectile with all of the data necessary to create a Collider object
/// </summary>
/// <param name="x">The top left corner x position of the Collider</param>
/// <param name="y">The top left corner y position of the Collider</param>
/// <param name="width">The width of the Collider</param>
/// <param name="height">The height of the Collider</param>
Projectile::Projectile(float x, float y, float width, float height, float angleToFireAt)
	: GameObject(x, y, width, height)
{
	projectileIndex = s_NumOfProjectiles;
	s_NumOfProjectiles++;
	if (s_NumOfProjectiles > MAX_NUMBER_OF_PROJECTILES)
	{
		delete this;
		return;
	}

	velocity = glm::vec2(4 * cos(angleToFireAt), 4 * sin(angleToFireAt));
	s_ActiveProjectiles[projectileIndex] = this;
}

Projectile::~Projectile()
{
	s_NumOfProjectiles--;
	for (int i = projectileIndex+1; i < s_NumOfProjectiles + projectileIndex+1 && i < MAX_NUMBER_OF_PROJECTILES; i++) {
		s_ActiveProjectiles[i]->ShiftProjectile();
	}
}

void Projectile::Update()
{
	collider->SetXPos(collider->GetXPos() + velocity.x);
	collider->SetYPos(collider->GetYPos() + velocity.y);

	*position += velocity;

	int screenWidth;
	int screenHeight;
	glfwGetWindowSize(currWindow, &screenWidth, &screenHeight);

	if (position->x < -5 || position->x > screenWidth + 5 || position->y < -5 || position->y > screenHeight + 5) {
		s_ActiveProjectiles[projectileIndex] = NULL;
		delete this;
		return;
	}

	renderData->model = glm::translate(renderData->model, glm::vec3(velocity.x, velocity.y, 0));
	renderData->mvp = renderData->proj * renderData->view * renderData->model;
}

void Projectile::ShiftProjectile()
{
	if (this != nullptr && projectileIndex != 0)
	{
		s_ActiveProjectiles[projectileIndex-1] = s_ActiveProjectiles[projectileIndex];
		s_ActiveProjectiles[projectileIndex] = NULL;
		projectileIndex--;
	}
}
