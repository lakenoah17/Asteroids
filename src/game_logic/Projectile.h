#pragma once
#include "GameObject.h"

class Projectile : public GameObject
{
public:
	Projectile(float x, float y, float width, float height, float angleToFireAt);
	~Projectile();
	void Update() override;
	static std::list<Projectile>* s_ActiveProjectiles;

private:
	glm::vec3 velocity;
	static unsigned int s_NumOfProjectiles;

};