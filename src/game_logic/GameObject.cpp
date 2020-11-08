#include "GameObject.h"

/// <summary>
/// Initializes a game object if no fields are given as a basic white square
/// </summary>
GameObject::GameObject()
{
	position = new glm::vec2(5, 5);
	collider = new Collider(0, 0, 10, 10);

	//Sets up a basic 50x50 square
	verticies = new float[16]
	{
		0.0f, 0.0f, 0.0f, 0.0f,
		50.0f, 0.0f, 1.0f, 0.0f,
		50.0f, 50.0f, 1.0f, 1.0f,
		0.0f, 50.0f, 0.0f, 1.0f
	};

	//Sets basic rectangle of indicies
	indicies = new unsigned int[6]{
		2, 1, 0,
		0, 3, 2
	};
	
	renderer = new Renderer("res/shaders/EmptyGameObject.shader", verticies, 16, 4, indicies, 6);
}

/// <summary>
/// Initializes the GameObject with a already created collider
/// </summary>
/// <param name="collider">A precreated collider the will be used for the GameObject</param>
GameObject::GameObject(Collider* collider)
	: collider(collider)
{
	//Initializes the position based on the precreated collider's values
	position = new glm::vec2(collider->GetXPos() + collider->GetWidth() / 2, collider->GetYPos() + collider->GetHeight() / 2);

	//Initializes the verticies at the positions specified by the colliders rectangle
	verticies = new float[16]
	{
		collider->GetXPos(),						collider->GetYPos(),						 0.0f, 0.0f,
		collider->GetXPos() + collider->GetWidth(), collider->GetYPos(),					     1.0f, 0.0f,
		collider->GetXPos() + collider->GetWidth(), collider->GetYPos() + collider->GetHeight(), 1.0f, 0.0f,
		collider->GetXPos(),					    collider->GetYPos() + collider->GetHeight(), 1.0f, 0.0f
	};

	//Basic rectangle indicies
	indicies = new unsigned int[6]{
		2, 1, 0,
		0, 3, 2
	};

	renderer = new Renderer("res/shaders/EmptyGameObject.shader", verticies, 16, 4, indicies, 6);
}

/// <summary>
/// Initializes a GameObject with all of the data necessary to create a Collider object
/// </summary>
/// <param name="x">The top left corner x position of the Collider</param>
/// <param name="y">The top left corner y position of the Collider</param>
/// <param name="width">The width of the Collider</param>
/// <param name="height">The height of the Collider</param>
GameObject::GameObject(float x, float y, float width, float height)
{
	//Creates Collider and initializes position of GameObject from the values passed in
	collider = new Collider(x, y, width, height);
	position = new glm::vec2(x + width/2, y + height/2);

	//Initializes the verticies at positions specified by the params
	verticies = new float[16]
	{
		x,		   y,		   0.0f, 0.0f,
		x + width, y,          1.0f, 0.0f,
		x + width, y + height, 1.0f, 0.0f,
		x,         y + height, 1.0f, 0.0f
	};

	//Basic rect index array
	indicies = new unsigned int[6]{
		2, 1, 0,
		0, 3, 2
	};

	renderer = new Renderer("res/shaders/EmptyGameObject.shader", verticies, 16, 4, indicies, 6);
}

/// <summary>
/// Deletes all pointers that will fall out of use after this object is deleted
/// </summary>
GameObject::~GameObject()
{
	delete collider;
	delete position;
	delete verticies;
	delete indicies;
	delete renderer;
}

/// <summary>
/// Draws the object to the screen using the created Renderer
/// </summary>
void GameObject::Draw()
{
	renderer->Clear();
	renderer->Draw();
}
