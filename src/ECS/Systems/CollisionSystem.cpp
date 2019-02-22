#include "ECS\Systems\CollisionSystem.h"

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

		e1Collision->setIsColliding(false);

		int cursorCount = 0;

		for (Entity* entity2 : m_entities)
		{
			PositionComponent* e2Position = (PositionComponent*)entity2->getComponent("POSITION");
			PhysicsComponent* e2PhysicsComponent = (PhysicsComponent*)entity2->getComponent("PHYSICS");
			CollisionComponent* e2Collision = (CollisionComponent*)entity2->getComponent("COLLISION");
			ControllerComponent* e2Controller = (ControllerComponent*)entity2->getComponent("CONTROLLER");

			if (entity1 != entity2)
			{
				if (e1Position->getPos().x <= e2Position->getPos().x + e2Collision->getCollider().w &&
					e1Position->getPos().x + e1Collision->getCollider().w >= e2Position->getPos().x &&
					e1Position->getPos().y <= e2Position->getPos().y + e2Collision->getCollider().h &&
					e1Position->getPos().y + e1Collision->getCollider().h >= e2Position->getPos().y)
				{
					if (!e1Collision->IsColliding())
					{
						if (e1Collision->m_tag == "player" && e2Collision->m_tag == "platform")
						{
							e1Collision->setIsColliding(true);
							PhysicsComponent* physicsComponent = (PhysicsComponent*)entity1->getComponent("PHYSICS");
							Vector velocity = physicsComponent->getVelocity();
							Vector position = e1Position->getPos();

							std::string direction = handleBoxCollision(e1Position->getPos(), e1Collision->getCollider(), e2Position->getPos(), e2Collision->getCollider());


							// check the top
							if (direction == "top")
							{
								position.y = e2Position->getPos().y - e1Collision->getCollider().h;
								e1Position->setPos(position);
								velocity.y = 0;
								physicsComponent->setVelocity(velocity);
								physicsComponent->setJumping(false);
							}
							// check the bottom
							if (direction == "bottom")
							{
								position.y = e2Position->getPos().y + e2Collision->getCollider().h;
								e1Position->setPos(position);
								velocity.y = 0;
								physicsComponent->setVelocity(velocity);
							}
							// check the left
							if (direction == "left")
							{
								position.x = e2Position->getPos().x - e1Collision->getCollider().w;
								e1Position->setPos(position);
								velocity.x = 0;
								physicsComponent->setVelocity(velocity);
							}
							// check the right
							if (direction == "right")
							{
								position.x = e2Position->getPos().x + e2Collision->getCollider().w;
								e1Position->setPos(position);
								velocity.x = 0;
								physicsComponent->setVelocity(velocity);
							}
						}

						/// <summary>
						/// Collision and physics for the
						/// </summary>
						/// <param name="dt"></param>
						if (e1Collision->m_tag == "player" && e2Collision->m_tag == "springboard")
						{
							e1Collision->setIsColliding(true);
							PhysicsComponent* physicsComponent = (PhysicsComponent*)entity1->getComponent("PHYSICS");
							Vector velocity = physicsComponent->getVelocity();
							Vector position = e1Position->getPos();

							std::string direction = handleBoxCollision(e1Position->getPos(), e1Collision->getCollider(), e2Position->getPos(), e2Collision->getCollider());


							// check the top
							if (direction == "top")
							{
								position.y = e2Position->getPos().y - e1Collision->getCollider().h;
								e1Position->setPos(position);
								velocity.y = -30;
								physicsComponent->setVelocity(velocity);
								physicsComponent->setJumping(true);
								e1Collision->setCursorState(true);
							}
							else
							{
								e1Collision->setCursorState(true);
							}
						}

						if (e1Collision->m_tag == "player" && e2Collision->m_tag == "obstacle" && !e1Collision->getCursorState())
						{
							PhysicsComponent* physicsComponent = (PhysicsComponent*)entity1->getComponent("PHYSICS");
							std::string direction = handleBoxCollision(e1Position->getPos(), e1Collision->getCollider(), e2Position->getPos(), e2Collision->getCollider());

							// if it has collided with any side
							if (direction != "")
							{
								std::cout << "you died" << std::endl;
								if (physicsComponent->alive)
									Mix_PlayChannel(4, m_spikeSound, 0);
								physicsComponent->alive = false;

							}
						}

						if (e1Collision->m_tag == "player" && e2Collision->m_tag == "goal")
						{
							std::string direction = handleBoxCollision(e1Position->getPos(), e1Collision->getCollider(), e2Position->getPos(), e2Collision->getCollider());

							// if it has collided with any side
							if (direction != "")
							{
								std::cout << "you win" << std::endl;
							}
						}

						if (e1Collision->m_tag == "cursor" && e2Collision->m_tag == "springboard" && !e1Collision->getCursorState())//e2Collision->m_tag == "platform" /*|| e2Collision->m_tag == "Obstacle"*/)
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

							}

							//check the bottom
							if (bottom < top && bottom < left && bottom < right && previousState.A)
							{
								m_grabbed = !m_grabbed;

							}

							//check the left
							if (left < right && left < top && left < bottom && previousState.A)
							{
								m_grabbed = !m_grabbed;

							}

							//check the right
							if (right < left && right < top && right < bottom && previousState.A)
							{
								m_grabbed = !m_grabbed;
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

						if (e1Collision->m_tag == "cursor" && e2Collision->m_tag == "platform" && !e1Collision->getCursorState())//e2Collision->m_tag == "platform" /*|| e2Collision->m_tag == "Obstacle"*/)
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

							}

							//check the bottom
							if (bottom < top && bottom < left && bottom < right && previousState.A)
							{
								m_grabbed = !m_grabbed;

							}

							//check the left
							if (left < right && left < top && left < bottom && previousState.A)
							{
								m_grabbed = !m_grabbed;

							}

							//check the right
							if (right < left && right < top && right < bottom && previousState.A)
							{
								m_grabbed = !m_grabbed;
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

						if (e1Collision->m_tag == "cursor" && e2Collision->m_tag == "obstacle" && !e1Collision->getCursorState())//e2Collision->m_tag == "platform" /*|| e2Collision->m_tag == "Obstacle"*/)
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

							}

							//check the bottom
							if (bottom < top && bottom < left && bottom < right && previousState.A)
							{
								m_grabbed = !m_grabbed;

							}

							//check the left
							if (left < right && left < top && left < bottom && previousState.A)
							{
								m_grabbed = !m_grabbed;

							}

							//check the right
							if (right < left && right < top && right < bottom && previousState.A)
							{
								m_grabbed = !m_grabbed;
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
}




/// <summary>
/// function that returns a string
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
