#pragma once

#include <engine/post_processing.hpp>
#include <engine/shader.hpp>

class BreakoutEffects : public PostProcessor {
public:
	// options
	bool Confuse, Chaos, Shake;

	BreakoutEffects(Shader shader, unsigned int width, unsigned int height);

	void Render(float time) override;

	void RenderBlock(const float time, const std::function<void()>&& f);
};