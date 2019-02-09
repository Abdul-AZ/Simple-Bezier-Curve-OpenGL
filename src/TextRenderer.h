#pragma once

#include <ft2build.h>
#include FT_FREETYPE_H

#include <map>
#include <iostream>
#include "glad/glad.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

void InitTextRendering(FT_Face& face);

void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color);