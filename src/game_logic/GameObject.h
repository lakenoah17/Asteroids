#pragma once
#include "Collider.h"

class GameObject
{
private:
	Collider* collider;
	//Position is at the center of the rectangle
	glm::vec2*  position;
	
	float* verticies;
	int* indicies;

public:
	GameObject();
	GameObject(Collider* collider);
	GameObject(float x, float y, float width, float height);

	~GameObject();

	void Draw();
};
