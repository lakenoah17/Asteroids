#include "Asteroid.h"

Asteroid::Asteroid()
{
	//Creates Collider and initializes position of GameObject from the values passed in
	position = new glm::vec2(120, 120);
	collider = new Collider(position->x - 12.5, position->y + 12.5, 25, 25);

	verticies = new float[40]
	{
		 0.0f,  10.0f, 0.0f, 0.0f,
	   -20.0f,  35.0f, 1.0f, 0.0f,
	   -50.0f,  20.0f, 1.0f, 1.0f,
	   -35.0f,   0.0f, 0.0f, 1.0f,
	   -50.0f, -20.0f, 0.0f, 0.0f,
	   -20.0f, -50.0f, 1.0f, 0.0f,
	    20.0f, -30.0f, 1.0f, 1.0f,
	    20.0f, -20.0f, 0.0f, 1.0f,
		50.0f,   0.0f, 0.0f, 0.0f,
		20.0f,  50.0f, 1.0f, 0.0f
	};

	//Basic rect index array
	indicies = new unsigned int[20]{
		0, 1,
		1, 2,
		2, 3,
		3, 4,
		4, 5,
		5, 6,
		6, 7,
		7, 8,
		8, 9,
		9, 0
	};

	rotation = 45;
	velocity = 100.0f * glm::vec2(cos(rotation), sin(rotation));

	renderData = Renderer::CreateRenderable("res/shaders/EmptyGameObject.shader", verticies, 40, 4, indicies, 20);

	//Updates the MVP matrix for rendering to match the members of the GameObject
	renderData->model = glm::translate(glm::mat4(1.0f), glm::vec3(position->x, position->y, 0));
	renderData->mvp = renderData->proj * renderData->view * renderData->model;
}

Asteroid::Asteroid(glm::vec2* position, glm::vec2 velocity, AsteroidSize size, float rotation)
	: velocity(velocity), size(size), rotation(rotation)
{
	position = position;
	//Creates Collider and initializes position of GameObject from the values passed in
	collider = new Collider(position->x - 25, position->y + 25, 50, 50);

	verticies = new float[40]
	{
		 0.0f,  10.0f, 0.0f, 0.0f,
	   -20.0f,  35.0f, 1.0f, 0.0f,
	   -50.0f,  20.0f, 1.0f, 1.0f,
	   -35.0f,   0.0f, 0.0f, 1.0f,
	   -50.0f, -20.0f, 0.0f, 0.0f,
	   -20.0f, -50.0f, 1.0f, 0.0f,
		20.0f, -30.0f, 1.0f, 1.0f,
		20.0f, -20.0f, 0.0f, 1.0f,
		50.0f,   0.0f, 0.0f, 0.0f,
		20.0f,  50.0f, 1.0f, 0.0f
	};

	//Basic rect index array
	indicies = new unsigned int[20]{
		0, 1,
		1, 2,
		2, 3,
		3, 4,
		4, 5,
		5, 6,
		6, 7,
		7, 8,
		8, 9,
		9, 0
	};

	renderData = Renderer::CreateRenderable("res/shaders/EmptyGameObject.shader", verticies, 40, 4, indicies, 20);

	//Updates the MVP matrix for rendering to match the members of the GameObject
	renderData->model = glm::translate(glm::mat4(1.0f), glm::vec3(position->x, position-> y, 0));
	renderData->mvp = renderData->proj * renderData->view * renderData->model;
}

Asteroid::~Asteroid()
{
}

void Asteroid::Update(float deltaTime)
{
	//Adjust both the colliders position and the GameObjects position
	collider->SetXPos(collider->GetXPos() + velocity.x * deltaTime);
	collider->SetYPos(collider->GetYPos() + velocity.y * deltaTime);

	*position += velocity * deltaTime;

	//Adjusts the graphical position
	renderData->model = glm::translate(renderData->model, glm::vec3(velocity.x * deltaTime, velocity.y * deltaTime, 0));
	renderData->mvp = renderData->proj * renderData->view * renderData->model;
}

void Asteroid::Draw() {
	renderData->BindRenderable();
	Renderer::Draw(renderData, GL_LINES);
}
