#include "trigonometry_scene.h"

void TrigonometryScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, m_height / 2.0f });
}

void TrigonometryScene::Update()
{
}

void TrigonometryScene::FixedUpdate()
{
}

float DegToRad(float degrees)
{
	return degrees * (PI / 180);
}

float RadToDeg(float radians)
{
	return radians * (180 / PI);
}

/*float Vector2Length(const Vector2& v)
{
	return sqrtf((v.x * v.x) + (v.y * v.y));
}*/

Vector2 Vector2Normalized(const Vector2& v)
{
	float length = Vector2Length(v);

	if (length == 0) return { 0, 0 };
	return Vector2{ v.x / length, v.y / length };
}

void TrigonometryScene::Draw()
{
	m_camera->BeginMode();

	DrawGrid(10, 5, WHITE);
	//DrawCircle(Vector2{ 0, 0 }, 1, RED);
	float radius = 3.0f;
	float sinRate = 0.8f;
	float cosRate = -0.8f;
	float time = (float) GetTime();

	float radians = 180 * DEG2RAD;

	int steps = 50;
	for (int i = 0; i < steps; i++)
	{
		float theta = (i / (float)steps) * (2 * PI); // 0 - 1
		float x = cosf(theta) * radius;
		float y = sinf(theta) * radius;
		DrawCircle(Vector2{ x, y }, 0.25f, RED);
	}

	// sin / cos
	for (float x = -9.0f; x < 9.0f; x += 0.2f)
	{
		float theta = ((x / 18.0f) * (2 * PI)); // 0 - 1
		float c = cosf((time * cosRate) + theta) * radius;
		float s = sinf((time * sinRate) + theta) * radius;
		DrawCircle(Vector2{ x, c }, 0.25f, GREEN);
		DrawCircle(Vector2{ x, s }, 0.25f, SKYBLUE);
	}

	float theta = time * sinRate * 2;
	float x = cosf(theta) * radius;
	float y = sinf(theta) * radius;
	DrawCircle(Vector2{ x, y }, 0.25f, YELLOW);

	float angle = atan2f(y, x);

	m_camera->EndMode();
}

void TrigonometryScene::DrawGUI()
{
}
