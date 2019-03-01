#include "ECS\Systems\CollisionSystem.h"

/// <summary>
/// 
/// </summary>
CollisionSystem::CollisionSystem()
{
	m_spikeSound = Mix_LoadWAV(".//resources//Sounds//spiketrap.wav");
}



/// <summary>
/// 
/// </summary>
/// <param name="dt"></param>
void CollisionSystem::update(double dt)
{
	m_clock = dt;
	for (Entity* entity1 : m_entities)
	{
		PositionComponent* e1Position			= (PositionComponent*)entity1->getComponent("POSITION");
		PhysicsComponent* e1PhysicsComponent	= (PhysicsComponent*)entity1->getComponent("PHYSICS");
		CollisionComponent* e1Collision			= (CollisionComponent*)entity1->getComponent("COLLISION");
		ControllerComponent* e1Controller		= (ControllerComponent*)entity1->getComponent("CONTROLLER");
		PlayerStateComponent* e1StateComponent	= (PlayerStateComponent*)entity1->getComponent("PLAYER_STATE");
		CursorComponent* e1CursorComponent		= (CursorComponent*)entity1->getComponent("CURSOR");
		PlacedComponent* e1placed				= (PlacedComponent*)entity1->getComponent("PLACED");

		for (Entity* entity2 : m_entities)
		{
			if (entity1 != entity2)
			{
				PositionComponent* e2Position			= (PositionComponent*)entity2->getComponent("POSITION");
				PhysicsComponent* e2PhysicsComponent	= (PhysicsComponent*)entity2->getComponent("PHYSICS");
				CollisionComponent* e2Collision			= (CollisionComponent*)entity2->getComponent("COLLISION");
				PlacedComponent* e2placed				= (PlacedComponent*)entity2->getComponent("PLACED");
			
				if (e1Position->getPos().x + e1Collision->getCollider().x <= e2Position->getPos().x + e2Collision->getCollider().x + e2Collision->getCollider().w &&
					e1Position->getPos().x + e1Collision->getCollider().x + e1Collision->getCollider().w >= e2Position->getPos().x + e2Collision->getCollider().x &&
					e1Position->getPos().y + e1Collision->getCollider().y <= e2Position->getPos().y + e2Collision->getCollider().y + e2Collision->getCollider().h &&
					e1Position->getPos().y + e1Collision->getCollider().y + e1Collision->getCollider().h >= e2Position->getPos().y + e2Collision->getCollider().y)
				{
					/// <summary>
					/// Collisions involving players
					/// </summary>
					if (e1Collision->getMainTag() == "player" || e1Collision->getMainTag() == "ai")
					{
						Vector velocity = e1PhysicsComponent->getVelocity();
						Vector position = e1Position->getPos();

						std::string direction = handleBoxCollision(e1Position->getPos(), e1Collision->getCollider(), e2Position->getPos(), e2Collision->getCollider());

						//	Collision with a platform.
						if (e2Collision->getMainTag() == "platform")
						{
							/// <summary>
							/// If its a standard platform.
							/// </summary>
							if (e2Collision->getSecondaryTag() == "" || e2Collision->getSecondaryTag() == "I")
							{
								// check the top
								if (direction == "top")
								{
									position.y = e2Position->getPos().y + e2Collision->getCollider().y - e1Collision->getCollider().h;
									e1Position->setPos(position);
									velocity.y = 0;
									e1PhysicsComponent->setVelocity(velocity);
									e1PhysicsComponent->setJumping(false);
								}
								// check the bottom
								if (direction == "bottom")
								{
									position.y = e2Position->getPos().y + e2Collision->getCollider().y + e2Collision->getCollider().h;
									e1Position->setPos(position);
									velocity.y = 0;
									e1PhysicsComponent->setVelocity(velocity);
								}
								// check the left
								if (direction == "left")
								{
									position.x = e2Position->getPos().x + e2Collision->getCollider().x - e1Collision->getCollider().w;
									e1Position->setPos(position);
									velocity.x = 0;
									e1PhysicsComponent->setVelocity(velocity);
								}
								// check the right
								if (direction == "right")
								{
									position.x = e2Position->getPos().x + e2Collision->getCollider().x + e2Collision->getCollider().w;
									e1Position->setPos(position);
									velocity.x = 0;
									e1PhysicsComponent->setVelocity(velocity);
								}
							}
							/// <summary>
							/// If the platform is a spring.
							/// </summary>
							else if (e2Collision->getSecondaryTag() == "spring")
							{
								// check the top
								if (direction == "top")
								{
									position.y = e2Position->getPos().y - e1Collision->getCollider().h;
									e1Position->setPos(position);
									velocity.y = -30;
									e1PhysicsComponent->setVelocity(velocity);
									e1PhysicsComponent->setJumping(true);
								}
							}
						}
						/// <summary>
						/// Collision with an obstacle.
						/// </summary>
						else if (e2Collision->getMainTag() == "obstacle")
						{
							//	 If the player is alive.
							if (e1StateComponent != nullptr && e1StateComponent->isAlive())
							{
								//	Kill the player.
								e1StateComponent->setAlive(false);

								/// <summary>
								/// If the obstacle was a spike.
								/// </summary>									
								if (e2Collision->getSecondaryTag() == "spike")
								{
									//	Play the spike sound effect.
									Mix_PlayChannel(4, m_spikeSound, 0);
								}
							}							
						}

						/// <summary>
						/// Collision with the goal.
						/// </summary>
						if (e2Collision->getMainTag() == "goal")
						{
							if (e1StateComponent != nullptr)
							{
								if (!e1StateComponent->hasWon())
								{
									e1StateComponent->setWon(true);
								}
							}
						}						
					}					

					/// <summary>
					/// Collisions involving the cursor AND a platform OR obstacle.
					/// </summary>
					if (e1Collision->getMainTag() == "cursor" && (e2Collision->getMainTag() == "platform" || e2Collision->getMainTag() == "obstacle") && e2placed->getPlaced() == false)
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

						if (((top < bottom) ||
							(bottom < top && bottom < left && bottom < right) ||
							(left < right && left < top && left < bottom) ||
							(right < left && right < top && right < bottom)) &&
							previousState.A)
						{
							e1CursorComponent->flipHoldingObject();
							entity1->addLink(entity2);

						}


						if (e1CursorComponent->isHoldingObject() == true && entity1->getLinkedEntities()[0] == entity2)
						{
							e2Position->setPos(e1Position->getPos());
						}
							
										
					}					
				}				
			}
		}
	}
}



/// <summary>
/// 
/// </summary>
void CollisionSystem::render(SDL_Renderer * renderer)
{
	for (Entity* entity : m_entities)
	{
		PositionComponent* position = (PositionComponent*)entity->getComponent("POSITION");
		CollisionComponent* collision = (CollisionComponent*)entity->getComponent("COLLISION");

		if (position != nullptr && collision != nullptr)
		{
			SDL_Rect colliderRect = { position->getPos().x, position->getPos().y, collision->getCollider().w, collision->getCollider().h };
			//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
			//SDL_RenderFillRect(renderer, &colliderRect);
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
	Vector player = Vector(p1.x  + c1.x + c1.w, p1.y + c1.y + c1.h);
	Vector entity = Vector(p2.x  + c2.x + c2.w, p2.y + c2.y + c2.h);

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
