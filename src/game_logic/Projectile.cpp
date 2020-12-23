#include "Projectile.h"

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
	//Intialized the velocity which won't be changed after this point
	velocity = 200.0f * glm::vec2(cos(angleToFireAt), sin(angleToFireAt));
}

/// <summary>
/// Destroys this projectile and shifts all of the other projectiles to fill the empty space created when the projectile is deleted
/// </summary>
Projectile::~Projectile()
{
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

	//Adjusts the graphical position
	renderData->model = glm::translate(renderData->model, glm::vec3(velocity.x * deltaTime, velocity.y * deltaTime, 0));
	renderData->mvp = renderData->proj * renderData->view * renderData->model;
}

/// <summary>
/// Draws the projectile to the screen
/// </summary>
void Projectile::Draw()
{
	renderData->BindRenderable();
	Renderer::Draw(renderData);
}
