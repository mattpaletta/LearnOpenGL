#include "breakout_effects.hpp"

BreakoutEffects::BreakoutEffects(Shader shader, unsigned int width, unsigned int height) : PostProcessor(shader, width, height) , Confuse(false), Chaos(false), Shake(false) {
	// initialize render data and uniforms
	this->initRenderData();
	this->PostProcessingShader.setInt("scene", 0, true);

	constexpr float offset = 1.0f / 300.0f;
	constexpr float offsets[9][2] = {
		{ -offset,  offset  },  // top-left
		{  0.0f,    offset  },  // top-center
		{  offset,  offset  },  // top-right
		{ -offset,  0.0f    },  // center-left
		{  0.0f,    0.0f    },  // center-center
		{  offset,  0.0f    },  // center - right
		{ -offset, -offset  },  // bottom-left
		{  0.0f,   -offset  },  // bottom-center
		{  offset, -offset  }   // bottom-right    
	};
	glUniform2fv(glGetUniformLocation(this->PostProcessingShader.ID, "offsets"), 9, (float*)offsets);

	int edge_kernel[9] = {
		-1, -1, -1,
		-1,  8, -1,
		-1, -1, -1
	};
	glUniform1iv(glGetUniformLocation(this->PostProcessingShader.ID, "edge_kernel"), 9, edge_kernel);

	float blur_kernel[9] = {
		1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f,
		2.0f / 16.0f, 4.0f / 16.0f, 2.0f / 16.0f,
		1.0f / 16.0f, 2.0f / 16.0f, 1.0f / 16.0f
	};
	glUniform1fv(glGetUniformLocation(this->PostProcessingShader.ID, "blur_kernel"), 9, blur_kernel);
}

void BreakoutEffects::Render(float time) {
	// set uniforms/options specific to the shader(s)
	this->PostProcessingShader.use();
	this->PostProcessingShader.setFloat("time", time);
	this->PostProcessingShader.setInt("confuse", this->Confuse);
	this->PostProcessingShader.setInt("chaos", this->Chaos);
	this->PostProcessingShader.setInt("shake", this->Shake);

	// Render the VBO in the base method.
	PostProcessor::Render(time);
}

void BreakoutEffects::RenderBlock(const float time, const std::function<void()>&& f) {
	this->BeginRender();
	f();
	this->EndRender();
	this->Render(time);
}