#include "polar_scene.h"
#include "polar.h"
#include <vector>
#include <memory>

void PolarScene::Initialize()
{
	m_camera = new SceneCamera(Vector2{ static_cast<float>(m_width) / 2, m_height / 2.0f });
}

std::unique_ptr<std::vector<Vector2>> GenerateArchimedeanSpiral(float startRad, float spacing, float thetaInitial, float thetaFinal, int pointCount)
{
	std::unique_ptr<std::vector<Vector2>> returnValue = std::make_unique<std::vector<Vector2>>();
	float interval = (thetaFinal - thetaInitial) / pointCount;

	for (int i = 0; i < pointCount; i++)
	{
		float angle = thetaInitial + (i * interval);
		float radius = startRad + (spacing * angle);
		Polar polar = Polar(angle, radius);
		returnValue->push_back((Vector2)polar);
	}

	return returnValue;
}

std::unique_ptr<std::vector<Vector2>> GenerateCardioid(float size, float thetaInitial, float thetaFinal, int pointCount)
{
	std::unique_ptr<std::vector<Vector2>> returnValue = std::make_unique<std::vector<Vector2>>();
	float interval = (thetaFinal - thetaInitial) / pointCount;

	for (int i = 0; i < pointCount; i++)
	{
		float angle = thetaInitial + (i * interval);
		float radius = size * (1 + cosf(angle));
		Polar polar = Polar(angle, radius);
		returnValue->push_back((Vector2)polar);
	}

	return returnValue;
}

std::unique_ptr<std::vector<Vector2>> GenerateLimacon(float loop, float dimple, float thetaInitial, float thetaFinal, int pointCount)
{
	std::unique_ptr<std::vector<Vector2>> returnValue = std::make_unique<std::vector<Vector2>>();
	float interval = (thetaFinal - thetaInitial) / pointCount;

	for (int i = 0; i < pointCount; i++)
	{
		float angle = thetaInitial + (i * interval);
		float radius = loop + (dimple * cosf(angle));
		Polar polar = Polar(angle, radius);
		returnValue->push_back((Vector2)polar);
	}

	return returnValue;
}

std::unique_ptr<std::vector<Vector2>> GenerateRoseCurve(float size, int petalCount, float thetaInitial, float thetaFinal, int pointCount)
{
	std::unique_ptr<std::vector<Vector2>> returnValue = std::make_unique<std::vector<Vector2>>();
	float interval = (thetaFinal - thetaInitial) / pointCount;

	for (int i = 0; i < pointCount; i++)
	{
		float angle = thetaInitial + (i * interval);
		float radius = size * cosf(petalCount * angle);
		Polar polar = Polar(angle, radius);
		returnValue->push_back((Vector2)polar);
	}

	return returnValue;
}

std::unique_ptr<std::vector<Vector2>> GenerateLituusCurve(float size, float thetaInitial, float thetaFinal, int pointCount)
{
	std::unique_ptr<std::vector<Vector2>> returnValue = std::make_unique<std::vector<Vector2>>();
	float interval = (thetaFinal - thetaInitial) / pointCount;

	for (int i = 0; i < pointCount; i++)
	{
		float angle = thetaInitial + (i * interval);
		float radius = sqrtf((size * size) / angle);
		Polar polar = Polar(angle, radius);
		returnValue->push_back((Vector2)polar);
		polar = Polar(angle, -radius);
		returnValue->push_back((Vector2)polar);
	}

	return returnValue;
}

void PolarScene::Update()
{
}

void PolarScene::Draw()
{
	m_camera->BeginMode();

	DrawGrid(10, 5, DARKGRAY);

	std::unique_ptr<std::vector<Vector2>> spiral = GenerateArchimedeanSpiral(0.25, 0.25, 0, 20, 100);
	//std::unique_ptr<std::vector<Vector2>> spiral = GenerateCardioid(3, 0, 20, 50);
	//std::unique_ptr<std::vector<Vector2>> spiral = GenerateLimacon(2, 5, 0, 20, 50);
	//std::unique_ptr<std::vector<Vector2>> spiral = GenerateRoseCurve(4, 13, 0, 20, 250);
	//std::unique_ptr<std::vector<Vector2>> spiral = GenerateLituusCurve(5, 0, 15, 70);
	for (int i = 0; i < spiral->size(); i++)
	{
		DrawCircle(spiral->at(i), 0.25f, RED);
	}

	m_camera->EndMode();
}

void PolarScene::DrawGUI()
{
}
