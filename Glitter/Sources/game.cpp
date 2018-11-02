#include "game.h"
#include "resource_manager.h"

Game::Game(GLuint width, GLuint height)
    : _width(width), _height(height), _state(GAME_ACTIVE), _keys()
{
    
}

Game::~Game()
{
}

void Game::Init()
{
}

void Game::ProcessInput(GLfloat dt)
{
}

void Game::Update(GLfloat dt)
{
}

void Game::Render()
{
}
