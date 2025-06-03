#pragma once
#include "scene.h"

struct Body;

class VectorScene : public Scene
{
private:
	Body* m_head{ nullptr };
	Body* m_player{ nullptr };

	void CreateBallFirework(const Vector2& position);
	void CreateHourglassFirework(const Vector2& position);
	void CreateBurstFirework(const Vector2& position);

public:
	VectorScene(const std::string& title, int width, int height, const Color& background = BLACK) :
		Scene(title, width, height, background)
	{
	}

	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;
	void Draw() override;
	void DrawGUI() override;
};