#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include <iostream>
#include <string>


using namespace std;

/** \brief Pole
* - Struktura przechowujaca informacje o polu na planszy gry: znak - okresla rodzaj pola przy wyswietlaniu (np baza gracza, sciezka, puste pole); kolor, numer - okreslaja jakiego koloru i ktory numer ma pionek stojacy na danym polu (jesli pole jest zajete); grafika - przechowuje odpowiednia grafike uzywana przy wyswietlaniu.*/
struct Pole
{
        char znak;
        int kolor;
        int numer;
        sf::Sprite grafika;
};
/** \brief Pionek
* - Struktura przechowujaca informacje o pionku: miejsce - przechowuje liczbe okreslajaca w ktorym miejscu swojej trasy jest pionek (od 0 do 44); grafika - przechowuje odpowiednia grafike uzywana przy wyswietlaniu.*/
struct Pionek
{
        int miejsce;
        sf::Sprite grafika;
};

Pole pole[11][11];
Pionek pionek[4][4];
int gracz;
int kosc;
int tak_nie[4]={0,0,0,0};
int wybrany;
int ilosc_graczy=0;
int tryb=1;
int skok_czasu;

int wyzwalacz_tura=0;
int wyzwalacz_kostka=0;

string tekst;
Pole *trasa[4][4][45]={
                    {

                    {&pole[0][0], &pole[4][0], &pole[4][1], &pole[4][2], &pole[4][3], &pole[4][4], &pole[3][4], &pole[2][4], &pole[1][4], &pole[0][4], &pole[0][5], &pole[0][6],
                    &pole[1][6], &pole[2][6], &pole[3][6], &pole[4][6], &pole[4][7], &pole[4][8], &pole[4][9], &pole[4][10],&pole[5][10],&pole[6][10],&pole[6][9], &pole[6][8],
                    &pole[6][7], &pole[6][6], &pole[7][6], &pole[8][6], &pole[9][6], &pole[10][6],&pole[10][5],&pole[10][4],&pole[9][4], &pole[8][4], &pole[7][4], &pole[6][4],
                    &pole[6][3], &pole[6][2], &pole[6][1], &pole[6][0], &pole[5][0], &pole[5][1], &pole[5][2], &pole[5][3], &pole[5][4]},

                    {&pole[0][1], &pole[4][0], &pole[4][1], &pole[4][2], &pole[4][3], &pole[4][4], &pole[3][4], &pole[2][4], &pole[1][4], &pole[0][4], &pole[0][5], &pole[0][6],
                    &pole[1][6], &pole[2][6], &pole[3][6], &pole[4][6], &pole[4][7], &pole[4][8], &pole[4][9], &pole[4][10],&pole[5][10],&pole[6][10],&pole[6][9], &pole[6][8],
                    &pole[6][7], &pole[6][6], &pole[7][6], &pole[8][6], &pole[9][6], &pole[10][6],&pole[10][5],&pole[10][4],&pole[9][4], &pole[8][4], &pole[7][4], &pole[6][4],
                    &pole[6][3], &pole[6][2], &pole[6][1], &pole[6][0], &pole[5][0], &pole[5][1], &pole[5][2], &pole[5][3], &pole[5][4]},

                    {&pole[1][0], &pole[4][0], &pole[4][1], &pole[4][2], &pole[4][3], &pole[4][4], &pole[3][4], &pole[2][4], &pole[1][4], &pole[0][4], &pole[0][5], &pole[0][6],
                    &pole[1][6], &pole[2][6], &pole[3][6], &pole[4][6], &pole[4][7], &pole[4][8], &pole[4][9], &pole[4][10],&pole[5][10],&pole[6][10],&pole[6][9], &pole[6][8],
                    &pole[6][7], &pole[6][6], &pole[7][6], &pole[8][6], &pole[9][6], &pole[10][6],&pole[10][5],&pole[10][4],&pole[9][4], &pole[8][4], &pole[7][4], &pole[6][4],
                    &pole[6][3], &pole[6][2], &pole[6][1], &pole[6][0], &pole[5][0], &pole[5][1], &pole[5][2], &pole[5][3], &pole[5][4]},

                    {&pole[1][1], &pole[4][0], &pole[4][1], &pole[4][2], &pole[4][3], &pole[4][4], &pole[3][4], &pole[2][4], &pole[1][4], &pole[0][4], &pole[0][5], &pole[0][6],
                    &pole[1][6], &pole[2][6], &pole[3][6], &pole[4][6], &pole[4][7], &pole[4][8], &pole[4][9], &pole[4][10],&pole[5][10],&pole[6][10],&pole[6][9], &pole[6][8],
                    &pole[6][7], &pole[6][6], &pole[7][6], &pole[8][6], &pole[9][6], &pole[10][6],&pole[10][5],&pole[10][4],&pole[9][4], &pole[8][4], &pole[7][4], &pole[6][4],
                    &pole[6][3], &pole[6][2], &pole[6][1], &pole[6][0], &pole[5][0], &pole[5][1], &pole[5][2], &pole[5][3], &pole[5][4]}

                    },

                    {

                    {&pole[0][9], &pole[0][6], &pole[1][6], &pole[2][6], &pole[3][6], &pole[4][6], &pole[4][7], &pole[4][8], &pole[4][9], &pole[4][10],&pole[5][10],&pole[6][10],
                    &pole[6][9], &pole[6][8], &pole[6][7], &pole[6][6], &pole[7][6], &pole[8][6], &pole[9][6], &pole[10][6],&pole[10][5],&pole[10][4],&pole[9][4], &pole[8][4],
                    &pole[7][4], &pole[6][4], &pole[6][3], &pole[6][2], &pole[6][1], &pole[6][0], &pole[5][0], &pole[4][0], &pole[4][1], &pole[4][2], &pole[4][3], &pole[4][4],
                    &pole[3][4], &pole[2][4], &pole[1][4], &pole[0][4], &pole[0][5], &pole[1][5], &pole[2][5], &pole[3][5], &pole[4][5]},

                    {&pole[0][10], &pole[0][6], &pole[1][6], &pole[2][6], &pole[3][6], &pole[4][6], &pole[4][7], &pole[4][8], &pole[4][9], &pole[4][10],&pole[5][10],&pole[6][10],
                    &pole[6][9], &pole[6][8], &pole[6][7], &pole[6][6], &pole[7][6], &pole[8][6], &pole[9][6], &pole[10][6],&pole[10][5],&pole[10][4],&pole[9][4], &pole[8][4],
                    &pole[7][4], &pole[6][4], &pole[6][3], &pole[6][2], &pole[6][1], &pole[6][0], &pole[5][0], &pole[4][0], &pole[4][1], &pole[4][2], &pole[4][3], &pole[4][4],
                    &pole[3][4], &pole[2][4], &pole[1][4], &pole[0][4], &pole[0][5], &pole[1][5], &pole[2][5], &pole[3][5], &pole[4][5]},

                    {&pole[1][9], &pole[0][6], &pole[1][6], &pole[2][6], &pole[3][6], &pole[4][6], &pole[4][7], &pole[4][8], &pole[4][9], &pole[4][10],&pole[5][10],&pole[6][10],
                    &pole[6][9], &pole[6][8], &pole[6][7], &pole[6][6], &pole[7][6], &pole[8][6], &pole[9][6], &pole[10][6],&pole[10][5],&pole[10][4],&pole[9][4], &pole[8][4],
                    &pole[7][4], &pole[6][4], &pole[6][3], &pole[6][2], &pole[6][1], &pole[6][0], &pole[5][0], &pole[4][0], &pole[4][1], &pole[4][2], &pole[4][3], &pole[4][4],
                    &pole[3][4], &pole[2][4], &pole[1][4], &pole[0][4], &pole[0][5], &pole[1][5], &pole[2][5], &pole[3][5], &pole[4][5]},

                    {&pole[1][10], &pole[0][6], &pole[1][6], &pole[2][6], &pole[3][6], &pole[4][6], &pole[4][7], &pole[4][8], &pole[4][9], &pole[4][10],&pole[5][10],&pole[6][10],
                    &pole[6][9], &pole[6][8], &pole[6][7], &pole[6][6], &pole[7][6], &pole[8][6], &pole[9][6], &pole[10][6],&pole[10][5],&pole[10][4],&pole[9][4], &pole[8][4],
                    &pole[7][4], &pole[6][4], &pole[6][3], &pole[6][2], &pole[6][1], &pole[6][0], &pole[5][0], &pole[4][0], &pole[4][1], &pole[4][2], &pole[4][3], &pole[4][4],
                    &pole[3][4], &pole[2][4], &pole[1][4], &pole[0][4], &pole[0][5], &pole[1][5], &pole[2][5], &pole[3][5], &pole[4][5]}

                    },

                    {

                    {&pole[9][9], &pole[6][10],&pole[6][9], &pole[6][8], &pole[6][7], &pole[6][6], &pole[7][6], &pole[8][6], &pole[9][6], &pole[10][6],&pole[10][5],&pole[10][4],
                    &pole[9][4], &pole[8][4], &pole[7][4], &pole[6][4], &pole[6][3], &pole[6][2], &pole[6][1], &pole[6][0], &pole[5][0], &pole[4][0], &pole[4][1], &pole[4][2],
                    &pole[4][3], &pole[4][4], &pole[3][4], &pole[2][4], &pole[1][4], &pole[0][4], &pole[0][5], &pole[0][6], &pole[1][6], &pole[2][6], &pole[3][6], &pole[4][6],
                    &pole[4][7], &pole[4][8], &pole[4][9], &pole[4][10],&pole[5][10],&pole[5][9], &pole[5][8], &pole[5][7], &pole[5][6]},

                    {&pole[9][10], &pole[6][10],&pole[6][9], &pole[6][8], &pole[6][7], &pole[6][6], &pole[7][6], &pole[8][6], &pole[9][6], &pole[10][6],&pole[10][5],&pole[10][4],
                    &pole[9][4], &pole[8][4], &pole[7][4], &pole[6][4], &pole[6][3], &pole[6][2], &pole[6][1], &pole[6][0], &pole[5][0], &pole[4][0], &pole[4][1], &pole[4][2],
                    &pole[4][3], &pole[4][4], &pole[3][4], &pole[2][4], &pole[1][4], &pole[0][4], &pole[0][5], &pole[0][6], &pole[1][6], &pole[2][6], &pole[3][6], &pole[4][6],
                    &pole[4][7], &pole[4][8], &pole[4][9], &pole[4][10],&pole[5][10],&pole[5][9], &pole[5][8], &pole[5][7], &pole[5][6]},

                    {&pole[10][9], &pole[6][10],&pole[6][9], &pole[6][8], &pole[6][7], &pole[6][6], &pole[7][6], &pole[8][6], &pole[9][6], &pole[10][6],&pole[10][5],&pole[10][4],
                    &pole[9][4], &pole[8][4], &pole[7][4], &pole[6][4], &pole[6][3], &pole[6][2], &pole[6][1], &pole[6][0], &pole[5][0], &pole[4][0], &pole[4][1], &pole[4][2],
                    &pole[4][3], &pole[4][4], &pole[3][4], &pole[2][4], &pole[1][4], &pole[0][4], &pole[0][5], &pole[0][6], &pole[1][6], &pole[2][6], &pole[3][6], &pole[4][6],
                    &pole[4][7], &pole[4][8], &pole[4][9], &pole[4][10],&pole[5][10],&pole[5][9], &pole[5][8], &pole[5][7], &pole[5][6]},

                    {&pole[10][10], &pole[6][10],&pole[6][9], &pole[6][8], &pole[6][7], &pole[6][6], &pole[7][6], &pole[8][6], &pole[9][6], &pole[10][6],&pole[10][5],&pole[10][4],
                    &pole[9][4], &pole[8][4], &pole[7][4], &pole[6][4], &pole[6][3], &pole[6][2], &pole[6][1], &pole[6][0], &pole[5][0], &pole[4][0], &pole[4][1], &pole[4][2],
                    &pole[4][3], &pole[4][4], &pole[3][4], &pole[2][4], &pole[1][4], &pole[0][4], &pole[0][5], &pole[0][6], &pole[1][6], &pole[2][6], &pole[3][6], &pole[4][6],
                    &pole[4][7], &pole[4][8], &pole[4][9], &pole[4][10],&pole[5][10],&pole[5][9], &pole[5][8], &pole[5][7], &pole[5][6]}

                    },

                    {

                    {&pole[9][0], &pole[10][4],&pole[9][4], &pole[8][4], &pole[7][4], &pole[6][4], &pole[6][3], &pole[6][2], &pole[6][1], &pole[6][0], &pole[5][0], &pole[4][0],
                    &pole[4][1], &pole[4][2], &pole[4][3], &pole[4][4], &pole[3][4], &pole[2][4], &pole[1][4], &pole[0][4], &pole[0][5], &pole[0][6], &pole[1][6], &pole[2][6],
                    &pole[3][6], &pole[4][6], &pole[4][7], &pole[4][8], &pole[4][9], &pole[4][10],&pole[5][10],&pole[6][10],&pole[6][9], &pole[6][8], &pole[6][7], &pole[6][6],
                    &pole[7][6], &pole[8][6], &pole[9][6], &pole[10][6],&pole[10][5],&pole[9][5], &pole[8][5], &pole[7][5], &pole[6][5]},

                    {&pole[9][1], &pole[10][4],&pole[9][4], &pole[8][4], &pole[7][4], &pole[6][4], &pole[6][3], &pole[6][2], &pole[6][1], &pole[6][0], &pole[5][0], &pole[4][0],
                    &pole[4][1], &pole[4][2], &pole[4][3], &pole[4][4], &pole[3][4], &pole[2][4], &pole[1][4], &pole[0][4], &pole[0][5], &pole[0][6], &pole[1][6], &pole[2][6],
                    &pole[3][6], &pole[4][6], &pole[4][7], &pole[4][8], &pole[4][9], &pole[4][10],&pole[5][10],&pole[6][10],&pole[6][9], &pole[6][8], &pole[6][7], &pole[6][6],
                    &pole[7][6], &pole[8][6], &pole[9][6], &pole[10][6],&pole[10][5],&pole[9][5], &pole[8][5], &pole[7][5], &pole[6][5]},

                    {&pole[10][0], &pole[10][4],&pole[9][4], &pole[8][4], &pole[7][4], &pole[6][4], &pole[6][3], &pole[6][2], &pole[6][1], &pole[6][0], &pole[5][0], &pole[4][0],
                    &pole[4][1], &pole[4][2], &pole[4][3], &pole[4][4], &pole[3][4], &pole[2][4], &pole[1][4], &pole[0][4], &pole[0][5], &pole[0][6], &pole[1][6], &pole[2][6],
                    &pole[3][6], &pole[4][6], &pole[4][7], &pole[4][8], &pole[4][9], &pole[4][10],&pole[5][10],&pole[6][10],&pole[6][9], &pole[6][8], &pole[6][7], &pole[6][6],
                    &pole[7][6], &pole[8][6], &pole[9][6], &pole[10][6],&pole[10][5],&pole[9][5], &pole[8][5], &pole[7][5], &pole[6][5]},

                    {&pole[10][1], &pole[10][4],&pole[9][4], &pole[8][4], &pole[7][4], &pole[6][4], &pole[6][3], &pole[6][2], &pole[6][1], &pole[6][0], &pole[5][0], &pole[4][0],
                    &pole[4][1], &pole[4][2], &pole[4][3], &pole[4][4], &pole[3][4], &pole[2][4], &pole[1][4], &pole[0][4], &pole[0][5], &pole[0][6], &pole[1][6], &pole[2][6],
                    &pole[3][6], &pole[4][6], &pole[4][7], &pole[4][8], &pole[4][9], &pole[4][10],&pole[5][10],&pole[6][10],&pole[6][9], &pole[6][8], &pole[6][7], &pole[6][6],
                    &pole[7][6], &pole[8][6], &pole[9][6], &pole[10][6],&pole[10][5],&pole[9][5], &pole[8][5], &pole[7][5], &pole[6][5]}

                    }

    };

sf::Texture tlo;
sf::Sprite grafika_tlo;
sf::Texture pole0;
sf::Texture pole1;
sf::Texture pole2;
sf::Texture pole3;
sf::Texture pole4;
sf::Texture pionek1;
sf::Texture pionek2;
sf::Texture pionek3;
sf::Texture pionek4;
sf::RenderWindow oknoAplikacji(sf::VideoMode(1280,720,32),"Chinczyk - by Adam Furmanek & Tomasz Gebski");
sf::Event event;
sf::Font MojFont;
sf::Text Tekst;

sf::Music zbicie;
sf::Music skok;
sf::Music menu;
sf::Music rozgrywka;
sf::Music klaskanie;

/** \brief inicjacja
* - Funkcja inicjujaca zmienne i struktury. Okresla rodzaj kazdego pola czyli "rysuje mape". Laduje elementy graficzne w formacie .png oraz audio w formacie .wav. Funkcja uruchamia sie tylko raz na poczatku programu.*/
void inicjacja()
{
    srand(time(NULL));
    oknoAplikacji.setFramerateLimit(120);
    char mapa[11][11]={
    {'1',  '1',  ' ',  ' ',  'l',  'k',  '2',  ' ',  ' ',  '2',  '2'},
    {'1',  '1',  ' ',  ' ',  'k',  '2',  'k',  ' ',  ' ',  '2',  '2'},
    {' ',  ' ',  ' ',  ' ',  'l',  '2',  'l',  ' ',  ' ',  ' ',  ' '},
    {' ',  ' ',  ' ',  ' ',  'k',  '2',  'k',  ' ',  ' ',  ' ',  ' '},
    {'1',  'k',  'l',  'k',  'l',  '2',  'l',  'k',  'l',  'k',  'l'},
    {'k',  '1',  '1',  '1',  '1',  ' ',  '3',  '3',  '3',  '3',  'k'},
    {'l',  'k',  'l',  'k',  'l',  '4',  'l',  'k',  'l',  'k',  '3'},
    {' ',  ' ',  ' ',  ' ',  'k',  '4',  'k',  ' ',  ' ',  ' ',  ' '},
    {' ',  ' ',  ' ',  ' ',  'l',  '4',  'l',  ' ',  ' ',  ' ',  ' '},
    {'4',  '4',  ' ',  ' ',  'k',  '4',  'k',  ' ',  ' ',  '3',  '3'},
    {'4',  '4',  ' ',  ' ',  '4',  'k',  'l',  ' ',  ' ',  '3',  '3'},
    };

    pole0.loadFromFile("pole0.png");
    pole1.loadFromFile("pole1.png");
    pole2.loadFromFile("pole2.png");
    pole3.loadFromFile("pole3.png");
    pole4.loadFromFile("pole4.png");

    for(int i=0;i<11;i++)
        for(int j=0;j<11;j++){
            pole[i][j].znak=mapa[i][j];

            if(pole[i][j].znak=='1')
                pole[i][j].grafika.setTexture(pole1);
            if(pole[i][j].znak=='2')
                pole[i][j].grafika.setTexture(pole2);
            if(pole[i][j].znak=='3')
                pole[i][j].grafika.setTexture(pole3);
            if(pole[i][j].znak=='4')
                pole[i][j].grafika.setTexture(pole4);
            if(pole[i][j].znak=='k'||pole[i][j].znak=='l')
                pole[i][j].grafika.setTexture(pole0);

            pole[i][j].grafika.setPosition(j*(oknoAplikacji.getSize().x)/26+(oknoAplikacji.getSize().x)/8,i*(oknoAplikacji.getSize().y)/13+(oknoAplikacji.getSize().x)/22);
            pole[i][j].grafika.setScale( 0.32, 0.32 );
       }

    pionek1.loadFromFile("pionek1.png");
    pionek2.loadFromFile("pionek2.png");
    pionek3.loadFromFile("pionek3.png");
    pionek4.loadFromFile("pionek4.png");

    for(int i=0;i<4;i++){
            pionek[0][i].grafika.setTexture(pionek1);
            pionek[1][i].grafika.setTexture(pionek2);
            pionek[2][i].grafika.setTexture(pionek3);
            pionek[3][i].grafika.setTexture(pionek4);

        for(int j=0;j<4;j++){
            pionek[i][j].grafika.setScale( 0.32, 0.32 );
        }
    }
    MojFont.loadFromFile("kwadryga.ttf");
    Tekst.setFont(MojFont);
    Tekst.setColor(sf::Color::Black);
    Tekst.setPosition(830,100);

    tlo.loadFromFile("tlo.jpg");
    grafika_tlo.setTexture(tlo);

    zbicie.openFromFile("zbicie.wav");
    skok.openFromFile("skok.wav");
    menu.openFromFile("menu.wav");
    menu.setLoop(1);
    klaskanie.openFromFile("klaskanie.wav");
}

/** \brief reset
* - Funkcja resetujaca poczatkowe ustawienia pionkow i graczy. Wywoluje sie przy uruchomieniu nowej gry.*/
void reset()
{
    gracz=4;
    tak_nie[0]=tak_nie[1]=tak_nie[2]=tak_nie[3]=0;

    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            pionek[i][j].miejsce=0;

    for(int i=0;i<11;i++)
        for(int j=0;j<11;j++){
            pole[i][j].kolor=0;
            pole[i][j].numer=0;
        }

    pole[0][0].kolor=1; pole[0][1].kolor=1; pole[1][0].kolor=1; pole[1][1].kolor=1;
    pole[0][9].kolor=2; pole[0][10].kolor=2; pole[1][9].kolor=2; pole[1][10].kolor=2;
    pole[9][0].kolor=4; pole[9][1].kolor=4; pole[10][0].kolor=4; pole[10][1].kolor=4;
    pole[9][9].kolor=3; pole[9][10].kolor=3; pole[10][9].kolor=3; pole[10][10].kolor=3;

    pole[0][0].numer=1; pole[0][1].numer=2; pole[1][0].numer=3; pole[1][1].numer=4;
    pole[0][9].numer=1; pole[0][10].numer=2; pole[1][9].numer=3; pole[1][10].numer=4;
    pole[9][0].numer=1; pole[9][1].numer=2; pole[10][0].numer=3; pole[10][1].numer=4;
    pole[9][9].numer=1; pole[9][10].numer=2; pole[10][9].numer=3; pole[10][10].numer=4;
}

/** \brief wyswietl
* - Funkcja wyswietlajaca wszystkie elementy w oknie programu. Kolejnosc nakladania elementow: tlo, plansza, pionki, tekst. Jest wywolywana przy przejciach glownej petli oraz przy zmianie komunikatow w trakcie gry.*/
void wyswietl()
{
    Tekst.setString(tekst);
    oknoAplikacji.draw(grafika_tlo);
        for(int i=0;i<11;i++)
            for(int j=0;j<11;j++){
                oknoAplikacji.draw(pole[i][j].grafika);
                if(pole[i][j].kolor==1){
                        pionek[0][pole[i][j].numer-1].grafika.setPosition(pole[i][j].grafika.getPosition().x,pole[i][j].grafika.getPosition().y);
                        oknoAplikacji.draw(pionek[0][pole[i][j].numer-1].grafika);
                }
                if(pole[i][j].kolor==2){
                        pionek[1][pole[i][j].numer-1].grafika.setPosition(pole[i][j].grafika.getPosition().x,pole[i][j].grafika.getPosition().y);
                        oknoAplikacji.draw(pionek[1][pole[i][j].numer-1].grafika);
                }
                if(pole[i][j].kolor==3){
                        pionek[2][pole[i][j].numer-1].grafika.setPosition(pole[i][j].grafika.getPosition().x,pole[i][j].grafika.getPosition().y);
                        oknoAplikacji.draw(pionek[2][pole[i][j].numer-1].grafika);
                }
                if(pole[i][j].kolor==4){
                        pionek[3][pole[i][j].numer-1].grafika.setPosition(pole[i][j].grafika.getPosition().x,pole[i][j].grafika.getPosition().y);
                        oknoAplikacji.draw(pionek[3][pole[i][j].numer-1].grafika);
                }
            }
        oknoAplikacji.draw(Tekst);
        oknoAplikacji.display();
}

/** \brief ruch
* - Funkcja pozwalajaca na poruszanie sie pionkow po planszy. Zostaje uruchomiona tylko gdy zostanie wybrany poprawnie pionek przez gracza lub komputer. Pionki z bazy wychodza na pole startowe, natomiast pionki na sciezce przesuawaja sie na odpowiednie pole w zaleznosci od kostki. Dane pola dotyczace pionka ktory na nami stal zostaja wyzerowane, a dane pola na ktorym staje przyjmuja odpowiednie wartosci informujace o kolorze i numerze pionka, a ten przyjmuje nowa wartosc miejsca w ktorym sie znajduje. Jesli na docelowym polu stal przeciwny pionek, zostaje on przeniesiony do swojej bazy. Wywolaniu funkcji ruch towarzyszy dzwiek skoku, oraz dzwiek zbicia, jesli takie zostalo wykonane.*/
void ruch()
{
    skok.stop();
    skok.play();

    ////WYZEROWANIA AKTUALNEGO MIEJSCA
    trasa[gracz-1][wybrany-1][pionek[gracz-1][wybrany-1].miejsce]->kolor=0;
    trasa[gracz-1][wybrany-1][pionek[gracz-1][wybrany-1].miejsce]->numer=0;

    ////PRZYPADEK DLA PIONKA W BAZIE
    if(pionek[gracz-1][wybrany-1].miejsce==0)
        pionek[gracz-1][wybrany-1].miejsce++;
    ////PRZYPADEK DLA PIONKA W POLU
    else
        pionek[gracz-1][wybrany-1].miejsce+=kosc;
    ////ZBICIE PIONKA
    if(trasa[gracz-1][wybrany-1][pionek[gracz-1][wybrany-1].miejsce]->kolor!=0){
        pionek[trasa[gracz-1][wybrany-1][pionek[gracz-1][wybrany-1].miejsce]->kolor-1][trasa[gracz-1][wybrany-1][pionek[gracz-1][wybrany-1].miejsce]->numer-1].miejsce=0;
        trasa[trasa[gracz-1][wybrany-1][pionek[gracz-1][wybrany-1].miejsce]->kolor-1][trasa[gracz-1][wybrany-1][pionek[gracz-1][wybrany-1].miejsce]->numer-1][0]->kolor=trasa[gracz-1][wybrany-1][pionek[gracz-1][wybrany-1].miejsce]->kolor;
        trasa[trasa[gracz-1][wybrany-1][pionek[gracz-1][wybrany-1].miejsce]->kolor-1][trasa[gracz-1][wybrany-1][pionek[gracz-1][wybrany-1].miejsce]->numer-1][0]->numer=trasa[gracz-1][wybrany-1][pionek[gracz-1][wybrany-1].miejsce]->numer;
        kosc=6;
        zbicie.stop();
        zbicie.play();
    }
    ////POSTAWIENIE PIONKA
    trasa[gracz-1][wybrany-1][pionek[gracz-1][wybrany-1].miejsce]->kolor=gracz;
    trasa[gracz-1][wybrany-1][pionek[gracz-1][wybrany-1].miejsce]->numer=wybrany;
}
/** \brief sprawdzenie
* - Funkcja ktora wywolywana jest przy zmianie gracza lub przy uzyciu oszustw. Sprawdza po kolei kazdy z czterech pionkow aktualnego gracza i zapisuje ktore z nich moge wykonac ruch, uwzgledniajac miedzy innymi: ilosc oczek na kostce, blokowanie trasy przez wlasne pionki, przekroczenie granicy sciezki. Wyswietlany jest odpowiedni komunikat o tym czy gracz ma jakakolwiek mozliwosc ruchu.*/
void sprawdzenie()
{
    char kosc_char=kosc+48;
    wyswietl();
    Sleep(skok_czasu);

    tekst+="\nKoÓæ: ";
    tekst+=kosc_char;

    wyswietl();

    for(int i=0;i<4;i++){
        tak_nie[i]=1;

        ////DLA PIONKOW W BAZIE////
        if(pionek[gracz-1][i].miejsce==0){
            if(kosc==6){
                if(trasa[gracz-1][i][1]->kolor==gracz){

                    ////pionek jest w bazie i wypadlo 6, ale stoi tam juz wlasny pionek
                    tak_nie[i]=0;
                }
                else{
                    ////pionek jest w bazie i wypadlo 6
                }
            }
            else{
                    ////pionek jest w bazie i nie wypadlo 6
                    tak_nie[i]=0;
                }
        }
        ////DLA PIONKOW NA MECIE////
        else if(pionek[gracz-1][i].miejsce==44){
            ////pionek jest juz na ostatnim miejscu mety
            tak_nie[i]=0;
        }
        ////DLA PIONKOW PRZESKAKUJACYCH METE////
        else if(kosc>44-pionek[gracz-1][i].miejsce){
            ////pionek wyszedlby poza mete
            tak_nie[i]=0;
        }
                ////DLA PIONKOW POZOSTALYCH////
        else if(trasa[gracz-1][i][pionek[gracz-1][i].miejsce+kosc]->kolor==gracz){
            ////pionek wszedlby na swojego
                tak_nie[i]=0;
            }
        ////DLA PIONKOW WCHODZACYCH NA METE////
        else if(kosc==44-pionek[gracz-1][i].miejsce){
            ////pionek moze sie tam ruszyc
        }
    }
    if(tak_nie[0]+tak_nie[1]+tak_nie[2]+tak_nie[3]==0){
        Sleep(skok_czasu);
        tekst+="\n\nBrak ruchu. ";
        if(gracz<=ilosc_graczy)
            tekst+="NaciÓnij LPM,\naby oddaæ turê.";
        wyswietl();
    }
    else{
        Sleep(skok_czasu);
        if(gracz<=ilosc_graczy)
            tekst+="\n\nWybierz pionek.";
        wyswietl();
    }
}

/** \brief wygrana
* - Funkcja wywolywana przy kazdym przejsciu glownej petli, sprawdzajaca czy pionki ktoregos z graczy zajmuja wszystkie pola mety. Jesli tak, gra sie konczy, wyswietla sie komunikat, uruchamia dzwiek wygranej. */
void wygrana()
{
    if(pole[5][1].kolor==1&&pole[5][2].kolor==1&&pole[5][3].kolor==1&&pole[5][4].kolor==1){
        tekst="Wygra³ czerwony.\n\n";
        tryb=0;
    }
    if(pole[1][5].kolor==2&&pole[2][5].kolor==2&&pole[3][5].kolor==2&&pole[4][5].kolor==2){
        tekst="Wygra³ niebieski.\n\n";
        tryb=0;
    }
    if(pole[5][6].kolor==3&&pole[5][7].kolor==3&&pole[5][8].kolor==3&&pole[5][9].kolor==3){
        tekst="Wygra³ ¿ó³ty.\n\n";
        tryb=0;
    }
    if(pole[6][5].kolor==4&&pole[7][5].kolor==4&&pole[8][5].kolor==4&&pole[9][5].kolor==4){
        tekst="Wygra³ zielony.\n\n";
        tryb=0;
    }
    if(tryb==0){
        if(klaskanie.getStatus()==0)
            klaskanie.play();
        wyswietl();
        Sleep(2000);
        tekst+="NaciÓnij LPM,\naby zagraæ jeszcze raz.";
        event.type=sf::Event::KeyPressed;
    }
}

/** \brief oszustwo
* - Funkcja wywolywana przy kazdym przejsciu glownej petli, sprawdzajace czy uzytkownik nie uzyl oszustw. Jesli tak, ilosc oczek na kostce zmienia sie w zaleznosci od oszustwa, a program ponownie sprawdz mozliwe ruchy pionkow.*/
void oszustwo()
{
    ////OSZUSTWA PROGRAMISTY
    if(event.type==sf::Event::KeyReleased){
        if(event.key.code==sf::Keyboard::Left){
            kosc--;
            sprawdzenie();
            wyswietl();
        }
        else if (event.key.code==sf::Keyboard::Right){
            kosc++;
            sprawdzenie();
            wyswietl();
        }
        else if(event.key.code==sf::Keyboard::Up){
            kosc=40;
            sprawdzenie();
            wyswietl();
        }
        event.type=sf::Event::KeyPressed;
    }
}

/** \brief wylaczenie
* -Funkcja wywolywana przy kazdym przejsciu glownej petli, sprawdzajace czy uzytkownik nie nacisnal przycisku "zamknij" w prawym gornym rogu badz, przycisku "esc" na klawiaturze. Ten pierwszy obslugiwany jest zakonczeniem programu, drugi przejsciem do menu. */
void wylaczenie()
{
    while(oknoAplikacji.pollEvent(event)){
        if(event.type==sf::Event::Closed){
            oknoAplikacji.close();
        }
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        reset();
        tryb=1;
    }
}

/** \brief wybor
* - Funkcja, pozwalajace graczowi wybrac odpowiedni pionek. Zbiera informacje o tym gdzie znajduje sie kursor, czy LPM jest klikniety i czy znajduje sie nad wlasciwym pionkiem. Jesli tak, zostaje uruchomiona funkcja ruch().*/
void wybor()
{
    if(event.type==sf::Event::MouseButtonPressed){
        int x,y;
        x=(sf::Mouse::getPosition(oknoAplikacji).x-(oknoAplikacji.getSize().x)/8)/(oknoAplikacji.getSize().x/26)+1;
        y=(sf::Mouse::getPosition(oknoAplikacji).y-(oknoAplikacji.getSize().x)/22)/(oknoAplikacji.getSize().y/13)+1;

        if(x>=0&&x<=11&&y>=0&&y<=11){
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&pole[y-1][x-1].kolor==gracz){
                if(tak_nie[pole[y-1][x-1].numer-1]==1){
                    wybrany=pole[y-1][x-1].numer;
                    ruch();
                    tak_nie[0]=tak_nie[1]=tak_nie[2]=tak_nie[3]=0;
                    wyzwalacz_kostka=0;
                }
            }
        }
    }
}
/** \brief wybor_komputer
* - Funkcja, wywolywana przy turze gracza komputerowego. Komputer losuje wartosc od 1 do 4 dopoki nie trafi pierwszego pionka mogacego sie ruszyc.*/
void wybor_komputer()
{
    do{
        wybrany=rand()%4+1;
    }while(tak_nie[wybrany-1]!=1);

    ruch();
    tak_nie[0]=tak_nie[1]=tak_nie[2]=tak_nie[3]=0;
}

/** \brief main
* - Funkcja main, zawiera menu oraz obsluge samej rozgrywki. Zawiera petle glowna, ktora w zaleznosci od zmiennej "tryb" uruchamia odpowiednie obszary, tak aby uzytkownik oblugiwal menu etapami (plansza witajaca, wybor ilosci graczy, wybor szybkosci gry, a dopiero potem rozgrywka oraz zatrzymanie jej w razie wygranej). Rozgyrwka opiera sie kolejno na: zmiana gracza, jesli zaden z jego pionkow nie moze sie ruszyc, sprawdzenie mozliwosci ruchu pionkow nowego gracz, wybor pionka do ruszenia przez komputer lub uzytkownika*/
int main()
{

    inicjacja();
    reset();

    while(oknoAplikacji.isOpen()){
        if(tryb==0){
            if(event.type==sf::Event::MouseButtonReleased){
                reset();
                tryb++;
                event.type=sf::Event::MouseButtonPressed;
            }
        }
        if(tryb==1){
            klaskanie.stop();
            rozgrywka.stop();
            if(menu.getStatus()==0)
                menu.play();

            tekst="Chiñczyk autorstwa\nAdam Furmanek\nTomasz Gêbski\n\nNaciÓnij LPM, aby zagraæ.\nNaciÓnij ESC, aby wróciæ.";
            if(event.type==sf::Event::MouseButtonReleased)
                tryb++;
        }
        if(tryb==2){
            tekst="Proszê wybraæ\niloÓæ graczy ludzkich.\n(0-4)";
            if(event.type==sf::Event::KeyReleased){
                if(event.key.code==sf::Keyboard::Num0)
                    ilosc_graczy=0;
                if(event.key.code==sf::Keyboard::Num1)
                    ilosc_graczy=1;
                if(event.key.code==sf::Keyboard::Num2)
                    ilosc_graczy=2;
                if(event.key.code==sf::Keyboard::Num3)
                    ilosc_graczy=3;
                if(event.key.code==sf::Keyboard::Num4)
                    ilosc_graczy=4;
                tryb++;
                event.type=sf::Event::KeyPressed;
            }
        }
        if(tryb==3){
            tekst="Proszê wybraæ\nszybkoÓæ gry. (0-3)";
            if(event.type==sf::Event::KeyReleased){
                if(event.key.code==sf::Keyboard::Num0)
                    skok_czasu=0;
                if(event.key.code==sf::Keyboard::Num1)
                    skok_czasu=100;
                if(event.key.code==sf::Keyboard::Num2)
                    skok_czasu=500;
                if(event.key.code==sf::Keyboard::Num3)
                    skok_czasu=1000;
                tryb++;
                menu.stop();
            }
            event.type=sf::Event::MouseButtonPressed;
        }
        if(tryb==4){

            if(rozgrywka.getStatus()==0){
                rozgrywka.stop();

                switch(rand()%3){
                    case 0:
                        rozgrywka.openFromFile("rozgrywka1.wav");
                        break;
                    case 1:
                        rozgrywka.openFromFile("rozgrywka2.wav");
                        break;
                    case 2:
                        rozgrywka.openFromFile("rozgrywka3.wav");
                        break;
                }
                rozgrywka.play();
            }

            if(tak_nie[0]+tak_nie[1]+tak_nie[2]+tak_nie[3]==0){
                if(wyzwalacz_tura==0){
                    if(gracz>ilosc_graczy || event.type==sf::Event::MouseButtonPressed){
                    event.type=sf::Event::MouseButtonReleased;
                    if(kosc!=6){
                        gracz++;
                        if(gracz==5)
                            gracz=1;
                    }
                    Sleep(skok_czasu);
                    tekst="Teraz gracz: ";
                    wyswietl();
                    Sleep(skok_czasu);

                    if(gracz==1)
                        tekst+="czerwony\n";
                    if(gracz==2)
                        tekst+="niebieski\n";
                    if(gracz==3)
                        tekst+="¿ó³ty\n";
                    if(gracz==4)
                        tekst+="zielony\n";
                    if(gracz<=ilosc_graczy){
                        wyswietl();
                        Sleep(skok_czasu);
                        tekst+="\nNaciÓnij LPM,\naby rzuciæ kostk¥\n";
                    }
                    wyzwalacz_tura=1;
                    }
                }
                if(wyzwalacz_tura==1){
                    if(gracz>ilosc_graczy || event.type==sf::Event::MouseButtonPressed){
                    event.type=sf::Event::MouseButtonReleased;
                    kosc=rand()%6+1;
                    sprawdzenie();
                    wyzwalacz_tura=0;
                    wyzwalacz_kostka=1;
                    }
                }
            }
            oszustwo();
            if(tak_nie[0]+tak_nie[1]+tak_nie[2]+tak_nie[3]>0){
                if(gracz<=ilosc_graczy&&wyzwalacz_kostka==1){
                    wybor();
                }
                else if(gracz>ilosc_graczy)
                    wybor_komputer();
            }
            wygrana();
        }
        wylaczenie();
        wyswietl();
    }

    return 0;
}
