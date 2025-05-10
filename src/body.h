#pragma once
#include "scene.h"
#include "raylib.h"

struct Body
{
public:
	Vector2 position{ 0, 0 };
	Vector2 velocity{ 0, 0 };

	float size{ 1 };
	float damping{ 0.3f };

	Color color{ WHITE };

	Body* next{ nullptr };
	Body* prev{ nullptr };

public:
	Body() = default;
	Body(const Vector2& position, const Vector2& velocity, const float size, const Color& color) :
		position{ position },
		velocity{ velocity },
		size{ size },
		color{ color }
	{ }
	Body(const Vector2& position, const float size, const Color& color) :
		position{ position },
		size{ size },
		color{ color }
	{ }

	void Step(float dt);
	void Draw(const Scene& scene);
};