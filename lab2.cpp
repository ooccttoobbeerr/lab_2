#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

//Kirienko Tatiana PS_22

using namespace sf;//включаем пространство имен sf, чтобы постоянно не писать sf::

void is_victory(int pole[3][3], bool & result, int is_cross) {//Проверка на победу
	int x;
	int y;
	bool flag;
	for (y = 0; y < 3; y++){//Проверка по горизонтали
		flag = true;
		for (x = 0; x < 3; x++){
			if (pole[y][x] != is_cross){
				flag = false;
			}
		}
		if (flag){
			result = true;
		}
	}
	for (x = 0; x < 3; x++){//Проверка по вертикали
		flag = true;
		for (y = 0; y < 3; y++){
			if (pole[y][x] != is_cross){
				flag = false;
			}
		}
		if (flag){
			result = true;
		}
	}
	{//Проверка по даигоналям
		flag = true;
		if (pole[0][0] != is_cross || pole[1][1] != is_cross || pole[2][2] != is_cross){
			flag = false;
		}
		if (flag){
			result = true;
		}
	}
	{
		flag = true;
		if (pole[0][2] != is_cross || pole[1][1] != is_cross || pole[2][0] != is_cross){
			flag = false;
		}
		if (flag){
			result = true;
		}
	}
}

void bot(int pole[3][3], int y, int x, int zero, int cross){
	int  quantity = 0;
	//Кoличество крестиков на поле
	for (y = 0; y < 3; y++){
		for (x = 0; x < 3; x++){
			if (pole[y][x] == cross){
				quantity++;
			}
		}
	}
	//Сколько крестиков, такой и ход
	if (quantity == 1){
		if (pole[1][1] != cross){
			pole[1][1] = zero;
		}
		else{
			pole[0][0] = zero;
		}
	}
	if (quantity > 1 && quantity < 6){
		for (y = 0; y < 3; y++){//Строки
			if (pole[y][0] == cross && pole[y][1] == cross){
				pole[y][2] = zero;
			}
			else if (pole[y][1] == cross && pole[y][2] == cross){
				pole[y][0] = zero;
			}
			else if (pole[y][0] == cross && pole[y][2] == cross){
				pole[y][1] = zero;
			}
		}
		for (x = 0; x < 3; x++){//Столбцы
			if (pole[0][x] == cross && pole[1][x] == cross){
				pole[2][x] = zero;
			}
			else if (pole[1][x] == cross && pole[2][x] == cross){
				pole[0][x] = zero;
			}
			else if (pole[0][x] == cross && pole[2][x] == cross){
				pole[1][x] = zero;
			}
		}
		if (pole[1][1] == zero){//Частные случаи
			if (pole[0][1] == cross && pole[1][2] == cross && pole[0][2] == 0){
				pole[0][2] = zero;
			}
			else if (pole[2][1] == cross && pole[1][2] == cross && pole[2][2] == 0){
				pole[2][2] = zero;
			}
			else if (pole[2][1] == cross && pole[1][0] == cross && pole[2][0] == 0){
				pole[2][0] = zero;
			}
			else if (pole[0][1] == cross && pole[1][0] == cross && pole[0][0] == 0){
				pole[0][0] = zero;
			}
			else if (pole[2][0] == cross && pole[0][2] == cross && pole[2][1] == 0){
				pole[0][1] = zero;
			}
			else if (pole[0][0] == cross && pole[2][2] == cross && pole[1][2] == 0){
				pole[1][0] = zero;
			}
			else if (pole[0][1] == cross && pole[2][1] == cross && pole[2][0] == 0){
				pole[0][2] = zero;
			}
			else if (pole[1][0] == cross && pole[1][2] == cross && pole[0][0] == 0){
				pole[2][2] = zero;
			}
		}

		else{
			if (pole[0][2] == cross || pole[2][2] == cross){//Частные случаи
				if (pole[2][0] != 0){
					pole[0][0] = zero;
				}
				else{
					pole[2][0] = zero;
				}
			}
			else if (pole[2][0] == cross){
				pole[0][2] = zero;
			}
		}
	}
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(970, 670), "tic-tac-toe");
	///////////////ФОН///////////////
	Image fonimage; 
	fonimage.loadFromFile("2.jpg");
	Texture fontexture;
	fontexture.loadFromImage(fonimage);
	Sprite fon;
	fon.setTexture(fontexture);
	fon.setTextureRect(IntRect(0, 0, 970, 670));
	fon.setPosition(0, 0);
	///////////////КВАДРАТИКИ///////////////
	Image heroimage; 
	heroimage.loadFromFile("3.png");
	Texture herotexture;
	herotexture.loadFromImage(heroimage);	
	Sprite cell1;
	cell1.setTexture(herotexture);
	cell1.setTextureRect(IntRect(0, 0, 190, 190));
	cell1.setPosition(60, 60);
	Sprite cell2;
	cell2.setTexture(herotexture);
	cell2.setTextureRect(IntRect(0, 0, 190, 190));
	cell2.setPosition(60, 260);
	Sprite cell3;
	cell3.setTexture(herotexture);
	cell3.setTextureRect(IntRect(0, 0, 190, 190));
	cell3.setPosition(60, 460);
	Sprite cell4;
	cell4.setTexture(herotexture);
	cell4.setTextureRect(IntRect(0, 0, 190, 190));
	cell4.setPosition(260, 60);
	Sprite cell5;
	cell5.setTexture(herotexture);
	cell5.setTextureRect(IntRect(0, 0, 190, 190));
	cell5.setPosition(260, 260);
	Sprite cell6;
	cell6.setTexture(herotexture);
	cell6.setTextureRect(IntRect(0, 0, 190, 190));
	cell6.setPosition(260, 460);
	Sprite cell7;
	cell7.setTexture(herotexture);
	cell7.setTextureRect(IntRect(0, 0, 190, 190));
	cell7.setPosition(460, 60);
	Sprite cell8;
	cell8.setTexture(herotexture);
	cell8.setTextureRect(IntRect(0, 0, 190, 190));
	cell8.setPosition(460, 260);
	Sprite cell9;
	cell9.setTexture(herotexture);
	cell9.setTextureRect(IntRect(0, 0, 190, 190));
	cell9.setPosition(460, 460);
	///////////////КНОПКИ///////////////
	Image button;
	button.loadFromFile("Button.png");
	Texture buttontexture;
	buttontexture.loadFromImage(button);
	Sprite button1;
	button1.setTexture(buttontexture);
	button1.setTextureRect(IntRect(0, 0, 220, 70));
	button1.setPosition(700, 210);
	Sprite button3;
	button3.setTexture(buttontexture);
	button3.setTextureRect(IntRect(0, 0, 220, 70));
	button3.setPosition(700, 290);
	///////////////НОЛИКИ И КРЕСТИКИ///////////////
	Image zero;
	zero.loadFromFile("1.png");
	Texture zerotexture;
	zerotexture.loadFromImage(zero);

	Image cross;
	cross.loadFromFile("clover.png");
	Texture crosstexture;
	crosstexture.loadFromImage(cross);

	Sprite crosssprite;
	Sprite crosssprite2;
	Sprite crosssprite3;
	Sprite crosssprite4;
	Sprite crosssprite5;
	Sprite crosssprite6;
	Sprite crosssprite7;
	Sprite crosssprite8;
	Sprite crosssprite9;

	Sprite zerosprite;
	Sprite zerosprite2;
	Sprite zerosprite3;
	Sprite zerosprite4;
	Sprite zerosprite5;
	Sprite zerosprite6;
	Sprite zerosprite7;
	Sprite zerosprite8;
	Sprite zerosprite9;
	///////////////ТЕКСТ///////////////
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
	Text string2("", font, 100);
	string2.setColor(Color::White);
	string2.setStyle(Text::Bold);
	string2.setPosition(70, 250);

	bool isMove = false;//флаг для щелчка мыши по спрайту
	bool cross_move = true;
	bool victory = false;
	bool is_pravila = false;
	bool you_win = false;
	bool you_loss = false;
	int pole[3][3] = { { 0,0,0 },{ 0, 0, 0 },{ 0, 0, 0 } };
	int i, k, X, Y;
	i = 0;
	int cross = 1, zero = 2;

	while (window.isOpen()){
		Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсорa
		Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
			///////////////ВЫВОД НОЛИКОВ И КРЕСТИКОВ В КВАДРАТИКИ///////////////
			if (event.type == sf::Event::MouseButtonReleased){
				if (event.key.code == sf::Mouse::Left){
					conclusion_noughts_and_crosses(pole, x, y, zero, cross)
					if (60 < pixelPos.x && pixelPos.x < 650 && 60 < pixelPos.y && pixelPos.y < 650)//Работа в игровом поле
						if (60 < pixelPos.x && pixelPos.x < 250){//1 проверка по x
							if (60 < pixelPos.y && pixelPos.y < 250){//1 проверка по y
								if (pole[0][0] == 0){
									pole[0][0] = cross;
									bot(pole, X, Y, zero, cross);
								}
							}
							else if (260 < pixelPos.y && pixelPos.y < 450){//2 проверка по y
								if (pole[1][0] == 0){
									pole[1][0] = cross;
									bot(pole, X, Y, zero, cross);
								}
							}
							else if (460 < pixelPos.y && pixelPos.y < 650){//3 проверка по y
								if (pole[2][0] == 0){
									pole[2][0] = cross;
									bot(pole, X, Y, zero, cross);
								}
							}
						}
						else if (260 < pixelPos.x && pixelPos.x < 450){//2 проверка по x
							if (60 < pixelPos.y && pixelPos.y < 250){//1 проверка по y
								if (pole[0][1] == 0){
									pole[0][1] = cross;
									bot(pole, X, Y, zero, cross);
								}
							}
							else if (260 < pixelPos.y && pixelPos.y < 450){//2 проверка по y
								if (pole[1][1] == 0){
									pole[1][1] = cross;
									bot(pole, X, Y, zero, cross);
								}
							}
							else if (460 < pixelPos.y && pixelPos.y < 650){//3 проверка по y
								if (pole[2][1] == 0){
									pole[2][1] = cross;
									bot(pole, X, Y, zero, cross);
								}
							}
						}
						else if (460 < pixelPos.x && pixelPos.x < 650){//3 проверка по x
							if (60 < pixelPos.y && pixelPos.y < 250){//1 проверка по y
								if (pole[0][2] == 0){
									pole[0][2] = cross;
									bot(pole, X, Y, zero, cross);
								}
							}
							else if (260 < pixelPos.y && pixelPos.y < 450){//2 проверка по y 
								if (pole[1][2] == 0){
									pole[1][2] = cross;
									bot(pole, X, Y, zero, cross);
								}
							}
							else if (460 < pixelPos.y && pixelPos.y < 650){//3 проверка по y
								if (pole[2][2] == 0){
									pole[2][2] = cross;
									bot(pole, X, Y, zero, cross);
								}
							}
						}
				}
			}
			///////////////ДЕЙСТВИЯ КНОПОК///////////////
			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left){
					if (button3.getGlobalBounds().contains(pixelPos.x, pixelPos.y)){
						std::cout << "isClicked!\n";
						isMove = true;
						window.close();
					}
					if (button1.getGlobalBounds().contains(pixelPos.x, pixelPos.y)){
						std::cout << "isClicked!\n";
						isMove = true;
						window.close();
						main();
					}
				}
		}
		is_victory(pole, you_win, cross);//Победа крестиков
		is_victory(pole, you_loss, zero);//Победа ноликов
		window.clear();
		window.draw(fon);
		window.draw(cell1);
		window.draw(cell2);
		window.draw(cell3);
		window.draw(cell4);
		window.draw(cell5);
		window.draw(cell6);
		window.draw(cell7);
		window.draw(cell8);
		window.draw(cell9);
		window.draw(button1);
		window.draw(button3);
		window.draw(text1);
		window.draw(text3);
		if (pole[0][0] == 1){
			crosssprite.setTexture(crosstexture);
			crosssprite.setTextureRect(IntRect(0, 0, 190, 190));
			crosssprite.setPosition(60, 60);
			window.draw(crosssprite);
		}
		else if (pole[0][0] == 2){
			zerosprite.setTexture(zerotexture);
			zerosprite.setTextureRect(IntRect(0, 0, 190, 190));
			zerosprite.setPosition(60, 60);
			window.draw(zerosprite);
		}
		if (pole[1][0] == 1){
			crosssprite2.setTexture(crosstexture);
			crosssprite2.setTextureRect(IntRect(0, 0, 190, 190));
			crosssprite2.setPosition(60, 260);
			window.draw(crosssprite2);
		}
		else if (pole[1][0] == 2){
			zerosprite2.setTexture(zerotexture);
			zerosprite2.setTextureRect(IntRect(0, 0, 190, 190));
			zerosprite2.setPosition(60, 260);
			window.draw(zerosprite2);
		}
		if (pole[2][0] == 1){
			crosssprite3.setTexture(crosstexture);
			crosssprite3.setTextureRect(IntRect(0, 0, 190, 190));
			crosssprite3.setPosition(60, 460);
			window.draw(crosssprite3);
		}
		else if (pole[2][0] == 2){
			zerosprite3.setTexture(zerotexture);
			zerosprite3.setTextureRect(IntRect(0, 0, 190, 190));
			zerosprite3.setPosition(60, 460);
			window.draw(zerosprite3);
		}
		if (pole[0][1] == 1){
			crosssprite4.setTexture(crosstexture);
			crosssprite4.setTextureRect(IntRect(0, 0, 190, 190));
			crosssprite4.setPosition(260, 60);
			window.draw(crosssprite4);
		}
		else if (pole[0][1] == 2){
			zerosprite4.setTexture(zerotexture);
			zerosprite4.setTextureRect(IntRect(0, 0, 190, 190));
			zerosprite4.setPosition(260, 60);
			window.draw(zerosprite4);
		}
		if (pole[1][1] == 1){
			crosssprite5.setTexture(crosstexture);
			crosssprite5.setTextureRect(IntRect(0, 0, 190, 190));
			crosssprite5.setPosition(260, 260);
			window.draw(crosssprite5);
		}
		else if (pole[1][1] == 2){
			zerosprite5.setTexture(zerotexture);
			zerosprite5.setTextureRect(IntRect(0, 0, 190, 190));
			zerosprite5.setPosition(260, 260);
			window.draw(zerosprite5);
		}
		if (pole[2][1] == 1){
			crosssprite6.setTexture(crosstexture);
			crosssprite6.setTextureRect(IntRect(0, 0, 190, 190));
			crosssprite6.setPosition(260, 460);
			window.draw(crosssprite6);
		}
		else if (pole[2][1] == 2){
			zerosprite6.setTexture(zerotexture);
			zerosprite6.setTextureRect(IntRect(0, 0, 190, 190));
			zerosprite6.setPosition(260, 460);
			window.draw(zerosprite6);
		}
		if (pole[0][2] == 1){
			crosssprite7.setTexture(crosstexture);
			crosssprite7.setTextureRect(IntRect(0, 0, 190, 190));
			crosssprite7.setPosition(460, 60);
			window.draw(crosssprite7);
		}
		else if (pole[0][2] == 2){
			zerosprite7.setTexture(zerotexture);
			zerosprite7.setTextureRect(IntRect(0, 0, 190, 190));
			zerosprite7.setPosition(460, 60);
			window.draw(zerosprite7);
		}
		if (pole[1][2] == 1){
			crosssprite8.setTexture(crosstexture);
			crosssprite8.setTextureRect(IntRect(0, 0, 190, 190));
			crosssprite8.setPosition(460, 260);
			window.draw(crosssprite8);
		}
		else if (pole[1][2] == 2){
			zerosprite8.setTexture(zerotexture);
			zerosprite8.setTextureRect(IntRect(0, 0, 190, 190));
			zerosprite8.setPosition(460, 260);
			window.draw(zerosprite8);
		}
		if (pole[2][2] == 1){
			crosssprite9.setTexture(crosstexture);
			crosssprite9.setTextureRect(IntRect(0, 0, 190, 190));
			crosssprite9.setPosition(460, 460);
			window.draw(crosssprite9);
		}
		else if (pole[2][2] == 2){
			zerosprite9.setTexture(zerotexture);
			zerosprite9.setTextureRect(IntRect(0, 0, 190, 190));
			zerosprite9.setPosition(460, 460);
			window.draw(zerosprite9);
		}
		if (you_win){
			string2.setString("Ты победил!\n");
			window.draw(string2);
		}
		else if (you_loss){
			string2.setString("Ты проиграл!\n");
			window.draw(string2);
		}
		else if (pole[0][0] != 0 && pole[0][1] != 0 && pole[0][2] != 0 &&
			pole[1][0] != 0 && pole[1][1] != 0 && pole[1][2] != 0 &&
			pole[2][0] != 0 && pole[2][1] != 0 && pole[2][2] != 0){
			string2.setString("Игра закончена!\n");
			window.draw(string2);
		}
		window.display();
	}
	return 0;
}
