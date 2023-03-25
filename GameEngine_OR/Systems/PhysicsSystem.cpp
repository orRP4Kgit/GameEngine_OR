#include "PhysicsSystem.h"

bool PhysicsSystem::IsColliding(ECS::ComponentHandle<BoxCollider> touchingBox, ECS::ComponentHandle<BoxCollider> touchedBox, float x, float y)
{
    

    return touchingBox-> rightEdge + x > touchedBox-> leftEdge && 
        touchedBox-> rightEdge > touchingBox-> leftEdge + x &&
        touchingBox-> bottomEdge + y > touchedBox-> topEdge &&
        touchedBox-> bottomEdge > touchingBox-> topEdge + y;
}

bool PhysicsSystem::IsColliding(ECS::ComponentHandle<BoxCollider> touchingBox, sf::RectangleShape touchedRectangle, float x, float y)
{
    float touchedRectLeft = touchedRectangle.getPosition().x;
    float touchedRectRight = touchedRectLeft + touchedRectangle.getGlobalBounds().width;
    float touchedRectTop = touchedRectangle.getPosition().y;
    float touchedRectBottom = touchedRectTop + touchedRectangle.getGlobalBounds().height;
    return touchingBox-> rightEdge + x > touchedRectLeft &&
        touchedRectRight > touchingBox-> leftEdge + x &&
        touchingBox-> bottomEdge + y > touchedRectTop &&
        touchedRectBottom > touchingBox-> topEdge + y;
}

bool PhysicsSystem::IsColliding(ECS::ComponentHandle<BoxCollider> touchingBox, ECS::ComponentHandle<BoxCollider> touchedBox)
{

    return touchingBox-> rightEdge > touchedBox-> leftEdge &&
        touchedBox-> rightEdge > touchingBox-> leftEdge &&
        touchingBox-> bottomEdge > touchedBox-> topEdge &&
        touchedBox-> bottomEdge > touchingBox-> topEdge;
}

bool PhysicsSystem::IsColliding(ECS::ComponentHandle<BoxCollider> touchingBox, sf::RectangleShape touchedRectangle)
{
    float touchedRectLeft = touchedRectangle.getPosition().x;
    float touchedRectRight = touchedRectLeft + touchedRectangle.getGlobalBounds().width;
    float touchedRectTop = touchedRectangle.getPosition().y;
    float touchedRectBottom = touchedRectTop + touchedRectangle.getGlobalBounds().height;
    return touchingBox-> rightEdge > touchedRectLeft &&
        touchedRectRight > touchingBox-> leftEdge &&
        touchingBox-> bottomEdge > touchedRectTop &&
        touchedRectBottom > touchingBox-> topEdge;
}

void PhysicsSystem::PushEntity(ECS::ComponentHandle<Transform> transform, ECS::ComponentHandle<BoxCollider> touchingBox, ECS::ComponentHandle<BoxCollider> touchedBox)
{
    // Scenario dealing with collision from the rightside by accelerating rightward

    if (transform->xSpeed > 0 &&
        touchedBox->rightEdge + transform->xSpeed > touchedBox->leftEdge &&
        touchingBox->topEdge < touchedBox->bottomEdge &&
        touchingBox->bottomEdge > touchedBox->topEdge)
    {
        transform->xSpeed = 0;
    }

    // Scenario dealing with collision from the bottomside by accelerating downward

    if (transform->ySpeed > 0 &&
        touchedBox->bottomEdge + transform->ySpeed > touchedBox->topEdge &&
        touchingBox->leftEdge < touchedBox->rightEdge &&
        touchingBox->rightEdge > touchedBox->leftEdge)
    {
        transform->ySpeed = 0;
    }

    // Scenario dealing with collision from the leftside by accelerating leftward

    if (transform->xSpeed < 0 &&
        touchedBox->leftEdge + transform->xSpeed > touchedBox->rightEdge &&
        touchingBox->topEdge < touchedBox->bottomEdge &&
        touchingBox->bottomEdge > touchedBox->topEdge)
    {
        transform->xSpeed = 0;
    }

    // Scenario dealing with collision from the topside by accelerating upward

    if (transform->ySpeed < 0 &&
        touchedBox->topEdge + transform->ySpeed > touchedBox->bottomEdge &&
        touchingBox->leftEdge < touchedBox->rightEdge &&
        touchingBox->rightEdge > touchedBox->leftEdge)
    {
        transform->ySpeed = 0;
    }
}

void PhysicsSystem::PushEntity(ECS::ComponentHandle<Transform> transform, ECS::ComponentHandle<BoxCollider> touchingBox, sf::RectangleShape touchedRectangle)
{
    float touchedRectLeft = touchedRectangle.getPosition().x;
    float touchedRectRight = touchedRectLeft + touchedRectangle.getGlobalBounds().width;
    float touchedRectTop = touchedRectangle.getPosition().y;
    float touchedRectBottom = touchedRectTop + touchedRectangle.getGlobalBounds().height;

    // Scenario dealing with collision from the rightside by accelerating rightward

    if (transform->xSpeed > 0 &&
        touchedRectRight + transform->xSpeed > touchedRectLeft &&
        touchingBox->topEdge < touchedRectBottom &&
        touchingBox->bottomEdge > touchedRectTop)
    {
        transform->xSpeed = 0;
    }

    // Scenario dealing with collision from the bottomside by accelerating downward

    if (transform->ySpeed > 0 &&
        touchedRectBottom + transform->ySpeed > touchedRectTop &&
        touchingBox->leftEdge < touchedRectRight &&
        touchingBox->rightEdge > touchedRectLeft)
    {
        transform->ySpeed = 0;
    }

    // Scenario dealing with collision from the leftside by accelerating leftward

    if (transform->xSpeed < 0 &&
        touchedRectLeft + transform->xSpeed > touchedRectRight &&
        touchingBox->topEdge < touchedRectBottom &&
        touchingBox->bottomEdge > touchedRectTop) 
    {
        transform->xSpeed = 0;
    }

    // Scenario dealing with collision from the topside by accelerating upward

    if (transform->ySpeed < 0 &&
        touchedRectTop + transform->ySpeed > touchedRectBottom &&
        touchingBox->leftEdge < touchedRectRight &&
        touchingBox->rightEdge > touchedRectLeft)
    {
        transform->ySpeed = 0;
    }

}

void PhysicsSystem::PushEntity(ECS::Entity* touchingEntity, ECS::Entity* touchedEntity)
{
    float newTouchingX = touchingEntity->get<Transform>()->xPos;
    float newTouchingY = touchingEntity->get<Transform>()->yPos;
    float newTouchingXSpeed = touchingEntity->get<Transform>()->xSpeed;
    float newTouchingYSpeed = touchingEntity->get<Transform>()->ySpeed;
    float newTouchedX = touchedEntity->get<Transform>()->xPos;
    float newTouchedY = touchedEntity->get<Transform>()->yPos;
    float newTouchedXSpeed = touchedEntity->get<Transform>()->xSpeed;
    float newTouchedYSpeed = touchedEntity->get<Transform>()->ySpeed;

    if (newTouchingXSpeed > 0 &&
        newTouchingX < newTouchedX)
    {
        touchedEntity->get<Transform>()->xPos++;
    }
    else if (newTouchingXSpeed < 0 &&
        newTouchingX > newTouchedX)
    {
        touchedEntity->get<Transform>()->xPos--;
    }

    if (newTouchingYSpeed > 0 &&
        newTouchingY < newTouchedY)
    {
        touchedEntity->get<Transform>()->yPos++;
    }
    else if (newTouchingYSpeed < 0 &&
        newTouchingY > newTouchedY)
    {
        touchedEntity->get<Transform>()->yPos--;
    }
}

void PhysicsSystem::tick(ECS::World* world, float DeltaTime)
{
    world->each<BoxCollider, Sprite2D, Transform>(
        [&](ECS::Entity* entity, ECS::ComponentHandle<BoxCollider> collider, ECS::ComponentHandle<Sprite2D> sprite, ECS::ComponentHandle<Transform> transform) -> void
        {
            collider->Update(transform->xPos, transform->yPos, sprite->self.getTextureRect().width, sprite->self.getTextureRect().height);
        });

    world->each<BoxCollider, Transform>(
        [&](ECS::Entity* touchingEntity, ECS::ComponentHandle<BoxCollider> touchingBox,ECS::ComponentHandle<Transform> transform) -> void
        {
            world->each<BoxCollider>(
                [&](ECS::Entity* touchedEntity, ECS::ComponentHandle<BoxCollider> touchedBox) -> void
                {
                    // Statement to avoid comparing the same entity to itself 
                    if (touchingEntity->getEntityId() == touchedEntity->getEntityId() || IsColliding(touchingBox, touchedBox) == false)
                    {
                        return;
                    }
                    PushEntity(touchingEntity, touchedEntity);
                });
        });

    world->each<Transform>(
        [&](ECS::Entity* entity, ECS::ComponentHandle<Transform> transform) -> void
        {
            transform->Move();
        });

}