#include <SFML/Graphics.hpp>

#include <Windows.h>

#include <string>
#include <iostream>
#include <cstdlib> 
#include <vector>
#include <ctime> importation des module 

#pragma region Variable
sf::RenderWindow app;

sf::Texture player;
sf::Sprite sprite_player;

int speed = 2;
int health = 6;

int taille = 64;

int offsetX = taille, offsetY = taille;

int px = 0, py = 0;

enum Dir { Down, Left, Right, Up };
sf::Vector2i anim(1, Down);
int animation = 18 - speed - 1;

bool mouvement = false;
bool colision_pers = false;

sf::Vector2f preview;

sf::View view;

int screenW = 800, screenH = 600;

sf::RectangleShape coeur;
sf::RectangleShape demi_coeur;

int space = false;

std::vector<sf::RectangleShape> vecbox;
#pragma endregion

#pragma region Levels
int tapmap[14][15] = {
	{0,0,0,0,8,0,0,5,0,6,0,0,0,0,0},
	{4,0,0,1,1,1,1,1,0,1,0,0,1,1,1},
	{1,1,0,0,0,0,3,0,0,3,0,4,0,0,0},
	{6,6,4,0,0,0,1,0,1,1,1,1,0,0,0},
	{1,1,1,1,2,0,0,0,0,0,1,0,6,6,6},
	{0,0,0,1,4,0,5,0,7,0,1,0,0,4,0},
	{1,1,1,1,1,0,1,0,1,1,1,1,1,1,1},
	{0,0,0,0,3,0,0,0,0,0,0,1,0,0,1},
	{7,0,0,0,2,6,6,6,0,7,0,1,0,0,1},
	{1,0,0,0,0,0,0,4,0,1,1,1,1,1,1},
	{0,1,0,1,1,1,1,1,1,1,0,1,0,0,0},
	{0,0,0,0,0,1,0,0,0,1,0,1,0,0,0},
	{0,0,1,0,0,0,0,3,0,1,0,1,0,0,0},
	{6,6,1,1,1,1,1,1,1,1,0,1,0,0,0},
};
#pragma endregion


#pragma region textures
	
sf::Texture block_texture,
			block_casse_texture,
			portal_texture,
			champigon_texture,
			mechant_texture,
			piege_texture,
			echelle_texture,
			depart_texture,
			coeur_texture,
			demi_coeur_texture;

#pragma endregion variable textures des blocks

#pragma region Fonction
	
void view_anim();
void gestion_anim();
void gestion_clavier();
void collision(bool collision);
std::vector<sf::RectangleShape> get_health(int health);
void reset_vetbox(bool position_reset);
void gestion_health();

#pragma endregion fonction declaration

#pragma region Variable collision

bool mechant_colision = false;
int mechant_colision_int = 0;
bool touche_le_sol_block = false;
bool touche_le_sol_block_casse = false;
bool touche_le_sol_piege = false;

#pragma endregion

//site color https://htmlcolorcodes.com/fr/

int main()
{

	app.create(sf::VideoMode(screenW, screenH,32),"Test Colision");
	app.setFramerateLimit(60);

#pragma region chargement image

	if (!block_texture.loadFromFile("texture/block.png")) std::cout << "erreur d'image chargement 'block.png'" << std::endl;
	if (!block_casse_texture.loadFromFile("texture/block_casse.jpg")) std::cout << "erreur d'image chargement 'block_casse.jpg'" << std::endl;
	if (!champigon_texture.loadFromFile("texture/champignon.png")) std::cout << "erreur d'image chargement 'champignon.png'" << std::endl;
	if (!mechant_texture.loadFromFile("texture/mechant.png")) std::cout << "erreur d'image chargement 'mechant.png'" << std::endl;
	if (!piege_texture.loadFromFile("texture/piege.png")) std::cout << "erreur d'image chargement 'piege.png'" << std::endl;
	if (!echelle_texture.loadFromFile("texture/ladders.png")) std::cout << "erreur d'image chargement 'ladders.png'" << std::endl;
	if (!depart_texture.loadFromFile("texture/champi.png")) std::cout << "erreur d'image chargement 'champi.png'" << std::endl;
	if (!portal_texture.loadFromFile("texture/portal.png")) std::cout << "erreur d'image chargement 'portal.png'" << std::endl;
	if (!demi_coeur_texture.loadFromFile("texture/coueur_demi.png")) std::cout << "erreur d'image chargement 'coueur_demi.png'" << std::endl;
	if (!coeur_texture.loadFromFile("texture/coueur_plein.png")) std::cout << "erreur d'image chargement 'coueur_plein.png'" << std::endl;

#pragma endregion chargement des texture des block

	reset_vetbox(true);

#pragma region elements
	if (!player.loadFromFile("player.png")) std::cout << "erreur d'image chargement" << std::endl;

	player.setSmooth(true);
	sprite_player.setTexture(player);

	gestion_anim();

	coeur.setTexture(&coeur_texture);
	demi_coeur.setTexture(&demi_coeur_texture);

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

		gestion_health();

		preview.x = px;
		preview.y = py;

		collision(false);

		gestion_clavier();

		collision(true);

		view_anim();

		animation++;
		gestion_anim();

		sprite_player.setPosition(px, py);

		app.clear();
		
		std::vector<sf::RectangleShape> vie = get_health(health);

		for (int i = 0; i < vecbox.size(); i++) app.draw(vecbox[i]);
		for (int i = 0; i < vie.size(); i++) app.draw(vie[i]);

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
#pragma region Variable
bool saut = false;
bool shift = false;
int fois = 0;
bool echelle_monter = false;
int is_saut = 0;
int py_avant = 0;
bool has_saut = false;
int douleur = 0;
int douleur_piege = 0;
#pragma endregion Variable pour collision et clavier
void gestion_clavier()
{
	#pragma region has_saut
		if (py_avant == py) is_saut++;
		py_avant = py;
		if (is_saut == 5) { has_saut = true; is_saut = 0; }

	#pragma endregion verification du saut

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		anim.y = Right;
		px += speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		anim.y = Left;
		px -= speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) shift = true;
	else shift = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		echelle_monter = true;
		if (space)
		{
			anim.y = Up;
			py -= 6;
		}
		else
		{
			echelle_monter = false;
			if (!saut)
			{
				if (has_saut)
				{
					saut = true;
				}
			}
		}
		has_saut = false;

	}else echelle_monter = false;
	if (saut)
	{
		fois++;

		py-=3;
		if (fois == 28)
		{
			saut = false;
			fois = 0;
		}
	}
}
void collision(bool collision)
{
	if (!collision &&!space && !saut) { py += 3; anim.y = Down;  }
	for (int y = 0; y < 14; y++)
	{
		for (int x = 0; x < 15; x++)
		{

			int top = y * offsetY;
			int bottom = top + offsetY;
			int left = x * offsetX;
			int right = left + offsetX;

			if (tapmap[y][x] == 1 && px + 38 >= left && px <= right && py + 48 >= top && py <= bottom)
			{
				//block
				if (tapmap[y + 2][x] == 7 && py + 48 >= top && shift);
				else if (tapmap[y + 2][x] == 7 && py <= bottom&&echelle_monter);
				else
				{					
					px = preview.x;
					py = preview.y;
					
				}

			}

			if (tapmap[y][x] == 2 && px + 38 >= left && px <= right && py + 48 >= top && py <= bottom)
			{
				//block_casse
				px = preview.x;
				py = preview.y;
				tapmap[y][x] = 0;
				reset_vetbox(false);
			}

			if (tapmap[y][x] == 3 && px + 38 >= left && px <= right && py + 48 >= top && py <= bottom)
			{
				//portal
				/*px = preview.x;
				py = preview.y;*/

			}
			if (tapmap[y][x] == 5 && px + 38 >= left && px <= right && py + 48 >= top && py <= bottom)
			{
				//mechant

				if (!mechant_colision)
				{
					health = health - 1;
					douleur = 0;
				}

				mechant_colision = true;
				std::cout << mechant_colision << std::endl;
			}
			else {
				if (collision) {
					douleur++;
					if (douleur == 5000)
					{
						mechant_colision = false;
						douleur = 0;
					}
				}
			}

			top = y * offsetY + 32;
			bottom = top + offsetY - 32;
			left = x * offsetX;
			right = left + offsetX;

			if (tapmap[y][x] == 6 && px + 38 >= left && px <= right && py + 48 >= top && py <= bottom)
			{
				//piege
				health = 6;
				reset_vetbox(true);
			}

			top = y * offsetY - offsetY * 2;
			bottom = top + offsetY * 3;
			left = x * offsetX;
			right = left + offsetX;

			if (tapmap[y][x] == 7 && px + 38 >= left && px <= right && py + 48 >= top && py <= bottom)
			{
				//echelle
				space = true;
			}
			else
			{
				if (collision)
				{
						space = false;
				}
			}

		}
	}
}
std::vector<sf::RectangleShape> get_health(int health) {
	std::vector<sf::RectangleShape> vie;
	sf::Vector2f position(screenW / 2, screenH / 2);
	position.x = sprite_player.getPosition().x + taille / 2 - (screenW / 2);
	position.y = sprite_player.getPosition().y + taille / 2 - (screenH / 2);

	coeur.setSize(sf::Vector2f(50, 50));
	demi_coeur.setSize(sf::Vector2f(50, 50));

		switch (health)
		{
		case 6:
			coeur.setPosition(sf::Vector2f(position.x + 10, position.y + 10));
			vie.push_back(coeur);
			coeur.setPosition(sf::Vector2f(position.x + 10+50, position.y + 10));
			vie.push_back(coeur);
			coeur.setPosition(sf::Vector2f(position.x + 10 + 50*2, position.y + 10));
			vie.push_back(coeur);
			break;
		case 5:
			coeur.setPosition(sf::Vector2f(position.x + 10, position.y + 10));
			vie.push_back(coeur);
			coeur.setPosition(sf::Vector2f(position.x + 10 + 50, position.y + 10));
			vie.push_back(coeur);
			demi_coeur.setPosition(sf::Vector2f(position.x + 10 + 50 * 2, position.y + 10));
			vie.push_back(demi_coeur);
			break;
		case 4:
			coeur.setPosition(sf::Vector2f(position.x + 10, position.y + 10));
			vie.push_back(coeur);
			coeur.setPosition(sf::Vector2f(position.x + 10 + 50, position.y + 10));
			vie.push_back(coeur);
			break;
		case 3:
			coeur.setPosition(sf::Vector2f(position.x + 10, position.y + 10));
			vie.push_back(coeur);
			demi_coeur.setPosition(sf::Vector2f(position.x + 10 + 50, position.y + 10));
			vie.push_back(demi_coeur);
			break;
		case 2:
			coeur.setPosition(sf::Vector2f(position.x + 10, position.y + 10));
			vie.push_back(coeur);
			break;
		case 1:
			demi_coeur.setPosition(sf::Vector2f(position.x + 10, position.y + 10));
			vie.push_back(demi_coeur);
			break;

		default:
			//std::cout << "erreur de vie" << std::endl;
			break;
		}
	return vie;
}
void reset_vetbox(bool position_reset)
{
	vecbox.clear();
	for (int y = 0; y < 14; y++)
	{
		for (int x = 0; x < 15; x++)
		{
			if (tapmap[y][x] == 1) {
				//block
				sf::RectangleShape block(sf::Vector2f(offsetX, offsetY));
				//block.setFillColor(sf::Color::Red);
				block.setTexture(&block_texture);
				block.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(block);
			}
			if (tapmap[y][x] == 2) {
				//block_casse
				sf::RectangleShape block_casse(sf::Vector2f(offsetX, offsetY));
				//block_casse.setFillColor(sf::Color(117,10,10,255));
				block_casse.setTexture(&block_casse_texture);
				block_casse.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(block_casse);
			}
			if (tapmap[y][x] == 3) {
				//portal
				sf::RectangleShape portal(sf::Vector2f(offsetX, offsetY));
				//portal.setFillColor(sf::Color::Blue);
				portal.setTexture(&portal_texture);
				portal.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(portal);
			}
			if (tapmap[y][x] == 4) {
				//champignon
				sf::RectangleShape champignon(sf::Vector2f(offsetX, offsetY));
				//champignon.setFillColor(sf::Color::Green);
				champignon.setTexture(&champigon_texture);
				champignon.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(champignon);
			}
			if (tapmap[y][x] == 5) {
				//mechant
				sf::RectangleShape mechant(sf::Vector2f(offsetX, offsetY));
				//mechant.setFillColor(sf::Color::Yellow);
				mechant.setTexture(&mechant_texture);
				mechant.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(mechant);
			}
			if (tapmap[y][x] == 6) {
				//piege
				sf::RectangleShape piege(sf::Vector2f(offsetX, offsetY));
				//piege.setFillColor(sf::Color::Magenta);
				piege.setTexture(&piege_texture);
				piege.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(piege);
			}
			if (tapmap[y][x] == 7) {
				//echelle
				sf::RectangleShape echelle(sf::Vector2f(offsetX, offsetY * 3));
				//echelle.setFillColor(sf::Color::White);
				echelle.setTexture(&echelle_texture);
				echelle.setPosition(sf::Vector2f(x * offsetX, y * offsetY - offsetY * 2));
				vecbox.push_back(echelle);
			}
			if (tapmap[y][x] == 8) {
				//debut
				sf::RectangleShape debut(sf::Vector2f(offsetX * 4, offsetY * 4));
				//debut.setFillColor(sf::Color(80, 220,255,255));
				debut.setTexture(&depart_texture);
				debut.setPosition(sf::Vector2f(x * offsetX, y * offsetY - offsetY * 3 + 10));
				if (position_reset)
				{
					px = debut.getPosition().x + offsetY * 4 / 2;
					py = debut.getPosition().y + offsetY * 3 + 5;
				}
				vecbox.push_back(debut);
			}
		}
	}
}
void gestion_health() {
	if (health <= 0)
	{
		reset_vetbox(true);
		health = 6;
	}
}