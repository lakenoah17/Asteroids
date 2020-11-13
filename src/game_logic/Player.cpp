#include "Player.h"

Player::Player()
{
	//Creates Collider and initializes position of GameObject from the values passed in
	collider = new Collider(100, 100, 25, 25);
	position = new glm::vec2(112.5f, 112.5f);

	//Initializes the verticies at positions specified by the params
	verticies = new float[16]
	{
		  0.0f,  12.5f, 0.0f, 0.0f,
		-12.5f, -12.5f, 1.0f, 0.0f,
		  0.0f,  -7.5f, 1.0f, 1.0f,
		 12.5f, -12.5f, 0.0f, 1.0f
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
	renderData->model = glm::translate(glm::mat4(1.0f), glm::vec3(position->x, position->y, 0));
	renderData->mvp = renderData->proj * renderData->view * renderData->model;
}

void Player::Update() {
	controls->Update();

	//Updates the MVP matrix for rendering to match the members of the GameObject
	renderData->mvp = renderData->proj * renderData->view * renderData->model;
}
