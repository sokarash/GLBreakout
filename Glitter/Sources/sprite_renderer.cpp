#include "sprite_renderer.h"

SpriteRenderer::SpriteRenderer(Shader & shader)
{
    this->_shader = shader;
    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &this->_quadVAO);
}

void SpriteRenderer::DrawSprite(Texture2D & texture, glm::vec2 position, glm::vec2 size, GLfloat rotation, glm::vec3 color)
{
    this->_shader.Use();
    glm::mat4 model = glm::mat4(1.0);

    // transformation order: scale, rotate, translate - backwards because read from right to left

    // translate to new positions
    model = glm::translate(model, glm::vec3(position, 0.0f));

    // move to origin, rotate, and move back
    model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

    model = glm::scale(model, glm::vec3(size, 1.0f));

    this->_shader.SetMatrix4("model", model);

    this->_shader.SetVector3f("spriteColor", color);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->_quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::initRenderData()
{
    // VAO/VBO config
    GLuint VBO;
    // combine position and texture information in one array to push them to the GPU in one go
    // its possible here since its only 2d and four values are used -> in shader vec4 is enough
    GLfloat vertices[] = {
        // Position // Texture coordainte
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
    };

    glGenVertexArrays(1, &this->_quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->_quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), (GLvoid*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
