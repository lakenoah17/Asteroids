#include "GameObject.h"

GameObject::GameObject()
{
	position = new glm::vec2(5, 5);
	collider = new Collider(0, 0, 10, 10);

	verticies = new float[16]
	{
		0.0f, 0.0f, 0.0f, 0.0f,
		5.0f, 0.0f, 1.0f, 0.0f,
		5.0f, 5.0f, 1.0f, 1.0f,
		0.0f, 5.0f, 0.0f, 1.0f
	};

	indicies = new unsigned int[6]{
		2, 1, 0,
		0, 3, 2
	};
	
	renderer = new Renderer("../../res/shaders/Spaceship.shader", verticies, indicies);
}

GameObject::GameObject(Collider* collider)
	: collider(collider)
{
	position = new glm::vec2(collider->GetXPos() + collider->GetWidth() / 2, collider->GetYPos() + collider->GetHeight() / 2);

	verticies = new float[16]
	{
		collider->GetXPos(),						collider->GetYPos(),						 0.0f, 0.0f,
		collider->GetXPos() + collider->GetWidth(), collider->GetYPos(),					     1.0f, 0.0f,
		collider->GetXPos() + collider->GetWidth(), collider->GetYPos() + collider->GetHeight(), 1.0f, 0.0f,
		collider->GetXPos(),					    collider->GetYPos() + collider->GetHeight(), 1.0f, 0.0f
	};

	indicies = new unsigned int[6]{
		2, 1, 0,
		0, 3, 2
	};

	renderer = new Renderer("../../res/shaders/Spaceship.shader", verticies, indicies);
}

GameObject::GameObject(float x, float y, float width, float height)
{
	collider = new Collider(x, y, width, height);
	position = new glm::vec2(x + width/2, y + height/2);

	verticies = new float[16]
	{
		x,		   y,		   0.0f, 0.0f,
		x + width, y,          1.0f, 0.0f,
		x + width, y + height, 1.0f, 0.0f,
		x,         y + height, 1.0f, 0.0f
	};

	indicies = new unsigned int[6]{
		2, 1, 0,
		0, 3, 2
	};

	renderer = new Renderer("../../res/shaders/Spaceship.shader", verticies, indicies);
}

GameObject::~GameObject()
{
	delete collider;
	delete position;
	delete verticies;
	delete indicies;
}

void GameObject::Draw()
{
	renderer->Clear();
	renderer->Draw();
}
