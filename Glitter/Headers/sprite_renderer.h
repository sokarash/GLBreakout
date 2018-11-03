#pragma once

#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "shader.h"

class SpriteRenderer
{
    #pragma region Fields

private:

    Shader _shader;
    GLuint _quadVAO;

    #pragma endregion

    #pragma region Constructor / Destructor

public:
    SpriteRenderer(Shader &shader);

    ~SpriteRenderer();

    #pragma endregion

    #pragma region Functions
public:
    void DrawSprite(Texture2D &tex, glm::vec2 pos, glm::vec2 size = glm::vec2(10, 10), GLfloat rot = 0.0f, glm::vec3 color = glm::vec3(1.0f));

private:
    void initRenderData();
    #pragma endregion
};


#endif