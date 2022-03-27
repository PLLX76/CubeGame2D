#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <Windows.h>

#include <fstream>

#include "portal.h"
#include "String.h"
#include "Levels.h"

#include <string>
#include <iostream>
#include <cstdlib> 
#include <vector>
#include <ctime> importation des module 

#pragma region Variable
sf::RenderWindow app;

sf::Image icon;

sf::Texture player;
sf::Sprite sprite_player;

sf::Sound sound_portal;
sf::Sound sound_damage;
sf::Sound sound_marche;

sf::Font font;
std::string font_path = "police.ttf";

int speed = 2;
int health = 6;

int taille = 64;

int record = 1;
sf::Text record_text;

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
std::string title = "GameCube2D";
int resolution = 32;

sf::RectangleShape coeur;
sf::RectangleShape demi_coeur;

int space = false;

std::vector<sf::RectangleShape> vecbox;

bool fullscreen;

sf::RectangleShape btn1;
sf::RectangleShape btn2;
sf::Text number;
int latence_int = 0;

sf::RectangleShape help_rect;
bool help = false;
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
			demi_coeur_texture,
			fin_texture;
sf::Texture fleche_droite,
			fleche_gauche;
sf::Texture help_texture;
#pragma endregion variable textures des blocks

#pragma region Fonction
	
void view_anim(sf::Event event);
void gestion_anim();
void gestion_clavier();
void collision(bool collision);
std::vector<sf::RectangleShape> get_health(int health);
void reset_vetbox(bool position_reset);
void gestion_health();
void config();
void charge();
void button();
void latence(bool latence);
bool help_function();

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
	config();
	charge();

	if (fullscreen) {
		screenW = sf::VideoMode::getFullscreenModes()[0].width;
		screenH = sf::VideoMode::getFullscreenModes()[0].height;
		app.create(sf::VideoMode(screenW, screenH, resolution), title, sf::Style::Fullscreen);
	}
	if (!fullscreen) app.create(sf::VideoMode(screenW, screenH, resolution), title, sf::Style::Default);
	app.setFramerateLimit(60);
	if (!icon.loadFromFile(("resourcespack/" + resourcespack + "/mechant.png").c_str())) std::cout << "error icon ligne 126" << std::endl;
	app.setIcon(500, 500, icon.getPixelsPtr());

#pragma region chargement image
	if (!block_texture.loadFromFile(("resourcespack/"+ resourcespack +"/texture/block.png").c_str())) if (!block_texture.loadFromFile("resourcespack/default/texture/block.png")) std::cout << "erreur d'image chargement 'block.png'" << std::endl;
	if (!block_casse_texture.loadFromFile(("resourcespack/"+resourcespack+"/texture/block_casse.jpg").c_str())) if (!block_casse_texture.loadFromFile("resourcespack/default/texture/block_casse.jpg")) std::cout << "erreur d'image chargement 'block_casse.jpg'" << std::endl;
	if (!champigon_texture.loadFromFile(("resourcespack/"+resourcespack+"/texture/champignon.png").c_str())) if (!champigon_texture.loadFromFile("resourcespack/default/texture/champignon.png")) std::cout << "erreur d'image chargement 'champignon.png'" << std::endl;
	if (!mechant_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/mechant.png").c_str())) if (!mechant_texture.loadFromFile("resourcespack/default/texture/mechant.png")) std::cout << "erreur d'image chargement 'mechant.png'" << std::endl;
	if (!piege_texture.loadFromFile(("resourcespack/"+resourcespack+"/texture/piege.png").c_str())) if (!piege_texture.loadFromFile("resourcespack/default/texture/piege.png")) std::cout << "erreur d'image chargement 'piege.png'" << std::endl;
	if (!echelle_texture.loadFromFile(("resourcespack/"+resourcespack+"/texture/ladders.png").c_str())) if (!echelle_texture.loadFromFile("resourcespack/default/texture/ladders.png")) std::cout << "erreur d'image chargement 'ladders.png'" << std::endl;
	if (!depart_texture.loadFromFile(("resourcespack/"+resourcespack+"/texture/champi.png").c_str())) if (!depart_texture.loadFromFile("resourcespack/default/texture/champi.png")) std::cout << "erreur d'image chargement 'champi.png'" << std::endl;
	if (!portal_texture.loadFromFile(("resourcespack/"+resourcespack+"/texture/portal.png").c_str())) if (!portal_texture.loadFromFile("resourcespack/default/texture/portal.png")) std::cout << "erreur d'image chargement 'portal.png'" << std::endl;
	if (!demi_coeur_texture.loadFromFile(("resourcespack/"+resourcespack+"/texture/coueur_demi.png").c_str())) if (!demi_coeur_texture.loadFromFile("resourcespack/default/texture/coueur_demi.png")) std::cout << "erreur d'image chargement 'coueur_demi.png'" << std::endl;
	if (!coeur_texture.loadFromFile(("resourcespack/"+resourcespack+"/texture/coueur_plein.png").c_str())) if (!coeur_texture.loadFromFile("resourcespack/default/texture/coueur_plein.png")) std::cout << "erreur d'image chargement 'coueur_plein.png'" << std::endl;
	if (!fin_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/fin.png").c_str())) if (!fin_texture.loadFromFile("resourcespack/default/texture/fin.png")) std::cout << "erreur chargement d'image 'fin.png'" << std::endl;
	if (!fleche_droite.loadFromFile(("resourcespack/" + resourcespack + "/texture/fleche-droite.png").c_str())) if (!fleche_droite.loadFromFile("resourcespack/default/texture/fleche-droite.png")) std::cout << "erreur de chargement d'image 'fleche-droite.png'" << std::endl;
	if (!fleche_gauche.loadFromFile(("resourcespack/" + resourcespack + "/texture/fleche-gauche.png").c_str())) if (!fleche_gauche.loadFromFile("resourcespack/default/texture/fleche-gauche.png")) std::cout << "erreur de chargement d'image 'fleche-gauche.png'" << std::endl;
	if (!help_texture.loadFromFile(("resourcespack/" + resourcespack + "/bouton.png").c_str())) if (!coeur_texture.loadFromFile("resourcespack/default/bouton.png")) std::cout << "erreur d'image chargement 'bouton.png'" << std::endl;
#pragma endregion chargement des texture des block

	reset_vetbox(true);

#pragma region elements
	if (!player.loadFromFile(("resourcespack/"+resourcespack+"/player.png").c_str())) if (!player.loadFromFile("resourcespack/default/player.png")) std::cout << "erreur chargement d'image 'player.png'" << std::endl;

	player.setSmooth(true);
	sprite_player.setTexture(player);

	gestion_anim();

	coeur.setTexture(&coeur_texture);
	demi_coeur.setTexture(&demi_coeur_texture);

	sf::SoundBuffer buffer_portal;
	if (!buffer_portal.loadFromFile(("resourcespack/" + resourcespack + "/sound/portal.ogg").c_str()))
		if (!buffer_portal.loadFromFile("resourcespack/default/sound/portal.ogg")) std::cout << "erreur de chargement de son 'portal.ogg'" << std::endl;

	sound_portal.setBuffer(buffer_portal);

	sf::SoundBuffer buffer_damage;
	if (!buffer_damage.loadFromFile(("resourcespack/" + resourcespack + "/sound/hurt.ogg").c_str()))
		if (!buffer_damage.loadFromFile("resourcespack/default/sound/hurt.ogg")) std::cout << "erreur de chargement de son 'hurt.ogg'" << std::endl;

	sound_damage.setBuffer(buffer_damage);

	sf::SoundBuffer buffer_marche;
	if (!buffer_marche.loadFromFile(("resourcespack/" + resourcespack + "/sound/stone2.ogg").c_str()))
		if (!buffer_marche.loadFromFile("resourcespack/default/sound/stone2.ogg")) std::cout << "erreur de chargement de son 'stone2.ogg'" << std::endl;

	sound_marche.setBuffer(buffer_marche);

	if (!font.loadFromFile(("resourcespack/" + resourcespack + "/police/"+font_path).c_str())) if (!font.loadFromFile("resourcespack/default/police/police.ttf")) std::cout << "erreur de chargement de police de charactère 'police.ttf'" << std::endl;

	record_text.setFont(font);
	record_text.setFillColor(sf::Color::Red);
	record_text.setStyle(sf::Text::Bold);
	record_text.setString(sf::String("record : " + std::to_string(record)));
	record_text.setPosition(sf::Vector2f(0,50));

	btn1.setSize(sf::Vector2f(50, 50));
	btn1.setPosition(sf::Vector2f(50, 50));
	btn1.setTexture(&fleche_gauche);

	btn2.setSize(sf::Vector2f(50, 50));
	btn2.setPosition(sf::Vector2f(150, 50));
	btn2.setTexture(&fleche_droite);

	number.setPosition(sf::Vector2f(110, 55));
	number.setString(sf::String(std::to_string(level)));
	number.setFont(font);
	number.setFillColor(sf::Color(107, 87, 70, 255));

	help_rect.setSize(sf::Vector2f(800, 360));
	help_rect.setTexture(&help_texture);

#pragma endregion

	while (app.isOpen())
	{
		sf::Event event;
		while (app.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				std::ofstream save(("resourcespack/" + resourcespack + "/save/save.txt").c_str());
				if (save.is_open())
				{
					save << record;
				}
				save.close();

				std::cout << "fermeture la fenetre" << std::endl;
				app.close();
				break;
			}
			if (event.type == sf::Event::KeyPressed) mouvement = true;
			else mouvement = false;

		}

		if (level > record) { record = level; record_text.setString(sf::String("record : " + std::to_string(record)));}

		sf::Vector2f position(screenW / 2, screenH / 2);
		position.x = sprite_player.getPosition().x + taille / 2 + (screenW / 2);
		position.y = sprite_player.getPosition().y + taille / 2 - (screenH / 2);
		record_text.setPosition(sf::Vector2f(position.x - 220, position.y + 10));
		position.x = sprite_player.getPosition().x + taille / 2;
		position.y = sprite_player.getPosition().y + taille / 2 + (screenH / 2);
		number.setPosition(sf::Vector2f(position.x - 90, position.y - 45));
		btn2.setPosition(sf::Vector2f(position.x - 50, position.y - 50));
		btn1.setPosition(sf::Vector2f(position.x - 150, position.y - 50));

		gestion_health();

		preview.x = px;
		preview.y = py;

		collision(false);

		gestion_clavier();

		collision(true);

		view_anim(event);

		animation++;
		gestion_anim();

		sprite_player.setPosition(px, py);

		app.clear();

		latence(false);
		button();
		number.setString(sf::String(std::to_string(level)));
		
		std::vector<sf::RectangleShape> vie = get_health(health);

		for (int i = 0; i < vecbox.size(); i++) app.draw(vecbox[i]);
		for (int i = 0; i < vie.size(); i++) app.draw(vie[i]);

		app.draw(sprite_player);

		app.draw(record_text);

		app.draw(btn1);
		app.draw(number);
		app.draw(btn2);

		help_function();
		if (help) app.draw(help_rect);

		app.display();

	}

}
void view_anim(sf::Event event)
{
	if (event.type == sf::Event::Resized)
	{
		screenW = event.size.width;
		screenH = event.size.height;
	}

	view.reset(sf::FloatRect(0, 0, screenW, screenH));
	sf::Vector2f position(screenW / 2, screenH / 2);
	position.x = sprite_player.getPosition().x + taille / 2 - (screenW / 2);
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
bool tp = false;
int tp_int = 0;
#pragma endregion Variable pour collision et clavier
void gestion_clavier()
{
	#pragma region has_saut

		if (py_avant == py) is_saut++; else is_saut = 0;
		py_avant = py;
		if (is_saut == 5) { has_saut = true; is_saut = 0; }

	#pragma endregion verification du saut

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		anim.y = Right;
		px += speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Q) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		anim.y = Left;
		px -= speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		if (latence_int == 0)
		{
			latence(true);
			ChargeLevels(level);
			ChargePortal(level);
			reset_vetbox(true);
			health = 6;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	{
		if (latence_int == 0) { help = !help; latence(true); }
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
	{
		fullscreen = !fullscreen;
		if (fullscreen) {
			app.setSize(sf::Vector2u(sf::VideoMode::getFullscreenModes()[0].width, sf::VideoMode::getFullscreenModes()[0].height));
			app.setPosition(sf::Vector2i(0, 0));
			screenW = sf::VideoMode::getFullscreenModes()[0].width;
			screenH = sf::VideoMode::getFullscreenModes()[0].height;
			app.setMouseCursorVisible(true);
			std::cout << speed << std::endl;
		}
		else if (!fullscreen) {
			app.setSize(sf::Vector2u( 800, 600));
			app.setMouseCursorVisible(true);
			screenW = 800; screenH = 600;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) shift = true;
	else shift = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
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
	for (int y = 0; y < heightmap; y++)
	{
		for (int x = 0; x < withtmap; x++)
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
				tapmap[y][x] = 0;
				if (tapmap[y-1][x] == 4){ tapmap[y-1][x] = 0;}
				reset_vetbox(false);
				sound_marche.play();
			}

			if (tapmap[y][x] == 3 && px + 38 >= left && px <= right && py + 48 >= top && py <= bottom)
			{
				//portal

				//std::cout << "portal :  " << tp << ", " << tp_int << std::endl;
				if (!tp &&collision)
				{
					std::cout << px << " " << py << std::endl;
					tp_int = 0;
					px = getPortalTp(y, x).x;
					py = getPortalTp(y, x).y;

					sound_portal.play();
				}

				if(collision) tp = true;

			}
			else {
				if (collision) {
					tp_int++;
					if (tp_int == 12000)
					{
						tp = false;
						tp_int = 0;
					}
				}
			}
			if (tapmap[y][x] == 5 && px + 38 >= left && px <= right && py + 48 >= top && py <= bottom)
			{
				//mechant

				if (!mechant_colision)
				{
					health = health - 1;
					douleur = 0;
					sound_damage.play();
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
			if (tapmap[y][x] == 10 && px + 38 >= left && px <= right && py + 48 >= top && py <= bottom)
			{
				//block_casse
				health = 6;
			}
			if (tapmap[y][x] == 9 && px + 38 >= left && px <= right && py + 48 >= top && py <= bottom)
			{
				level++;
				charge();
				reset_vetbox(true);
				record_text.setString(sf::String("record : " + std::to_string(record)));
			}

			top = y * offsetY + 32;
			bottom = top + offsetY - 32;
			left = x * offsetX;
			right = left + offsetX;

			if (tapmap[y][x] == 6 && px + 38 >= left && px <= right && py + 48 >= top && py <= bottom)
			{
				health = 6;
				charge();
				reset_vetbox(true);
				sound_damage.play();
					
				record_text.setString(sf::String("record : " + std::to_string(record)));
				
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
	for (int y = 0; y < heightmap; y++)
	{
		for (int x = 0; x < withtmap; x++)
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
				debut.setPosition(sf::Vector2f(x * offsetX - offsetX * 4 / 2 + 50, y * offsetY - offsetY * 3 + 10));
				if (position_reset)
				{
					px = debut.getPosition().x + offsetX * 4 / 2;
					py = debut.getPosition().y + offsetY * 3 + 5;
				}
				vecbox.push_back(debut);
			}
			if (tapmap[y][x] == 9) {
				//fin
				sf::RectangleShape fin(sf::Vector2f(offsetX, offsetY));
				//piege.setFillColor(sf::Color::Magenta);
				fin.setTexture(&fin_texture);
				fin.setPosition(sf::Vector2f(x * offsetX, y * offsetY + 10));
				vecbox.push_back(fin);
			}
			if (tapmap[y][x] == 10) {
				//block heal
				sf::RectangleShape block_heal(sf::Vector2f(offsetX, offsetY));
				//piege.setFillColor(sf::Color::Magenta);
				block_heal.setTexture(&coeur_texture);
				block_heal.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(block_heal);
			}
		}
	}
}
void gestion_health() {
	if (health <= 0)
	{
		charge();
		reset_vetbox(true);
		record_text.setString(sf::String("record : " + std::to_string(record)));
		health = 6;
	}
	if (py > 1200)
	{
		charge();
		reset_vetbox(true);
		record_text.setString(sf::String("record : " + std::to_string(record)));
		health = 6;
	}
}
void config()
{
	std::ifstream ifs(("resourcespack/"+resourcespack+"/Config/window.ini").c_str());

	if (ifs.is_open())
	{
		std::getline(ifs, title);
		ifs >> screenW >> screenH;
		ifs >> resolution;
		ifs >> fullscreen;
		ifs >> speed;
		ifs >> health;
		ifs >> resourcespack;
		ifs >> level;
		ifs >> font_path;
	}
	ifs.close();

	int save_record = 0;

	std::ifstream save(("resourcespack/" + resourcespack + "/save/save.txt").c_str());
	if (save.is_open())
	{
		save >> save_record;
	}
	save.close();

	if (save_record == 0) { help = true; save_record++; }

	save_record = record;
	if (level == 0) level = record;
}
void charge() {
	ChargeLevels(level);
	ChargePortal(level);
	if (level == 0)
	{
		level++;
		ChargeLevels(level);
		ChargePortal(level);
	}
	
}
void button() {

	sf::Vector2f position(screenW / 2, screenH / 2);
	position.x = sprite_player.getPosition().x + taille / 2 - (screenW / 2);
	position.y = sprite_player.getPosition().y + taille / 2 - (screenH / 2);

	int top = btn1.getPosition().y - position.y;
	int bottom = top + 50;
	int left = btn1.getPosition().x - position.x;
	int right = left + 50;

	//std::cout << sf::Mouse::getPosition(app).x << ", " << sf::Mouse::getPosition(app).y << std::endl;

	if (sf::Mouse::getPosition(app).x >= left && sf::Mouse::getPosition(app).x <= right && sf::Mouse::getPosition(app).y >= top && sf::Mouse::getPosition(app).y <= bottom)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (latence_int == 0)
			{
				level--;
				if (level < 1) level = 1;

				latence(true);
				ChargeLevels(level);
				ChargePortal(level);
				reset_vetbox(true);
			}
		}
	}


	top = btn2.getPosition().y - position.y;
	bottom = top + 50;
	left = btn2.getPosition().x - position.x;
	right = left + 50;

	if (sf::Mouse::getPosition(app).x >= left && sf::Mouse::getPosition(app).x <= right && sf::Mouse::getPosition(app).y >= top && sf::Mouse::getPosition(app).y <= bottom)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (latence_int == 0)
			{
				level++;
				if (level > record) level--;
				latence(true);
				ChargeLevels(level);
				ChargePortal(level);
				reset_vetbox(true);
			}
		}
	}
}
void latence(bool latence) {
	if (latence) latence_int++;
	if (latence_int != 0)
	{
		latence_int++;
		if (latence_int == 10)
		{
			latence_int = 0;
		}
	}
}
bool help_function()
{
	sf::Vector2f position(screenW / 2, screenH / 2);
	position.x = sprite_player.getPosition().x + taille / 2 - (screenW / 2);
	position.y = sprite_player.getPosition().y + taille / 2 - (screenH / 2);

	help_rect.setPosition(position.x, position.y);
	help_rect.setSize(sf::Vector2f(screenW,screenH));

	return true;
}