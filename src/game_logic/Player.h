#pragma once
#include "GameObject.h"
#include "Controller.h"

class Player : public GameObject
{
private:
	Controller* controls;

public:
	Player();

	void Update() override;
};