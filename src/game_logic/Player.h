#pragma once

#include "ProjectileManager.h"
#include "Controller.h"

class Player : public GameObject
{
private:
	Controller* controls;
	ProjectileManager* pm;

public:
	Player();

	void Update(float deltaTime) override;
	void Draw() override;
};