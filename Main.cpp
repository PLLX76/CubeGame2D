#include <SFML/Graphics.hpp>

#include <string>
#include <iostream>
#include <cstdlib> 
#include <vector>
#include <ctime> importation des module 

#pragma region Variable
sf::RenderWindow app;

sf::Texture player;
sf::Sprite sprite_player;

int speed = 1;

int taille = 64;

int offsetX = taille, offsetY = taille;

int px = 0, py = 0;

enum Dir { Down, Left, Right, Up };
sf::Vector2i anim(1, Down);
int animation = 18 - speed - 1;

bool mouvement = false;

const int taillemap = 10;

sf::Vector2f preview;

sf::View view;

int screenW = 800, screenH = 600;
#pragma endregion

#pragma region Fonction
	
void view_anim();
void gestion_anim();
void gestion_clavier();

#pragma endregion


int main()
{

	app.create(sf::VideoMode(screenW, screenH,32),"Test Colision");
	app.setFramerateLimit(60);

#pragma region chargement image

#pragma endregion chargement des images

	int tapmap[taillemap][taillemap] =
	{
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,1,0,0,0,0},
		{0,0,0,0,0,1,0,0,0,0},
		{0,0,0,0,0,1,1,0,0,0},
		{0,0,0,0,1,0,1,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,1,0,0,0,0,0,0},
		{0,0,0,1,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
	};

	std::vector<sf::RectangleShape> vecbox;

	for (int y = 0; y < taillemap; y++)
	{
		for (int x = 0; x < taillemap; x++)
		{
			if (tapmap[y][x] == 1) {
				sf::RectangleShape box(sf::Vector2f(offsetX,offsetY));
				box.setFillColor(sf::Color::Red);
				box.setPosition(sf::Vector2f(x*offsetX,y*offsetY));
				vecbox.push_back(box);
			}
		}
	}


#pragma region elements
	if (!player.loadFromFile("player.png")) std::cout << "erreur d'image chargement" << std::endl;

	player.setSmooth(true);
	sprite_player.setTexture(player);

	gestion_anim();
#pragma endregion

	while (app.isOpen())
	{

		sf::Event event;
		while (app.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				std::cout << "fermeture la fenetre" << std::endl;
				app.close();
				break;
			}
			if (event.type == sf::Event::KeyPressed) mouvement = true;
			else mouvement = false;
			
		}

		preview.x = px;
		preview.y = py;

		gestion_clavier();

		for (int y = 0; y < taillemap; y++)
		{
			for (int x = 0; x < taillemap; x++)
			{
				int top = y*offsetY;
				int bottom = y*offsetY+offsetY;
				int left = x*offsetX;
				int right = x * offsetX + offsetX;

				if (tapmap[y][x]==1 && px+38 >= left && px <= right && py+48 >= top && py <= bottom)
				{
					px = preview.x;
					py = preview.y;
				}

			}
		}

		view_anim();

		animation++;
		gestion_anim();

		sprite_player.setPosition(px, py);

		app.clear();
		
		for (int i = 0; i < vecbox.size(); i++) app.draw(vecbox[i]);
		

		app.draw(sprite_player);

		app.display();

	}

}

void view_anim()
{
	view.reset(sf::FloatRect(0, 0, screenW, screenH));
	sf::Vector2f position(screenW / 2, screenH / 2);
	position.x = sprite_player.getPosition().x + taille/2 - (screenW / 2);
	position.y = sprite_player.getPosition().y + taille / 2 - (screenH / 2);
	view.reset(sf::FloatRect(position.x, position.y, screenW, screenH));
	app.setView(view);
}
void gestion_anim() {
	if (animation == 18 - speed)
	{
		if (mouvement)
		{
			anim.x++;
			if (anim.x * 64 + 10 >= player.getSize().x - 10) anim.x = 0;
			sprite_player.setTextureRect(sf::IntRect(anim.x * 48, anim.y * 48, 48, 48));


		}
		else
		{
			if (anim.x * 64 + 10 >= player.getSize().x - 10) anim.x = 0;
			sprite_player.setTextureRect(sf::IntRect(anim.x, anim.y * 48, 48, 48));
		}

		animation = 0;
	}
}
void gestion_clavier()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		anim.y = Up;
		py -= speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		anim.y = Down;
		py += speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		anim.y = Right;
		px += speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		anim.y = Left;
		px -= speed;
	}
}