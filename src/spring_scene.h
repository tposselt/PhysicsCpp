#pragma once
#include "scene.h"

struct Body;

class SpringScene : public Scene
{
private:
	Body* m_selectedBody{ nullptr };
	Body* m_connectBody{ nullptr };

public:
	SpringScene(const std::string& title, int width, int height, const Color& background = BLACK) :
		Scene(title, width, height, background)
	{
	}

	void Initialize() override;
	void Update() override;
	void FixedUpdate() override;
	void Draw() override;
	void DrawGUI() override;
};