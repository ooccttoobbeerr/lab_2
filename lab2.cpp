#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

//Kirienko Tatiana PS_22

using namespace sf;//включаем пространство имен sf, чтобы постоянно не писать sf::

struct GraphicResource {
	Image* image;
	Texture* texture;
	Sprite* sprite;
};

GraphicResource make_the_sprite(String file_name) {
	GraphicResource graphic_resource;
	graphic_resource.image = new Image();
	graphic_resource.texture = new Texture();
	graphic_resource.sprite = new Sprite();
	graphic_resource.image->loadFromFile(file_name);
	graphic_resource.texture->loadFromImage(*graphic_resource.image);
	graphic_resource.sprite->setTexture(*graphic_resource.texture);
	return graphic_resource;
}

void clean_the_memory(GraphicResource & graphic_resource) {
	delete graphic_resource.image;
	delete graphic_resource.texture;
	delete graphic_resource.sprite;
}

void draw_the_sprite(RenderWindow & window, Sprite & sprite, int i, int j, int sprite_width, int sprite_heigh, float x, float y) {
	sprite.setTextureRect(IntRect(i, j, sprite_width, sprite_heigh));//рисуем 
	sprite.setPosition(x, y);//задаем начальные координаты появления спрайта
	window.draw(sprite);
}

void is_victory(int pole[3][3], bool & result, int is_cross) {//Проверка на победу
	int x;
	int y;
	bool flag;
	for (y = 0; y < 3; y++) {//Проверка по горизонтали
		flag = true;
		for (x = 0; x < 3; x++) {
			if (pole[y][x] != is_cross) {
				flag = false;
			}
		}
		if (flag) {
			result = true;
		}
	}
	for (x = 0; x < 3; x++) {//Проверка по вертикали
		flag = true;
		for (y = 0; y < 3; y++) {
			if (pole[y][x] != is_cross) {
				flag = false;
			}
		}
		if (flag) {
			result = true;
		}
	}
	{//Проверка по даигоналям
		flag = true;
		if (pole[0][0] != is_cross || pole[1][1] != is_cross || pole[2][2] != is_cross) {
			flag = false;
		}
		if (flag) {
			result = true;
		}
	}
	{
		flag = true;
		if (pole[0][2] != is_cross || pole[1][1] != is_cross || pole[2][0] != is_cross) {
			flag = false;
		}
		if (flag) {
			result = true;
		}
	}
}

int count_crosses(int pole[3][3], int x, int y, int cross) {
	int  quantity = 0;
	for (y = 0; y < 3; y++) {
		for (x = 0; x < 3; x++) {
			if (pole[y][x] == cross) {
				quantity++;
			}
		}
	}
	return quantity;
}

void special_cases(int pole[3][3], int zero, int cross) {

	if (pole[1][1] == zero) {//Частные случаи
		if (pole[0][1] == cross && pole[1][2] == cross && pole[0][2] == 0) {
			pole[0][2] = zero;
		}
		else if (pole[2][1] == cross && pole[1][2] == cross && pole[2][2] == 0) {
			pole[2][2] = zero;
		}
		else if (pole[2][1] == cross && pole[1][0] == cross && pole[2][0] == 0) {
			pole[2][0] = zero;
		}
		else if (pole[0][1] == cross && pole[1][0] == cross && pole[0][0] == 0) {
			pole[0][0] = zero;
		}
		else if (pole[2][0] == cross && pole[0][2] == cross && pole[2][1] == 0) {
			pole[0][1] = zero;
		}
		else if (pole[0][0] == cross && pole[2][2] == cross && pole[1][2] == 0) {
			pole[1][0] = zero;;
		}
		else if (pole[0][1] == cross && pole[2][1] == cross && pole[2][0] == 0) {
			pole[0][2] = zero;
		}
		else if (pole[1][0] == cross && pole[1][2] == cross && pole[0][0] == 0) {
			pole[2][2] = zero;
		}
	}
	else {
		if (pole[0][2] == cross || pole[2][2] == cross) {//Частные случаи
			if (pole[2][0] != 0) {
				pole[0][0] = zero;
			}
			else {
				pole[2][0] = zero;
			}
		}
		else if (pole[2][0] == cross) {
			pole[0][2] = zero;
		}
	}

}

void setting_noughts_and_crosses(int pole[3][3], int y, int x, int zero, int cross) {

	if (count_crosses(pole, x, y, cross) == 1) {
		if (pole[1][1] != cross) {
			pole[1][1] = zero;
		}
		else {
			pole[0][0] = zero;
		}
	}
	if (count_crosses(pole, x, y, cross) > 1 && count_crosses(pole, x, y, cross) < 6) {
		for (y = 0; y < 3; y++) {//Строки
			if (pole[y][0] == cross && pole[y][1] == cross) {
				pole[y][2] = zero;
			}
			else if (pole[y][1] == cross && pole[y][2] == cross) {
				pole[y][0] = zero;
			}
			else if (pole[y][0] == cross && pole[y][2] == cross) {
				pole[y][1] = zero;
			}
		}
		for (x = 0; x < 3; x++) {//Столбцы
			if (pole[0][x] == cross && pole[1][x] == cross) {
				pole[2][x] = zero;
			}
			else if (pole[1][x] == cross && pole[2][x] == cross) {
				pole[0][x] = zero;
			}
			else if (pole[0][x] == cross && pole[2][x] == cross) {
				pole[1][x] = zero;
			}
		}
		special_cases(pole, zero, cross);
	}
}

void draw_window(RenderWindow &window, int pole[3][3],GraphicResource &squareimage, GraphicResource &fonimage, GraphicResource &zeroimage, GraphicResource &crossimage) {
	draw_the_sprite(window, *fonimage.sprite, 0, 0, 970, 670, 0, 0);
	draw_the_sprite(window, *squareimage.sprite, 0, 0, 190, 190, 60, 60);
	draw_the_sprite(window, *squareimage.sprite, 0, 0, 190, 190, 60, 260);
	draw_the_sprite(window, *squareimage.sprite, 0, 0, 190, 190, 60, 460);
	draw_the_sprite(window, *squareimage.sprite, 0, 0, 190, 190, 260, 60);
	draw_the_sprite(window, *squareimage.sprite, 0, 0, 190, 190, 260, 260);
	draw_the_sprite(window, *squareimage.sprite, 0, 0, 190, 190, 260, 460);
	draw_the_sprite(window, *squareimage.sprite, 0, 0, 190, 190, 460, 60);
	draw_the_sprite(window, *squareimage.sprite, 0, 0, 190, 190, 460, 260);
	draw_the_sprite(window, *squareimage.sprite, 0, 0, 190, 190, 460, 460);
	if (pole[0][0] == 1) {
		draw_the_sprite(window, *crossimage.sprite, 0, 0, 190, 190, 60, 60);
	}
	else if (pole[0][0] == 2) {
		draw_the_sprite(window, *zeroimage.sprite, 0, 0, 190, 190, 60, 60);
	}
	if (pole[1][0] == 1) {
		draw_the_sprite(window, *crossimage.sprite, 0, 0, 190, 190, 60, 260);
	}
	else if (pole[1][0] == 2) {
		draw_the_sprite(window, *zeroimage.sprite, 0, 0, 190, 190, 60, 260);
	}
	if (pole[2][0] == 1) {
		draw_the_sprite(window, *crossimage.sprite, 0, 0, 190, 190, 60, 460);
	}
	else if (pole[2][0] == 2) {
		draw_the_sprite(window, *zeroimage.sprite, 0, 0, 190, 190, 60, 460);
	}
	if (pole[0][1] == 1) {
		draw_the_sprite(window, *crossimage.sprite, 0, 0, 190, 190, 260, 60);
	}
	else if (pole[0][1] == 2) {
		draw_the_sprite(window, *zeroimage.sprite, 0, 0, 190, 190, 260, 60);
	}
	if (pole[1][1] == 1) {
		draw_the_sprite(window, *crossimage.sprite, 0, 0, 190, 190, 260, 260);
	}
	else if (pole[1][1] == 2) {
		draw_the_sprite(window, *zeroimage.sprite, 0, 0, 190, 190, 260, 260);
	}
	if (pole[2][1] == 1) {
		draw_the_sprite(window, *crossimage.sprite, 0, 0, 190, 190, 260, 460);
	}
	else if (pole[2][1] == 2) {
		draw_the_sprite(window, *zeroimage.sprite, 0, 0, 190, 190, 260, 460);
	}
	if (pole[0][2] == 1) {
		draw_the_sprite(window, *crossimage.sprite, 0, 0, 190, 190, 460, 60);
	}
	else if (pole[0][2] == 2) {
		draw_the_sprite(window, *zeroimage.sprite, 0, 0, 190, 190, 460, 60);
	}
	if (pole[1][2] == 1) {
		draw_the_sprite(window, *crossimage.sprite, 0, 0, 190, 190, 460, 260);
	}
	else if (pole[1][2] == 2) {
		draw_the_sprite(window, *zeroimage.sprite, 0, 0, 190, 190, 460, 260);
	}
	if (pole[2][2] == 1) {
		draw_the_sprite(window, *crossimage.sprite, 0, 0, 190, 190, 460, 460);
	}
	else if (pole[2][2] == 2) {
		draw_the_sprite(window, *zeroimage.sprite, 0, 0, 190, 190, 460, 460);
	}
}

void game(RenderWindow &window, GraphicResource &squareimage, GraphicResource &fonimage, GraphicResource &zeroimage, GraphicResource &crossimage, Sprite &button1, Sprite &button3, Text text1, Text text3, Text string2) {
	bool isMove = false, cross_move = true, victory = false, you_win = false, you_loss = false;
	int pole[3][3] = { { 0,0,0 },{ 0, 0, 0 },{ 0, 0, 0 } };
	int i = 0, X = 0, Y = 0, cross = 1, zero = 2;

	while (window.isOpen()) {
		Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсорa
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.key.code == sf::Mouse::Left) {
					if (60 < pixelPos.x && pixelPos.x < 650 && 60 < pixelPos.y && pixelPos.y < 650)//Работа в игровом поле
						if (60 < pixelPos.x && pixelPos.x < 250) {//1 проверка по x
							if (60 < pixelPos.y && pixelPos.y < 250) {//1 проверка по y
								if (pole[0][0] == 0) {
									pole[0][0] = cross;
									setting_noughts_and_crosses(pole, X, Y, zero, cross);
								}
							}
							else if (260 < pixelPos.y && pixelPos.y < 450) {//2 проверка по y
								if (pole[1][0] == 0) {
									pole[1][0] = cross;
									setting_noughts_and_crosses(pole, X, Y, zero, cross);
								}
							}
							else if (460 < pixelPos.y && pixelPos.y < 650) {//3 проверка по y
								if (pole[2][0] == 0) {
									pole[2][0] = cross;
									setting_noughts_and_crosses(pole, X, Y, zero, cross);
								}
							}
						}
						else if (260 < pixelPos.x && pixelPos.x < 450) {//2 проверка по x
							if (60 < pixelPos.y && pixelPos.y < 250) {//1 проверка по y
								if (pole[0][1] == 0) {
									pole[0][1] = cross;
									setting_noughts_and_crosses(pole, X, Y, zero, cross);
								}
							}
							else if (260 < pixelPos.y && pixelPos.y < 450) {//2 проверка по y
								if (pole[1][1] == 0) {
									pole[1][1] = cross;
									setting_noughts_and_crosses(pole, X, Y, zero, cross);
								}
							}
							else if (460 < pixelPos.y && pixelPos.y < 650) {//3 проверка по y
								if (pole[2][1] == 0) {
									pole[2][1] = cross;
									setting_noughts_and_crosses(pole, X, Y, zero, cross);
								}
							}
						}
						else if (460 < pixelPos.x && pixelPos.x < 650) {//3 проверка по x
							if (60 < pixelPos.y && pixelPos.y < 250) {//1 проверка по y
								if (pole[0][2] == 0) {
									pole[0][2] = cross;
									setting_noughts_and_crosses(pole, X, Y, zero, cross);
								}
							}
							else if (260 < pixelPos.y && pixelPos.y < 450) {//2 проверка по y 
								if (pole[1][2] == 0) {
									pole[1][2] = cross;
									setting_noughts_and_crosses(pole, X, Y, zero, cross);
								}
							}
							else if (460 < pixelPos.y && pixelPos.y < 650) {//3 проверка по y
								if (pole[2][2] == 0) {
									pole[2][2] = cross;
									setting_noughts_and_crosses(pole, X, Y, zero, cross);
								}
							}
						}
				}
			}
			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left) {
					if (button3.getGlobalBounds().contains(float (pixelPos.x), float (pixelPos.y))) {
						std::cout << "isClicked!\n";
						isMove = true;
						window.close();
					}
					if (button1.getGlobalBounds().contains(float (pixelPos.x), float (pixelPos.y))) {
						std::cout << "isClicked!\n";
						isMove = true;
						game(window, squareimage, fonimage, zeroimage, crossimage, button1, button3, text1, text3, string2);
					}
				}
		}
		is_victory(pole, you_win, cross);//Победа крестиков
		is_victory(pole, you_loss, zero);//Победа ноликов
		window.clear();
		draw_window(window, pole, squareimage, fonimage, zeroimage, crossimage);
		draw_the_sprite(window, button1, 0, 0, 220, 70, 700, 210);
		draw_the_sprite(window, button3, 0, 0, 220, 70, 700, 290);
		window.draw(text1);
		window.draw(text3);
		if (you_win) {
			string2.setString("Ты победил!\n");
			window.draw(string2);
		}
		else if (you_loss) {
			string2.setString("Ты проиграл!\n");
			window.draw(string2);
		}
		else if (pole[0][0] != 0 && pole[0][1] != 0 && pole[0][2] != 0 &&
			pole[1][0] != 0 && pole[1][1] != 0 && pole[1][2] != 0 &&
			pole[2][0] != 0 && pole[2][1] != 0 && pole[2][2] != 0) {
			string2.setString("Игра закончена!\n");
			window.draw(string2);
		}
		window.display();
	}
}

int main()
{
	RenderWindow window(VideoMode(970, 670), "tic-tac-toe");
	GraphicResource fonimage = make_the_sprite("2.jpg");
	GraphicResource squareimage = make_the_sprite("3.png");
	GraphicResource button = make_the_sprite("Button.png");
	GraphicResource zeroimage = make_the_sprite("1.png");
	GraphicResource crossimage = make_the_sprite("clover.png");
	Sprite button1 = *button.sprite;
	Sprite button3 = *button.sprite;
	Font font;
	font.loadFromFile("CyrilicOld.ttf");
	Text text3("", font, 40);
	text3.setColor(Color::White);
	text3.setStyle(Text::Bold);
	text3.setString("Выход");
	text3.setPosition(735, 295);
	Text text1("", font, 40);
	text1.setColor(Color::White);
	text1.setStyle(Text::Bold);
	text1.setString("Очистить");
	text1.setPosition(720, 215);
	font.loadFromFile("CyrilicOld.ttf");
	Text string2("", font, 100);
	string2.setColor(Color::White);
	string2.setStyle(Text::Bold);
	string2.setPosition(70, 250);

	game(window, squareimage, fonimage, zeroimage, crossimage, button1, button3, text1, text3, string2);

	clean_the_memory(zeroimage);
	clean_the_memory(crossimage);
	clean_the_memory(button);
	clean_the_memory(squareimage);
	clean_the_memory(fonimage);
	return 0;
}
