#pragma once
#include "Collider.h"
#include "../graphics/Renderer.h"

class GameObject
{
protected:
	//Position is at the top left of the container
	Collider* collider;

	//Position is at the center of the rectangle
	glm::vec2*  position;
	//The rotation in radians of the GameObject
	float rotation = 0.0f;

	Renderable* renderData;
	
	float* verticies;
	unsigned int* indicies;

public:
	GameObject();
	GameObject(Collider* collider);
	GameObject(float x, float y, float width, float height);

	~GameObject();

	virtual void Update(float deltaTime);
	virtual void Draw();

	glm::vec2* GetPosition() { return position; }
	Collider* GetCollider() { return collider; }
};
