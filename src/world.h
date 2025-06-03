#pragma once
#include "raylib.h"
#include <vector>
#include "body.h"
#include "spring.h"
#include "contact.h"

class Scene;

using bodies_t = std::vector<Body*>;
using springs_t = std::vector<Spring*>;
using contacts_t = std::vector<Contact>;

class World
{
private:
	bodies_t m_bodies;
	springs_t m_springs;
	contacts_t m_contacts;

public:
	inline static Vector2 gravity{ 0, -9.81f };
	static float bodyGScale;
	static float bodyDamping;
	static float bodyMass;
	static int bodyType;

	inline static float gravitation = 10;
	inline static float springStiffnessMultiplier = 1.0f;
	inline static bool simulate = true;

	~World();

	void Initialize(Vector2 gravity = Vector2{ 0, -9.81f }, size_t poolSize = 30); // size_t = unsigned int

	//Body* CreateBody(const Vector2& position, float size, const Color& color);
	Body* CreateBody(Body::Type bodyType, const Vector2& position, float mass, float size, const Color& color);

	Spring* CreateSpring(Body* bodyA, Body* bodyB, float restLength, float stiffness, float damping);

	void Step(float timestep); // (deltatime)
	void Draw(const Scene& scene);

	void DestroyAll();
	void World::ApplyGravitation(bodies_t& bodies, float strength);

	std::vector<Body*>& GetBodies() { return m_bodies; }
};