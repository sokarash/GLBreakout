#pragma once

#include <glad/glad.h>

enum GameState {GAME_ACTIVE, GAME_MENU, GAME_WIN };

class Game
{
    
    #pragma region fields
public:
        GameState _state;
        GLboolean _keys[1024];
        GLuint _width, _height;
    #pragma endregion

    #pragma region Constructor / Destructor
public:
    Game(GLuint width, GLuint height);
    ~Game();

    #pragma endregion

    #pragma region Functions
public:
    void Init();

    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();

    #pragma endregion
        
};
