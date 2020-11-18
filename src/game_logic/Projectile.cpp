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

	//If this projectile would be over the maximum number of Projectiles it deletes itself
	if (s_NumOfProjectiles > MAX_NUMBER_OF_PROJECTILES)
	{
		delete this;
		return;
	}

	//Intialized the velocity which won't be changed after this point
	velocity = 200.0f * glm::vec2(cos(angleToFireAt), sin(angleToFireAt));
	s_ActiveProjectiles[projectileIndex] = this;
}

/// <summary>
/// Destroys this projectile and shifts all of the other projectiles to fill the empty space created when the projectile is deleted
/// </summary>
Projectile::~Projectile()
{
	s_NumOfProjectiles--;
	for (int i = projectileIndex+1; i < s_NumOfProjectiles + projectileIndex+1 && i < MAX_NUMBER_OF_PROJECTILES; i++) {
		s_ActiveProjectiles[i]->ShiftProjectile();
	}
}

/// <summary>
/// Updates the position of the Projectile based on the velocity and decides whether it should be deleted or not
/// </summary>
/// <param name="deltaTime">The time between this frame and the last frame</param>
void Projectile::Update(float deltaTime)
{
	//Adjust both the colliders position and the GameObjects position
	collider->SetXPos(collider->GetXPos() + velocity.x * deltaTime);
	collider->SetYPos(collider->GetYPos() + velocity.y * deltaTime);

	*position += velocity * deltaTime;

	int screenWidth;
	int screenHeight;
	glfwGetWindowSize(currWindow, &screenWidth, &screenHeight);

	//Deletes this projectile if it is outside of the bounds of the window
	if (position->x < -5 || position->x > screenWidth + 5 || position->y < -5 || position->y > screenHeight + 5) {
		s_ActiveProjectiles[projectileIndex] = NULL;
		delete this;
		return;
	}

	//Adjusts the graphical position
	renderData->model = glm::translate(renderData->model, glm::vec3(velocity.x * deltaTime, velocity.y * deltaTime, 0));
	renderData->mvp = renderData->proj * renderData->view * renderData->model;
}

/// <summary>
/// Shifts the projectile as far left as it can be in the s_ActiveProjectiles array
/// </summary>
void Projectile::ShiftProjectile()
{
	if (this != nullptr && projectileIndex != 0)
	{
		s_ActiveProjectiles[projectileIndex-1] = s_ActiveProjectiles[projectileIndex];
		s_ActiveProjectiles[projectileIndex] = NULL;
		projectileIndex--;
	}
}
