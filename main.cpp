#include <SFML/Graphics.hpp>
#include <time.h>

using namespace sf;

const int M = 20; // Mer Xaxain hartaki barcruyun@
const int N = 10; // Mer xaxain hartaki Laynutyun@

int field[M][N] = { 0 }; // Mer xaxain hartakna skzbnakan arjeq@ 0 qani vor ayn datarka

struct Point
{
	int x, y;
} a[4], b[4];

int figures[7][4] = 
{
	1, 3, 5, 7, // I				//////////////////
	2, 4, 5, 7, // S				//	 0	//	 1	//
	3, 5, 4, 6, // Z				//////////////////
	3, 5, 4, 7, // T				//	 2	//	 3	//
	2, 3, 5, 7, // L				//////////////////
	3, 5, 7, 6, // J				//   4  //   5  //
	2, 3, 4, 5, // O				//////////////////
};									//	 6	//	 7	//
									//////////////////

bool check()
{
	for(int i = 0; i < 4; i++)
		if(a[i].x < 0 || a[i].x >= N || a[i].y >= M) return 0;
		else if(field[a[i].y][a[i].x]) return 0;
 
	return 1;
}
								
int main()
{	
	srand(time(0));
	RenderWindow window(VideoMode(273, 410),"MY_Tetris_Game");
	Texture texture,backgraund_texture,texture_frame;
	texture.loadFromFile("C:\\Users\\Erik\\Desktop\\SFML_Project\\Tetris\\Imges\\Tetris.png");
	backgraund_texture.loadFromFile("C:\\Users\\Erik\\Desktop\\SFML_Project\\Tetris\\Imges\\background.png");
	texture_frame.loadFromFile("C:\\Users\\Erik\\Desktop\\SFML_Project\\Tetris\\Imges\\frame.png");
	Sprite sprite(texture), sprite_backgraund(backgraund_texture), sprite_frame(texture_frame);;
	sprite.setTextureRect(IntRect(0, 0, 15, 15));
	int dx = 0;
	bool rotate = 0;
	int colorNum = 1;
	bool beginGame = true; 
	int n = rand() % 7;
	float timer = 0, delay = 0.3;
	Clock clock;
	while(window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		Event event;
		while(window.pollEvent(event))
		{
		if(event.type == Event::Closed)
			window.close();
		if(event.type == Event::KeyPressed)
		if (event.key.code == Keyboard::Up) rotate = true;
		if(event.key.code == Keyboard::Left) dx = -1;
		else if(event.key.code == Keyboard::Right) dx = 1;
		}
		
		if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;
		for (int i = 0; i < 4; i++) 
		{
			b[i] = a[i];
			a[i].x += dx;
		}
		if(!check()){
			for(int i = 0; i<4; i++) 
			a[i] = b[i];
		}
		
		if(rotate)
		{
			Point p = a[1];
			for (int i = 0; i < 4; i++)
			{
				int x = a[i].y - p.y;
				int y = a[i].x - p.x;
				a[i].x = p.x - x;
				a[i].y = p.y + y;
			}
			
			if (!check()) { 
	        	for (int i = 0; i < 4; i++)
	        	a[i] = b[i];
	        }
		}

		if(timer > delay)
		{
			for(int i = 0; i < 4; i++) 
			{
				b[i] = a[i];
				a[i].y += 1;
			}
			if(!check())
			{
				for(int i = 0; i < 4; i++) field[b[i].y][b[i].x] = colorNum;
				colorNum = 1 + rand() % 7;
				n = rand() % 7;
				for(int i = 0; i < 4; i++)
				{
					a[i].x = figures[n][i] % 2 + 4;
					a[i].y = figures[n][i] / 2;
					if(field[a[i].y][a[i].x] != 0) window.close();
				}
			}
			timer = 0;
		}
		if(beginGame)
		{
			beginGame = false;
			n = rand() % 7;
			for(int i = 0; i < 4; i++)
			{
				a[i].x = figures[n][i] % 2 + 4;;
				a[i].y = figures[n][i] / 2;
			}
		}
		
		int k = M - 1;
		for(int i = M - 1; i > 0; i--)
		{
			int count = 0;
			for(int j = 0; j < N; j++)
			{
				if(field[i][j]) count++;
				field[k][j] = field[i][j];
			}
			if(count < N) k--;
		}
		
		dx = 0;
		rotate = 0;
		delay = 0.3;	
		window.clear(Color::White);
		window.draw(sprite_backgraund);
		for(int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
		{	
			if (field[i][j] == 0) continue;
			if(field[i][j] <= 4) 
			sprite.setTextureRect(IntRect((field[i][j] - 1) * 15, 0, 15, 15));
			else sprite.setTextureRect(IntRect((field[i][j] - 5) * 15, 15, 15, 15));
			sprite.setPosition(j * 15, i * 15);
			sprite.move(24, 31);
			window.draw(sprite);
		}
		
		for (int i = 0; i < 4; i++)
		{	
			if(colorNum <= 4)
			sprite.setTextureRect(IntRect((colorNum - 1) * 15, 0, 15, 15));
			else sprite.setTextureRect(IntRect((colorNum - 5) * 15, 15, 15, 15));
			sprite.setPosition(a[i].x * 15, a[i].y * 15);
			sprite.move(24, 31);
			window.draw(sprite);
		}
		window.display();
	}
	return 0;
}
