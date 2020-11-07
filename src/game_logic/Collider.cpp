#include "Collider.h"

Collider::Collider(float x, float y, float width, float height)
	: rect(x, y, width, height)
{
}

Collider::~Collider()
{
}

//Checks if the two colliders are colliding or not
bool Collider::CheckForCollision(Collider& otherCollider)
{
	glm::vec4 otherRect = otherCollider.GetRect();

	return rect[0] < otherRect[0] + otherRect[2] &&
		   otherRect[0] < rect[0] + rect[2] &&
		   rect[1] < otherRect[1] + otherRect[3] &&
		   otherRect[1] < rect[1] + rect[3];
}
