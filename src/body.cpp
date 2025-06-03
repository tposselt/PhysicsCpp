#include "body.h"
#include "integrator.h"
#include "world.h"
#include "raymath.h"

void Body::Step(float dt)
{
	if (type != Type::Dynamic) return;

	// apply gravity
	force += (World::gravity * gravityScale) * mass;
	// compute acceleration
	acceleration = (force * inverseMass);

	SemiImplicitIntegrator(*this, dt);

}

void Body::Draw(const Scene& scene)
{
	scene.DrawCircle(position, size, color);
}

void Body::ApplyForce(const Vector2& force, ForceMode forceMode)
{
	switch (forceMode)
	{
	case Body::ForceMode::Force:
		this->force += force;
		break;
	case Body::ForceMode::Impulse:
		this->velocity += force * inverseMass;
		break;
	case Body::ForceMode::Velocity:
		this->velocity += force;
		break;
	default:
		break;
	}
}

void Body::ClearForce()
{
	this->force = { 0, 0 };
}
