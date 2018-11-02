#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"

SpriteRenderer *Renderer;


Game::Game(GLuint width, GLuint height)
    : _width(width), _height(height), _state(GAME_ACTIVE), _keys()
{
    
}

Game::~Game()
{
    delete Renderer;
}

void Game::Init()
{
    ResourceManager::LoadShader(std::string(PROJECT_SOURCE_DIR) + "/Glitter/shader/sprite.vs.glsl", std::string(PROJECT_SOURCE_DIR) + "/Glitter/shader/sprite.fs.glsl", "", "sprite");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->_width), static_cast<GLfloat>(this->_height), 0.0f, -1.0f, 1.0f);
    ResourceManager::GetShader("sprite").Use();
    ResourceManager::GetShader("sprite").SetInteger("image", 0);
    ResourceManager::GetShader("sprite").Use().SetMatrix4("projection", projection);

    Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

    ResourceManager::LoadTexture(std::string(PROJECT_SOURCE_DIR) + "/Glitter/textures/awesomeface.png", GL_TRUE, "face");
}

void Game::ProcessInput(GLfloat dt)
{
}

void Game::Update(GLfloat dt)
{
}

void Game::Render()
{
    Renderer->DrawSprite(ResourceManager::GetTexture("face"), glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}
