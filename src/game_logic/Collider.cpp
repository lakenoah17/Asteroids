#include "Collider.h"

/// <summary>
/// Initializes the colliders rect field
/// </summary>
/// <param name="x">The x position of the top left of the rect</param>
/// <param name="y">The y position of the top left of the rect</param>
/// <param name="width">The width of the rect</param>
/// <param name="height">The height of the rect</param>
Collider::Collider(float x, float y, float width, float height)
	: rect(x, y, width, height)
{
}

Collider::~Collider()
{
}

/// <summary>
/// Checks if this collider is colliding with the passed in collider through AABB collision
/// </summary>
/// <param name="otherCollider">A reference to the other objects collider</param>
/// <returns>Whether the two objects are colliding or not</returns>
bool Collider::CheckForCollision(Collider& otherCollider)
{
	glm::vec4 otherRect = *otherCollider.GetRect();

	//Checks if the two collide using AABB collision
	return rect[0] < otherRect[0] + otherRect[2] &&
		   otherRect[0] < rect[0] + rect[2] &&
		   rect[1] < otherRect[1] + otherRect[3] &&
		   otherRect[1] < rect[1] + rect[3];
}
