#include "komunikacja.hpp"
#include "pliki.hpp"

void Mikrokontroler::Stop()
{
	for(int i=0;i<4;i++)
	{
		//write(urzadzenie,1);
	}
	
	//arduino << "stop";
	//arduino.close();
}

int Mikrokontroler::MovX(int x)
{
	int a;
	//std::fstream arduino;
	//arduino.open(urzadzenie, std::ios_base::in | std::ios_base::out);
	//arduino << "movx" << x;
	//while(arduino >> a);
	//arduino >> a;
	//arduino.close();
	return a;
}
int Mikrokontroler::MovY(int y)
{
	int a;
	//std::fstream arduino;
	//arduino.open(urzadzenie, std::ios_base::in | std::ios_base::out);
	//arduino << "movy" << y;
	//while(arduino >> a);
	//arduino.close();
	return a;
}

bool Mikrokontroler::Inicjalizacja()
{
	char dane[5];
	int licznik=0;
	
	while(true && licznik < 10)
	{
		for(int i=0;i<4;i++)
		{
			//arduino >> dane[i];
		}
		if(!strncmp(dane,"star",4))
		{
			//arduino << 'o';
			return true;
		} 
		licznik++;
	}
	return false;
}

void Mikrokontroler::On()
{
	
	//arduino << "onnn";
	//arduino.close();
}

void Mikrokontroler::Off()
{
	
	//arduino << "offf";
	//arduino.close();
}

Mikrokontroler::Mikrokontroler()
{
	nazwa=NULL;
	
}

Mikrokontroler::Mikrokontroler(char *lokalizacja) //Magia
{
	nazwa = new char[DLUGOSC_NAZW_PLIKOW];
	strncpy(nazwa,lokalizacja,DLUGOSC_NAZW_PLIKOW);
	
	urzadzenie = open(nazwa, O_RDWR | O_NOCTTY | O_NDELAY);
	if(urzadzenie == -1) 
	{
		printf( "failed to open port\n" );
		exit(4);
	}
	
	memset(&config,0,sizeof(config));
    config.c_iflag=0;
    config.c_oflag=0;
    config.c_cflag=CS8|CREAD|CLOCAL;           
	config.c_lflag=0;
    config.c_cc[VMIN]=1;
    config.c_cc[VTIME]=5;

            
    cfsetospeed(&config,B9600);           
    cfsetispeed(&config,B9600);            

	tcsetattr(urzadzenie,TCSANOW,&config);
        
}

Mikrokontroler::~Mikrokontroler()
{
	if(nazwa!=NULL)
	{
		delete[] nazwa;
	}
	close(urzadzenie);
}

void Petle(char *nazwa,int x,int y)
{
	Mikrokontroler Arduino(nazwa);
	while(true)
	{
		Arduino.Inicjalizacja();
		Arduino.MovX(5);
		Arduino.MovY(5);
		break;
	}
}
void Manualne(char *nazwa)
{
	
}
	
