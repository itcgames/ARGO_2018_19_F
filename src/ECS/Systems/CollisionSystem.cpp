#include "ECS\Systems\CollisionSystem.h"

/// <summary>
/// 
/// </summary>
CollisionSystem::CollisionSystem() :
	m_collectionCount(0),
	m_grabbed(false),
	m_platGrab(false),
	m_obGrab(false),
	m_springGrab(false)
{
	m_spikeSound = Mix_LoadWAV(".//resources//Sounds//spiketrap.wav");
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void CollisionSystem::update(double dt)
{
	for (Entity* entity1 : m_entities)
	{
		PositionComponent* e1Position = (PositionComponent*)entity1->getComponent("POSITION");
		PhysicsComponent* e1PhysicsComponent = (PhysicsComponent*)entity1->getComponent("PHYSICS");
		CollisionComponent* e1Collision = (CollisionComponent*)entity1->getComponent("COLLISION");
		ControllerComponent* e1Controller = (ControllerComponent*)entity1->getComponent("CONTROLLER");
		PlayerStateComponent* e1StateComponent = (PlayerStateComponent*)entity1->getComponent("PLAYER_STATE");

		int cursorCount = 0;

		for (Entity* entity2 : m_entities)
		{
			PositionComponent* e2Position = (PositionComponent*)entity2->getComponent("POSITION");
			PhysicsComponent* e2PhysicsComponent = (PhysicsComponent*)entity2->getComponent("PHYSICS");
			CollisionComponent* e2Collision = (CollisionComponent*)entity2->getComponent("COLLISION");
			ControllerComponent* e2Controller = (ControllerComponent*)entity2->getComponent("CONTROLLER");
			PlayerStateComponent* e2StateComponent = (PlayerStateComponent*)entity2->getComponent("PLAYER_STATE");

			if (entity1 != entity2)
			{
				if (e1Position->getPos().x <= e2Position->getPos().x + e2Collision->getCollider().w &&
					e1Position->getPos().x + e1Collision->getCollider().w >= e2Position->getPos().x &&
					e1Position->getPos().y <= e2Position->getPos().y + e2Collision->getCollider().h &&
					e1Position->getPos().y + e1Collision->getCollider().h >= e2Position->getPos().y)
				{
					/// <summary>
					/// Collisions between players and platforms.
					/// </summary>
					if (e1Collision->getMainTag() == "player" && e2Collision->getMainTag() == "platform")
					{
						Vector velocity = e1PhysicsComponent->getVelocity();
						Vector position = e1Position->getPos();

						std::string direction = handleBoxCollision(e1Position->getPos(), e1Collision->getCollider(), e2Position->getPos(), e2Collision->getCollider());

						// check the top
						if (direction == "top")
						{
							position.y = e2Position->getPos().y - e1Collision->getCollider().h;
							e1Position->setPos(position);
							velocity.y = 0;
							e1PhysicsComponent->setVelocity(velocity);
							e1PhysicsComponent->setJumping(false);
						}
						// check the bottom
						if (direction == "bottom")
						{
							position.y = e2Position->getPos().y + e2Collision->getCollider().h;
							e1Position->setPos(position);
							velocity.y = 0;
							e1PhysicsComponent->setVelocity(velocity);
						}
						// check the left
						if (direction == "left")
						{
							position.x = e2Position->getPos().x - e1Collision->getCollider().w;
							e1Position->setPos(position);
							velocity.x = 0;
							e1PhysicsComponent->setVelocity(velocity);
						}
						// check the right
						if (direction == "right")
						{
							position.x = e2Position->getPos().x + e2Collision->getCollider().w;
							e1Position->setPos(position);
							velocity.x = 0;
							e1PhysicsComponent->setVelocity(velocity);
						}
					}

					/// <summary>
					/// Collision and physics for the player and springboard
					/// </summary>
					if (e1Collision->getMainTag() == "player" && e2Collision->getMainTag() == "springboard")
					{
						Vector velocity = e1PhysicsComponent->getVelocity();
						Vector position = e1Position->getPos();

						std::string direction = handleBoxCollision(e1Position->getPos(), e1Collision->getCollider(), e2Position->getPos(), e2Collision->getCollider());


						// check the top
						if (direction == "top")
						{
							position.y = e2Position->getPos().y - e1Collision->getCollider().h;
							e1Position->setPos(position);
							velocity.y = -30;
							e1PhysicsComponent->setVelocity(velocity);
							e1PhysicsComponent->setJumping(true);
							e1Collision->setCursorState(true);
						}
						else
						{
							e1Collision->setCursorState(true);
						}
					}

					/// <summary>
					/// Collisions between the players and obstacles.
					/// </summary>
					if (e1Collision->getMainTag() == "player" && e2Collision->getMainTag() == "obstacle" && !e1Collision->getCursorState())
					{						
						if (e1StateComponent != nullptr)
						{
							if (e1StateComponent->isAlive())
							{
								e1StateComponent->setAlive(false);

								if (e2Collision->getSecondaryTag() == "Spike")
								{
									Mix_PlayChannel(4, m_spikeSound, 0);
								}
							}							
						}													
					}

					/// <summary>
					/// Collisions between the players and the goal.
					/// </summary>
					if (e1Collision->getMainTag() == "player" && e2Collision->getMainTag() == "goal")
					{
						if (e1StateComponent != nullptr)
						{
							if (!e1StateComponent->hasWon())
							{
								e1StateComponent->setWon(true);								
							}
						}
					}

					/// <summary>
					/// Collisions between the cursor and the springboard
					/// </summary>
					if (e1Collision->getMainTag() == "cursor" && e2Collision->getMainTag() == "springboard" && !e1Collision->getCursorState() && !m_platGrab && !m_obGrab)//e2Collision->m_tag == "platform" /*|| e2Collision->m_tag == "Obstacle"*/)
					{
						ControllerState currentState = e1Controller->getCurrentState();
						ControllerState previousState = e1Controller->getPreviousState();

						// Get the right and bottom of the colliders
						Vector cursor = Vector(e1Position->getPos().x + e1Collision->getCollider().w, e1Position->getPos().y + e1Collision->getCollider().h);
						Vector entity = Vector(e2Position->getPos().x + e2Collision->getCollider().w, e2Position->getPos().y + e2Collision->getCollider().h);

						float top = cursor.y - e2Position->getPos().y;
						float bottom = entity.y - e1Position->getPos().y;
						float left = cursor.x - e2Position->getPos().x;
						float right = entity.x - e1Position->getPos().x;

						//check the top
						if (top < bottom && previousState.A)// && !previousState.A ) //top < left && top < right &&
						{
							m_grabbed = !m_grabbed;
							m_springGrab = !m_springGrab;
						}

						//check the bottom
						if (bottom < top && bottom < left && bottom < right && previousState.A)
						{
							m_grabbed = !m_grabbed;
							m_springGrab = !m_springGrab;
						}

						//check the left
						if (left < right && left < top && left < bottom && previousState.A)
						{
							m_grabbed = !m_grabbed;
							m_springGrab = !m_springGrab;
						}

						//check the right
						if (right < left && right < top && right < bottom && previousState.A)
						{
							m_grabbed = !m_grabbed;
							m_springGrab = !m_springGrab;
						}

						if (m_grabbed == true)
						{
							e1Collision->setObstacleCursor(true);
							e2Position->setPos(e1Position->getPos());

							//e1Collision->setCursorState(true);
							e1Collision->setCollectedObj(true);
							std::cout << e2Position->getPos().x << ", " << e1Position->getPos().x << std::endl;
							std::cout << e2Position->getPos().y << ", " << e1Position->getPos().y << std::endl;
						}

						if (currentState.Y)
						{
							m_grabbed = false;
						}

						if (m_grabbed == false)
						{
							e2Position->setPos(e2Position->getPos());
						}

						if (currentState.A && e2Position->getPos() == e1Position->getPos())
						{
							m_grabbed = false;
						}
					}

					/// <summary>
					/// Collisions between the cursor and the platforms.
					/// </summary>
					if (e1Collision->getMainTag() == "cursor" && e2Collision->getMainTag() == "platform" && !e1Collision->getCursorState() && !m_obGrab && !m_springGrab)//e2Collision->m_tag == "platform" /*|| e2Collision->m_tag == "Obstacle"*/)
					{
						ControllerState currentState = e1Controller->getCurrentState();
						ControllerState previousState = e1Controller->getPreviousState();

						// Get the right and bottom of the colliders
						Vector cursor = Vector(e1Position->getPos().x + e1Collision->getCollider().w, e1Position->getPos().y + e1Collision->getCollider().h);
						Vector entity = Vector(e2Position->getPos().x + e2Collision->getCollider().w, e2Position->getPos().y + e2Collision->getCollider().h);

						float top = cursor.y - e2Position->getPos().y;
						float bottom = entity.y - e1Position->getPos().y;
						float left = cursor.x - e2Position->getPos().x;
						float right = entity.x - e1Position->getPos().x;

						//check the top
						if (top < bottom && previousState.A)// && !previousState.A ) //top < left && top < right &&
						{
							m_grabbed = !m_grabbed;
							m_platGrab = !m_platGrab;
						}

						//check the bottom
						if (bottom < top && bottom < left && bottom < right && previousState.A)
						{
							m_grabbed = !m_grabbed;
							m_platGrab = !m_platGrab;
						}

						//check the left
						if (left < right && left < top && left < bottom && previousState.A)
						{
							m_grabbed = !m_grabbed;
							m_platGrab = !m_platGrab;
						}

						//check the right
						if (right < left && right < top && right < bottom && previousState.A)
						{
							m_grabbed = !m_grabbed;
							m_platGrab = !m_platGrab;
						}

						if (m_grabbed == true)
						{
							e1Collision->setObstacleCursor(true);
							e2Position->setPos(e1Position->getPos());

							//e1Collision->setCursorState(true);
							e1Collision->setCollectedObj(true);
							std::cout << e2Position->getPos().x << ", " << e1Position->getPos().x << std::endl;
							std::cout << e2Position->getPos().y << ", " << e1Position->getPos().y << std::endl;
						}

						if (currentState.Y)
						{
							m_grabbed = false;
						}

						if (m_grabbed == false)
						{
							e2Position->setPos(e2Position->getPos());
						}

						if (currentState.A && e2Position->getPos() == e1Position->getPos())
						{
							m_grabbed = false;
						}
					}

					/// <summary>
					/// Collisions between the cursor and obstacles.
					/// </summary>
					if (e1Collision->getMainTag() == "cursor" && e2Collision->getMainTag() == "obstacle" && !e1Collision->getCursorState() && !m_platGrab && !m_springGrab)//e2Collision->m_tag == "platform" /*|| e2Collision->m_tag == "Obstacle"*/)
					{
						ControllerState currentState = e1Controller->getCurrentState();
						ControllerState previousState = e1Controller->getPreviousState();

						// Get the right and bottom of the colliders
						Vector cursor = Vector(e1Position->getPos().x + e1Collision->getCollider().w, e1Position->getPos().y + e1Collision->getCollider().h);
						Vector entity = Vector(e2Position->getPos().x + e2Collision->getCollider().w, e2Position->getPos().y + e2Collision->getCollider().h);

						float top = cursor.y - e2Position->getPos().y;
						float bottom = entity.y - e1Position->getPos().y;
						float left = cursor.x - e2Position->getPos().x;
						float right = entity.x - e1Position->getPos().x;

						//check the top
						if (top < bottom && previousState.A)// && !previousState.A ) //top < left && top < right &&
						{
							m_grabbed = !m_grabbed;
							m_obGrab = !m_obGrab;
						}

						//check the bottom
						if (bottom < top && bottom < left && bottom < right && previousState.A)
						{
							m_grabbed = !m_grabbed;
							m_obGrab = !m_obGrab;
						}

						//check the left
						if (left < right && left < top && left < bottom && previousState.A)
						{
							m_grabbed = !m_grabbed;
							m_obGrab = !m_obGrab;
						}

						//check the right
						if (right < left && right < top && right < bottom && previousState.A)
						{
							m_grabbed = !m_grabbed;
							m_obGrab = !m_obGrab;
						}

						if (m_grabbed == true)
						{
							e1Collision->setObstacleCursor(true);
							e2Position->setPos(e1Position->getPos());

							//e1Collision->setCursorState(true);
							e1Collision->setCollectedObj(true);
							std::cout << e2Position->getPos().x << ", " << e1Position->getPos().x << std::endl;
							std::cout << e2Position->getPos().y << ", " << e1Position->getPos().y << std::endl;
						}

						if (currentState.Y)
						{
							m_grabbed = false;
						}

						if (m_grabbed == false)
						{
							e2Position->setPos(e2Position->getPos());
						}

						if (currentState.A && e2Position->getPos() == e1Position->getPos())
						{
							m_grabbed = false;
						}
					}
				}				
			}
		}
	}
}




/// <summary>
/// function that returns a string indicating the direction of the collision
/// </summary>
/// <param name="p1"></param>
/// <param name="c1"></param>
/// <param name="p2"></param>
/// <param name="c2"></param>
/// <returns></returns>
std::string CollisionSystem::handleBoxCollision(Vector & p1, SDL_Rect & c1, Vector & p2, SDL_Rect & c2)
{
	std::string direction = "";

	// Get the right and bottom of the colliders
	Vector player = Vector(p1.x + c1.w, p1.y + c1.h);
	Vector entity = Vector(p2.x + c2.w, p2.y + c2.h);

	float top = player.y - p2.y;
	float bottom = entity.y - p1.y;
	float left = player.x - p2.x;
	float right = entity.x - p1.x;

	// check the top
	if (top < bottom && top < left && top < right)
	{
		direction = "top";
	}
	// check the bottom
	if (bottom < top && bottom < left && bottom < right)
	{
		direction = "bottom";
	}
	// check the left
	if (left < right && left < top && left < bottom)
	{
		direction = "left";
	}
	// check the right
	if (right < left && right < top && right < bottom)
	{
		direction = "right";
	}

	return direction;
}
