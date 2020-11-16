#include "Projectile.h"

GLFWwindow* Projectile::currWindow;
unsigned int Projectile::s_NumOfProjectiles;
Projectile* Projectile::s_ActiveProjectiles[2];

/// <summary>
/// Initializes a Projectile with all of the data necessary to create a Collider object
/// </summary>
/// <param name="x">The top left corner x position of the Collider</param>
/// <param name="y">The top left corner y position of the Collider</param>
/// <param name="width">The width of the Collider</param>
/// <param name="height">The height of the Collider</param>
Projectile::Projectile(float x, float y, float width, float height, float angleToFireAt)
{
	projectileIndex = s_NumOfProjectiles;
	s_NumOfProjectiles++;
	if (s_NumOfProjectiles > 2)
	{
		delete this;
		return;
	}

	//Creates Collider and initializes position of GameObject from the values passed in
	collider = new Collider(x, y, width, height);
	position = new glm::vec2(x + width / 2, y + height / 2);

	//Initializes the verticies at positions specified by the params
	verticies = new float[16]
	{
		x,		   y,		   0.0f, 0.0f,
		x + width, y,          1.0f, 0.0f,
		x + width, y + height, 1.0f, 0.0f,
		x,         y + height, 1.0f, 0.0f
	};

	//Basic rect index array
	indicies = new unsigned int[6]{
		2, 1, 0,
		0, 3, 2
	};

	renderData = Renderer::CreateRenderable("res/shaders/EmptyGameObject.shader", verticies, 16, 4, indicies, 6);

	//Updates the MVP matrix for rendering to match the members of the GameObject
	renderData->model = glm::translate(glm::mat4(1.0f), glm::vec3(collider->GetXPos(), collider->GetYPos(), 0));
	renderData->mvp = renderData->proj * renderData->view * renderData->model;

	velocity = glm::vec3(.05 * cos(angleToFireAt), .05 * sin(angleToFireAt), 0);
	s_ActiveProjectiles[projectileIndex] = this;
}

Projectile::~Projectile()
{
	s_NumOfProjectiles--;
}

void Projectile::Update()
{
	collider->SetXPos(collider->GetXPos() + velocity.x);
	collider->SetYPos(collider->GetYPos() + velocity.y);

	position->x += velocity.x;
	position->y += velocity.y;

	int screenWidth;
	int screenHeight;
	glfwGetWindowSize(currWindow, &screenWidth, &screenHeight);

	if (position->x < -5 || position->x > screenWidth + 5 || position->y < -5 || position->y > screenHeight + 5) {
		s_ActiveProjectiles[projectileIndex] = NULL;
		delete this;
		return;
	}

	renderData->model = glm::translate(glm::mat4(1.0f), glm::vec3(collider->GetXPos(), collider->GetYPos(), 0));
	renderData->mvp = renderData->proj * renderData->view * renderData->model;
}
