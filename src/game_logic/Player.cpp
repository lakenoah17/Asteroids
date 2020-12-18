#include "Player.h"

Player::Player()
{
	//Getting the size of the window to allow for screen wrapping
	int windowWidth;
	int windowHeight;
	glfwGetWindowSize(Controller::currWindow, &windowWidth, &windowHeight);

	//Creates Collider and initializes position of GameObject from the values passed in
	position = new glm::vec2(windowWidth/2, windowHeight/2);
	collider = new Collider(position->x - 12.5, position->y + 12.5, 25, 25);

	//Initializes the verticies relative to the position in world space
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

	controls = new Controller(position, collider->GetRect(), rotation);

	pm = new ProjectileManager(Controller::currWindow);

	renderData = Renderer::CreateRenderable("res/shaders/Spaceship.shader", verticies, 16, 4, indicies, 8);

	//Updates the MVP matrix for rendering to match the members of the GameObject
	renderData->model = glm::translate(glm::mat4(1.0f), glm::vec3(position->x, position->y, 0));
	renderData->mvp = renderData->proj * renderData->view * renderData->model;
}

/// <summary>
/// Updates the players position based on calculations from the controllers update method
/// </summary>
/// <param name="deltaTime">The time between this frame and the last frame</param>
void Player::Update(float deltaTime) {
	controls->Update(deltaTime);

	collider->SetXPos(position->x - 12.5f);
	collider->SetYPos(position->y + 12.5f);

	//Updates the MVP matrix for rendering to match the members of the GameObject
	renderData->model = glm::translate(glm::mat4(1.0f), glm::vec3(position->x, position->y, 0));
	renderData->model = glm::rotate(renderData->model, rotation - glm::half_pi<float>(), glm::vec3(0, 0, 1));
	renderData->mvp = renderData->proj * renderData->view * renderData->model;
}

/// <summary>
/// Binds and draws a player to the screen
/// </summary>
void Player::Draw()
{
	renderData->BindRenderable();
	Renderer::Draw(renderData, GL_LINES);
}
