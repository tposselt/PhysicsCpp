#include "vector_scene.h"
#include "body.h"
#include "raymath.h"
#include "math_utils.h"

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
		Body* body = m_world->CreateBody(position, 0.05f, ColorFromHSV(randomf(baseColor - 50, baseColor + 50), 1.0f, 1.0f));
		float theta = randomf(0, 360);
		float x = cosf(theta);
		float y = sinf(theta);

		body->velocity = Vector2{ x, y } *(randomf(-4.0f, 4.0f));
	}
}

void VectorScene::CreateHourglassFirework(const Vector2& position)
{
	float baseColor = randomf(0, 360);
	float theta = randomf(0, 2 * PI);

	for (int i = 0; i < 100; i++)
	{
		Vector2 direction = Vector2Normalize(Vector2{ 1, randomf(-0.5f, 0.5f) });
		Body* body = m_world->CreateBody(position, 0.05f, ColorFromHSV(randomf(baseColor - 50, baseColor + 50), 1.0f, 1.0f));
		float x = (cosf(theta) * direction.x) - (sinf(theta) * direction.y);
		float y = (sinf(theta) * direction.x) + (cosf(theta) * direction.y);

		body->velocity = Vector2{ x, y } *(randomf(-4.0f, 4.0f));
	}
}

void VectorScene::CreateBurstFirework(const Vector2& position)
{
	float baseColor = randomf(0, 360);
	float theta = randomf(0, 2 * PI);

	for (int i = 0; i < 100; i++)
	{
		Vector2 direction = Vector2{ 1, randomf(0.0f, 0.5f) };
		Body* body = m_world->CreateBody(position, 0.05f, ColorFromHSV(randomf(baseColor - 50, baseColor + 50), 1.0f, 1.0f));
		float x = (cosf(theta) * direction.x) - (sinf(theta) * direction.y);
		float y = (sinf(theta) * direction.x) + (cosf(theta) * direction.y);

		body->velocity = Vector2{ x, y } * randomf(0, 10.0f);
	}
}


void VectorScene::Update()
{
	float dt = GetFrameTime();

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

	m_world->Step(dt);
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
}
