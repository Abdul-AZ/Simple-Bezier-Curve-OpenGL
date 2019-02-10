#pragma once
#include <vector>
#include <iostream>
#include <glad/glad.h>
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void InitLineRendering();

void RenderLine(std::vector<glm::vec2>& points);