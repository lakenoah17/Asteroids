#include "Player.h"

Player::Player()
{
	//Creates Collider and initializes position of GameObject from the values passed in
	collider = new Collider(100, 100, 25, 25);
	position = new glm::vec2(112.5f, 112.5f);

	//Initializes the verticies at positions specified by the params
	verticies = new float[16]
	{
		112.5f, 100.0f,	0.0f, 0.0f,
		100.0f, 125.0f, 1.0f, 0.0f,
		112.5f, 120.0f, 1.0f, 0.0f,
		125.0f, 125.0f, 1.0f, 0.0f
	};

	//Basic rect index array
	indicies = new unsigned int[8]{
		0, 1,
		1, 2,
		2, 3,
		3, 0
	};

	controls = new Controller(this, position, collider->GetRect(), rotation);

	renderData = Renderer::CreateRenderable("res/shaders/EmptyGameObject.shader", verticies, 16, 4, indicies, 8);

	//Updates the MVP matrix for rendering to match the members of the GameObject
	renderData->model = glm::translate(glm::mat4(1.0f), glm::vec3(collider->GetXPos(), collider->GetYPos(), 0));
	renderData->mvp = renderData->proj * renderData->view * renderData->model;
}

void Player::Update() {
	controls->Update();

	//Updates the MVP matrix for rendering to match the members of the GameObject
	renderData->model = glm::rotate(renderData->model, rotation, glm::vec3(0, 0, 1));
	renderData->model = glm::translate(renderData->model, glm::vec3(0));
	renderData->mvp = renderData->proj * renderData->view * renderData->model;
}
