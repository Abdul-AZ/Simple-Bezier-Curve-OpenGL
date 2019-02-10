#version 330 core
layout(location = 0) in vec2 aPos;

uniform mat4 model;
uniform mat4 projection;

void main()
{
	vec4 result = projection * model * vec4(aPos.x, aPos.y, 0.0f, 1.0f);
	gl_Position = result;
}
