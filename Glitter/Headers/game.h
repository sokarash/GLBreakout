#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

enum GameState {GAME_ACTIVE, GAME_MENU, GAME_WIN };

class Game
{
    public:
    #pragma region fields
        GameState _state;
        GLboolean _keys[1024];
        GLuint _width, _height;
    #pragma endregion

    #pragma region Constructor / Destructor

    Game(GLuint width, GLuint height);
    ~Game();

    #pragma endregion

    #pragma region Functions

    void Init();

    void ProcessInput(GLfloat dt);
    void Update(GLfloat dt);
    void Render();

    #pragma endregion
        
};
