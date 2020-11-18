#pragma once

#include "Projectile.h"
#include "Controller.h"

class Player : public GameObject
{
private:
	Controller* controls;

public:

	Player();

	void Update(float deltaTime) override;
};