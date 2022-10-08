#version 450

layout (location = 0) in vec3 Normal;
layout (location = 1) in vec3 WorldPos;
layout (location = 2) in vec2 Tex;
layout (location = 4) in vec4 Color;
layout(location = 0) out vec4 o_color;

void main() {
	// Constants
	float AmbientFactor = 0.3;
	vec3 DiffuseColor = vec3(Color.r, Color.g, Color.b);
	vec3 SpecularColor = vec3(1, 1, 1);

	// Apply procedural pattern based on the uv coordinates
	bool2 less_half = Tex - floor(Tex) < vec2(0.5, 0.5);
	float darken_factor = less_half.r ^ less_half.g? 0.5 : 1.0;

	// Fade out checkerboard pattern when it tiles too often
	vec2 dx = dfdx(Tex), dy = dfdy(Tex);
	float texel_distance = sqrt(dot(dx, dx) + dot(dy, dy));
	darken_factor = lerp(darken_factor, 0.75, clamp(5.0 * texel_distance - 1.5, 0.0, 1.0));

	// Calculate color
	o_color = vec4(saturate(AmbientFactor * darken_factor * DiffuseColor + SpecularColor), 1);
}