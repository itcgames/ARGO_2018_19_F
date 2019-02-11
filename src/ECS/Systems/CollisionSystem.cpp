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
		CollisionComponent* e1Collision = (CollisionComponent*)entity1->getComponent("COLLISION");
		e1Collision->setIsColliding(false);

		for (Entity* entity2 : m_entities)
		{
			PositionComponent* e2Position = (PositionComponent*)entity2->getComponent("POSITION");
			CollisionComponent* e2Collision = (CollisionComponent*)entity2->getComponent("COLLISION");

			if (entity1 != entity2)
			{
				if (e1Position->getPos().x <= e2Position->getPos().x + e2Collision->getCollider().w &&
					e1Position->getPos().x + e1Collision->getCollider().w >= e2Position->getPos().x &&
					e1Position->getPos().y <= e2Position->getPos().y + e2Collision->getCollider().h &&
					e1Position->getPos().y + e1Collision->getCollider().h >= e2Position->getPos().y)
				{
					if (!e1Collision->IsColliding())
					{
						if (e1Collision->m_tag == "Player" && e2Collision->m_tag == "Platform")
						{
							PhysicsComponent* physicsComponent = (PhysicsComponent*)entity1->getComponent("PHYSICS");
							Vector velocity = physicsComponent->getVelocity();
							Vector position = e1Position->getPos();

							// Get the right and bottom of the colliders
							Vector player = Vector(e1Position->getPos().x + e1Collision->getCollider().w, e1Position->getPos().y + e1Collision->getCollider().h);
							Vector entity = Vector(e2Position->getPos().x + e2Collision->getCollider().w, e2Position->getPos().y + e2Collision->getCollider().h);

							float top = player.y - e2Position->getPos().y;
							float bottom = entity.y - e1Position->getPos().y;
							float left = player.x - e2Position->getPos().x;
							float right = entity.x - e1Position->getPos().x;

							// check the top
							if (top < bottom && top < left && top < right)
							{
								position.y = e2Position->getPos().y - e1Collision->getCollider().h;
								e1Position->setPos(position);
								velocity.y = 0;
								physicsComponent->setVelocity(velocity);
								physicsComponent->setJumping(false);
							}
							// check the bottom
							if (bottom < top && bottom < left && bottom < right)
							{
								position.y = e2Position->getPos().y + e2Collision->getCollider().h;
								e1Position->setPos(position);
								velocity.y = 0;
								physicsComponent->setVelocity(velocity);
							}
							// check the left
							if (left < right && left < top && left < bottom)
							{
								position.x = e2Position->getPos().x - e1Collision->getCollider().w;
								e1Position->setPos(position);
								velocity.x = 0;
								physicsComponent->setVelocity(velocity);
							}
							// check the right
							if (right < left && right < top && right < bottom)
							{
								position.x = e2Position->getPos().x + e2Collision->getCollider().w;
								e1Position->setPos(position);
								velocity.x = 0;
								physicsComponent->setVelocity(velocity);
							}
						}

						if (e1Collision->m_tag == "Player" && e2Collision->m_tag == "Obstacle")
						{
							PhysicsComponent* physicsComponent = (PhysicsComponent*)entity1->getComponent("PHYSICS");
							Vector velocity = physicsComponent->getVelocity();
							Vector position = e1Position->getPos();

							// Get the right and bottom of the colliders
							Vector player = Vector(e1Position->getPos().x + e1Collision->getCollider().w, e1Position->getPos().y + e1Collision->getCollider().h);
							Vector entity = Vector(e2Position->getPos().x + e2Collision->getCollider().w, e2Position->getPos().y + e2Collision->getCollider().h);

							float top = player.y - e2Position->getPos().y;
							float bottom = entity.y - e1Position->getPos().y;
							float left = player.x - e2Position->getPos().x;
							float right = entity.x - e1Position->getPos().x;

							// check the top
							if (top < bottom && top < left && top < right)
							{
								physicsComponent->alive = false;
								std::cout << "you died" << std::endl;
							}
							// check the bottom
							if (bottom < top && bottom < left && bottom < right)
							{
								std::cout << "you died" << std::endl;
								physicsComponent->alive = false;
							}
							// check the left
							if (left < right && left < top && left < bottom)
							{
								std::cout << "you died" << std::endl;
								physicsComponent->alive = false;
							}
							// check the right
							if (right < left && right < top && right < bottom)
							{
								std::cout << "you died" << std::endl;
								physicsComponent->alive = false;
							}
						}

						if (e1Collision->m_tag == "Player" && e2Collision->m_tag == "Goal")
						{
							PhysicsComponent* physicsComponent = (PhysicsComponent*)entity1->getComponent("PHYSICS");
							Vector velocity = physicsComponent->getVelocity();
							Vector position = e1Position->getPos();

							// Get the right and bottom of the colliders
							Vector player = Vector(e1Position->getPos().x + e1Collision->getCollider().w, e1Position->getPos().y + e1Collision->getCollider().h);
							Vector entity = Vector(e2Position->getPos().x + e2Collision->getCollider().w, e2Position->getPos().y + e2Collision->getCollider().h);

							float top = player.y - e2Position->getPos().y;
							float bottom = entity.y - e1Position->getPos().y;
							float left = player.x - e2Position->getPos().x;
							float right = entity.x - e1Position->getPos().x;

							// check the top
							if (top < bottom && top < left && top < right)
							{
								std::cout << "You win" << std::endl;
							}
							// check the bottom
							if (bottom < top && bottom < left && bottom < right)
							{
								std::cout << "You win" << std::endl;
							}
							// check the left
							if (left < right && left < top && left < bottom)
							{
								std::cout << "You win" << std::endl;
							}
							// check the right
							if (right < left && right < top && right < bottom)
							{
								std::cout << "You win" << std::endl;
							}
						}
					}
				}
			}
		}
	}
}
