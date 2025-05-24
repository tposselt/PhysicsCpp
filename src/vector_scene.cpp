#include "vector_scene.h"
#include "body.h"
#include "raymath.h"
#include "raygui.h"
#include "math_utils.h"
#include "gui.h"

void VectorScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, m_height / 2.0f });
	m_world = new World();
	m_world->Initialize();
}

void VectorScene::CreateBallFirework(const Vector2& position)
{
	float baseColor = randomf(0, 360);
	for (int i = 0; i < 100; i++)
	{
		Body::Type type = (Body::Type)GUI::bodyTypeActive;
		Body* body = m_world->CreateBody(type, position, GUI::sizeValue, GUI::massValue, ColorFromHSV(randomf(baseColor - 50, baseColor + 50), 1.0f, 1.0f));
		float theta = randomf(0, 360);
		float x = cosf(theta);
		float y = sinf(theta);

		body->velocity = Vector2{ x, y } *(randomf(-4.0f, 4.0f));
		body->gravityScale = GUI::gravityScaleValue;
		body->restitution = GUI::restitutionValue;
		body->damping = GUI::dampingValue;
	}
}

void VectorScene::CreateHourglassFirework(const Vector2& position)
{
	float baseColor = randomf(0, 360);
	float theta = randomf(0, 2 * PI);

	for (int i = 0; i < 100; i++)
	{
		Vector2 direction = Vector2Normalize(Vector2{ 1, randomf(-0.5f, 0.5f) });
		Body::Type type = (Body::Type)GUI::bodyTypeActive;
		Body* body = m_world->CreateBody(type, position, GUI::sizeValue, GUI::massValue, ColorFromHSV(randomf(baseColor - 50, baseColor + 50), 1.0f, 1.0f)); float x = (cosf(theta) * direction.x) - (sinf(theta) * direction.y);
		float y = (sinf(theta) * direction.x) + (cosf(theta) * direction.y);

		body->velocity = Vector2{ x, y } *(randomf(-4.0f, 4.0f));
		body->gravityScale = GUI::gravityScaleValue;
		body->restitution = GUI::restitutionValue;
		body->damping = GUI::dampingValue;
	}
}

void VectorScene::CreateBurstFirework(const Vector2& position)
{
	float baseColor = randomf(0, 360);
	float theta = randomf(0, 2 * PI);

	for (int i = 0; i < 100; i++)
	{
		Vector2 direction = Vector2{ 1, randomf(0.0f, 0.5f) };
		Body::Type type = (Body::Type)GUI::bodyTypeActive;
		Body* body = m_world->CreateBody(type, position, GUI::sizeValue, GUI::massValue, ColorFromHSV(randomf(baseColor - 50, baseColor + 50), 1.0f, 1.0f)); float x = (cosf(theta) * direction.x) - (sinf(theta) * direction.y);
		float y = (sinf(theta) * direction.x) + (cosf(theta) * direction.y);

		body->velocity = Vector2{ x, y } * randomf(0, 10.0f);
		body->gravityScale = GUI::gravityScaleValue;
		body->restitution = GUI::restitutionValue;
		body->damping = GUI::dampingValue;
	}
}


void VectorScene::Update()
{
	float dt = GetFrameTime();
	GUI::Update();


	if (IsMouseButtonPressed(0))
	{
		Vector2 position = m_camera->ScreenToWorld(GetMousePosition());

		int type = (int) randomf(0, 3);

		switch (type)
		{
		case 0: 
			CreateHourglassFirework(position);
			break;
		case 1: 
			CreateBallFirework(position);
			break;
		case 2:
			CreateBurstFirework(position);
			break;
		}
	}

	// apply collision
	for (auto body : m_world->GetBodies())
	{
		if (body->position.y < -5)
		{
			body->position.y = -5;
			body->velocity.y *= -body->restitution;
		}
		if (body->position.x < -9)
		{
			body->position.x = -9;
			body->velocity.x *= -body->restitution;
		}
		if (body->position.x > 9)
		{
			body->position.x = 9;
			body->velocity.x *= -body->restitution;
		}
	}
}

void VectorScene::FixedUpdate()
{
	// apply forces
	m_world->Step(Scene::fixedTimestep);
}

void VectorScene::Draw()
{
	m_camera->BeginMode();

	DrawGrid(10, 5, DARKGRAY);
	m_world->Draw(*this);

	m_camera->EndMode();
}

void VectorScene::DrawGUI()
{
	GUI::Draw();
}
