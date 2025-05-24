#include "spring.h"
#include "body.h"
#include "raymath.h"

void Spring::ApplyForce(float damping, float kMultiplier)
{
	// direction = bodyA <---- bodyB
	Vector2 direction = bodyA->position - bodyB->position;
	float lengthSqr = Vector2LengthSqr(direction);
	if (lengthSqr <= EPSILON) return;

	// calculate spring forces
	float length = sqrtf(lengthSqr);
	float displacement = length - restLength;
	float forceMagnitude = -(k * kMultiplier) * displacement; // Hooke's law

	Vector2 ndirection = direction / length;
	Vector2 force = ndirection * forceMagnitude;

	// damp spring to prevent oscillation
	Vector2 dv = bodyA->velocity - bodyB->velocity;
	float dampFactor = Vector2DotProduct(dv, ndirection) * damping;
	Vector2 dampingForce = ndirection * dampFactor;

	force -= dampingForce;

	bodyA->ApplyForce(force);
	bodyB->ApplyForce(Vector2Negate(force));
}

void Spring::Draw(const Scene& scene)
{
	scene.DrawLine(bodyA->position, bodyB->position, 3, WHITE);
}
