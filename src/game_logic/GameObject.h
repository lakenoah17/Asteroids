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
	//The rotation in degrees of the GameObject
	float rotation = 0.0f;

	Renderable* renderData;
	
	float* verticies;
	unsigned int* indicies;

public:
	GameObject();
	GameObject(Collider* collider);
	GameObject(float x, float y, float width, float height);

	~GameObject();

	Renderable* GetDrawData();

	virtual void Update();
};
