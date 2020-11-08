#pragma once
#include "Collider.h"
#include "../graphics/Renderer.h"

class GameObject
{
private:
	Collider* collider;

	//Position is at the center of the rectangle
	glm::vec2*  position;
	Renderer* renderer;
	
	float* verticies;
	unsigned int* indicies;

public:
	GameObject();
	GameObject(Collider* collider);
	GameObject(float x, float y, float width, float height);

	~GameObject();

	void Draw();

	Renderer* GetRenderer() {
		return renderer;
	}
};
