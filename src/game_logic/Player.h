#pragma once

#include "Projectile.h"
#include "Controller.h"

class Player : public GameObject
{
private:
	Controller* controls;
	static std::list<Projectile>* projectiles;

public:

	Player();

	void Update() override;

	static std::list<Projectile>* GetProjectiles() { return projectiles; }
};