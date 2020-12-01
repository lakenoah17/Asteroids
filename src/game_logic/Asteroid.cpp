#include "Asteroid.h"

/// <summary>
/// Usable but not advised
/// </summary>
Asteroid::Asteroid()
{
	size = AsteroidSize::LARGE;

	//Creates Collider and initializes position of GameObject from the values passed in
	position = new glm::vec2(120, 120);
	collider = new Collider(position->x - 50, position->y + 50, 100, 100);

	verticies = new float[40]
	{
		 0.0f,  10.0f, 0.0f, 0.0f,
	   -20.0f,  35.0f, 1.0f, 0.0f,
	   -50.0f,  20.0f, 1.0f, 1.0f,
	   -35.0f,   0.0f, 0.0f, 1.0f,
	   -50.0f, -20.0f, 0.0f, 0.0f,
	   -20.0f, -50.0f, 1.0f, 0.0f,
	    20.0f, -30.0f, 1.0f, 1.0f,
	    20.0f, -20.0f, 0.0f, 1.0f,
		50.0f,   0.0f, 0.0f, 0.0f,
		20.0f,  50.0f, 1.0f, 0.0f
	};

	//Basic rect index array
	indicies = new unsigned int[20]{
		0, 1,
		1, 2,
		2, 3,
		3, 4,
		4, 5,
		5, 6,
		6, 7,
		7, 8,
		8, 9,
		9, 0
	};

	rotation = 45;
	velocity = 10.0f * glm::vec2(cos(rotation), sin(rotation));

	renderData = Renderer::CreateRenderable("res/shaders/EmptyGameObject.shader", verticies, 40, 4, indicies, 20);

	//Updates the MVP matrix for rendering to match the members of the GameObject
	renderData->model = glm::translate(glm::mat4(1.0f), glm::vec3(position->x, position->y, 0));
	renderData->mvp = renderData->proj * renderData->view * renderData->model;
}

/// <summary>
/// Initializes and Asteroid based on the specified parameters
/// </summary>
/// <param name="thisPosition">The position to start the asteroid at</param>
/// <param name="velocity">The velocity the asteroid will travel at</param>
/// <param name="size">The size of the asteroid to create</param>
/// <param name="rotation">The angle the asteroid will travel at in world space</param>
/// <param name="timeToSpawn">The time the asteroid will spawn at (Currently unimplemented)</param>
Asteroid::Asteroid(glm::vec2* thisPosition, glm::vec2 velocity, AsteroidSize size, float rotation, float timeToSpawn)
	: velocity(velocity), size(size), rotation(rotation), timeToSpawn(timeToSpawn)
{
	//Sets this here so parent constructor doesn't have to be called
	position = thisPosition;

	//Used to decide between 2 types of Asteroidbased on the size.
	//Random number between 0 and 1
	float randNum = rand() / (float)RAND_MAX;

	//Changes the way Asteroids generate based on the size specified
	switch (size)
	{
	case AsteroidSize::SMALL:

		//Creates Collider and initializes position of GameObject from the values passed in
		collider = new Collider(position->x - 12.5f, position->y + 12.5f, 25, 25);

		//Chooses which set of verticies to use randomly. Can be further changed to add more types of asteroids
		if (randNum > .5f)
		{
			verticies = new float[24]
			{
				 0.0f,   7.5f, 0.0f, 0.0f,
			   -10.0f,  12.5f, 1.0f, 0.0f,
			   -12.5f,   0.0f, 1.0f, 1.0f,
			    -7.5f, -10.0f, 0.0f, 1.0f,
			     5.0f, -12.5f, 0.0f, 0.0f,
			    12.5f,  10.0f, 1.0f, 0.0f
			};
		}
		else
		{
			verticies = new float[24]
			{
				 0.0f,  12.5f, 0.0f, 0.0f,
			   -12.5f,  10.5f, 1.0f, 0.0f,
			   -10.5f,   5.0f, 1.0f, 1.0f,
				-5.0f, -12.5f, 0.0f, 1.0f,
				 7.5f,   0.0f, 0.0f, 0.0f,
				12.5f,  10.0f, 1.0f, 0.0f
			};
		}

		//Indicies of a small asteroid
		indicies = new unsigned int[12]{
			0, 1,
			1, 2,
			2, 3,
			3, 4,
			4, 5,
			5, 0
		};

		renderData = Renderer::CreateRenderable("res/shaders/EmptyGameObject.shader", verticies, 24, 4, indicies, 12);
		break;
	case AsteroidSize::MEDIUM:
		//Creates Collider and initializes position of GameObject from the values passed in
		collider = new Collider(position->x - 25, position->y + 25, 50, 50);

		//Chooses which set of verticies to use randomly. Can be further changed to add more types of asteroids
		if (randNum > .5f)
		{
			verticies = new float[32]
			{
			   -10.0f,  25.0f, 0.0f, 0.0f,
			   -25.0f,  20.0f, 1.0f, 0.0f,
			   -20.0f,  10.0f, 1.0f, 1.0f,
			   -10.0f,  -5.0f, 0.0f, 1.0f,
			   -20.0f, -25.0f, 0.0f, 0.0f,
			   -5.0f,  -15.0f, 1.0f, 0.0f,
				15.0f, -20.0f, 1.0f, 1.0f,
				25.0f,  15.0f, 0.0f, 1.0f
			};
		}
		else
		{
			verticies = new float[32]
			{
			    10.0f,  25.0f, 0.0f, 0.0f,
			   -10.0f,  25.0f, 1.0f, 0.0f,
			   -20.0f,  12.0f, 1.0f, 1.0f,
			   -25.0f,  -5.0f, 0.0f, 1.0f,
			   -15.0f, -25.0f, 0.0f, 0.0f,
			   -5.0f,  -20.0f, 1.0f, 0.0f,
				10.0f,  0.0f, 1.0f, 1.0f,
				25.0f,  17.5f, 0.0f, 1.0f
			};
		}

		//Indicies of a medium asteroid
		indicies = new unsigned int[16]{
			0, 1,
			1, 2,
			2, 3,
			3, 4,
			4, 5,
			5, 6,
			6, 7,
			7, 0
		};

		renderData = Renderer::CreateRenderable("res/shaders/EmptyGameObject.shader", verticies, 32, 4, indicies, 16);
		break;
	case AsteroidSize::LARGE:
		//Creates Collider and initializes position of GameObject from the values passed in
		collider = new Collider(position->x - 50, position->y + 50, 100, 100);

		//Chooses which set of verticies to use randomly. Can be further changed to add more types of asteroids
		if (randNum > .5f)
		{
			verticies = new float[40]
			{
				 0.0f,  10.0f, 0.0f, 0.0f,
			   -20.0f,  35.0f, 1.0f, 0.0f,
			   -50.0f,  20.0f, 1.0f, 1.0f,
			   -35.0f,   0.0f, 0.0f, 1.0f,
			   -50.0f, -20.0f, 0.0f, 0.0f,
			   -20.0f, -50.0f, 1.0f, 0.0f,
				20.0f, -30.0f, 1.0f, 1.0f,
				20.0f, -20.0f, 0.0f, 1.0f,
				50.0f,   0.0f, 0.0f, 0.0f,
				20.0f,  50.0f, 1.0f, 0.0f
			};
		}
		else
		{
			verticies = new float[40]
			{
				 0.0f,  25.0f, 0.0f, 0.0f,
			   -15.0f,  40.0f, 1.0f, 0.0f,
			   -50.0f,  25.0f, 1.0f, 1.0f,
			   -50.0f,   0.0f, 0.0f, 1.0f,
			   -35.0f, -20.0f, 0.0f, 0.0f,
			   -20.0f, -50.0f, 1.0f, 0.0f,
				20.0f, -30.0f, 1.0f, 1.0f,
				40.0f, -40.0f, 0.0f, 1.0f,
				50.0f,   0.0f, 0.0f, 0.0f,
				15.0f,  50.0f, 1.0f, 0.0f
			};
		}

		//Indicies of a large asteroid
		indicies = new unsigned int[20]{
			0, 1,
			1, 2,
			2, 3,
			3, 4,
			4, 5,
			5, 6,
			6, 7,
			7, 8,
			8, 9,
			9, 0
		};

		renderData = Renderer::CreateRenderable("res/shaders/EmptyGameObject.shader", verticies, 40, 4, indicies, 20);
		break;
	//Currently not fully implemented
	case AsteroidSize::XLARGE:
		if (randNum > .5f)
		{
			verticies = new float[40]
			{
				 0.0f,  10.0f, 0.0f, 0.0f,
			   -20.0f,  35.0f, 1.0f, 0.0f,
			   -50.0f,  20.0f, 1.0f, 1.0f,
			   -35.0f,   0.0f, 0.0f, 1.0f,
			   -50.0f, -20.0f, 0.0f, 0.0f,
			   -20.0f, -50.0f, 1.0f, 0.0f,
				20.0f, -30.0f, 1.0f, 1.0f,
				20.0f, -20.0f, 0.0f, 1.0f,
				50.0f,   0.0f, 0.0f, 0.0f,
				20.0f,  50.0f, 1.0f, 0.0f
			};
		}
		else
		{
			verticies = new float[40]
			{
				 0.0f,  25.0f, 0.0f, 0.0f,
			   -15.0f,  40.0f, 1.0f, 0.0f,
			   -50.0f,  25.0f, 1.0f, 1.0f,
			   -50.0f,   0.0f, 0.0f, 1.0f,
			   -35.0f, -20.0f, 0.0f, 0.0f,
			   -20.0f, -50.0f, 1.0f, 0.0f,
				20.0f, -30.0f, 1.0f, 1.0f,
				40.0f, -40.0f, 0.0f, 1.0f,
				50.0f,   0.0f, 0.0f, 0.0f,
				15.0f,  50.0f, 1.0f, 0.0f
			};
		}

		//Indicies of a large asteroid
		indicies = new unsigned int[20]{
			0, 1,
			1, 2,
			2, 3,
			3, 4,
			4, 5,
			5, 6,
			6, 7,
			7, 8,
			8, 9,
			9, 0
		};

		renderData = Renderer::CreateRenderable("res/shaders/EmptyGameObject.shader", verticies, 40, 4, indicies, 20);
		break;
	default:
		break;
	}

	this->velocity.x *= cos(rotation);
	this->velocity.y *= sin(rotation);

	
	//Updates the MVP matrix for rendering to match the members of the GameObject
	renderData->model = glm::translate(glm::mat4(1.0f), glm::vec3(position->x, position-> y, 0));
	renderData->mvp = renderData->proj * renderData->view * renderData->model;
}

Asteroid::~Asteroid()
{
}

/// <summary>
/// Updates the Asteroids position and wraps if necessary
/// </summary>
/// <param name="deltaTime">The time since the last frame</param>
void Asteroid::Update(float deltaTime)
{
	*position += velocity * deltaTime;

	int windowWidth = 1080;
	int windowHeight = 800;

	//Adjust both the colliders position and the GameObjects position
	collider->SetXPos(collider->GetXPos() + velocity.x * deltaTime);
	collider->SetYPos(collider->GetYPos() + velocity.y * deltaTime);

	//Adjusts the graphical position
	renderData->model = glm::translate(renderData->model, glm::vec3(velocity.x * deltaTime, velocity.y * deltaTime, 0));
	
	bool wrapScreen = false;
	//Wraps the object from the left side to the right side
	if (position->x < -50) {
		position->x = windowWidth + 50;
		wrapScreen = true;
	}
	//Wraps the object from the left side to the right side
	if (position->x > windowWidth + 50) {
		position->x = -50;
		wrapScreen = true;
	}

	//Wraps the object from the bottom to the top (OpenGL uses Left-Bottom coordinate system)
	if (position->y < -50) {
		position->y = windowHeight + 50;
		wrapScreen = true;
	}
	//Wraps the object from the top to the bottom (OpenGL uses Left-Bottom coordinate system)
	if (position->y > windowHeight + 50) {
		position->y = -50;
		wrapScreen = true;
	}

	//Wraps the asteroid to the other side of the screen
	if (wrapScreen) {
		collider->SetXPos(position->x - 12.5);
		collider->SetYPos(position->y + 12.5);
		renderData->model = glm::translate(glm::mat4(1.0f), glm::vec3(position->x, position->y, 0));
	}

	renderData->mvp = renderData->proj * renderData->view * renderData->model;
}

/// <summary>
/// Draws the asteroid to the screen
/// </summary>
void Asteroid::Draw() {
	renderData->BindRenderable();
	Renderer::Draw(renderData, GL_LINES);
}

/// <summary>
/// Splits the Asteroid into 2 new ones of 1 size smaller
/// </summary>
/// <returns>A tuple with two new asteroids each one size smaller than the one they came from</returns>
std::tuple<Asteroid*, Asteroid*> Asteroid::SplitAsteroid()
{
	//If the asteroid is a small Asteroid it can't be split further
	if (size == AsteroidSize::SMALL)
	{
		return std::make_tuple(nullptr, nullptr);
	}

	//creates the new Asteroids with the same position and velocity as the parent. Rotation is offset by 45 degrees or quarter pi radians
	Asteroid* ast1 = new Asteroid(new glm::vec2(position->x, position->y), velocity, (AsteroidSize)((int)size - 1), rotation - glm::quarter_pi<float>(), 0);
	Asteroid* ast2 = new Asteroid(new glm::vec2(position->x, position->y), velocity, (AsteroidSize)((int)size - 1), rotation + glm::quarter_pi<float>(), 0);

	std::tuple<Asteroid*, Asteroid*> asts = std::make_tuple(ast1, ast2);

	return asts;
}
