#pragma once
#include "scene.h"
#include "raylib.h"

struct Spring
{
public:
	struct Body* bodyA;
	struct Body* bodyB;
	float restLength;
	float k; // stiffness
	float damping;

public:
	Spring() = default;
	Spring(Body* bodyA, Body* bodyB, float restLength, float k, float damping = 0) :
		bodyA{ bodyA },
		bodyB{ bodyB },
		restLength{ restLength },
		k{ k },
		damping{ damping }
	{ }

	void ApplyForce(float damping = 0.5f, float kMultiplier = 1);
	static void ApplyForce(const Vector2& position, Body& body, float restLength, float k);
	void Draw(const Scene& scene);

};
