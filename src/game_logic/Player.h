#pragma once

#include "Projectile.h"
#include "Controller.h"

class Player : public GameObject
{
private:
	Controller* controls;
	static std::list<Projectile>* projectiles;

public:
	static std::list<Projectile>* projectiles;

	Player();

	void Update() override;

	std::list<Projectile>* GetProjectiles() { return projectiles; }
};