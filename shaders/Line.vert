#version 330 core
layout(location = 0) in vec2 aPos;

uniform mat4 projection;

void main()
{
	vec4 result = projection * vec4(aPos.x, aPos.y, 0.0f, 1.0);
	gl_Position = result;
}
