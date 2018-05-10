#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <fstream>
#include <Windows.h>
#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

void plikmaxscore(unsigned long int & maxscore)
{
	ifstream plik;
	plik.open("images/wynik.png");
	if (!plik.good())
	{
		ofstream plikz;
		plikz.open("images/wynik.png");
		plikz << "0";
		plikz.close();
		plik.open("images/wynik.png");
	}
	plik >> maxscore;
	plik.close();
}

int plik(int & resX, int & resY, bool & fullscreen,short & maxfps, bool & vsync, bool wczytaj, bool zapisz, float & predkosc, float & przyspieszenie, float & maxpredkosc, bool & tworzyc)
{
	if (zapisz == 1)
		if (tworzyc == 1)
		{
			{
				ofstream plik;
				plik.open("config.ini");
				plik << resX << "\n";
				plik << resY << "\n";
				plik << fullscreen << "\n";
				plik << maxfps << "\n";
				plik << vsync << "\n";
				plik << predkosc << "\n";
				plik << przyspieszenie << "\n";
				plik << maxpredkosc << "\n";
				plik << "\n";
				plik << "/* OPIS */";
				plik << "\n // 1: Rozdzielczosc X (px) - Nie zalecana jest ni�sza ni� 1280x720\n // 2: Rozdzielczosc Y (px) - Nie zalecana jest ni�sza ni� 1280x720\n // 3: Pelny ekran ( 0 - okno, 1 - pelny ekran )\n // 4: MAXFPS ( Domyslnie - 60. UWAGA! Zmiana tej wartosci na wieksza niz twoj komputer jest w stanie wygenerowac spowoduje spowolnienia! )\n // 5: VSync ( 0 - wylaczony, 1 - wlaczony )\n // 6: Predkosc startowa marchewek ( domyslnie 3 )\n // 7: Przyspieszenie marchewek ( domyslnie 0.25 )\n // 8: Max Predkosc marchewek ( domyslnie 9 )";
			}
		}
	ifstream config;		//Zmienna do odczytywania configu
	config.open("config.ini");
	if (wczytaj == 1)
	{
		if (!config.good())		//Jesli brakuje / nie da si� odczyta� pliku configu stworz go
		{
			/*
			string tekst[12];
			ifstream backup;
			backup.open("config.ini");
			for (int i = 0; i < 12; i++)
			{
			backup >> tekst[i];
			}
			ofstream configbackup;
			configbackup.open("config.ini.bak");
			for (int i = 0; i < 12; i++)
			{
			configbackup << tekst[i] << endl;
			}
			*/
			int wybor = MessageBox(NULL, "B��d odczytu pliku konfiguracyjnego! \nPlik jest uszkodzony lub nie istnieje.\nStworzyc nowy?", "Blad odczytu pliku!", MB_YESNOCANCEL | MB_ICONERROR);
			switch (wybor)
			{
			case IDYES:
			{
				tworzyc = 1;
				break;
			}
			case IDNO:
			{
				tworzyc = 0;
				break;
			}
			case IDCANCEL:
			{
				return 1;
			}
			}
			if (tworzyc == 1)
			{
				ofstream stworzcfg;		//Stw�rz plik configu
				stworzcfg.open("config.ini");
				if (!stworzcfg.good())		//Brak uprawnie� - wy�wietl komunikat
				{
					MessageBox(NULL, "Brak uprawnien do stworzenia pliku!", "Blad tworzenia pliku!", MB_OK | MB_ICONERROR);
					cout << "Brak uprawnien do stworzenia pliku" << endl;
					return 2;
				}
				stworzcfg << "1920\n";
				stworzcfg << "1080\n";
				stworzcfg << "1\n";
				stworzcfg << "60\n";
				stworzcfg << "1\n";
				stworzcfg << "3\n";
				stworzcfg << "0.25\n";
				stworzcfg << "9\n";
				stworzcfg << "\n";
				stworzcfg << "/* OPIS */";
				stworzcfg << "\n // 1: Rozdzielczosc X (px) - Nie zalecana jest ni�sza ni� 1280x720\n // 2: Rozdzielczosc Y (px) - Nie zalecana jest ni�sza ni� 1280x720\n // 3: Pelny ekran ( 0 - okno, 1 - pelny ekran )\n // 4: MAXFPS ( Domyslnie - 60. UWAGA! Zmiana tej wartosci na wieksza niz twoj komputer jest w stanie wygenerowac spowoduje spowolnienia! )\n // 5: VSync ( 0 - wylaczony, 1 - wlaczony )\n // 6: Predkosc startowa marchewek ( domyslnie 3 )\n // 7: Przyspieszenie marchewek ( domyslnie 0.25 )\n // 8: Max Predkosc marchewek ( domyslnie 9 )";
			}
			resX = 1920;
			resY = 1080;
			fullscreen = 1;
			maxfps = 60;
			vsync = 1;
			predkosc = 3;
			przyspieszenie = 0.25;
			maxpredkosc = 9;
		}
	}
	if (wczytaj == 1)
	{
		config >> resX;
		config >> resY;
		config >> fullscreen;
		config >> maxfps;
		config >> vsync;
		config >> predkosc;
		config >> przyspieszenie;
		config >> maxpredkosc;
	}
}

void wycentrujtext(Text & text, int resX, int resY, double skalaY, int wysokosc)
{
	FloatRect textrect = text.getGlobalBounds();
	//cout << "SkalaY: " << skalaY << endl;
	text.setOrigin(textrect.left + textrect.width / 2.0f, textrect.top + textrect.height / 2.0f);
	text.setPosition(Vector2f(resX / 2.0f, resY / 2.0f  + (wysokosc * skalaY  )  ));
	//cout << "ResX: " << resX << " ResY: " << resY << endl;
}

void wycentrujsprite(Sprite & sprite, int resX, int resY, double skalaY, double skalaX, int wysokosc)
{
	//cout << "SkalaX: " << skalaX << endl;
	FloatRect spriterect = sprite.getGlobalBounds();
	cout << "Spriterect.left: " << spriterect.left << " Spriterect.width: " << spriterect.width / 2.0f << endl;
	cout << "Spriterect.left: " << spriterect.left << " Spriterect.width * skalaX: " << spriterect.width * skalaX / 2.0f << endl;
	sprite.setOrigin(spriterect.left + spriterect.width /* skalaX*/ / 2.0f, spriterect.top + spriterect.height /* skalaY*/ / 2.0f);
	sprite.setPosition(Vector2f(resX / 2.0f, resY / 2.0f + (wysokosc * skalaY)));
	//cout << sprite.getPosition().x << endl;
}

void ustawrozdzielczosc(short & wybor_rozdzielczosc, short & iloscrozdzielczosci, int resX, int resY, int & resXt, int & resYt)
{
	if (resX == 1024)
		wybor_rozdzielczosc = 1;
	else
		if (resX == 1280)
			wybor_rozdzielczosc = 2;
		else
			if (resX == 1440)
				wybor_rozdzielczosc = 3;
			else
				if (resX == 1600)
					wybor_rozdzielczosc = 4;
				else
					if (resX == 1920)
						wybor_rozdzielczosc = 5;
					else
						if (resX == 2560)
							wybor_rozdzielczosc = 6;
						else
							if (resX == 3840)
								wybor_rozdzielczosc = 7;
							else
								if (resX == 5120)
									wybor_rozdzielczosc = 8;
								else
									if (resX == 7680)
										wybor_rozdzielczosc = 9;
									else
									{
										wybor_rozdzielczosc = 10;
										resXt = resX;
										resYt = resY;
										iloscrozdzielczosci = 10;
									}
}

bool ustawmaxfps(short & wybor_maxfps, short & iloscmaxfps, short & maxfps, int & maxfpst)
{
	if (maxfps == 30)
		wybor_maxfps = 0;
	else
		if (maxfps == 60)
			wybor_maxfps = 1;
		else
			if (maxfps == 75)
				wybor_maxfps = 2;
			else
				if (maxfps == 100)
					wybor_maxfps = 3;
				else
					if (maxfps == 120)
						wybor_maxfps = 4;
					else
						if (maxfps == 144)
							wybor_maxfps = 5;
						else
							if (maxfps == 240)
								wybor_maxfps = 6;
							else
							{
								wybor_maxfps = 8;
								maxfpst = maxfps;
								iloscmaxfps = iloscmaxfps + 1;
								if (maxfps > 240)
								{
									MessageBox(NULL, "Zbyt wysoka czestotliwosc odswiezania ekranu!\nZmniejsz w pliku config.ini", "Zbyt wysoka czestotliwosc odswiezania!", MB_OK | MB_ICONEXCLAMATION);
									wybor_maxfps = 2;
									maxfps = 60;
									maxfpst = 60;
									iloscmaxfps = iloscmaxfps - 1;
									return 1;
								}
							}
	return 0;
}

short menu(int & resX, int & resY, bool & fullscreen, double skalaY, double skalaX, bool fullscreeno, bool vsync, short maxfps, float & predkosc, float & przyspieszenie, float & maxpredkosc, bool & tworzyc)
{
	//cout << "SkalaY: " << skalaY << endl;
	int resXt = 0;
	int resYt = 0;
	int resXo = resX;
	int resYo = resY;
	int maxfpst;
	bool fullscreenoriginal = fullscreen;
	bool vsyncoriginal = vsync;
	short maxfpsoriginal = maxfps;
	short iloscrozdzielczosci = 9;
	short iloscmaxfps = 6;
	short wybor_maxfps = 0;
	short wybor_rozdzielczosc = 0;
	ustawrozdzielczosc(wybor_rozdzielczosc, iloscrozdzielczosci, resX, resY, resXt, resYt);
	ustawmaxfps(wybor_maxfps, iloscmaxfps, maxfps, maxfpst);
	resY = (resX / 16) * 9;
	bool zmieniono = 0;
	Sprite logo;
	Texture txt_logo;
	txt_logo.loadFromFile("images/logo.png");
	logo.setTexture(txt_logo);
	wycentrujsprite(logo, resX, resY, skalaY, skalaX, -350);
	logo.setScale(skalaX / 4, skalaX / 4);
	//logo.move(-70 * skalaX, 0);
	RenderWindow okno(VideoMode(resX, resY, 32), "Gruniozerca - Menu Glowne");
	if (fullscreen == 1)
	{
		okno.create(VideoMode(resX, resY, 32), "Gruniozerca - Menu", Style::Fullscreen);
	}
	while (okno.isOpen())
	{
		Mouse mouse;
		Event zdarzenie;
		if (okno.pollEvent(zdarzenie))
		{
			if (zdarzenie.type == zdarzenie.Closed) return 1;
			if (zdarzenie.type == zdarzenie.KeyPressed && zdarzenie.key.code == Keyboard::Escape) return 1;
		}
		Text startbutton;
		Font font;
		Text optionsbutton;
		Text exitbutton;
		Text opcjen;

		if (!font.loadFromFile("arial.ttf"))
		{
			return 2;
		}

		opcjen.setFont(font);
		opcjen.setString("OPCJE");
		opcjen.setCharacterSize(100 * skalaY);
		opcjen.setFillColor(Color::Green);
		wycentrujtext(opcjen, resX, resY, skalaY, -350);

		startbutton.setFont(font);
		startbutton.setCharacterSize(100 * skalaY);
		startbutton.setStyle(Text::Bold);
		startbutton.setString("START GRY");
		wycentrujtext(startbutton, resX, resY, skalaY, 150);

		optionsbutton.setFont(font);
		optionsbutton.setCharacterSize(100 * skalaY);
		optionsbutton.setStyle(Text::Bold);
		optionsbutton.setString("OPCJE");
		wycentrujtext(optionsbutton, resX, resY, skalaY, 300);

		exitbutton.setFont(font);
		exitbutton.setCharacterSize(100 * skalaY);
		exitbutton.setStyle(Text::Bold);
		exitbutton.setString("WYJSCIE");
		wycentrujtext(exitbutton, resX, resY, skalaY, 450);

		Vector2f mysz(Mouse::getPosition(okno));

		if (startbutton.getGlobalBounds().contains(mysz))
		{
			startbutton.setFillColor(Color::Blue);
			if (mouse.isButtonPressed(Mouse::Left))
			{
				return 3;
			}
		}
		else
			startbutton.setFillColor(Color::White);

		if (optionsbutton.getGlobalBounds().contains(mysz))
		{
			optionsbutton.setFillColor(Color::Blue);
			if (mouse.isButtonPressed(Mouse::Left))
			{
				while (1)
				{
					
					Text rozdzielczosc;
					rozdzielczosc.setFont(font);
					rozdzielczosc.setString("Rozdzielczosc:");
					rozdzielczosc.setCharacterSize(60*skalaY);
					rozdzielczosc.setPosition(200 * skalaX, 350 * skalaY);
					rozdzielczosc.setFillColor(Color::Yellow);
					
					Text fullscreen;
					fullscreen.setFont(font);
					fullscreen.setString("Pelny ekran:");
					fullscreen.setCharacterSize(60 * skalaY);
					fullscreen.setPosition(200 * skalaX, 500 * skalaY);
					fullscreen.setFillColor(Color::Yellow);

					Text VSync;
					VSync.setFont(font);
					VSync.setString("Synchronizacja pionowa:");
					VSync.setCharacterSize(60 * skalaY);
					VSync.setPosition(200 * skalaX, 650 * skalaY);
					VSync.setFillColor(Color::Yellow);

					Text MaxFPS;
					MaxFPS.setFont(font);
					MaxFPS.setString("Max FPS:");
					MaxFPS.setCharacterSize(60 * skalaY);
					MaxFPS.setPosition(200 * skalaX, 800 * skalaY);
					MaxFPS.setFillColor(Color::Yellow);

					string resx = to_string(resX);
					string resy = to_string(resY);
					Text rozdzielczoscw;
					rozdzielczoscw.setFont(font);
					rozdzielczoscw.setString(resx + "x" + resy);
					if (wybor_rozdzielczosc == 10)
					{
						rozdzielczoscw.setString("Niestandardowa: " + resx + "x" + resy);
					}
					rozdzielczoscw.setCharacterSize(60 * skalaY);
					rozdzielczoscw.setPosition(700 * skalaX, 350 * skalaY);
					rozdzielczoscw.setFillColor(Color(192, 192, 192, 255));

					string fullscr = "tak";
					if (fullscreeno == 0)
						fullscr = "nie";
					Text fullscreenw;
					fullscreenw.setFont(font);
					fullscreenw.setString(fullscr);
					fullscreenw.setCharacterSize(60 * skalaY);
					fullscreenw.setPosition(600 * skalaX, 500 * skalaY);
					fullscreenw.setFillColor(Color(192,192,192,255));

					string Vsync = "tak";
					if (vsync == 0)
						Vsync = "nie";
					Text VSyncw;
					VSyncw.setFont(font);
					VSyncw.setString(Vsync);
					VSyncw.setCharacterSize(60 * skalaY);
					VSyncw.setPosition(900 * skalaX, 650 * skalaY);
					VSyncw.setFillColor((Color(192, 192, 192, 255)));

					String MaxFPSwS = to_string(maxfps);
					Text MaxFPSw;
					MaxFPSw.setFont(font);
					MaxFPSw.setString(MaxFPSwS);
					if (wybor_maxfps == 7)
					{
						MaxFPSw.setString("Niestandardowa: " + maxfpst);
					}
					MaxFPSw.setCharacterSize(60 * skalaY);
					MaxFPSw.setPosition(570 * skalaX, 800 * skalaY);
					MaxFPSw.setFillColor((Color(192, 192, 192, 255)));

					Vector2f mysz(Mouse::getPosition(okno));

					if (okno.pollEvent(zdarzenie))
					{
						if (zdarzenie.type == zdarzenie.Closed) return 1;
						if (zdarzenie.type == zdarzenie.KeyPressed && zdarzenie.key.code == Keyboard::Escape)
						{
							if (resXo != resX || fullscreeno != fullscreenoriginal || vsync != vsyncoriginal || maxfps != maxfpsoriginal)
							{
								tworzyc = 1;
								cout << "ResX: " << resX << " ResY: " << resY << endl;
								plik(resX, resY, fullscreeno, maxfps, vsync, 0, 1, predkosc, przyspieszenie, maxpredkosc, tworzyc);
								MessageBox(NULL, "Uruchom ponownie program aby zobaczyc zmiany", "Uruchom ponownie", MB_OK | MB_ICONEXCLAMATION);
								return 10;
								tworzyc = 0;
								break;
							}
							break;
						}
						if (rozdzielczoscw.getGlobalBounds().contains(mysz))
						{
							if (mouse.isButtonPressed(Mouse::Left) && zdarzenie.type != Event::MouseMoved)
							{
								if (wybor_rozdzielczosc < iloscrozdzielczosci)
									wybor_rozdzielczosc++;
								else
									wybor_rozdzielczosc = 0;
							}
							if (mouse.isButtonPressed(Mouse::Right) && zdarzenie.type != Event::MouseMoved)
							{
								if (wybor_rozdzielczosc > 0)
								{
									wybor_rozdzielczosc--;
								}
								else
									wybor_rozdzielczosc = iloscrozdzielczosci;
							}
							if (wybor_rozdzielczosc == 0)
								resX = 960;
							if (wybor_rozdzielczosc == 1)
								resX = 1024;
							if (wybor_rozdzielczosc == 2)
								resX = 1280;
							if (wybor_rozdzielczosc == 3)
								resX = 1440;
							if (wybor_rozdzielczosc == 4)
								resX = 1600;
							if (wybor_rozdzielczosc == 5)
								resX = 1920;
							if (wybor_rozdzielczosc == 6)
								resX = 2560;
							if (wybor_rozdzielczosc == 7)
								resX = 3840;
							if (wybor_rozdzielczosc == 8)
								resX = 5120;
							if (wybor_rozdzielczosc == 9)
								resX = 7680;
							if (wybor_rozdzielczosc == 10)
								resX = resXt;
							resY = (resX / 16) * 9;
						}

						if (fullscreenw.getGlobalBounds().contains(mysz) && zdarzenie.type != Event::MouseMoved)
						{
							if (mouse.isButtonPressed(Mouse::Left) || mouse.isButtonPressed(Mouse::Right))
							{
								if (fullscreeno == 0)
									fullscreeno = 1;
								else fullscreeno = 0;
								zmieniono = 1;
							}
						}

						if (MaxFPSw.getGlobalBounds().contains(mysz) && zdarzenie.type != Event::MouseMoved)
						{
							if (mouse.isButtonPressed(Mouse::Left))
							{
								if (wybor_maxfps < iloscmaxfps)
									wybor_maxfps++;
								else
									wybor_maxfps = 0;
							}
							if (mouse.isButtonPressed(Mouse::Right))
							{
								if (wybor_maxfps > 0)
									wybor_maxfps--;
								else
									wybor_maxfps = iloscmaxfps;
							}
							if (wybor_maxfps == 0)
								maxfps = 30;
							if (wybor_maxfps == 1)
								maxfps = 60;
							if (wybor_maxfps == 2)
								maxfps = 75;
							if (wybor_maxfps == 3)
								maxfps = 100;
							if (wybor_maxfps == 4)
								maxfps = 120;
							if (wybor_maxfps == 5)
								maxfps = 144;
							if (wybor_maxfps == 6)
								maxfps = 240;
							if (wybor_maxfps == 7)
								maxfps = maxfpst;
						}

						if (VSyncw.getGlobalBounds().contains(mysz) && zdarzenie.type != Event::MouseMoved)
						{
							if (mouse.isButtonPressed(Mouse::Left) || mouse.isButtonPressed(Mouse::Right))
							{
								if (vsync == 0)
								{
									vsync = 1;
								}
								else
									vsync = 0;
							}
						}
					}
					//if (resXo != resX || fullscreeno != fullscreenoriginal || vsync != vsyncoriginal || maxfps != maxfpsoriginal)

					if (rozdzielczoscw.getGlobalBounds().contains(mysz))
						rozdzielczoscw.setFillColor(Color::Cyan);
					else
					{
						rozdzielczoscw.setFillColor((Color(192, 192, 192, 255)));
						if (resXo != resX)
							rozdzielczoscw.setFillColor(Color(255,50,50,255));
					}

					if (fullscreenw.getGlobalBounds().contains(mysz))
						fullscreenw.setFillColor(Color::Cyan);
					else
					{
						fullscreenw.setFillColor((Color(192, 192, 192, 255)));
						if(fullscreeno != fullscreenoriginal)
							fullscreenw.setFillColor(Color(255, 50, 50, 255));
					}

					if (MaxFPSw.getGlobalBounds().contains(mysz))
						MaxFPSw.setFillColor(Color::Cyan);
					else
					{
						MaxFPSw.setFillColor((Color(192, 192, 192, 255)));
						if (maxfps != maxfpsoriginal)
							MaxFPSw.setFillColor(Color(255, 50, 50, 255));
					}

					if (VSyncw.getGlobalBounds().contains(mysz))
						VSyncw.setFillColor(Color::Cyan);
					else
					{
						VSyncw.setFillColor((Color(192, 192, 192, 255)));
						if (vsync != vsyncoriginal)
							VSyncw.setFillColor(Color(255, 50, 50, 255));
					}
					okno.clear();
					okno.draw(rozdzielczosc);
					okno.draw(fullscreen);
					okno.draw(VSync);
					okno.draw(MaxFPS);
					okno.draw(rozdzielczoscw);
					okno.draw(fullscreenw);
					okno.draw(VSyncw);
					okno.draw(MaxFPSw);
					okno.draw(opcjen);
					okno.display();
				}
			}
		}
		else
			optionsbutton.setFillColor(Color::White);

		if (exitbutton.getGlobalBounds().contains(mysz))
		{
			exitbutton.setFillColor(Color::Blue);
			if (mouse.isButtonPressed(Mouse::Left))
			{
				return 1;
			}
		}
		else
			exitbutton.setFillColor(Color::White);

		okno.clear();
		okno.draw(logo);
		okno.draw(startbutton);
		okno.draw(optionsbutton);
		okno.draw(exitbutton);
		okno.display();
	}
}

void wyswietlwynik(unsigned long int punkty, Text & wynik, string string_wynik)
{
	string_wynik = to_string(punkty);
	string_wynik = "Punkty: " + string_wynik;
	wynik.setString(string_wynik);
}

int uziemmarchewke(Texture txt_marchewkawziemi[3], Sprite & marchewkawziemi, Sprite marchewka, short mchkolor, int ktoram)
{
	marchewkawziemi.setPosition(marchewka.getPosition().x - 26, marchewka.getPosition().y - 77);
	marchewkawziemi.setTexture(txt_marchewkawziemi[mchkolor]);
	ktoram++;
	return ktoram;
}

void zmienkolor(Sprite & grunio, Texture txt_grunio[], short & grkolor, short & mchkolor, bool wgore)
{
	if (wgore == 1)
	{
		if (grkolor < 2)
			grkolor++;
		else
			grkolor = 0;
	}
	if (wgore == 0)
	{
		if (grkolor > 0)
			grkolor--;
		else
			grkolor = 2;
	}
	grunio.setTexture(txt_grunio[grkolor]);
}

void animacjapunktownadgr(int & klatkaanimacji_punktynadgr, Text & text_punktynadgr, double maxfps, short ciag, bool & zjedzona, float grX, float grY, float skalaX, float skalaY)
{
	FloatRect spriterect = text_punktynadgr.getGlobalBounds();
	text_punktynadgr.setPosition(grX - (spriterect.width/2), grY - (spriterect.height*2));
	int dlugosc = 2;
	if (klatkaanimacji_punktynadgr <= 5.0 * dlugosc * ( maxfps/ 60 ))
		text_punktynadgr.setFillColor(Color(0, 200, 255, 255));
	if (klatkaanimacji_punktynadgr >= 5.0 * dlugosc * (maxfps / 60))
		text_punktynadgr.setFillColor(Color(0, 200, 255, 200));
	if (klatkaanimacji_punktynadgr >= 6.0 * dlugosc * (maxfps / 60))
		text_punktynadgr.setFillColor(Color(0, 200, 255, 175));
	if (klatkaanimacji_punktynadgr >= 7.0 * dlugosc * (maxfps / 60))
		text_punktynadgr.setFillColor(Color(0, 200, 255, 150));
	if (klatkaanimacji_punktynadgr >= 8.0 * dlugosc * (maxfps / 60))
		text_punktynadgr.setFillColor(Color(0, 200, 255, 125));
	if (klatkaanimacji_punktynadgr >= 9.0 * dlugosc * (maxfps / 60))
		text_punktynadgr.setFillColor(Color(0, 200, 255, 100));
	if (klatkaanimacji_punktynadgr >= 10.0 * dlugosc * (maxfps / 60))
		text_punktynadgr.setFillColor(Color(0, 200, 255, 75));
	if (klatkaanimacji_punktynadgr >= 11.0 * dlugosc * (maxfps / 60))
		text_punktynadgr.setFillColor(Color(0, 200, 255, 50));
	if (klatkaanimacji_punktynadgr >= 12.0 * dlugosc * (maxfps / 60))
		text_punktynadgr.setFillColor(Color(0, 200, 255, 25));
	if (klatkaanimacji_punktynadgr >= 13.0 * dlugosc * (maxfps / 60))
		text_punktynadgr.setFillColor(Color(0, 200, 255, 0));
	if (klatkaanimacji_punktynadgr >= 14.0 * dlugosc * (maxfps / 60))
	{
		klatkaanimacji_punktynadgr = 0;
		zjedzona = 0;
		cout << spriterect.width << endl;
	}
	text_punktynadgr.move(0, klatkaanimacji_punktynadgr * -2.0 / (maxfps / 60));
	klatkaanimacji_punktynadgr++;
}

void wyswietlzdobytepunkty(short & ciag, Text & text_punktynadgr, int & klatkaanimacji_punktynadgr, int maxfps, bool & zjedzona, float grX, float grY, float skalaX, float skalaY)
{
	int punkty = 0;
	if (ciag == 1)
		punkty = 10;
	if (ciag == 2)
		punkty = 50;
	if (ciag == 3)
		punkty = 100;
	if (ciag == 4)
		punkty = 200;
	if (ciag == 5)
		punkty = 500;
	if (ciag == 6)
		punkty = 1000;
	if (ciag == 7)
		punkty = 2000;
	if (ciag >= 8)
		punkty = 5000;
	string pkt = to_string(punkty);
	text_punktynadgr.setString(pkt);
	text_punktynadgr.setPosition(grX, grY);
	animacjapunktownadgr(klatkaanimacji_punktynadgr, text_punktynadgr, maxfps, ciag, zjedzona, grX, grY, skalaX, skalaY);
}

void dodajpunkty(unsigned long int & punkty, short & ciag)
{
	if (ciag == 0)
		punkty += 10;
	if (ciag == 1)
		punkty += 50;
	if (ciag == 2)
		punkty += 100;
	if (ciag == 3)
		punkty += 200;
	if (ciag == 4)
		punkty += 500;
	if (ciag == 5)
		punkty += 1000;
	if (ciag == 6)
		punkty += 2000;
	if (ciag >= 7)
		punkty += 5000;
	ciag++;
}

bool sprawdzczyzjedzona(Sprite & marchewka, Sprite grunio, bool & stworzona, float & marchY, float & predkoscmarchewki, float przyspieszenie, int maxprmarchewki, short grkolor, short mchkolor, unsigned long int & punkty, short & ciag)
{
	FloatRect grunioBOX = grunio.getGlobalBounds();
	FloatRect MarchewkaBOX = marchewka.getGlobalBounds();
	if (grunioBOX.intersects(MarchewkaBOX))
	{
		if (grkolor == mchkolor)
		{
			marchY = -1000;
			stworzona = 0;
			//cout << "MLEM" << endl;
			if (predkoscmarchewki < maxprmarchewki)
				predkoscmarchewki = predkoscmarchewki + przyspieszenie;
			//cout << "Predkosc marchewki: " << predkoscmarchewki << endl;
			//cout << "GRKolor: " << grkolor << " MCHKolor: " << mchkolor << endl;
			dodajpunkty(punkty, ciag);
			//cout << "Punkty: " << punkty << " Ciag: " << ciag << endl;
			return 1;
		}
	}
	return 0;
}

void pokazzycia(Sprite zycie[], int zycia, Texture & txt_zycie, Texture & txt_pusty, Text & text_zycia)
{
	//cout << "Zycia: " << zycia << endl;
	text_zycia.setString("");
	for (int i = 0; i < 5; i++)
	{
		zycie[i].setTexture(txt_pusty);
	}
	if (zycia > 5)
	{
		string ilosczyc = to_string(zycia);
		ilosczyc = ilosczyc + "x";
		text_zycia.setString(ilosczyc);
		zycie[0].setTexture(txt_zycie);
	}
	else
	{
		if (zycia == 1)
		{
			zycie[0].setTexture(txt_zycie);
		}
		if (zycia == 2)
		{
			for (int i = 0; i < 2; i++)
			{
				zycie[i].setTexture(txt_zycie);
			}
		}
		if (zycia == 3)
		{
			//cout << "ELO" << endl;
			for (int i = 0; i < 3; i++)
			{
				zycie[i].setTexture(txt_zycie);
			}
		}
		if (zycia == 4)
		{
			for (int i = 0; i < 4; i++)
			{
				zycie[i].setTexture(txt_zycie);
			}
		}
		if (zycia == 5)
		{
			for (int i = 0; i < 5; i++)
			{
				zycie[i].setTexture(txt_zycie);
			}
		}
	}
}

bool sprawdzmarchewke(Sprite & marchewka, double skalaY, bool & stworzona, float & marchY, int resY, int marchsizeY, float predkoscmarchewki, float przyspieszenie, int maxprmarchewki, short mchkolor, short grkolor, short & ciag, int & ktoram, Sprite & marchewkawziemi, Texture txt_marchewkawziemi[3], long int & zycia)
{
	if (marchY > resY - (200*skalaY) + marchsizeY)
	{
		ktoram = uziemmarchewke(txt_marchewkawziemi, marchewkawziemi, marchewka, mchkolor, ktoram);
		marchY = -1000;
		stworzona = 0;
		//cout << "Wykonano" << endl;
		if (predkoscmarchewki < maxprmarchewki)
			predkoscmarchewki = predkoscmarchewki + przyspieszenie;
		//cout << "Predkosc marchewki: " << predkoscmarchewki << endl;
		//cout << "GRKolor: " << grkolor << " MCHKolor: " << mchkolor << endl;
		ciag = 0;
		//cout << "Ciag: " << ciag << endl;
		zycia--;
		return 1;
	}
	return 0;
}

void sprawdzciag(short & ciag, long int & zycia)
{
	int wartosczanowezycie = 20;
	if (ciag >= wartosczanowezycie)
	{
		zycia++;
		ciag = 8;
	}
}

void ruszmarchewke (Sprite & marchewka, double skalaX, double skalaY, bool stworzona, float marchX, float & marchY, float predkoscmarchewki, Clock zegar, Time czas)
{
	if (stworzona == 1)
	{
		marchY = marchY + ( ( predkoscmarchewki * skalaY * czas.asMilliseconds() )  / 10  );
		marchewka.setPosition(marchX, marchY);
	}
}
void stworzmarchewke (Sprite & marchewka, double & skalaX, double & skalaY, Texture txt_marchewka[], float & grX, bool & stworzona, int & resX, float & marchX, float & marchY, float & predkoscmarchewki, short & mchkolor)
{
	short maxodstep = 1200;
	if (stworzona == 0)
	{
		while (1)
		{
			int pozX = ( rand() * 1246 ) % resX;
			int pozY = (rand() * 4212) % 200;
			if (grX - pozX < maxodstep - ( predkoscmarchewki * 50 ) && grX - pozX > -maxodstep + ( predkoscmarchewki * 50) || grX == pozX)
			{
				//cout << "POZX: " << pozX << endl;
				marchX = pozX*skalaX;
				marchY = -pozY*skalaY;
				marchewka.setPosition(marchX, marchY);
				//cout << "MarchY: " << marchY << endl;
				stworzona = 1;
				break;
			}
		}
		
		mchkolor = rand() % 3;
		marchewka.setTexture(txt_marchewka[mchkolor]);
	}
}

bool gameover(Text & text_gameover, int & klatkaanimacji_gameover, int maxfps)
{
	if (klatkaanimacji_gameover > 0 && klatkaanimacji_gameover * 80 / maxfps < 255)
		text_gameover.setFillColor(Color(255, 0, 0, klatkaanimacji_gameover * 80 / maxfps));
	if (klatkaanimacji_gameover * 80 / maxfps > 300 && klatkaanimacji_gameover * 80 / maxfps < 555)
		text_gameover.setFillColor(Color(255, 0, 0, 555 - ( klatkaanimacji_gameover * 80 / maxfps)));
	if(klatkaanimacji_gameover * 80 / maxfps < 610)
		klatkaanimacji_gameover++;
	cout << "Klatkaanimacji: " << klatkaanimacji_gameover * 80 / maxfps << endl;
	if (klatkaanimacji_gameover * 80 / maxfps > 600)
		return 1;
	else return 0;
}

bool sprawdzczyzginales(long int zycia, bool & stworzona, Sprite & grunio, Music & muzyka, int & klatkaanimacji_smierc, int maxfps, float & grY, float & grX, float & grXt, Text & text_gameover, int & klatkaanimacji_gameover, int resY)
{
	if (zycia < 0)
	{
		if (klatkaanimacji_smierc == 0)
		{
			grXt = grX;
			klatkaanimacji_smierc++;
		}
		muzyka.stop();
		stworzona = 0;
		//cout << "Zginales" << endl;
		if (klatkaanimacji_smierc > 220 * 144 / maxfps && klatkaanimacji_smierc < 400 * 144 / maxfps)
		{
			grunio.setRotation(klatkaanimacji_smierc - (220 * 144 / maxfps));
		}
		if (klatkaanimacji_smierc < 200 * 144 / maxfps && klatkaanimacji_smierc > 150 * 144 / maxfps)
		{
			grY += klatkaanimacji_smierc * -2 / maxfps;
		}
		if (klatkaanimacji_smierc > 450 * 144 / maxfps)
		{
			grY += klatkaanimacji_smierc * 3 / maxfps;
		}
		if (klatkaanimacji_smierc < 800 * 144 / maxfps && klatkaanimacji_smierc > 0)
		{
			klatkaanimacji_smierc++;
			grX = grXt;
		}
		if (klatkaanimacji_smierc >= 600 / resY * 144 / maxfps)
		{
			if (gameover(text_gameover, klatkaanimacji_gameover, maxfps) == 1)
			{
				return 1;
			}
		}
	}
}

short przyciskipauzy(Text & przycisk_pauza_wznow, Text & przycisk_pauza_restart, Text & przycisk_pauza_wyjscie, Vector2f mysz)
{
	if (przycisk_pauza_wznow.getGlobalBounds().contains(mysz))
	{
		przycisk_pauza_wznow.setFillColor(Color::Cyan);
		if (Mouse::isButtonPressed(Mouse::Left))
			return 1;
	}
	else
		przycisk_pauza_wznow.setFillColor(Color(192,192,192,255));

	if (przycisk_pauza_restart.getGlobalBounds().contains(mysz))
	{
		przycisk_pauza_restart.setFillColor(Color::Cyan);
		if (Mouse::isButtonPressed(Mouse::Left))
			return 2;
	}
	else
		przycisk_pauza_restart.setFillColor(Color(192, 192, 192, 255));

	if (przycisk_pauza_wyjscie.getGlobalBounds().contains(mysz))
	{
		przycisk_pauza_wyjscie.setFillColor(Color::Cyan);
		if (Mouse::isButtonPressed(Mouse::Left))
			return 3;
	}
	else 
		przycisk_pauza_wyjscie.setFillColor(Color(192, 192, 192, 255));

	return 0;
}

int main()
{
	srand(time(NULL));
	/* 
	default_random_engine generator;
	uniform_int_distribution<int> distribution(1, 10);
	cout << "TEST LOSOWANIA: " << distribution(generator) << endl;
	*/
	unsigned long int maxscore = 0;
	int klatkaanimacji_gameover = 0;
	int klatkaanimacji_smierc = 0;
	short odpauzowac = 0;
	long int zycia = 0;
	float grXt = 0;
	int klatkaanimacji_punktynadgr = 0;
	bool zjedzona = 0;
	bool tworzyc = 0;
	int ktoram = 0;
	short ciag = 0;
	unsigned long int punkty = 0;
	int resX = 1920;		//Rozdzielczo�� ekranu X - domy�lna warto��
	int resY = 1080;		//Rozdzielczo�� ekranu Y - domy�lna warto��
	double skalaX = resX / 1920.0;
	double skalaY = resY / 1080.0;
	bool fullscreen = 0;		//Pe�ny ekran - domy�lna warto��
	short maxfps = 60;		//Max FPS - domy�lna warto��
	bool vsync = 0;		//Synchronizacja pionowa - domy�lna warto��
	float maxprmarchewki = 9;
	float przyspieszanie = 0.25;
	float predkoscmarchewki = 3;
	float glosnosc = 50;
	float glosnoscmuzyki = 100 * (glosnosc / 100);
	float glosnoscdzwiekow = 100 * (glosnosc / 100);
	plik(resX, resY, fullscreen, maxfps, vsync, 1, 0, predkoscmarchewki, przyspieszanie, maxprmarchewki, tworzyc);
	skalaX = resX / 1920.0;
	skalaY = resY / 1080.0;
	sf::SoundBuffer plik_dzwiek_dobrze;
	plik_dzwiek_dobrze.loadFromFile("sounds/dobrze.wav");
	sf::SoundBuffer plik_dzwiek_zle;
	plik_dzwiek_zle.loadFromFile("sounds/zle.wav");
	sf::Sound dzwiek_zebraniemarchewki;
	sf::Sound dzwiek_marchewkauciekla;
	dzwiek_zebraniemarchewki.setBuffer(plik_dzwiek_dobrze);
	dzwiek_marchewkauciekla.setBuffer(plik_dzwiek_zle);
	dzwiek_zebraniemarchewki.setVolume(glosnoscdzwiekow);
	dzwiek_marchewkauciekla.setVolume(glosnoscdzwiekow);
	plikmaxscore(maxscore);
	sf::Music muzyka;
	if(!muzyka.openFromFile("sounds/muzyka.ogg"))
		MessageBox(NULL, "Nie uda�o si� wczyta� muzyki!\nUpewnij si�, �e plik muzyka.ogg jest w folderze sounds.", "Blad wczytywania muzyki!", MB_OK | MB_ICONERROR);
	muzyka.play();
	muzyka.setLoop(true);
	muzyka.setVolume(glosnoscmuzyki);
	
	RenderWindow oknoh(VideoMode(1, 1, 1),"1",Style::None);
	switch (menu(resX, resY, fullscreen, skalaY, skalaX, fullscreen, vsync, maxfps, predkoscmarchewki, przyspieszanie, maxprmarchewki, tworzyc))
	{
	case 1:
	{
		return 0;
		break;
	}
	case 2:
	{
		MessageBox(NULL, "Nie uda�o si� wczyta� czcionki!\nUpewnij si�, �e plik arial.ttf jest w g��wnym folderze gry.", "Blad wczytywania czcionki!", MB_OK | MB_ICONERROR);
		return 3;
		break;
	}
	case 3:
	{
		oknoh.close();
		break;
	}
	case 10:
	{
		oknoh.close();
		return 2;
	}
	}
	oknoh.close();
	skalaX = resX / 1920.0;
	skalaY = resY / 1080.0;
	bool pause = 0;
	short mchkolor = 0;
	short grkolor = 0;
	bool stworzona = 0;		//czy marchewka jest ju� stworzona?
	short grsizeX = 96;		//Szeroko�� tekstury grunia w px
	short grsizeY = 68;		//Wysoko�� tekstury grunia w px
	short marchsizeX = 52;		//Szeroko�� tekstury marchewki w px
	short marchsizeY = 77;		//Wysoko�� tekstury marchewki w px
	float predkoscgr = 1;		//Pr�dko�� grunia ( domyslnie 1 )
	Clock zegar;
	Time czas;
	Sprite grunio;
	Sprite marchewka;
	Sprite tlo;
	Sprite pauza;
	Sprite zycie[5];
	Sprite marchewkawziemi[1000];
	Texture txt_pusty;
	Texture txt_marchewkawziemi[3];
	Texture txt_tlo;
	Texture txt_marchewka[3];
	Texture txt_grunio[3];
	Texture txt_pauza;
	Texture txt_zycie;
	Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		MessageBox(NULL, "Nie uda�o si� wczyta� czcionki!\nUpewnij si�, �e plik arial.ttf jest w g��wnym folderze gry.", "Blad wczytywania czcionki!", MB_OK | MB_ICONERROR);
		return 3;
	}
	RenderWindow okno(VideoMode(resX, resY, 32), "Gruniozerca");
	if (fullscreen == 1)
	{
		okno.create(VideoMode(resX, resY, 32), "Gruniozerca", Style::Fullscreen);
	}

	Text text_punktynadgr;
	text_punktynadgr.setFont(font);
	text_punktynadgr.setCharacterSize(50*skalaY);
	text_punktynadgr.setStyle(Text::Bold);

	Text text_gameover;
	text_gameover.setFont(font);
	text_gameover.setCharacterSize(150 * skalaY);
	text_gameover.setStyle(Text::Bold);
	text_gameover.setString("GAME OVER!");
	text_gameover.setFillColor(Color(255, 0, 0, 0));
	wycentrujtext(text_gameover, resX, resY, skalaY, 0);

	Text text_zycia;
	FloatRect rect_textzycia = text_zycia.getGlobalBounds();
	text_zycia.setFont(font);
	text_zycia.setCharacterSize(50*skalaY);
	text_zycia.setStyle(Text::Bold);
	text_zycia.setOrigin(rect_textzycia.left + rect_textzycia.width, rect_textzycia.top + rect_textzycia.height);
	string string_text_zycia = to_string(zycia);
	int znaki = string_text_zycia.size();
	text_zycia.setPosition(resX - 220 - (znaki*(50 * skalaY)), 0);

	Text przycisk_pauza_wyjscie;
	Text przycisk_pauza_restart;
	Text przycisk_pauza_wznow;
	Text wynik;
	
	wynik.setCharacterSize(50 * skalaY);
	wynik.setFont(font);
	wynik.setPosition(0, 0);
	wynik.setStyle(Text::Italic);
	wynik.setStyle(Text::Bold);

	string string_wynik;

	grunio.setOrigin(grsizeX / 2, grsizeY / 2);
	float grX = resX / 2;
	float grY = resY - 220;
	float marchX = 0;
	float marchY = 0;
	txt_tlo.loadFromFile("images/tlo.png");
	txt_marchewka[0].loadFromFile("images/marchewka_cz.png");
	txt_marchewka[1].loadFromFile("images/marchewka_zi.png");
	txt_marchewka[2].loadFromFile("images/marchewka_ni.png");
	txt_grunio[0].loadFromFile("images/grunio_cz.png");
	txt_grunio[1].loadFromFile("images/grunio_zi.png");
	txt_grunio[2].loadFromFile("images/grunio_ni.png");
	txt_pauza.loadFromFile("images/pauza.png");
	txt_marchewkawziemi[0].loadFromFile("images/marchewkawziemi_cz.png");
	txt_marchewkawziemi[1].loadFromFile("images/marchewkawziemi_zi.png");
	txt_marchewkawziemi[2].loadFromFile("images/marchewkawziemi_ni.png");
	txt_zycie.loadFromFile("images/zycie.png");
	txt_pusty.loadFromFile("images/pusty.png");
	for (int i = 0; i < 5; i++)
	{
		zycie[i].setTexture(txt_zycie);
		zycie[i].setPosition(resX - ((105 + 5)*(i + 1)*skalaX),0);
		zycie[i].setScale(skalaX / 1.5, skalaY / 1.5);
	}
	pauza.setTexture(txt_pauza);
	tlo.setTexture(txt_tlo);
	grunio.setTexture(txt_grunio[0]);
	grunio.setPosition(grX, grY);
	//cout << "SkalaY: " << skalaY << endl;

	string string_pauza_wznow = "Wznow";
	string string_pauza_restart = "Restart";
	string string_pauza_wyjscie = "Wyjscie";

	przycisk_pauza_wyjscie.setString(string_pauza_wyjscie);
	przycisk_pauza_restart.setString(string_pauza_restart);
	przycisk_pauza_wznow.setString(string_pauza_wznow);

	przycisk_pauza_wyjscie.setFont(font);
	przycisk_pauza_restart.setFont(font);
	przycisk_pauza_wznow.setFont(font);

	przycisk_pauza_wyjscie.setCharacterSize(150 * skalaY); // Ustalanie
	przycisk_pauza_restart.setCharacterSize(150 * skalaY); // rozmiaru czcionki
	przycisk_pauza_wznow.setCharacterSize(150 * skalaY); // napis�w w menu opcji

	wycentrujtext(przycisk_pauza_wyjscie, resX, resY, skalaY, 300);
	wycentrujtext(przycisk_pauza_restart, resX, resY, skalaY, 0);
	wycentrujtext(przycisk_pauza_wznow, resX, resY, skalaY, -300);

	przycisk_pauza_wyjscie.setScale(skalaX, skalaY);
	przycisk_pauza_restart.setScale(skalaX, skalaY);
	przycisk_pauza_wznow.setScale(skalaX, skalaY);

	przycisk_pauza_wyjscie.setFillColor(Color::Yellow);
	przycisk_pauza_restart.setFillColor(Color::Yellow);
	przycisk_pauza_wznow.setFillColor(Color::Yellow);

	tlo.setOrigin(0, 1080);
	tlo.setPosition(0, resY);
	marchewka.setOrigin(marchsizeX / 2, marchsizeY);
	plik(resX, resY, fullscreen, maxfps, vsync, 0, 1, predkoscmarchewki, przyspieszanie, maxprmarchewki, tworzyc);
	grunio.setScale(skalaX, skalaX);
	marchewka.setScale(skalaX, skalaX);
	wycentrujsprite(pauza, resX, resY, skalaY, skalaX, 0);
	pauza.setScale(skalaX, skalaX);
	tlo.setScale(skalaX, skalaX);
	okno.setVerticalSyncEnabled(vsync);
	okno.setFramerateLimit(maxfps);
	przyspieszanie = przyspieszanie * skalaY;
	grY = grY + (220 - (220 * skalaY));
	//cout << "SkalaX: " << skalaX << endl;
	//cout << "SkalaY: " << skalaY << endl;
	while (okno.isOpen())
	{
		czas = zegar.getElapsedTime();
		Vector2f mysz(Mouse::getPosition(okno));
		//rect_textzycia = text_zycia.getGlobalBounds();
		//text_zycia.setPosition(resX - (220 + (rect_textzycia.width/2)), 0);
		//cout << "RESX: " << resx << " RESY: " << resy << " FULLSCREEN: " << fullscreen << endl;
		Event zdarzenie;
		if (okno.pollEvent(zdarzenie))
		{
			if (zdarzenie.type == zdarzenie.Closed) okno.close();
			if (zdarzenie.type == zdarzenie.KeyPressed && zdarzenie.key.code == Keyboard::Escape)
			{
				if (pause == 0)
				{
					pause = 1;
					muzyka.pause();
				}
				else
				{
					pause = 0;
					muzyka.play();
				}
					
			}
			//if (zdarzenie.type == zdarzenie.KeyPressed && zdarzenie.key.code == Keyboard::U)
				//zycia++;
			//if (zdarzenie.type == zdarzenie.KeyPressed && zdarzenie.key.code == Keyboard::J)
				//zycia--;
			//if (zdarzenie.type == zdarzenie.KeyPressed && zdarzenie.key.code == Keyboard::E)
			//{
			//	if (obrocony == 0)
			//	{
			//		grunio.setScale({ -1,1 });
			//		obrocony = 1;
			//	}
			//	else
			//	{
			//		grunio.setScale({ 1, 1 });
			//		obrocony = 0;
			//	}
			//}
			//if (zdarzenie.type == zdarzenie.KeyPressed && zdarzenie.key.code == Keyboard::E)
			//{
			//	stworzona = 0;
			//	stworzmarchewke(marchewka, skalaX, skalaY, txt_marchewka, grX, stworzona, resX, marchX, marchY);
			//}
			if (pause == 0)
			{
				if (zdarzenie.type == zdarzenie.KeyPressed && zdarzenie.key.code == Keyboard::E)
				{
					zmienkolor(grunio, txt_grunio, grkolor, mchkolor, 1);
					//cout << "GRKolor: " << grkolor << " MCHKolor: " << mchkolor << endl;
				}
				if (zdarzenie.type == zdarzenie.KeyPressed && zdarzenie.key.code == Keyboard::R)
				{
					zmienkolor(grunio, txt_grunio, grkolor, mchkolor, 0);
					//cout << "GRKolor: " << grkolor << " MCHKolor: " << mchkolor << endl;
				}
			}
		}
		string_text_zycia = to_string(zycia);
		znaki = string_text_zycia.size();
		//cout << "Znaki: " << znaki << endl;
		text_zycia.setPosition(resX - 110 - ((znaki+1)*(29 * skalaY)), 0);
		if (pause == 0)
		{
			if (Keyboard::isKeyPressed(Keyboard::Right))
			{
				grunio.setScale(skalaX, skalaY);
				grX = grX + (predkoscgr*czas.asMilliseconds());
				//grunio.move(Vector2f(predkoscgr*czas.asMilliseconds(),0));
			}
			if (Keyboard::isKeyPressed(Keyboard::Left))
			{
				grunio.setScale(-skalaX, skalaY);
				grX = grX - (predkoscgr*czas.asMilliseconds());
				//grunio.move(Vector2f(-predkoscgr*czas.asMilliseconds(),0));
			}
		}
		//cout << czas.asMilliseconds() * maxfps << endl;
		//czas = zegar.getElapsedTime();
		//cout << 1.0f/czas.asSeconds() << endl;
		//zegar.restart().asSeconds();
		zegar.restart().asSeconds();
		//cout << "GrunioY: " << grY << endl;
		if (grX < 0+(grsizeX/2)*skalaX) grX = 0+(grsizeX/2)*skalaX;
		if (grX > resX-(grsizeX/2*skalaX)) grX = resX-(grsizeX/2*skalaX);
		if (pause == 0)
		{
			stworzmarchewke(marchewka, skalaX, skalaY, txt_marchewka, grX, stworzona, resX, marchX, marchY, predkoscmarchewki, mchkolor);
			if (sprawdzczyzjedzona(marchewka, grunio, stworzona, marchY, predkoscmarchewki, przyspieszanie, maxprmarchewki, grkolor, mchkolor, punkty, ciag))
			{
				zjedzona = 1;
				dzwiek_zebraniemarchewki.play();
				grXt = grX;
			}
			if (sprawdzmarchewke(marchewka, skalaY, stworzona, marchY, resY, marchsizeY, predkoscmarchewki, przyspieszanie, maxprmarchewki, mchkolor, grkolor, ciag, ktoram, marchewkawziemi[ktoram], txt_marchewkawziemi, zycia))
				dzwiek_marchewkauciekla.play();
			ruszmarchewke(marchewka, skalaX, skalaY, stworzona, marchX, marchY, predkoscmarchewki, zegar, czas);
			if (zjedzona == 1)
			{
				wyswietlzdobytepunkty(ciag, text_punktynadgr, klatkaanimacji_punktynadgr, maxfps, zjedzona, grXt, grY, skalaX, skalaY);
			}
			pokazzycia(zycie, zycia, txt_zycie, txt_pusty, text_zycia);
			sprawdzciag(ciag, zycia);
			if (sprawdzczyzginales(zycia, stworzona, grunio, muzyka, klatkaanimacji_smierc, maxfps, grY, grX, grXt, text_gameover, klatkaanimacji_gameover, resY) == 1)
			{
				if (punkty > maxscore)
				{
					ofstream plikmscore;
					plikmscore.open("images/wynik.png");
					plikmscore << punkty;
					plikmscore.close();
				}
				grX = resX / 2;
				grunio.setRotation(0);
				grY = resY - 220;
				grY = grY + (220 - (220 * skalaY));
				punkty = 0;
				ciag = 0;
				zycia = 3;
				stworzona = 0;
				pause = 0;
				muzyka.play();
				klatkaanimacji_gameover = 0;
				klatkaanimacji_smierc = 0;
				klatkaanimacji_punktynadgr = 0;
			}
		}
		//cout << "MarchY: " << marchY << endl;
		//cout << "MarchX: " << marchX << " MarchY: " << marchY << " Stworzona: " << stworzona << " Predkoscmarchewki: " << predkoscmarchewki << endl;
		grunio.setPosition(grX, grY);
		wyswietlwynik(punkty, wynik, string_wynik);
		if (pause == 1)
		{
			odpauzowac = przyciskipauzy(przycisk_pauza_wznow, przycisk_pauza_restart, przycisk_pauza_wyjscie, mysz);
			if (odpauzowac == 1)
			{
				pause = 0;
				muzyka.play();
				odpauzowac = 0;
			}
			if (odpauzowac == 2)
			{
				grX = resX / 2;
				punkty = 0;
				ciag = 0;
				zycia = 3;
				stworzona = 0;
				pause = 0;
				muzyka.play();
				odpauzowac = 0;
			}
			if (odpauzowac == 3)
			{
				return 0;
			}
		}
		okno.clear(Color(0,0,0));
		okno.draw(tlo);
		okno.draw(grunio);
		okno.draw(marchewka);
		okno.draw(text_punktynadgr);
		okno.draw(text_zycia);
		okno.draw(text_gameover);
		for (int i = 0; i < 5; i++)
		{
			okno.draw(zycie[i]);
		}
		okno.draw(wynik);
		for (int i = 0; i <= ktoram; i++)
		{
			okno.draw(marchewkawziemi[i]);
		}
		if (pause == 1)
		{
			okno.draw(pauza);
			okno.draw(przycisk_pauza_wznow);
			okno.draw(przycisk_pauza_restart);
			okno.draw(przycisk_pauza_wyjscie);
		}
		okno.display();
	}
	return 0;
}