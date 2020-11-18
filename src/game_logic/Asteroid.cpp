#include "Asteroid.h"

Asteroid::Asteroid()
{
	//Creates Collider and initializes position of GameObject from the values passed in
	position = new glm::vec2(120, 120);
	collider = new Collider(position->x - 12.5, position->y + 12.5, 25, 25);

	//Initializes the verticies relative to the position in world space
	verticies = new float[16]
	{
		position->x,         position->y + 12.5f, 0.0f, 0.0f,
		position->x - 12.5f, position->y - 12.5f, 1.0f, 0.0f,
		position->x,         position->y - 7.5f,  1.0f, 1.0f,
		position->x + 12.5f, position->y - 12.5f, 0.0f, 1.0f
	};

	verticies = new float[16]
	{
		 0.0f,    12.5f, 0.0f, 0.0f,
		-12.5f,  -12.5f, 1.0f, 0.0f,
		 0.0f,   -7.5f,  1.0f, 1.0f,
		 12.5f,  -12.5f, 0.0f, 1.0f
	};

	//Basic rect index array
	indicies = new unsigned int[8]{
		0, 1,
		1, 2,
		2, 3,
		3, 0
	};

	renderData = Renderer::CreateRenderable("res/shaders/EmptyGameObject.shader", verticies, 16, 4, indicies, 8);

	//Updates the MVP matrix for rendering to match the members of the GameObject
	renderData->model = glm::translate(glm::mat4(1.0f), glm::vec3(position->x, position->y, 0));
	renderData->mvp = renderData->proj * renderData->view * renderData->model;
}

Asteroid::Asteroid(glm::vec2 position, glm::vec2 velocity, AsteroidSize size, float rotation)
{
}

Asteroid::~Asteroid()
{
}

void Asteroid::Update()
{
}
