#ifndef _komunikacja_hpp_
#define _komunikacja_hpp_

#include <fstream>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

class Mikrokontroler{
	
	char *nazwa;
	int urzadzenie;
	struct termios config;
	public:
	//Metody:
	void Stop();
	int MovX(int x);
	int MovY(int y);
	bool Inicjalizacja();
	void On();
	void Off();
	
	//Konstruktory:
	Mikrokontroler();
	Mikrokontroler(char *lokalizacja);
	~Mikrokontroler();
	
};

void Petle(char *nazwa,int x,int y);
void Manualne(char *nazwa);


#endif
