#include"Game.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand(static_cast<unsigned>(time(0)));

	RenderWindow window(VideoMode(1280, 720), "Revenge of Luigi.exe");
	Game game;

	Clock clock;
	float time;

	window.setFramerateLimit(120);

	while (window.isOpen())
	{
		Event Event;

		while (window.pollEvent(Event))
		{
			switch (Event.type)
			{
			case Event::Closed:
				window.close();
				break;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::BackSpace))
			window.close();
	
		time = clock.getElapsedTime().asMilliseconds();
		clock.restart();

		game.update(time, window);

		window.clear();
		game.draw(window);
		window.display();
	}

	return 0;
}