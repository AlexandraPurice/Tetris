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
	1,3,5,7,
	2,4,5,7,
	3,5,4,6,
	3,5,4,7,
	2,3,5,7,
	3,5,7,6,
	2,3,4,5,
};

bool check()
{
	int i;
	for (i = 0; i<4; i++)
		if (a[i].x<0 || a[i].x >= N || a[i].y >= M)
			return 0;
		else
			if (field[a[i].y][a[i].x])
				return 0;

	return 1;
};

int score, t;

int main()
{
	int i, j, n, colorNum, dx;
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
	colorNum = 0;
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
		for (i = 0; i<4; i++)
		{
			b[i] = a[i];
			a[i].x += dx;
		}
		if (!check())
			for (i = 0; i<4; i++)
				a[i] = b[i];
		//ROTIRE PIESE
		if (rotate)
		{
			Point p = a[1];
			for (i = 0; i<4; i++)
			{
				int x = a[i].y - p.y;
				int y = a[i].x - p.x;
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
			if (!check())
				for (i = 0; i<4; i++)
					a[i] = b[i];
		}
		//Tick
		if (timer>delay)
		{
			for (i = 0; i<4; i++)
			{
				b[i] = a[i];
				a[i].y += 1;
			}

			if (!check())
			{
				for (i = 0; i<4; i++)
					field[b[i].y][b[i].x] = colorNum;

				colorNum = 1 + rand() % 7;
				n = rand() % 7;
				for (i = 0; i<4; i++)
				{
					a[i].x = figures[n][i] % 2;
					a[i].y = figures[n][i] / 2;
				}
			}

			timer = 0;
		}

		//score
		sf::Font arial;
		arial.loadFromFile("arial.ttf");
		std::ostringstream ssScore;
		ssScore << "Score: " << std::endl;
		ssScore << score;
		sf::Text lblScore;
		lblScore.setCharacterSize(20);
		lblScore.setPosition({ 250, 100 });
		lblScore.setFont(arial);
		lblScore.setString(ssScore.str());
		//elimina linie
		int k = M - 1;
		for (i = M - 1; i > 0; i--)
		{
			int count = 0;
			for (j = 0; j < N; j++)
			{
				if (field[i][j])
					count++;
				field[k][j] = field[i][j];
				if (count >= N - 1 + 1)
				{
					t++;
					lblScore.setCharacterSize(20);
					lblScore.setPosition({ 220, 200 });
					lblScore.setFont(arial);
					lblScore.setString(ssScore.str());
					score = score + 10;
					ssScore.str("");
					ssScore << "Score " << score;
					lblScore.setString(ssScore.str());
				}
			}
			if (t == 6)
			{
				t = 0;
				lblScore.setCharacterSize(20);
				lblScore.setPosition({ 220, 200 });
				lblScore.setFont(arial);
				lblScore.setString(ssScore.str());
				score = score + 40;
				ssScore.str("");
				ssScore << "Score " << score;
				lblScore.setString(ssScore.str());
			}

			if (count < N)
				k--;
		}
		dx = 0; rotate = 0; delay = 0.3;
		//draw
		window.clear(Color::White);
		window.draw(background);
		window.draw(frame);
		for (i = 0; i<M; i++)
			for (j = 0; j < N; j++)
			{
				if (field[i][j] == 0)
					continue;
				s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
				s.setPosition(j * 18, i * 18);
				s.move(28, 31);
				window.draw(s);
			}
		for (int i = 0; i < M; i++)
		{
			if (field[0][i] != 0)
				for (int j = i; j < N; j++)
					if (field[i][j] != 0)
					{
						sf::Font arial;
						arial.loadFromFile("arial.ttf");

						std::ostringstream gameover;
						gameover << "GAME OVER ";
						sf::Text lblGame;

						lblGame.setCharacterSize(30);
						lblGame.setPosition({ 100, 200 });
						lblGame.setFont(arial);
						lblGame.setString(gameover.str());
						window.draw(lblGame);

					}
		}
		for (i = 0; i<4; i++)
		{
			s.setTextureRect(IntRect(colorNum * 18, 0, 18, 18));
			s.setPosition(a[i].x * 18, a[i].y * 18);
			s.move(28, 31);
			window.draw(s);
		}

		window.draw(lblScore);
		window.display();
	}

	return 0;
}