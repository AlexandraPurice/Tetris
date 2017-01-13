
#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>
#include <sstream>

using namespace sf;

const int M = 20;
const int N = 10;

int field[M][N] = { 0 };

struct Point
{
	int x, y;
} a[4], b[4];

int figures[7][4] =
{
	1,3,5,7, // I
	2,4,5,7, // Z
	3,5,4,6, // S
	3,5,4,7, // T
	2,3,5,7, // L
	3,5,7,6, // J
	2,3,4,5, // O
};

bool check()
{
	int i;
	for ( i = 0; i<4; i++)
		if (a[i].x<0 || a[i].x >= N || a[i].y >= M)
			return 0;
		else
			if (field[a[i].y][a[i].x])
				return 0;

	return 1;
};


int main()
{
	int i, j,n, colorNum,dx;
	bool rotate;
	float timer, delay;
	srand(time(0));

	RenderWindow window(VideoMode(320, 480), "TETRIS");

	Texture t1, t2, t3;
	t1.loadFromFile("C:/Users/Alexandra/Desktop/imagini/tiles.png");
	t2.loadFromFile("C:/Users/Alexandra/Desktop/imagini/background.png");
	t3.loadFromFile("C:/Users/Alexandra/Desktop/imagini/frame.png");

	Sprite s(t1), background(t2), frame(t3);

	dx = 0;
	rotate = 0;
	colorNum = 1;
	timer = 0, delay = 0.3;

	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		Event e;
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)
				window.close();

			if (e.type == Event::KeyPressed)
				if (e.key.code == Keyboard::Up)
					rotate = true;
				else
					if (e.key.code == Keyboard::Left)
						dx = -1;
					else
						if (e.key.code == Keyboard::Right)
							dx = 1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Down))
			delay = 0.05;

		//MUTARE
		for ( i = 0; i<4; i++)
		{
			b[i] = a[i];
			a[i].x += dx;
		}
		if (!check())
			for ( i = 0; i<4; i++)
				a[i] = b[i];

		dx = 0; rotate = 0; delay = 0.3;


		window.draw(frame);
		window.display();
	}

	return 0;
}






