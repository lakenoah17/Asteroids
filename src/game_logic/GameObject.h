#pragma once
#include "Collider.h"

class GameObject
{
private:
	Collider* collider;
	float xPos;
	float yPos;

public:
	GameObject();
	GameObject(float x, float y, float width, float height);

	~GameObject();


};
