#pragma once
#include "scene.h"
#include "raylib.h"

struct Body
{
public:
	enum class Type
	{
		Dynamic,
		Kinematic,
		Static
	};

	enum class ForceMode
	{
		Force,
		Impulse,
		Velocity
	};

public:
	Vector2 position{ 0, 0 };
	Vector2 velocity{ 0, 0 };
	Vector2 acceleration{ 0,0 };
	Vector2 force{ 0,0 };

	float mass{ 1 };
	float inverseMass{ 1 };

	float gravityScale{ 1.0f };
	float restitution{ 1.0f };

	float size{ 1 };
	float damping{ 0.3f };

	Type type = Type::Dynamic;
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
	Body(int type, const Vector2& position, float mass, const float size, const Color& color) :
		type{ type },
		position{ position },
		mass{ mass },
		size{ size },
		color{ color }
	{
		inverseMass = (this->type == Type::Dynamic && mass != 0) ? 1 / mass : 0;
	}
	Body(Type type, const Vector2& position, float mass, const float size, const Color& color) :
		type{ type },
		position{ position },
		mass{ mass },
		size{ size },
		color{ color }
	{
		inverseMass = (this->type == Type::Dynamic && mass != 0) ? 1 / mass : 0;
	}

	void Step(float dt);
	void Draw(const Scene& scene);
	void ApplyForce(const Vector2& force, ForceMode foceMode = ForceMode::Force);
	void ClearForce();
};