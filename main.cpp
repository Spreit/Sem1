#include <Game.hpp>

int main()
{
    mt::Game game;

    game.SetResolution(600, 600);
    game.SetCaption("Firework");
    game.Setup();

    game.Run();

    return 0;
}