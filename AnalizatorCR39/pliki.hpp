#ifndef _pliki_hpp_
#define _pliki_hpp_

#include <stdlib.h>
#include <stdexcept>
#include <iostream>
#include <string.h>
#include <stdio.h>
//#include <thread>

#define DLUGOSC_NAZW_PLIKOW 256

typedef struct Zlecenia{
	bool Tworz_wektor : 1;
	bool Tworz_jpg : 1;
	bool Zdef_nazwa_wekt : 1;
	bool Zdef_nazwa_jpg : 1;
	bool Wektor_binarny : 1;
	bool Wyrzuc_okienko : 1;
	bool Kamera : 1;
	bool Zbieraj_odczyty : 1;
	bool Sterowanie : 1;
	bool Manualne : 1;
} Zlecenia;
	
class Zadania{
	
	int ile_zadan;
	Zlecenia zadania;	
	char *nazwa_jpg;
	char *nazwa_wek;
	char *nazwa_wej;
	
	//Do automatyki:
	char *nazwa_urzadzenia;
	int jazda_x;
	int jazda_y;
	//std::thread watek1;
	
	public:
	//Metody:
	char* getjpg();
	char* getwek();
	char* getwej();
	
	friend void Wodz(Zadania &co_wykonac);
	
	//Konstrukcja zadan:
	Zadania();
	Zadania(int ile, char *argumenty[]);
	~Zadania();
};

#endif
