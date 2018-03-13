#include "pliki.hpp"
#include "funkcje.hpp"
#include "komunikacja.hpp"

//Metody:
char* Zadania::getjpg()
{
	return nazwa_jpg;
}

char* Zadania::getwek()
{
	return nazwa_wek;
}

char* Zadania::getwej()
{
	return nazwa_wej;
}

//Konstruktory:

//Funkcje rozpoznajace przelaczniki:
inline bool Czy_zapis_wektora(char *zdanie)
{
	if(!strncmp(zdanie,"-o",2))
	return true;
	else
	return false;
}

inline bool Czy_zapis_jpg(char *zdanie)
{
	if(!strncmp(zdanie,"-jpg",4))
	return true;
	else
	return false;
}
inline bool Czy_zdef_nazw_jpg(char *zdanie)
{
	if(strstr(zdanie,".jpg"))
	return true;
	else
	throw "brak lub niepoprawna nazwa grafiki!";
	return false;
}

inline bool Czy_wyswietlic_okienko(char *zdanie)
{
	if(!strncmp(zdanie,"-s",2))
	return true;
	else
	return false;
}

inline bool Czy_kamera(char *zdanie)
{
	if(!strncmp(zdanie,"-v",2))
	return true;
	else
	return false;
}

inline bool Czy_zbierac(char *zdanie)
{
	if(!strncmp(zdanie,"-g",2))
	return true;
	else
	return false;
}

//Domyslny:
Zadania::Zadania()
{
	ile_zadan=2;
	zadania.Tworz_jpg=true;
	zadania.Tworz_wektor=true;
	zadania.Zdef_nazwa_jpg=true;
	zadania.Zdef_nazwa_wekt=true;
	zadania.Wektor_binarny=false;
	zadania.Wyrzuc_okienko=false;
	zadania.Kamera=false;
	zadania.Zbieraj_odczyty=false;
	zadania.Sterowanie=false;
	zadania.Manualne=false;
	
	nazwa_jpg = new char[DLUGOSC_NAZW_PLIKOW];
	strcpy(nazwa_jpg,"out.jpg");
	nazwa_wek = new char[DLUGOSC_NAZW_PLIKOW];
	strcpy(nazwa_wek,"out.dat");
	
	nazwa_wej=NULL;
	
	//automatyka:
	nazwa_urzadzenia = new char[DLUGOSC_NAZW_PLIKOW];
	strcpy(nazwa_urzadzenia,"/dev/ttyUSB0");
	jazda_x=0;
	jazda_y=0;
}

//Konstruktor bazujacy na wprowadzonych argumentach do programu
Zadania::Zadania(int ile, char *argumenty[])
{
	ile_zadan=ile;
	
	try
	{
		if ( ile < 2 )
		{
			throw "usage: program [opcje] <zdjecie>";
		}
		
		if(!strstr(argumenty[ile-1],".jpg") && !strstr(argumenty[ile-1],".png") )
		throw "Zły format pliku wejsciowego!";
		
	}
	catch(const char *txt)
	{
		std::cerr << "Złe użycie programu, powód: " << txt << std::endl;
		exit(1);
	}
	
	//Nazwa graf wejsciowej:
	nazwa_wej = new char[DLUGOSC_NAZW_PLIKOW];
	strncpy(nazwa_wej,argumenty[ile-1],DLUGOSC_NAZW_PLIKOW-1);
	
	//Konstrukcja manualna zadan w programie:
	try
	{
		for(int i=1; i<ile; i++)
		{
			
			if(Czy_zapis_wektora(argumenty[i]))
			{
				zadania.Tworz_wektor=true;
				if(ile>i)
				{
					
					if(strstr(argumenty[i+1],".dat"))
					{
						zadania.Wektor_binarny=true;
						zadania.Zdef_nazwa_wekt=true;
					}
					else if(strstr(argumenty[i+1],".txt"))
					{
						zadania.Wektor_binarny=false;
						zadania.Zdef_nazwa_wekt=true;
					}
					else
					{
						throw "brak lub niepoprawna nazwa pliku z danymi!"; //można by użyć coś lepszego
						zadania.Zdef_nazwa_wekt=false;
					}
					
				}
				else
				throw "brak nazwy wektora!";
				if(zadania.Zdef_nazwa_wekt==true)
				{
					nazwa_wek = new char[DLUGOSC_NAZW_PLIKOW];
					strncpy(nazwa_wek,argumenty[i+1],DLUGOSC_NAZW_PLIKOW-1); 
				}
				else
				{
					nazwa_wek = new char[DLUGOSC_NAZW_PLIKOW];
					strcpy(nazwa_wek,"wektor.dat");
				}
			}
			
			if(Czy_zapis_jpg(argumenty[i]))
			{
				zadania.Tworz_jpg=true;
				if(ile>i)
				zadania.Zdef_nazwa_jpg=Czy_zdef_nazw_jpg(argumenty[i+1]);
				else
				throw "brak nazwy grafiki!";
				if(zadania.Zdef_nazwa_jpg==true)
				{
					nazwa_jpg = new char[DLUGOSC_NAZW_PLIKOW];
					strncpy(nazwa_jpg,argumenty[i+1],DLUGOSC_NAZW_PLIKOW-1);
				}
				else
				{
					nazwa_jpg = new char[DLUGOSC_NAZW_PLIKOW];
					strcpy(nazwa_jpg,"zdjecie.jpg");
				}
			}
			
			if(Czy_wyswietlic_okienko(argumenty[i]))
			{
				zadania.Wyrzuc_okienko=true;
			}
			
			if(Czy_kamera(argumenty[i]))
			{
				zadania.Kamera=true;
			}
			
			if(Czy_zbierac(argumenty[i]))
			{
				zadania.Zbieraj_odczyty=true;
			}
			
			//Sterowanie automatyką:
			if(strstr(argumenty[i],"-a"))
			{
				zadania.Sterowanie=true;
				//Domyslne bujanie:
				jazda_x=5;
				jazda_y=5;
				nazwa_urzadzenia = new char[DLUGOSC_NAZW_PLIKOW];
				strcpy(nazwa_urzadzenia,"/dev/ttyUSB0");
				
				if(strstr(argumenty[i],"m"))
				{
					zadania.Manualne=true;
					jazda_x=0;
					jazda_y=0;
				}
				if(strstr(argumenty[i],"d")) //Wysokie ryzyko!
				{
					jazda_x=atoi(argumenty[i+1]);
					jazda_y=atoi(argumenty[i+2]);
				}
			}
			
			
			//Mozna dac inne
		}
		
		
	}
	catch(const char* txt)
	{
		std::cerr << "Wystąpił problem: " << txt << " Pomoc: -h" << std::endl;
		exit(99);
	}
	catch(...)
	{
		std::cerr << "Nieznany problem podczas ładowania zadan! Pomoc: -h" << std::endl;
		exit(99);
	}
	
	//Domyslnia konstrukcja zadan:
	if(ile_zadan==2)
	{
		try
		{
		
		}
		catch(...)
		{
		
		}
	}
	
}

Zadania::~Zadania()
{
	if(zadania.Zdef_nazwa_wekt)
	delete[] nazwa_wek;
	if(zadania.Zdef_nazwa_jpg)
	delete[] nazwa_jpg;
	//Zawsze:
	if(nazwa_wej!=NULL);
	delete[] nazwa_wej;
}

//Koniec konstruowania

void Wodz(Zadania &co_wykonac)
{
	//Domyslnie:
	OpenCV grafika(co_wykonac.getwej());
	OpenCV szare(grafika);
	szare.Konwersja();
	
	std::vector<cv::Vec3f> Slady; 
	Slady=szare.Transformata();
	grafika.Nanies_kolka(Slady);
	
	//Okazjonalnie:
	if(co_wykonac.zadania.Tworz_jpg)
	{
		grafika.Zapisz(co_wykonac.getjpg());
	}
	
	if(co_wykonac.zadania.Tworz_wektor)
	{
		if(co_wykonac.zadania.Wektor_binarny)
		{
			Zapisz_wek_dat(co_wykonac.nazwa_wek,Slady); //nieukonczone
		}
		else
		{
			Zapisz_wek_txt(co_wykonac.nazwa_wek,Slady);
		}
	}
	
	if(co_wykonac.zadania.Wyrzuc_okienko)
	{
		grafika.Wyswietl();
	}
	/*
	if(co_wykonac.zadania.Sterowanie)
	{
		if(co_wykonac.zadania.Manualne)
		{
			
		}
		else
		{
			co_wykonac.watek1 = std::thread(Petle,co_wykonac.nazwa_urzadzenia,co_wykonac.jazda_x,co_wykonac.jazda_y);
		}
	}
	*/
	if(co_wykonac.zadania.Kamera)
	{
		grafika.Video(co_wykonac.zadania.Zbieraj_odczyty,co_wykonac.nazwa_wek,25,true);
	}
	/*
	if(co_wykonac.zadania.Sterowanie && !co_wykonac.zadania.Manualne) //chwilowo
	{
		co_wykonac.watek1.join();
	}
	* */
}
