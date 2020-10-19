#include <iostream>
#include <windows.h>
#include <time.h>
#include <conio.h>

using namespace std;

int gra=1;
int gracz=1;
int kosc;
int pionek[5][5][3];
int baza_pionka[5][5][3];
int skok_czasu=100;
int skok_czasu_3=0;
int wybrany_pionek;
int tak_nie[5];
int wyjscie_z_bazy[5][3];
int meta[5][3];
int tryb;
int licznik_komputera;
int liczba_graczy=4;
int liczba_graczy_komputerowych=0;
int czy_pionek;

string nazwa_gracza[5]={"0","Czerwony","Niebieski","Zielony","Zolty"};
string mapa_oryginal[12][12]={
    {"X","X","X","X","X","X","X","X","X","X","X","X"},
    {"X","  .  ","  .  ","     ","     ","  l  ","  k  ","  l  ","     ","     ","  .  ","  .  "},
    {"X","  .  ","  .  ","     ","     ","  k  ","  0  ","  k  ","     ","     ","  .  ","  .  "},
    {"X","     ","     ","     ","     ","  l  ","  0  ","  l  ","     ","     ","     ","     "},
    {"X","     ","     ","     ","     ","  k  ","  0  ","  k  ","     ","     ","     ","     "},
    {"X","  l  ","  k  ","  l  ","  k  ","  l  ","  0  ","  l  ","  k  ","  l  ","  k  ","  l  "},
    {"X","  k  ","  0  ","  0  ","  0  ","  0  ","     ","  0  ","  0  ","  0  ","  0  ","  k  "},
    {"X","  l  ","  k  ","  l  ","  k  ","  l  ","  0  ","  l  ","  k  ","  l  ","  k  ","  l  "},
    {"X","     ","     ","     ","     ","  k  ","  0  ","  k  ","     ","     ","     ","     "},
    {"X","     ","     ","     ","     ","  l  ","  0  ","  l  ","     ","     ","     ","     "},
    {"X","  .  ","  .  ","     ","     ","  k  ","  0  ","  k  ","     ","     ","  .  ","  .  "},
    {"X","  .  ","  .  ","     ","     ","  l  ","  k  ","  l  ","     ","     ","  .  ","  .  "}
};
string mapa[12][12];

void reset();
void menu();
void zerowanie_mapy();
void nalozenie_pionkow();
void wypisanie_mapy();
int sprawdzenie_wygranej();
void rzut_kostka();
void sprawdzenie();
int sprawdzenie_ruchu_pionka1(int a, int b);
int sprawdzenie_ruchu_pionka2(int a, int b, int j);
void wybor();
void ruch_pozorny();
void ruch_pionka(int a, int b);
void sprawdzenie_zbicia();

int main()
{
    while(1){
        reset();
        menu();
        if(tryb==4)
            return 0;
        while(tryb!=4){
            if(liczba_graczy_komputerowych==1){
                if(gracz==liczba_graczy)
                    tryb=3;
                else
                    tryb=1;
            }
            if(liczba_graczy_komputerowych==2){
                if(gracz==liczba_graczy||gracz==liczba_graczy-1)
                    tryb=3;
                else
                    tryb=1;
            }
            if(liczba_graczy_komputerowych==3){
                if(gracz==liczba_graczy||gracz==liczba_graczy-1||gracz==liczba_graczy-2)
                    tryb=3;
                else
                    tryb=1;
            }
            system("cls");
            zerowanie_mapy();
            nalozenie_pionkow();
            wypisanie_mapy();
            if (sprawdzenie_wygranej()==1)
                break;
            rzut_kostka();
            sprawdzenie();
            wybor();
            if(wybrany_pionek==6)
                break;
            ruch_pozorny();
            ruch_pionka(pionek[gracz][wybrany_pionek][1],pionek[gracz][wybrany_pionek][2]);
            if(wybrany_pionek!=5)
                sprawdzenie_zbicia();
            if(kosc!=6){
                gracz++;
                if(gracz==liczba_graczy+1)
                    gracz=1;
                }
            if(kbhit())
                if(getch()=='q')
                    break;
        }
    }
}

void menu()
{
    Sleep(300);
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
    cout<<"C";
    Sleep(120);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    cout<<"H";
    Sleep(120);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout<<"I";
    Sleep(120);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    cout<<"N";
    Sleep(120);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
    cout<<"C";
    Sleep(120);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    cout<<"Z";
    Sleep(120);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout<<"Y";
    Sleep(120);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    cout<<"K"<<endl<<endl;
    Sleep(120);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    cout<<"Nacisnij 1 aby zagrac"<<endl;
    Sleep(120);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout<<"Nacisnij 2 aby wlaczyc tryb testowy"<<endl;
    Sleep(120);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    cout<<"Nacisnij 3 aby wlaczyc tryb widza"<<endl;
    Sleep(120);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
    cout<<"Nacisnij 4 aby wyjsc"<<endl;
    Sleep(120);
    tryb=getch()-48;
    if(tryb>4)
        tryb=4;
    if(tryb<1)
        tryb=1;
    if(tryb==1||tryb==3){
        if(tryb==1)
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
        else
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
        cout<<"Podaj liczbe graczy"<<endl;
        cin>>liczba_graczy;
        if(liczba_graczy>4){
            liczba_graczy=4;
        }
        if(liczba_graczy<2){
            liczba_graczy=2;
        }
    }
    if(tryb==1){
        cout<<"Podaj liczbe graczy komputerowych"<<endl;
        cin>>liczba_graczy_komputerowych;
        if(liczba_graczy_komputerowych<0)
            liczba_graczy_komputerowych=0;
        if(liczba_graczy_komputerowych>liczba_graczy-1)
            liczba_graczy_komputerowych=liczba_graczy-1;
        cout<<"Wpisz nazwe pierwszego gracza"<<endl;
        cin>>nazwa_gracza[1];
        if(liczba_graczy-liczba_graczy_komputerowych>1){
            cout<<"Wpisz nazwe drugiego gracza"<<endl;
            cin>>nazwa_gracza[2];
        }
        if(liczba_graczy-liczba_graczy_komputerowych>2){
            cout<<"Wpisz nazwe trzeciego gracza"<<endl;
            cin>>nazwa_gracza[3];
        }
        if(liczba_graczy-liczba_graczy_komputerowych>3){
            cout<<"Wpisz nazwe czwartego gracza"<<endl;    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
            cin>>nazwa_gracza[4];
        }
        cout<<"Podaj czas wyswietlania interfejsu"<<endl;;
        cin>>skok_czasu;
    }
    if(tryb==2)
    {
        skok_czasu=0;
    }
    if(tryb==3)
    {
        cout<<"Podaj czas wyswietlania interfejsu"<<endl;;
        cin>>skok_czasu;
        cout<<"Podaj czas wyswietlania mapy:"<<endl;
        cin>>skok_czasu_3;
        cout<<"Aby wyjsc do menu nacisnij q";
        Sleep(800);
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}

void reset()
{
    srand(time(NULL));

    pionek[1][1][1]=1;pionek[1][1][2]=1;pionek[1][2][1]=1;pionek[1][2][2]=2;pionek[1][3][1]=2;pionek[1][3][2]=1;pionek[1][4][1]=2;pionek[1][4][2]=2;
    pionek[2][1][1]=1;pionek[2][1][2]=10;pionek[2][2][1]=1;pionek[2][2][2]=11;pionek[2][3][1]=2;pionek[2][3][2]=10;pionek[2][4][1]=2;pionek[2][4][2]=11;
    pionek[4][1][1]=10;pionek[4][1][2]=1;pionek[4][2][1]=10;pionek[4][2][2]=2;pionek[4][3][1]=11;pionek[4][3][2]=1;pionek[4][4][1]=11;pionek[4][4][2]=2;
    pionek[3][1][1]=10;pionek[3][1][2]=10;pionek[3][2][1]=10;pionek[3][2][2]=11;pionek[3][3][1]=11;pionek[3][3][2]=10;pionek[3][4][1]=11;pionek[3][4][2]=11;

    baza_pionka[1][1][1]=1;baza_pionka[1][1][2]=1;baza_pionka[1][2][1]=1;baza_pionka[1][2][2]=2;baza_pionka[1][3][1]=2;baza_pionka[1][3][2]=1;baza_pionka[1][4][1]=2;baza_pionka[1][4][2]=2;
    baza_pionka[2][1][1]=1;baza_pionka[2][1][2]=10;baza_pionka[2][2][1]=1;baza_pionka[2][2][2]=11;baza_pionka[2][3][1]=2;baza_pionka[2][3][2]=10;baza_pionka[2][4][1]=2;baza_pionka[2][4][2]=11;
    baza_pionka[4][1][1]=10;baza_pionka[4][1][2]=1;baza_pionka[4][2][1]=10;baza_pionka[4][2][2]=2;baza_pionka[4][3][1]=11;baza_pionka[4][3][2]=1;baza_pionka[4][4][1]=11;baza_pionka[4][4][2]=2;
    baza_pionka[3][1][1]=10;baza_pionka[3][1][2]=10;baza_pionka[3][2][1]=10;baza_pionka[3][2][2]=11;baza_pionka[3][3][1]=11;baza_pionka[3][3][2]=10;baza_pionka[3][4][1]=11;baza_pionka[3][4][2]=11;

    wyjscie_z_bazy[1][1]=5;wyjscie_z_bazy[1][2]=1;
    wyjscie_z_bazy[2][1]=1;wyjscie_z_bazy[2][2]=7;
    wyjscie_z_bazy[4][1]=11;wyjscie_z_bazy[4][2]=5;
    wyjscie_z_bazy[3][1]=7;wyjscie_z_bazy[3][2]=11;

    meta[1][1]=6;meta[1][2]=5;
    meta[2][1]=5;meta[2][2]=6;
    meta[4][1]=7;meta[4][2]=6;
    meta[3][1]=6;meta[3][2]=7;

    gracz=1;

    nazwa_gracza[0]="0";
    nazwa_gracza[1]="Czerwony";
    nazwa_gracza[2]="Niebieski";
    nazwa_gracza[3]="Zielony";
    nazwa_gracza[4]="Zolty";

    liczba_graczy=4;
    liczba_graczy_komputerowych=0;
}

void zerowanie_mapy()
{
    for(int i=0;i<12;i++)
        for(int j=0;j<12;j++)
            mapa[i][j]=mapa_oryginal[i][j];
}

void nalozenie_pionkow()
{
    mapa[pionek[1][1][1]][pionek[1][1][2]]="[[1]]";
    mapa[pionek[1][2][1]][pionek[1][2][2]]="[[2]]";
    mapa[pionek[1][3][1]][pionek[1][3][2]]="[[3]]";
    mapa[pionek[1][4][1]][pionek[1][4][2]]="[[4]]";

    mapa[pionek[2][1][1]][pionek[2][1][2]]="{{1}}";
    mapa[pionek[2][2][1]][pionek[2][2][2]]="{{2}}";
    mapa[pionek[2][3][1]][pionek[2][3][2]]="{{3}}";
    mapa[pionek[2][4][1]][pionek[2][4][2]]="{{4}}";

    mapa[pionek[3][1][1]][pionek[3][1][2]]=";;1;;";
    mapa[pionek[3][2][1]][pionek[3][2][2]]=";;2;;";
    mapa[pionek[3][3][1]][pionek[3][3][2]]=";;3;;";
    mapa[pionek[3][4][1]][pionek[3][4][2]]=";;4;;";

    mapa[pionek[4][1][1]][pionek[4][1][2]]="::1::";
    mapa[pionek[4][2][1]][pionek[4][2][2]]="::2::";
    mapa[pionek[4][3][1]][pionek[4][3][2]]="::3::";
    mapa[pionek[4][4][1]][pionek[4][4][2]]="::4::";

    if(gracz==1){
    mapa[pionek[1][1][1]][pionek[1][1][2]]="[[1]]";
    mapa[pionek[1][2][1]][pionek[1][2][2]]="[[2]]";
    mapa[pionek[1][3][1]][pionek[1][3][2]]="[[3]]";
    mapa[pionek[1][4][1]][pionek[1][4][2]]="[[4]]";
    }

    if(gracz==2){
    mapa[pionek[2][1][1]][pionek[2][1][2]]="{{1}}";
    mapa[pionek[2][2][1]][pionek[2][2][2]]="{{2}}";
    mapa[pionek[2][3][1]][pionek[2][3][2]]="{{3}}";
    mapa[pionek[2][4][1]][pionek[2][4][2]]="{{4}}";
    }

    if(gracz==3){
    mapa[pionek[3][1][1]][pionek[3][1][2]]=";;1;;";
    mapa[pionek[3][2][1]][pionek[3][2][2]]=";;2;;";
    mapa[pionek[3][3][1]][pionek[3][3][2]]=";;3;;";
    mapa[pionek[3][4][1]][pionek[3][4][2]]=";;4;;";
    }
}

void wypisanie_mapy()
{
    for(int i=1;i<12;i++){
        for(int k=0;k<3;k++){
            for(int j=1;j<12;j++){

                    if(((mapa[i][j]=="[[1]]")||(mapa[i][j]=="[[2]]")||(mapa[i][j]=="[[3]]")||(mapa[i][j]=="[[4]]"))&&(k==1))
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),204);
                    cout<<mapa[i][j][0]<<mapa[i][j][1];
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),192);
                    cout<<mapa[i][j][2];
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),204);
                    cout<<mapa[i][j][3]<<mapa[i][j][4];
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

                }
                    else if(((mapa[i][j]=="{{1}}")||(mapa[i][j]=="{{2}}")||(mapa[i][j]=="{{3}}")||(mapa[i][j]=="{{4}}"))&&(k==1))
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),187);
                    cout<<mapa[i][j][0]<<mapa[i][j][1];
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),176);
                    cout<<mapa[i][j][2];
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),187);
                    cout<<mapa[i][j][3]<<mapa[i][j][4];
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

                }
                    else if(((mapa[i][j]==";;1;;")||(mapa[i][j]==";;2;;")||(mapa[i][j]==";;3;;")||(mapa[i][j]==";;4;;"))&&(k==1))
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),170);
                    cout<<mapa[i][j][0]<<mapa[i][j][1];
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),160);
                    cout<<mapa[i][j][2];
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),170);
                    cout<<mapa[i][j][3]<<mapa[i][j][4];
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

                }
                    else if(((mapa[i][j]=="::1::")||(mapa[i][j]=="::2::")||(mapa[i][j]=="::3::")||(mapa[i][j]=="::4::"))&&(k==1))
                {
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),238);
                    cout<<mapa[i][j][0]<<mapa[i][j][1];
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),224);
                    cout<<mapa[i][j][2];
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),238);
                    cout<<mapa[i][j][3]<<mapa[i][j][4];
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);

                }

                    else{
                if(((mapa[i][j]=="{{1}}")||(mapa[i][j]=="{{2}}")||(mapa[i][j]=="{{3}}")||(mapa[i][j]=="{{4}}"))&&(k==0||k==2))
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),187);
                if(((mapa[i][j]=="[[1]]")||(mapa[i][j]=="[[2]]")||(mapa[i][j]=="[[3]]")||(mapa[i][j]=="[[4]]"))&&(k==0||k==2))
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),204);
                if(((mapa[i][j]==";;1;;")||(mapa[i][j]==";;2;;")||(mapa[i][j]==";;3;;")||(mapa[i][j]==";;4;;"))&&(k==0||k==2))
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),170);
                if(((mapa[i][j]=="::1::")||(mapa[i][j]=="::2::")||(mapa[i][j]=="::3::")||(mapa[i][j]=="::4::"))&&(k==0||k==2))
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),238);
                if(mapa[i][j]=="     ")
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),255);
                if(mapa[i][j]=="  .  "&&k==1)
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),240);
                if(mapa[i][j]=="  .  "&&(k==0||k==2))
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),255);
                if(mapa[i][j]=="  k  ")
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),119);
                if(mapa[i][j]=="  l  ")
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),136);
                if(mapa[i][j]=="  0  ")
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),0);
                cout<<mapa[i][j];
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                    }
            }
            cout<<endl;
        }
    }
    if(tryb==3)
        Sleep(skok_czasu_3);
    cout<<endl;
}

int sprawdzenie_wygranej()
{
    if(pionek[gracz][1][1]==pionek[gracz][2][1]&&
        pionek[gracz][1][1]==pionek[gracz][3][1]&&
        pionek[gracz][1][1]==pionek[gracz][4][1]&&
        pionek[gracz][1][2]==pionek[gracz][2][2]&&
        pionek[gracz][1][2]==pionek[gracz][3][2]&&
        pionek[gracz][1][2]==pionek[gracz][4][2]){
        Sleep(skok_czasu);
        if(gracz==1)
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
        if(gracz==2)
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
        if(gracz==3)
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
        if(gracz==4)
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
        cout<<"Zwyciezyl "<<nazwa_gracza[gracz]<<"!"<<endl<<"Nacisnij, aby wrocic do menu";
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
        getch();
        return 1;
        }
    else{
        return 0;
    }
}

void rzut_kostka()
{

    Sleep(skok_czasu);
    if(tryb==2){
        cout<<"[Test]:Podaj numer gracza"<<endl;
        gracz=getch()-48;
        if(gracz<1)
            gracz=1;
        if(gracz>4)
            gracz=4;
    }
    if(gracz==1)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
    if(gracz==2)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    if(gracz==3)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    if(gracz==4)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout<<"Gracz "<<nazwa_gracza[gracz]<<" rzuca kostka"<<endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
    if(tryb==1){
        getch();
        kosc=rand()%6+1;
    }
    if(tryb==2){
        cout<<"[Test]:Podaj liczbe oczek na kostce"<<endl;
        kosc=getch()-48;
        if(kosc>6)
            kosc=6;
        if(kosc<1)
            kosc=1;
    }
    if(tryb==3){
        kosc=rand()%6+1;
    }
    Sleep(skok_czasu);
        if(gracz==1)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
    if(gracz==2)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    if(gracz==3)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    if(gracz==4)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    cout<<"Wyrzucono "<<kosc<<endl;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}

void sprawdzenie()
{
    if(gracz==1)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
    if(gracz==2)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
    if(gracz==3)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
    if(gracz==4)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
    Sleep(skok_czasu);
    if(tryb==1||tryb==2)
        cout<<"Wybierz pionek:"<<endl;
    for (int i=1;i<5;i++){
        Sleep(skok_czasu);
        tak_nie[i]=1;
        if(pionek[gracz][i][1]==baza_pionka[gracz][i][1]&&pionek[gracz][i][2]==baza_pionka[gracz][i][2]){
            if(kosc==6){
                if((wyjscie_z_bazy[gracz][1]==pionek[gracz][1][1]&&wyjscie_z_bazy[gracz][2]==pionek[gracz][1][2])||
                    (wyjscie_z_bazy[gracz][1]==pionek[gracz][2][1]&&wyjscie_z_bazy[gracz][2]==pionek[gracz][2][2])||
                    (wyjscie_z_bazy[gracz][1]==pionek[gracz][3][1]&&wyjscie_z_bazy[gracz][2]==pionek[gracz][3][2])||
                    (wyjscie_z_bazy[gracz][1]==pionek[gracz][4][1]&&wyjscie_z_bazy[gracz][2]==pionek[gracz][4][2])){
                    cout<<i<<". Wyjscie zablokowane przez inny pionek"<<endl;
                    tak_nie[i]=0;
                }
                else
                    cout<<i<<". Wyjdz z bazy"<<endl;
            }
            else{
                cout<<i<<". Potrzeba 6 aby wyjsc"<<endl;
                tak_nie[i]=0;
            }
        }
        else{
            if(pionek[gracz][i][1]==meta[gracz][1]&&pionek[gracz][i][2]==meta[gracz][2]){
                cout<<i<<". Pionek jest na mecie."<<endl;
                tak_nie[i]=0;
            }
            else{
                if(kosc>sprawdzenie_ruchu_pionka1(pionek[gracz][i][1],pionek[gracz][i][2])){
                    cout<<i<<". Pionek nie moze sie tam ruszyc."<<endl;
                    tak_nie[i]=0;
                }
                else{
                    if(sprawdzenie_ruchu_pionka2(pionek[gracz][i][1],pionek[gracz][i][2],i)==1){
                        cout<<i<<". Pionek nie moze wejsc na swojego."<<endl;
                        tak_nie[i]=0;
                    }
                    else{
                        cout<<i<<". Rusz sie o "<<kosc<<" pol"<<endl;
                    }
                }

            }
        }
    }
    Sleep(skok_czasu);
    cout<<"5. Oddanie tury"<<endl;
    cout<<"6. Wyjscie do menu"<<endl;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
}

int sprawdzenie_ruchu_pionka1(int a, int b)
{
    int ilosc_ruchow=0;
    while(a!=meta[gracz][1]||b!=meta[gracz][2]){
        ilosc_ruchow++;
        switch(gracz){
            case 1:
                if(a==5&&b!=5&&b!=11)
                    {b++;break;}
                if(a==7&&b!=1&&b!=7)
                    {b--;break;}
                if(b==5&&a!=1&&a!=7)
                    {a--;break;}
                if(b==7&&a!=5&&a!=11)
                    {a++;break;}
                if(a==1&&b!=7)
                    {b++;break;}
                if(a==11&&b!=5)
                    {b--;break;}
                if(b==1&&a==7)
                    {a--;break;}
                if(a==6&&b!=5&&b!=11)
                    {b++;break;}
                if(b==11&&a!=7)
                    {a++;break;}
            case 2:
                if(a==5&&b!=5&&b!=11)
                    {b++;break;}
                if(a==7&&b!=1&&b!=7)
                    {b--;break;}
                if(b==5&&a!=1&&a!=7)
                    {a--;break;}
                if(b==7&&a!=5&&a!=11)
                    {a++;break;}
                if(a==1&&b==5)
                    {b++;break;}
                if(b==6&&a!=5&&a!=11)
                    {a++;break;}
                if(a==11&&b!=5)
                    {b--;break;}
                if(b==1&&a!=5)
                    {a--;break;}
                if(b==11&&a!=7)
                    {a++;break;}
            case 4:
                if(a==5&&b!=5&&b!=11)
                    {b++;break;}
                if(a==7&&b!=1&&b!=7)
                    {b--;break;}
                if(b==5&&a!=1&&a!=7)
                    {a--;break;}
                if(b==7&&a!=5&&a!=11)
                    {a++;break;}
                if(a==1&&b!=7)
                    {b++;break;}
                if(a==11&&b==7)
                    {b--;break;}
                if(b==6&&a!=7&&a!=1)
                    {a--;break;}
                if(b==1&&a!=5)
                    {a--;break;}
                if(b==11&&a!=7)
                    {a++;break;}
            case 3:
                if(a==5&&b!=5&&b!=11)
                    {b++;break;}
                if(a==7&&b!=1&&b!=7)
                    {b--;break;}
                if(b==5&&a!=1&&a!=7)
                    {a--;break;}
                if(b==7&&a!=5&&a!=11)
                    {a++;break;}
                if(a==1&&b!=7)
                    {b++;break;}
                if(a==11&&b!=5)
                    {b--;break;}
                if(b==1&&a!=5)
                    {a--;break;}
                if(b==11&&a==5)
                    {a++;break;}
                if(a==6&&b!=7&&b!=1)
                    {b--;break;}
        }
    }
return ilosc_ruchow;
}

int sprawdzenie_ruchu_pionka2(int a, int b, int i)
{
    for(int j=kosc;j>0;j--){
        switch(gracz){
            case 1:
                if(a==5&&b!=5&&b!=11)
                    {b++;break;}
                if(a==7&&b!=1&&b!=7)
                    {b--;break;}
                if(b==5&&a!=1&&a!=7)
                    {a--;break;}
                if(b==7&&a!=5&&a!=11)
                    {a++;break;}
                if(a==1&&b!=7)
                    {b++;break;}
                if(a==11&&b!=5)
                    {b--;break;}
                if(b==1&&a==7)
                    {a--;break;}
                if(a==6&&b!=5&&b!=11)
                    {b++;break;}
                if(b==11&&a!=7)
                    {a++;break;}
            case 2:
                if(a==5&&b!=5&&b!=11)
                    {b++;break;}
                if(a==7&&b!=1&&b!=7)
                    {b--;break;}
                if(b==5&&a!=1&&a!=7)
                    {a--;break;}
                if(b==7&&a!=5&&a!=11)
                    {a++;break;}
                if(a==1&&b==5)
                    {b++;break;}
                if(b==6&&a!=5&&a!=11)
                    {a++;break;}
                if(a==11&&b!=5)
                    {b--;break;}
                if(b==1&&a!=5)
                    {a--;break;}
                if(b==11&&a!=7)
                    {a++;break;}
            case 4:
                if(a==5&&b!=5&&b!=11)
                    {b++;break;}
                if(a==7&&b!=1&&b!=7)
                    {b--;break;}
                if(b==5&&a!=1&&a!=7)
                    {a--;break;}
                if(b==7&&a!=5&&a!=11)
                    {a++;break;}
                if(a==1&&b!=7)
                    {b++;break;}
                if(a==11&&b==7)
                   {b--;break;}
                if(b==6&&a!=7&&a!=1)
                    {a--;break;}
                if(b==1&&a!=5)
                    {a--;break;}
                if(b==11&&a!=7)
                    {a++;break;}
            case 3:
                if(a==5&&b!=5&&b!=11)
                    {b++;break;}
                if(a==7&&b!=1&&b!=7)
                    {b--;break;}
                if(b==5&&a!=1&&a!=7)
                    {a--;break;}
                if(b==7&&a!=5&&a!=11)
                    {a++;break;}
                if(a==1&&b!=7)
                    {b++;break;}
                if(a==11&&b!=5)
                    {b--;break;}
                if(b==1&&a!=5)
                    {a--;break;}
                if(b==11&&a==5)
                    {a++;break;}
                if(a==6&&b!=7&&b!=1)
                    {b--;break;}
        }
    }
    czy_pionek=0;
    for(int j=1;j<5;j++){
        if(j!=i)
            if((a==pionek[gracz][j][1]&&b==pionek[gracz][j][2])){
                if(a==meta[gracz][1]&&b==meta[gracz][2]){
                    czy_pionek=czy_pionek;
                }
                else
                    czy_pionek++;
            }
        else
            czy_pionek=czy_pionek;
    }
    if(czy_pionek==0)
        return 0;
    else
        return 1;
}

void wybor()
{
    int wyborek=0;
    while(wyborek==0){
        if((tryb==1||tryb==2)){
            Sleep(skok_czasu);
            wybrany_pionek=getch()-48;
            if((wybrany_pionek==1||wybrany_pionek==2||wybrany_pionek==3||wybrany_pionek==4)&&tak_nie[wybrany_pionek]==0){
                Sleep(skok_czasu);
                if(gracz==1)
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
                if(gracz==2)
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
                if(gracz==3)
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                if(gracz==4)
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                cout<<"Nie mozesz ruszyc tego pionka"<<endl;
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                wyborek=0;
            }
            else if(wybrany_pionek>6||wybrany_pionek<1){
                Sleep(skok_czasu);
                if(gracz==1)
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
                if(gracz==2)
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
                if(gracz==3)
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                if(gracz==4)
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                cout<<"Nie ma takiego pionka"<<endl;
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                wyborek=0;
            }
            else
                wyborek=1;
        }
        if(tryb==3){
            wybrany_pionek=rand()%4+1;
            if(tak_nie[wybrany_pionek]==0){
                if (licznik_komputera<20){
                    licznik_komputera++;
                    wyborek=0;
                }
                else{
                    wybrany_pionek=5;
                    licznik_komputera=0;
                    wyborek=1;
                }
            }
            else{
                wyborek=1;
            }
        }
    }
}

void ruch_pozorny()
{
    if((pionek[gracz][wybrany_pionek][1]==baza_pionka[gracz][wybrany_pionek][1]&&pionek[gracz][wybrany_pionek][2]==baza_pionka[gracz][wybrany_pionek][2])||wybrany_pionek==5){
    }
    else{
    int przed_pozornym1=pionek[gracz][wybrany_pionek][1];
    int przed_pozornym2=pionek[gracz][wybrany_pionek][2];
    int przed_pozornym_kosc=kosc;

    int kosc2=kosc;
    for(int i=0;i<kosc2-1;i++){
    kosc=1;
    ruch_pionka(pionek[gracz][wybrany_pionek][1],pionek[gracz][wybrany_pionek][2]);
    system("cls");
    zerowanie_mapy();
    nalozenie_pionkow();
    wypisanie_mapy();
    Sleep(skok_czasu);
    }

    kosc=przed_pozornym_kosc;
    pionek[gracz][wybrany_pionek][1]=przed_pozornym1;
    pionek[gracz][wybrany_pionek][2]=przed_pozornym2;
    }
}

void ruch_pionka(int a, int b)
{
    if(tryb==3){
        Sleep(3*skok_czasu);
    }
    if(pionek[gracz][wybrany_pionek][1]==baza_pionka[gracz][wybrany_pionek][1]&&pionek[gracz][wybrany_pionek][2]==baza_pionka[gracz][wybrany_pionek][2]){
        pionek[gracz][wybrany_pionek][1]=wyjscie_z_bazy[gracz][1];
        pionek[gracz][wybrany_pionek][2]=wyjscie_z_bazy[gracz][2];
    }
    else{
        for(int i=kosc;i>0;i--){
            switch(gracz){
                case 1:
                    if(a==5&&b!=5&&b!=11)
                        {b++;break;}
                    if(a==7&&b!=1&&b!=7)
                        {b--;break;}
                    if(b==5&&a!=1&&a!=7)
                        {a--;break;}
                    if(b==7&&a!=5&&a!=11)
                        {a++;break;}
                    if(a==1&&b!=7)
                        {b++;break;}
                    if(a==11&&b!=5)
                        {b--;break;}
                    if(b==1&&a==7)
                        {a--;break;}
                    if(a==6&&b!=5&&b!=11)
                        {b++;break;}
                    if(b==11&&a!=7)
                        {a++;break;}
                case 2:
                    if(a==5&&b!=5&&b!=11)
                        {b++;break;}
                    if(a==7&&b!=1&&b!=7)
                        {b--;break;}
                    if(b==5&&a!=1&&a!=7)
                        {a--;break;}
                    if(b==7&&a!=5&&a!=11)
                        {a++;break;}
                    if(a==1&&b==5)
                        {b++;break;}
                    if(b==6&&a!=5&&a!=11)
                        {a++;break;}
                    if(a==11&&b!=5)
                        {b--;break;}
                    if(b==1&&a!=5)
                        {a--;break;}
                    if(b==11&&a!=7)
                        {a++;break;}
                case 4:
                    if(a==5&&b!=5&&b!=11)
                        {b++;break;}
                    if(a==7&&b!=1&&b!=7)
                        {b--;break;}
                    if(b==5&&a!=1&&a!=7)
                        {a--;break;}
                    if(b==7&&a!=5&&a!=11)
                        {a++;break;}
                    if(a==1&&b!=7)
                        {b++;break;}
                    if(a==11&&b==7)
                       {b--;break;}
                    if(b==6&&a!=7&&a!=1)
                        {a--;break;}
                    if(b==1&&a!=5)
                        {a--;break;}
                    if(b==11&&a!=7)
                        {a++;break;}
                case 3:
                    if(a==5&&b!=5&&b!=11)
                        {b++;break;}
                    if(a==7&&b!=1&&b!=7)
                        {b--;break;}
                    if(b==5&&a!=1&&a!=7)
                        {a--;break;}
                    if(b==7&&a!=5&&a!=11)
                        {a++;break;}
                    if(a==1&&b!=7)
                        {b++;break;}
                    if(a==11&&b!=5)
                        {b--;break;}
                    if(b==1&&a!=5)
                        {a--;break;}
                    if(b==11&&a==5)
                        {a++;break;}
                    if(a==6&&b!=7&&b!=1)
                        {b--;break;}

            }
        }
        pionek[gracz][wybrany_pionek][1]=a;
        pionek[gracz][wybrany_pionek][2]=b;
    }
}

void sprawdzenie_zbicia()
{

    for(int k=1;k<5;k++){
        if(k!=gracz){
            for(int l=1;l<5;l++){
                if(pionek[gracz][wybrany_pionek][1]==pionek[k][l][1]&&pionek[gracz][wybrany_pionek][2]==pionek[k][l][2]){
                    if(gracz==1)
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),12);
                    if(gracz==2)
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
                    if(gracz==3)
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),10);
                    if(gracz==4)
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),14);
                    cout<<"Gracz "<<nazwa_gracza[gracz]<<" zbil pionka graczowi "<<nazwa_gracza[k]<<"!"<<endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),15);
                    Sleep(3*skok_czasu);
                    pionek[k][l][1]=baza_pionka[k][l][1];
                    pionek[k][l][2]=baza_pionka[k][l][2];
                    kosc=6;
                }
            }
        }
    }
}

