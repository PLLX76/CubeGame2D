#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <Windows.h>

#include <fstream>

#include "portal.h"
#include "Levels.h"
#include "item.h"

#include <string>
#include <iostream>
#include <cstdlib> 
#include <vector>
#include <ctime>

#pragma region Variable
sf::RenderWindow app;

sf::Image icon;

sf::Texture player;
sf::Sprite sprite_player;

sf::Sound sound_portal;
sf::Sound sound_damage;
sf::Sound sound_marche;
sf::Sound sound_levelup;
sf::Sound sound_heal;
sf::Sound sound_tnt;

sf::Font font;
std::string font_path = "police.ttf";

int speed = 2;
int health = 6;

int taille = 64;

int record = 1;
sf::Text record_text;
sf::Text time_in_level;

int offsetX = taille, offsetY = taille;

int px = 0, py = 0;

enum Dir { Down, Left, Right, Up };
sf::Vector2i anim(1, Down);
//int animation = 18 - speed - 1;

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
sf::RectangleShape btn1_no;
sf::RectangleShape btn2_no;
sf::Text number;

sf::RectangleShape help_rect;
bool help = false;
bool mouvement = false;

sf::Vector2f position_coeur(screenW / 2, screenH / 2);

bool speed_item_pressed = false;

int use_potion_int = 0;

int reload = 10;
#pragma endregion

#pragma region Clock

sf::Clock time_speed;
sf::Clock time_mechant_damage;
sf::Clock time_anim;
sf::Clock time_fps;
sf::Clock time_fullscrenn;
sf::Clock time_portal;
sf::Clock time_item_change;
sf::Clock time_manette;
sf::Clock time_heal_sound;
sf::Clock time_Reload_And_HelpMenu;
sf::Clock time_bouton_level;
sf::Clock time_tnt;

sf::Clock time_in_level_second;
int time_in_level_minute = 0;
#pragma endregion time

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
fin_texture,
TNT_texture;
sf::Texture fleche_droite,
fleche_gauche,
fleche_droite_no,
fleche_gauche_no;
sf::Texture help_texture;
sf::Texture Rien;
#pragma endregion variable textures des blocks
	
#pragma region item
int ItemSelectedPlaceInList = 0;

sf::Vector2f position_item(screenW / 2, screenH / 2);

bool have_item = false;

sf::RectangleShape item;
sf::Text item_text;

sf::RectangleShape item_sword; sf::RectangleShape item_sword_inverse;
sf::Texture item_sword_texture;
sf::Texture item_sword_texture_inverse;
bool SwordSelected = false;

sf::Texture item_heal_texture;
sf::Texture item_up_texture;
sf::Texture item_speed_texture;
#pragma endregion

#pragma region Fonction

void view_anim();
void gestion_anim();
void gestion_clavier();
void collision(bool collision);
std::vector<sf::RectangleShape> get_health(int health);
void reset_vetbox(bool position_reset);
void gestion_health();
void config();
void charge();
void button();
void timer();
bool help_function();
void gestion_mannette();
void draw_item_selecte(int change_place);
void draw_item_selecte();
void fullscrenn(bool ignore);
void couleur();

#pragma endregion fonction declaration

#pragma region Variable collision
int mechant_colision_int = 0;
bool touche_le_sol_block = false;
bool touche_le_sol_block_casse = false;
bool touche_le_sol_piege = false;

#pragma endregion

#pragma region color
struct Color
{
	int r;
	int g;
	int b;
};
sf::Color color_right_text;
sf::Color color_level_number;
#pragma endregion

//site color https://htmlcolorcodes.com/fr/

int main()
{
	config();
	get_resource_level_existed();
	charge();
	couleur();

	fullscrenn(true);
	
	app.setFramerateLimit(60);
	if (!icon.loadFromFile(("resourcespack/" + resourcespack + "/mechant.png").c_str())) if (!icon.loadFromFile("resourcespack/default/mechant.png")) std::cout << "error icon ligne 126" << std::endl;
	app.setIcon(500, 500, icon.getPixelsPtr());

#pragma region chargement image
	if (!block_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/block.png").c_str())) if (!block_texture.loadFromFile("resourcespack/default/texture/block.png")) std::cout << "erreur d'image chargement 'block.png'" << std::endl;
	if (!block_casse_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/block_casse.jpg").c_str())) if (!block_casse_texture.loadFromFile("resourcespack/default/texture/block_casse.jpg")) std::cout << "erreur d'image chargement 'block_casse.jpg'" << std::endl;
	if (!TNT_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/TNT.jpg").c_str())) if (!TNT_texture.loadFromFile("resourcespack/default/texture/TNT.jpg")) std::cout << "erreur d'image chargement 'TNT.jpg'" << std::endl;
	if (!champigon_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/champignon.png").c_str())) if (!champigon_texture.loadFromFile("resourcespack/default/texture/champignon.png")) std::cout << "erreur d'image chargement 'champignon.png'" << std::endl;
	if (!mechant_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/mechant.png").c_str())) if (!mechant_texture.loadFromFile("resourcespack/default/texture/mechant.png")) std::cout << "erreur d'image chargement 'mechant.png'" << std::endl;
	if (!piege_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/piege.png").c_str())) if (!piege_texture.loadFromFile("resourcespack/default/texture/piege.png")) std::cout << "erreur d'image chargement 'piege.png'" << std::endl;
	if (!echelle_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/ladders.png").c_str())) if (!echelle_texture.loadFromFile("resourcespack/default/texture/ladders.png")) std::cout << "erreur d'image chargement 'ladders.png'" << std::endl;
	if (!depart_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/champi.png").c_str())) if (!depart_texture.loadFromFile("resourcespack/default/texture/champi.png")) std::cout << "erreur d'image chargement 'champi.png'" << std::endl;
	if (!portal_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/portal.png").c_str())) if (!portal_texture.loadFromFile("resourcespack/default/texture/portal.png")) std::cout << "erreur d'image chargement 'portal.png'" << std::endl;
	if (!demi_coeur_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/coueur_demi.png").c_str())) if (!demi_coeur_texture.loadFromFile("resourcespack/default/texture/coueur_demi.png")) std::cout << "erreur d'image chargement 'coueur_demi.png'" << std::endl;
	if (!coeur_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/coueur_plein.png").c_str())) if (!coeur_texture.loadFromFile("resourcespack/default/texture/coueur_plein.png")) std::cout << "erreur d'image chargement 'coueur_plein.png'" << std::endl;
	if (!fin_texture.loadFromFile(("resourcespack/" + resourcespack + "/texture/fin.png").c_str())) if (!fin_texture.loadFromFile("resourcespack/default/texture/fin.png")) std::cout << "erreur chargement d'image 'fin.png'" << std::endl;
	if (!fleche_droite.loadFromFile(("resourcespack/" + resourcespack + "/texture/fleche-droite.png").c_str())) if (!fleche_droite.loadFromFile("resourcespack/default/texture/fleche-droite.png")) std::cout << "erreur de chargement d'image 'fleche-droite.png'" << std::endl;
	if (!fleche_gauche.loadFromFile(("resourcespack/" + resourcespack + "/texture/fleche-gauche.png").c_str())) if (!fleche_gauche.loadFromFile("resourcespack/default/texture/fleche-gauche.png")) std::cout << "erreur de chargement d'image 'fleche-gauche.png'" << std::endl;
	if (!fleche_droite_no.loadFromFile(("resourcespack/" + resourcespack + "/texture/fleche-droite-no.png").c_str())) if (!fleche_droite_no.loadFromFile("resourcespack/default/texture/fleche-droite-no.png")) std::cout << "erreur de chargement d'image 'fleche-droite-no.png'" << std::endl;
	if (!fleche_gauche_no.loadFromFile(("resourcespack/" + resourcespack + "/texture/fleche-gauche-no.png").c_str())) if (!fleche_gauche_no.loadFromFile("resourcespack/default/texture/fleche-gauche-no.png")) std::cout << "erreur de chargement d'image 'fleche-gauche-no.png'" << std::endl;
	if (!help_texture.loadFromFile(("resourcespack/" + resourcespack + "/bouton.png").c_str())) if (!help_texture.loadFromFile("resourcespack/default/bouton.png")) std::cout << "erreur d'image chargement 'bouton.png'" << std::endl;
#pragma endregion chargement des texture des block

#pragma region chargement item
	if (!item_heal_texture.loadFromFile(("resourcespack/" + resourcespack + "/item/item_potion.png").c_str())) if (!item_heal_texture.loadFromFile("resourcespack/default/item/item_potion.png")) std::cout << "erreur d'image chargement 'item_potion.png'" << std::endl;
	if (!item_sword_texture.loadFromFile(("resourcespack/" + resourcespack + "/item/sword.png").c_str())) if (!item_sword_texture.loadFromFile("resourcespack/default/item/sword.png")) std::cout << "erreur d'image chargement 'sword_inverse.png'" << std::endl;
	if (!item_sword_texture_inverse.loadFromFile(("resourcespack/" + resourcespack + "/item/sword_inverse.png").c_str())) if (!item_sword_texture.loadFromFile("resourcespack/default/item/sword_inverse.png")) std::cout << "erreur d'image chargement 'sword.png'" << std::endl;
	if (!item_up_texture.loadFromFile(("resourcespack/" + resourcespack + "/item/Up.png").c_str())) if (!item_up_texture.loadFromFile("resourcespack/default/item/Up.png")) std::cout << "erreur d'image chargement 'Up.png'" << std::endl;
	if (!item_speed_texture.loadFromFile(("resourcespack/" + resourcespack + "/item/speed.png").c_str())) if (!item_speed_texture.loadFromFile("resourcespack/default/item/speed.png")) std::cout << "erreur d'image chargement 'speed.png'" << std::endl;

	item_sword.setTexture(&item_sword_texture);
	item_sword.setSize({ 40, 40 });
	item_sword.getInverseTransform();
#pragma endregion chargement des items


	reset_vetbox(true);

#pragma region elements

	if (!player.loadFromFile(("resourcespack/" + resourcespack + "/player.png").c_str())) if (!player.loadFromFile("resourcespack/default/player.png")) std::cout << "erreur chargement d'image 'player.png'" << std::endl;

	player.setSmooth(true);
	sprite_player.setTexture(player);

	anim.x++;
	if (anim.x * 64 + 10 >= player.getSize().x - 10) anim.x = 0;
	sprite_player.setTextureRect(sf::IntRect(anim.x, anim.y * 48, 48, 48));


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

	sf::SoundBuffer buffer_levelup;
	if (!buffer_levelup.loadFromFile(("resourcespack/" + resourcespack + "/sound/levelup.ogg").c_str()))
		if (!buffer_levelup.loadFromFile("resourcespack/default/sound/levelup.ogg")) std::cout << "erreur de chargement de son 'levelup.ogg'" << std::endl;
	sound_levelup.setBuffer(buffer_levelup);
	sound_levelup.setVolume(50.0f);

	sf::SoundBuffer buffer_heal;
	if (!buffer_heal.loadFromFile(("resourcespack/" + resourcespack + "/sound/heal.ogg").c_str()))
		if (!buffer_heal.loadFromFile("resourcespack/default/sound/heal.ogg")) std::cout << "erreur de chargement de son 'stone2.ogg'" << std::endl;

	sound_heal.setBuffer(buffer_heal);

	sf::SoundBuffer buffer_tnt;
	if (!buffer_tnt.loadFromFile(("resourcespack/" + resourcespack + "/sound/tnt.ogg").c_str()))
		if (!buffer_tnt.loadFromFile("resourcespack/default/sound/tnt.ogg")) std::cout << "erreur de chargement de son 'tnt.ogg'" << std::endl;

	sound_tnt.setBuffer(buffer_tnt);

	if (!font.loadFromFile(("resourcespack/" + resourcespack + "/police/" + font_path).c_str())) if (!font.loadFromFile("resourcespack/default/police/police.ttf")) std::cout << "erreur de chargement de police de charact�re 'police.ttf'" << std::endl;

	record_text.setFont(font);
	record_text.setFillColor(color_right_text);
	record_text.setStyle(sf::Text::Bold);
	record_text.setString(sf::String("record : " + std::to_string(record)));
	record_text.setPosition(sf::Vector2f(0, 50));

	time_in_level.setFont(font);
	time_in_level.setFillColor(color_right_text);
	time_in_level.setStyle(sf::Text::Bold);
	time_in_level.setString(sf::String("time : " + std::to_string(time_in_level_minute)+" : " + std::to_string(time_in_level_second.getElapsedTime().asSeconds())));
	time_in_level.setPosition(sf::Vector2f(0, 100));

	btn1.setSize(sf::Vector2f(50, 50));
	btn1.setPosition(sf::Vector2f(50, 50));
	btn1.setTexture(&fleche_gauche);

	btn2.setSize(sf::Vector2f(50, 50));
	btn2.setPosition(sf::Vector2f(150, 50));
	btn2.setTexture(&fleche_droite);

	btn1_no.setSize(sf::Vector2f(50, 50));
	btn1_no.setPosition(sf::Vector2f(50, 50));
	btn1_no.setTexture(&fleche_gauche_no);

	btn2_no.setSize(sf::Vector2f(50, 50));
	btn2_no.setPosition(sf::Vector2f(150, 50));
	btn2_no.setTexture(&fleche_droite_no);

	number.setPosition(sf::Vector2f(110, 55));
	number.setString(sf::String(std::to_string(level)));
	number.setFont(font);
	number.setFillColor(color_level_number);

	help_rect.setSize(sf::Vector2f(800, 360));
	help_rect.setTexture(&help_texture);

#pragma endregion

	while (app.isOpen())
	{
		sf::Event event;
		while (app.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				std::ofstream save("resourcespack/default/save/save.txt");
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
			if (event.type == sf::Event::MouseWheelScrolled)
			{
				if (time_item_change.getElapsedTime().asMilliseconds() > 50)
				{
					draw_item_selecte(event.mouseWheelScroll.delta);
					time_item_change.restart();
				}
			}
		}
		if (time_fps.getElapsedTime().asMilliseconds() > reload)
		{

			if (level > record) { record = level; record_text.setString(sf::String("record : " + std::to_string(record))); }

			screenH = app.getSize().y;
			screenW = app.getSize().x;

#pragma region set-position
			sf::Vector2f position(screenW / 2, screenH / 2);
			position.x = sprite_player.getPosition().x + taille / 2 + (screenW / 2);
			position.y = sprite_player.getPosition().y + taille / 2 - (screenH / 2);
			record_text.setPosition(sf::Vector2f(position.x - 220, position.y + 10));
			time_in_level.setPosition(sf::Vector2f(position.x - 220, position.y + 50));

			position.x = sprite_player.getPosition().x + taille / 2;
			position.y = sprite_player.getPosition().y + taille / 2 + (screenH / 2);
			number.setPosition(sf::Vector2f(position.x - 90, position.y - 45));
			btn2.setPosition(sf::Vector2f(position.x - 50, position.y - 50));
			btn1.setPosition(sf::Vector2f(position.x - 150, position.y - 50));
			btn2_no.setPosition(sf::Vector2f(position.x - 50, position.y - 50));
			btn1_no.setPosition(sf::Vector2f(position.x - 150, position.y - 50));

			position_item.x = sprite_player.getPosition().x + taille / 2 - screenW / 2;
			position_item.y = sprite_player.getPosition().y + taille / 2 + screenH / 2;

			position_coeur.x = sprite_player.getPosition().x + taille / 2 - (screenW / 2);
			position_coeur.y = sprite_player.getPosition().y + taille / 2 - (screenH / 2);
#pragma endregion

			gestion_health();

			preview.x = px;
			preview.y = py;

			collision(false);

			gestion_clavier();
			button();
			gestion_mannette();

			collision(true);

			if (speed_item_pressed) timer();

			view_anim();

			gestion_anim();

			sprite_player.setPosition(px, py);

			help_function();

			app.clear();

			number.setString(sf::String(std::to_string(level)));

			if (time_in_level_second.getElapsedTime().asSeconds() >= 60)
			{
				time_in_level_second.restart();
				time_in_level_minute++;
			}
			int int_of_time_in_level_second = trunc(time_in_level_second.getElapsedTime().asSeconds());
			time_in_level.setString(sf::String("time: " + std::to_string(time_in_level_minute) + "m " + std::to_string(int_of_time_in_level_second)+"s"));

			std::vector<sf::RectangleShape> vie = get_health(health);
			for (int i = 0; i < vecbox.size(); i++) app.draw(vecbox[i]);
			for (int i = 0; i < vie.size(); i++) app.draw(vie[i]);

			app.draw(sprite_player);

			draw_item_selecte();

			if (have_item)
			{
				app.draw(item);
				app.draw(item_text);
			}
			app.draw(item_sword);

			app.draw(record_text);
			app.draw(time_in_level);

			if (record != 1 && record != 0)
			{
				if (level != 1) app.draw(btn1);
				else app.draw(btn1_no);
				app.draw(number);
				if (level != record) app.draw(btn2);
				else app.draw(btn2_no);
			}
			if (help) app.draw(help_rect);

			app.display();

			time_fps.restart();
		}
	}
}
#pragma region Variable
bool saut = false;
bool jump_item = false;
bool shift = false;
int fois = 0;
int jump_item_fois = 0;
bool echelle_monter = false;
int is_saut = 0;
int py_avant = 0;
bool has_saut = false;
int douleur = 0;
bool tp = false;
int tp_int = 0;
#pragma endregion Variable pour collision et clavier
void view_anim()
{
	view.reset(sf::FloatRect(0, 0, screenW, screenH));
	sf::Vector2f position(screenW / 2, screenH / 2);
	position.x = sprite_player.getPosition().x + taille / 2 - (screenW / 2);
	position.y = sprite_player.getPosition().y + taille / 2 - (screenH / 2);
	view.reset(sf::FloatRect(position.x, position.y, screenW, screenH));
	app.setView(view);
}
void gestion_anim() {
	if (SwordSelected)
	{
		if (anim.y == Right) { item_sword.setPosition({ sprite_player.getPosition().x + 27, sprite_player.getPosition().y + 5 }); item_sword.setTexture(&item_sword_texture); }
		else if (anim.y == Left) { item_sword.setPosition({ sprite_player.getPosition().x - 27, sprite_player.getPosition().y + 5 }); item_sword.setTexture(&item_sword_texture_inverse); }
		else item_sword.setPosition({ -1000,-1000 });
	}
	else item_sword.setPosition({ -1000,-1000 });
	
	if (time_anim.getElapsedTime().asMilliseconds() > 300)
	{
		anim.x++;
		time_anim.restart();
	}
	if (anim.y != Down && !saut && !jump_item)
	{
		if (anim.x * 64 + 10 >= player.getSize().x - 10) anim.x = 0;
		sprite_player.setTextureRect(sf::IntRect(anim.x * 48, anim.y * 48, 48, 48));
	}
}
void gestion_clavier()
{
#pragma region has_saut

	if (py_avant == py) is_saut++; else is_saut = 0;
	py_avant = py;
	if (is_saut == 5) { has_saut = true; is_saut = 0; }

#pragma endregion verification du saut

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
	{
		if (time_item_change.getElapsedTime().asMilliseconds() > 50)
		{
			draw_item_selecte(1);
			time_item_change.restart();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
	{
		if (time_item_change.getElapsedTime().asMilliseconds() > 50)
		{
			draw_item_selecte(-1);
			time_item_change.restart();
		}
	}

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
		if (time_Reload_And_HelpMenu.getElapsedTime().asMilliseconds() > 50)
		{
			time_Reload_And_HelpMenu.restart();
			ChargeLevels(level);
			ChargePortal(level);
			reset_vetbox(true);
			health = 6;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
	{
		if (time_Reload_And_HelpMenu.getElapsedTime().asMilliseconds() > 50) { help = !help; time_Reload_And_HelpMenu.restart();}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11)) fullscrenn(false);

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

	}
	else echelle_monter = false;
	if (saut)
	{
		fois++;

		py -= 3;
		if (fois == 28)
		{
			saut = false;
			fois = 0;
		}
	}
}
std::vector<sf::RectangleShape> get_health(int health) {
	std::vector<sf::RectangleShape> vie;

	coeur.setSize(sf::Vector2f(50, 50));
	demi_coeur.setSize(sf::Vector2f(50, 50));

	switch (health)
	{
	case 6:
		coeur.setPosition(sf::Vector2f(position_coeur.x + 10, position_coeur.y + 10));
		vie.push_back(coeur);
		coeur.setPosition(sf::Vector2f(position_coeur.x + 10 + 50, position_coeur.y + 10));
		vie.push_back(coeur);
		coeur.setPosition(sf::Vector2f(position_coeur.x + 10 + 50 * 2, position_coeur.y + 10));
		vie.push_back(coeur);
		break;
	case 5:
		coeur.setPosition(sf::Vector2f(position_coeur.x + 10, position_coeur.y + 10));
		vie.push_back(coeur);
		coeur.setPosition(sf::Vector2f(position_coeur.x + 10 + 50, position_coeur.y + 10));
		vie.push_back(coeur);
		demi_coeur.setPosition(sf::Vector2f(position_coeur.x + 10 + 50 * 2, position_coeur.y + 10));
		vie.push_back(demi_coeur);
		break;
	case 4:
		coeur.setPosition(sf::Vector2f(position_coeur.x + 10, position_coeur.y + 10));
		vie.push_back(coeur);
		coeur.setPosition(sf::Vector2f(position_coeur.x + 10 + 50, position_coeur.y + 10));
		vie.push_back(coeur);
		break;
	case 3:
		coeur.setPosition(sf::Vector2f(position_coeur.x + 10, position_coeur.y + 10));
		vie.push_back(coeur);
		demi_coeur.setPosition(sf::Vector2f(position_coeur.x + 10 + 50, position_coeur.y + 10));
		vie.push_back(demi_coeur);
		break;
	case 2:
		coeur.setPosition(sf::Vector2f(position_coeur.x + 10, position_coeur.y + 10));
		vie.push_back(coeur);
		break;
	case 1:
		demi_coeur.setPosition(sf::Vector2f(position_coeur.x + 10, position_coeur.y + 10));
		vie.push_back(demi_coeur);
		break;

	default:
		break;
	}
	return vie;
}
void collision(bool collision)
{
	if (!collision && !space && !saut && !jump_item) { py += 3; anim.y = Down; }
	for (int y = 0; y < heightmap; y++)
	{
		for (int x = 0; x < withtmap; x++)
		{

#pragma region collision item

			int top = y * offsetY;
			int bottom = top + offsetY;
			int left = x * offsetX;
			int right = left + offsetX;

			//item_heal
			if (tapmap[y][x] == 50 && px + 38 >= left && px <= right && py + 48 >= top && py <= bottom) add_item_id(1);
			if (tapmap[y][x] == 51 && px + 38 >= left && px <= right && py + 48 >= top && py <= bottom) add_item_id(2);
			if (tapmap[y][x] == 52 && px + 38 >= left && px <= right && py + 48 >= top && py <= bottom) add_item_id(3);
			if (tapmap[y][x] == 53 && px + 38 >= left && px <= right && py + 48 >= top && py <= bottom) add_item_id(4);

			top = y * offsetY;
			bottom = top + offsetY;
			left = x * offsetX;
			right = left + offsetX;
			if (use_potion_int == 0&& SwordSelected)
			{
				if (tapmap[y][x] == 5 && item_sword.getPosition().x + 40 >= left && item_sword.getPosition().x <= right && item_sword.getPosition().y + 40 >= top && item_sword.getPosition().y <= bottom)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) || sf::Joystick::isButtonPressed(0, 2))
					{
						std::cout << remove_item_id(2) << std::endl;
						tapmap[y][x] = 0;
						reset_vetbox(false);
						use_potion_int = 20;
						SwordSelected = false;
					}
				}
			}

#pragma endregion

#pragma region collision block

			if (tapmap[y][x] == 1 && px + 38 >= left && px <= right && py + 48 >= top && py <= bottom)
			{
				//block
				if (heightmap > y + 2)
				{
					int yadd2 = y + 2;
					if (tapmap[yadd2][x] == 7 && py + 48 >= top && shift);
					else if (tapmap[yadd2][x] == 7 && py <= bottom && echelle_monter);
					else
					{
						px = preview.x;
						py = preview.y;

					}
				}
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
				if (0 < y - 1)
					if (tapmap[y - 1][x] == 4) { tapmap[y - 1][x] = 0; }
				reset_vetbox(false);
				sound_marche.play();
			}

			if (tapmap[y][x] == 3 && px + 38 >= left && px <= right && py + 48 >= top && py <= bottom)
			{
				//portal

				//std::cout << "portal :  " << tp << ", " << tp_int << std::endl;
				if (time_portal.getElapsedTime().asSeconds() >= 1 && collision)
				{
					std::cout << px << " " << py << std::endl;
					tp_int = 0;

					px = getPortalTp(y, x).x;
					py = getPortalTp(y, x).y;

					sound_portal.play();
					time_portal.restart();
				}

			}
			if (tapmap[y][x] == 5 && px + 38 >= left && px <= right && py + 48 >= top && py <= bottom)
			{
				//mechant

				if (time_mechant_damage.getElapsedTime().asMilliseconds() > 500)
				{
					health = health - 1;
					douleur = 0;
					sound_damage.play();
					time_mechant_damage.restart();
				}

			}
			if (tapmap[y][x] == 10 && px + 38 >= left && px <= right && py + 48 >= top && py <= bottom)
			{
				//heal
				health = 6;
				if (time_heal_sound.getElapsedTime().asSeconds() > 2)
				{
					time_heal_sound.restart();
					sound_heal.play();
				}
			}
			if (tapmap[y][x] == 11 && px + 38 >= left && px <= right && py + 48 >= top && py <= bottom)
			{
				if (time_tnt.getElapsedTime().asSeconds() >= 1)
				{
					time_tnt.restart();
				}
				else if (time_tnt.getElapsedTime().asMilliseconds() >= 900 && time_tnt.getElapsedTime().asMilliseconds() < 1000)
				{

					tapmap[y][x] = 0;
					if (0 < y - 1)
						tapmap[y - 1][x] = 0;
					if (heightmap > y + 1)
						tapmap[y + 1][x] = 0;
					if (0 < x - 1)
						tapmap[y][x - 1] = 0;
					if (withtmap > x + 1)
						tapmap[y][x + 1] = 0;
					if (0 < y - 1 && 0 < x - 1)
						tapmap[y - 1][x - 1] = 0;
					if (heightmap > y + 1 && withtmap > x + 1)
						tapmap[y + 1][x + 1] = 0;
					if (heightmap > y + 1 && 0 < x - 1)
						tapmap[y + 1][x - 1] = 0;
					if (0 < y - 1 && withtmap > x + 1)
						tapmap[y - 1][x + 1] = 0;

					reset_vetbox(false);
				}
				else
				{
					px = preview.x;
					py = preview.y;
				}
			}
			if (tapmap[y][x] == 9 && px + 38 >= left && px <= right && py + 48 >= top && py <= bottom)
			{
				//fin
				if (level == record) sound_levelup.play();
				level++;
				charge();
				record_text.setString(sf::String("record : " + std::to_string(record)));
				time_in_level_minute = 0;
				time_in_level_second.restart();
			}

			top = y * offsetY + 32;
			bottom = top + offsetY - 32;
			left = x * offsetX;
			right = left + offsetX;
			if (tapmap[y][x] == 6 && px + 38 >= left && px <= right && py + 48 >= top && py <= bottom)
			{
				if (py >= top) {
					px = preview.x;
					py = preview.y;
				}
				else
				{
					health = 6;
					charge();
					sound_damage.play();
					remove_all_item();
				}

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
#pragma endregion 

	}
}
void reset_vetbox(bool position_reset)
{
	vecbox.clear();
	int resize = 0;
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
				resize++;
			}
			if (tapmap[y][x] == 2) {
				//block_casse
				sf::RectangleShape block_casse(sf::Vector2f(offsetX, offsetY));
				//block_casse.setFillColor(sf::Color(117,10,10,255));
				block_casse.setTexture(&block_casse_texture);
				block_casse.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(block_casse);
				resize++;
			}
			if (tapmap[y][x] == 3) {
				//portal
				sf::RectangleShape portal(sf::Vector2f(offsetX, offsetY));
				//portal.setFillColor(sf::Color::Blue);
				portal.setTexture(&portal_texture);
				portal.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(portal);
				resize++;
			}
			if (tapmap[y][x] == 4) {
				//champignon
				sf::RectangleShape champignon(sf::Vector2f(offsetX, offsetY));
				//champignon.setFillColor(sf::Color::Green);
				champignon.setTexture(&champigon_texture);
				champignon.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(champignon);
				resize++;
			}
			if (tapmap[y][x] == 5) {
				//mechant
				sf::RectangleShape mechant(sf::Vector2f(offsetX, offsetY));
				//mechant.setFillColor(sf::Color::Yellow);
				mechant.setTexture(&mechant_texture);
				mechant.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(mechant);
				resize++;
			}
			if (tapmap[y][x] == 6) {
				//piege
				sf::RectangleShape piege(sf::Vector2f(offsetX, offsetY));
				//piege.setFillColor(sf::Color::Magenta);
				piege.setTexture(&piege_texture);
				piege.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(piege);
				resize++;
			}
			if (tapmap[y][x] == 7) {
				//echelle
				sf::RectangleShape echelle(sf::Vector2f(offsetX, offsetY * 3));
				//echelle.setFillColor(sf::Color::White);
				echelle.setTexture(&echelle_texture);
				echelle.setPosition(sf::Vector2f(x * offsetX, y * offsetY - offsetY * 2));
				vecbox.push_back(echelle);
				resize++;
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
				resize++;
			}
			if (tapmap[y][x] == 9) {
				//fin
				sf::RectangleShape fin(sf::Vector2f(offsetX, offsetY));
				//piege.setFillColor(sf::Color::Magenta);
				fin.setTexture(&fin_texture);
				fin.setPosition(sf::Vector2f(x * offsetX, y * offsetY + 10));
				vecbox.push_back(fin);
				resize++;
			}
			if (tapmap[y][x] == 10) {
				//block heal
				sf::RectangleShape block_heal(sf::Vector2f(offsetX, offsetY));
				//piege.setFillColor(sf::Color::Magenta);
				block_heal.setTexture(&coeur_texture);
				block_heal.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(block_heal);
				resize++;
			}
			if (tapmap[y][x] == 11) {
				//TNT
				sf::RectangleShape TNT(sf::Vector2f(offsetX, offsetY));
				//piege.setFillColor(sf::Color::Magenta);
				TNT.setTexture(&TNT_texture);
				TNT.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(TNT);
				resize++;
			}
			if (tapmap[y][x] == 50) {
				//heal
				sf::RectangleShape item_heal(sf::Vector2f(offsetX, offsetY));
				item_heal.setTexture(&item_heal_texture);
				item_heal.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(item_heal);
				resize++;
			}
			if (tapmap[y][x] == 51) {
				//sword
				sf::RectangleShape item_sword(sf::Vector2f(offsetX, offsetY));
				item_sword.setTexture(&item_sword_texture);
				item_sword.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(item_sword);
				resize++;
			}
			if (tapmap[y][x] == 52) {
				//up
				sf::RectangleShape item_up(sf::Vector2f(offsetX, offsetY));
				item_up.setTexture(&item_up_texture);
				item_up.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(item_up);
				resize++;
			}
			if (tapmap[y][x] == 53) {
				//speed
				sf::RectangleShape item_speed(sf::Vector2f(offsetX, offsetY));
				item_speed.setTexture(&item_speed_texture);
				item_speed.setPosition(sf::Vector2f(x * offsetX, y * offsetY));
				vecbox.push_back(item_speed);
				resize++;
			}
		}
	}
	vecbox.resize(resize);
}
void gestion_health() {
	if (health <= 0)
	{
		charge();
		reset_vetbox(true);
		record_text.setString(sf::String("record : " + std::to_string(record)));
		remove_all_item();
		health = 6;
	}
	if (py > heightmap * taille+100)
	{
		charge();
		reset_vetbox(true);
		record_text.setString(sf::String("record : " + std::to_string(record)));
		health = 6;
	}
}
void config()
{
	std::ifstream ifs(("resourcespack/" + resourcespack + "/Config/window.ini").c_str());


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

	std::ifstream save("resourcespack/default/save/save.txt");
	if (save.is_open())
	{
		save >> save_record;
	}
	save.close();

	if (save_record == 0) { help = true; save_record++; }

	record = save_record;
	if (level == 0) level = record;
}
void charge() {
	ChargeLevels(level);
	ChargePortal(level);
	reset_vetbox(true);
}
std::vector<int> inv = get_item_list();
void button() {
	bool use_potion = true;

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
			if (level != 0)
			{
				if (time_bouton_level.getElapsedTime().asMilliseconds() > 150)
				{

					level--;
					if (level < 1) level = 1;
					time_bouton_level.restart();
					charge();
					use_potion = false;
					use_potion_int = 10;
					time_in_level_minute = 0;
					time_in_level_second.restart();
				}
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
			if (level != record)
			{
				if (time_bouton_level.getElapsedTime().asMilliseconds() > 150)
				{
					level++;
					if (level > record) level--;
					time_bouton_level.restart();
					charge();
					use_potion = false;
					use_potion_int = 10;
					time_in_level_minute = 0;
					time_in_level_second.restart();
				}
			}
		}
	}
	if (use_potion && use_potion_int == 0)
	{
		inv = get_item_list();
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)||sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl) || sf::Joystick::isButtonPressed(0, 2))
		{
			if (inv.size() >= 1)
			{
				switch (inv[ItemSelectedPlaceInList])
				{
				case 1:
					ItemSelectedPlaceInList = 0;
					for (int i = 0; i < 2; i++)
					{
						if (health + 1 <= 6)
						{
							health += 1;
						}
					}
					remove_item_id(1);
					break;
				case 2:
					break;
				case 3:
					if (!jump_item)
					{
						jump_item = true;
					}
					remove_item_id(3);
					break;
				case 4:
					remove_item_id(4);
					speed += 1;
					speed_item_pressed = true;
					time_speed.restart();
					timer();
					break;
				default:
					break;
				}
			}
			use_potion_int = 20;
		}
		if (inv.size() >= 1)
		{
			if (inv[ItemSelectedPlaceInList] == 2) SwordSelected = true;
			else SwordSelected = false;
		}
		else SwordSelected = false;
		
	}	
	else if (use_potion_int != 0) use_potion_int--;

	if (jump_item)
	{
		jump_item_fois++;

		py -= 5;

		if (jump_item_fois == 50)
		{
			jump_item = false;
			jump_item_fois = 0;
		}
	}
}
void timer()
{
	if (speed_item_pressed)
	{
		if (time_speed.getElapsedTime().asSeconds() > 5.0f)
		{
			time_speed.restart();
			speed--;
			speed_item_pressed = false;
		}
	}
}
bool help_function()
{
	sf::Vector2f position(screenW / 2, screenH / 2);
	position.x = sprite_player.getPosition().x + taille / 2 - (screenW / 2);
	position.y = sprite_player.getPosition().y + taille / 2 - (screenH / 2);

	help_rect.setPosition(position.x, position.y);
	help_rect.setSize(sf::Vector2f(screenW, screenH));

	return true;
}
void gestion_mannette()
{
	
	if (sf::Joystick::isButtonPressed(0, 0))
	{
		echelle_monter = true;
		if (space)
		{
			anim.y = Up;
			py -= 6;
		}
		else
		{
			if (!saut)
			{
				if (has_saut)
				{
					saut = true;
				}
			}
		}
		has_saut = false;
	}
	if (sf::Joystick::isButtonPressed(0, 3))
	{
		if (time_manette.getElapsedTime().asMilliseconds() >= 150)
		{
			time_manette.restart();
			ChargeLevels(level);
			ChargePortal(level);
			reset_vetbox(true);
			health = 6;
		}
	}
	if (sf::Joystick::isButtonPressed(0, 1))
	{
		shift = true;
	}
	if (sf::Joystick::isButtonPressed(0, 5))
	{
		if (level != record)
		{
			if (time_manette.getElapsedTime().asMilliseconds() >= 150)
			{
				time_manette.restart();

				level++;
				if (level > record) level--;
				charge();
				time_in_level_minute = 0;
				time_in_level_second.restart();
			}
		}
	}
	if (sf::Joystick::isButtonPressed(0, 4))
	{
		if (level != 0)
		{
			if (time_manette.getElapsedTime().asMilliseconds() >= 150)
			{
				time_manette.restart();

				level--;
				if (level < 1) level = 1;
				charge();
				time_in_level_minute = 0;
				time_in_level_second.restart();
			}
		}
	}
	

	int JoystickX = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
	int JoystickZ =  sf::Joystick::getAxisPosition(0, sf::Joystick::Z);

	if (JoystickZ > 0)
	{
		if (time_item_change.getElapsedTime().asMilliseconds() > 150)
		{
			draw_item_selecte(-1);
			time_item_change.restart();
		}
	}
	if (JoystickZ < 0)
	{
		if (time_item_change.getElapsedTime().asMilliseconds() > 150)
		{
			draw_item_selecte(1);
			time_item_change.restart();
		}
	}
	if (JoystickX > 1)
	{
		anim.y = Right;
		px += speed;
	}
	if (JoystickX < -1)
	{
		anim.y = Left;
		px -= speed;
	}
}
void draw_item_selecte(int change_place) {
	inv = get_item_list();
	if (ItemSelectedPlaceInList + change_place > ItemSelectedPlaceInList)
	{
		int ItemSelectedPlaceInListAdd1 = ItemSelectedPlaceInList + 1;
		if (ItemSelectedPlaceInListAdd1 < inv.size())
		{
			ItemSelectedPlaceInList += change_place;
		}
	}
	else if (ItemSelectedPlaceInList + change_place < ItemSelectedPlaceInList)
	{
		if (ItemSelectedPlaceInList - 1 >= 0)
		{
			ItemSelectedPlaceInList += change_place;
		}
	}
	
	item.setSize({30,30});
	item.setPosition(position_item.x + 10, position_item.y - 30);
	item_text.setPosition(position_item.x + 60, position_item.y - 25);
	item_text.setFont(font);
	item_text.setCharacterSize(15);

	if (inv.size() >= 1)
	{
		//std::cout << ItemSelectedPlaceInList << std::endl;
		if (ItemSelectedPlaceInList <= inv.size())
		{
			have_item = true;
			switch (inv[ItemSelectedPlaceInList])
			{
			case 1:
				item.setTexture(&item_heal_texture);
				item_text.setString("Heal potion");
				break;
			case 2:
				item.setTexture(&item_sword_texture);
				item_text.setString("Sword");
				break;
			case 3:
				item.setTexture(&item_up_texture);
				item_text.setString("Up jump");
				break;
			case 4:
				item.setTexture(&item_speed_texture);
				item_text.setString("speed");
				break;
			default:
				break;
			}
		}
		else have_item = false;
		inv.clear();
	}
	else have_item = false;
	
}
void draw_item_selecte() {
	inv = get_item_list();

	item.setSize({ 30,30 });
	item.setPosition(position_item.x + 10, position_item.y - 30);
	item_text.setPosition(position_item.x + 60, position_item.y - 25);
	item_text.setFont(font);
	item_text.setCharacterSize(15);

	if (inv.size() >= 1)
	{
		//std::cout << ItemSelectedPlaceInList << std::endl;
		if (ItemSelectedPlaceInList <= inv.size())
		{
			have_item = true;
			switch (inv[ItemSelectedPlaceInList])
			{
			case 1:
				item.setTexture(&item_heal_texture);
				item_text.setString("Heal potion");
				break;
			case 2:
				item.setTexture(&item_sword_texture);
				item_text.setString("Sword");
				break;
			case 3:
				item.setTexture(&item_up_texture);
				item_text.setString("Up jump");
				break;
			case 4:
				item.setTexture(&item_speed_texture);
				item_text.setString("speed");
				break;
			default:
				if (ItemSelectedPlaceInList - 1 >= 0)
				{
					ItemSelectedPlaceInList -= 1;
				}
				break;
			}
		}
		else have_item = false;
		inv.clear();
	}
	else have_item = false;

}
void fullscrenn(bool ignore) {
	if (ignore || time_fullscrenn.getElapsedTime().asMilliseconds() > 200)
	{
		if (!ignore)
		{
			fullscreen = !fullscreen;
		}
		if (fullscreen) {
			if (!ignore) reload = 14;
			time_fps.restart();
			app.create(sf::VideoMode::getFullscreenModes()[0], title, sf::Style::Fullscreen);
			screenW = sf::VideoMode::getFullscreenModes()[0].width;
			screenH = sf::VideoMode::getFullscreenModes()[0].height;
		}
		else if (!fullscreen) {
			if (!ignore) reload = 14;
			time_fps.restart();
			app.create(sf::VideoMode(800, 600,resolution), title, sf::Style::Default);
			screenW = 800;
			screenH = 600;
		}
		time_fullscrenn.restart();
	}
}
void couleur() {
	std::ifstream ifs(("resourcespack/" + resourcespack + "/color/color.ini").c_str());

	Color struct_right_text{};
	Color struct_level_number{};

	if (ifs.is_open())
	{
		ifs >> struct_right_text.r >> struct_right_text.g >> struct_right_text.b;
		ifs >> struct_level_number.r >> struct_level_number.g >> struct_level_number.b;
	}
	ifs.close();
	color_right_text.r = struct_right_text.r; color_right_text.g = struct_right_text.g; color_right_text.b = struct_right_text.b;
	color_level_number.r = struct_level_number.r; color_level_number.g = struct_level_number.g; color_level_number.b = struct_level_number.b;
}