#pragma once
#include "glm/glm.hpp"
#include "glm/geometric.hpp"

class Collider
{
private:
	glm::vec4 rect;

public:
	Collider(float x, float y, float width, float height);
	~Collider();

	bool CheckForCollision(Collider& otherCollider);


	/////////////////////////////////////////////////////////
	//All of these functions are for encapsulation purposes//
	/////////////////////////////////////////////////////////

	float GetXPos() { return rect[0]; }
	void SetXPos(float value) { rect[0] = value; }

	float GetYPos() { return rect[1]; }
	void SetYPos(float value) { rect[1] = value; }

	float GetWidth() { return rect[2]; }
	void SetWidth(float value) { rect[2] = value; }

	float GetHeight() { return rect[3]; }
	void SetHeight(float value) { rect[3] = value; }

	glm::vec4 GetRect() { return rect; }
};