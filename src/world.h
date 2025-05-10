#pragma once
#include "raylib.h"
#include <vector>

struct Body;
class Scene;

class World
{
private:
	std::vector<Body*> m_bodies;

public:
	static Vector2 gravity;
	~World();

	void Initialize(Vector2 gravity = Vector2{ 0, -9.81f }, size_t poolSize = 30); // size_t = unsigned int

	Body* CreateBody(const Vector2& position, float size, const Color& color);
	void Step(float timestep); // (deltatime)
	void Draw(const Scene& scene);

	void DestroyAll();
};