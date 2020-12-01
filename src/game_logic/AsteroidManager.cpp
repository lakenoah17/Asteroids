#include "AsteroidManager.h"

unsigned int AsteroidManager::s_MAX_NUMBER_OF_ASTEROIDS;
Asteroid* AsteroidManager::s_ActiveAsteroids[100];
unsigned int AsteroidManager::s_NumOfAsteroids;
GLFWwindow* AsteroidManager::currWindow;

/// <summary>
/// Makes an AsteroidManager
/// </summary>
/// <param name="window">Needed to decide whether an asteroid should screenwrap or not</param>
AsteroidManager::AsteroidManager(GLFWwindow* window)
{
	AsteroidManager::currWindow = window;
}

AsteroidManager::~AsteroidManager()
{
}

/// <summary>
/// Loops through all of the Asteroids and updates them
/// </summary>
/// <param name="deltaTime">The time between this and the last frame</param>
void AsteroidManager::UpdateAsteroids(float deltaTime)
{
	for (int i = 0; i < s_NumOfAsteroids; i++)
	{
		s_ActiveAsteroids[i]->Update(deltaTime);	
	}
}

/// <summary>
/// Checks for collisions between the Asteroids and an array of GameObjects
/// </summary>
/// <param name="objsToCompareAgainst">Objects to check for collission with</param>
/// <param name="numOfObjs">The length of the array</param>
void AsteroidManager::CheckForCollisions(GameObject* objsToCompareAgainst[], int numOfObjs) {
	for (int i = 0; i < numOfObjs; i++)
	{
		for (int j = 0; j < s_NumOfAsteroids; j++)
		{
			//Checks if the two objects are valid then checks if they are colliding
			if (objsToCompareAgainst[i] && s_ActiveAsteroids[j] && s_ActiveAsteroids[j]->GetCollider()->CheckForCollision(objsToCompareAgainst[i]->GetCollider())) {
				
				std::tuple<Asteroid*, Asteroid*> newAsts = s_ActiveAsteroids[j]->SplitAsteroid();
				
				//Checks to see if the tuple returned is valid
				if (std::get<0>(newAsts))
				{
					s_ActiveAsteroids[s_NumOfAsteroids] = std::get<0>(newAsts);
					s_NumOfAsteroids++;

					s_ActiveAsteroids[s_NumOfAsteroids] = std::get<1>(newAsts);
					s_NumOfAsteroids++;
				}

				delete s_ActiveAsteroids[j];
				s_ActiveAsteroids[j] = nullptr;

				ShiftAsteroids();
				s_NumOfAsteroids--;

				delete objsToCompareAgainst[i];
				objsToCompareAgainst[i] = nullptr;
			}
		}
	}
}

/// <summary>
/// Draws all of the Asteroids to the screen
/// </summary>
void AsteroidManager::DrawAsteroids()
{
	for (int i = 0; i < s_NumOfAsteroids; i++)
	{
		s_ActiveAsteroids[i]->Draw();
	}
}

/// <summary>
/// Generates asteroids based on the current level the user is on
/// </summary>
/// <param name="level">The level the user is on</param>
void AsteroidManager::GenerateAsteroids(unsigned int level)
{
	//Gets the screen width and height
	int screenWidth;
	int screenHeight;
	glfwGetWindowSize(currWindow, &screenWidth, &screenHeight);

	//Num of asteroids is equal to 5 plus 5 times the level the player is on
	s_NumOfAsteroids = 5 + (level * 5);
	for (int i = 0; i < s_NumOfAsteroids; i++)
	{
		//Generates Asteroid positions randomly
		float xPos = ((((float)rand()) / RAND_MAX) * screenWidth ) - 5;
		float yPos;

		//This check is used to make sure the asteroids spawn outside of the screen and not in the middle
		if (xPos < -3 || xPos > screenWidth + 3)
		{
			yPos = ((((float)rand()) / RAND_MAX) * screenHeight) - 10;
		}
		else
		{
			yPos = (((float)rand()) / RAND_MAX) >= .5f ? -4 : screenHeight - 10;
		}

		//Rotation is randomized as well
		float rotation = ((((float)rand()) / RAND_MAX) * 2 * glm::pi<float>());
		s_ActiveAsteroids[i] = new Asteroid(new glm::vec2(xPos, yPos), glm::vec2(40.0f), AsteroidSize::MEDIUM, rotation, 10.0f);
	}
}

/// <summary>
/// Shifts all of the asteroids to fill space in the array
/// </summary>
void AsteroidManager::ShiftAsteroids()
{
	for (int i = 1; i < s_NumOfAsteroids; i++)
	{
		if (!s_ActiveAsteroids[i-1])
		{
			s_ActiveAsteroids[i - 1] = s_ActiveAsteroids[i];
			s_ActiveAsteroids[i] = nullptr;
		}
	}
}
