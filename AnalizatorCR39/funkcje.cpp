#include "funkcje.hpp"

//Metody:
std::vector<cv::Vec3f> OpenCV::Transformata()
{
	std::vector<cv::Vec3f> kol;
	
	HoughCircles( zdjecie, kol, CV_HOUGH_GRADIENT, 1, zdjecie.rows/60, 18, 13, 1, 17 );
	
	return kol;
}

void OpenCV::Konwersja()
{
	cv::cvtColor( zdjecie, zdjecie, CV_BGR2GRAY );
    //cv::GaussianBlur( zdjecie, zdjecie, cv::Size(9, 9), 2, 2 );
}

void OpenCV::Nanies_kolka(std::vector<cv::Vec3f> naniesione)
{
	for( size_t i = 0; i < naniesione.size(); i++ )
	{
      cv::Point center(cvRound(naniesione[i][0]), cvRound(naniesione[i][1]));
      int radius = cvRound(naniesione[i][2]);
      // circle center
      cv::circle( zdjecie, center, 3, cv::Scalar(0,255,0), -1, 8, 0 );
      // circle outline
      cv::circle( zdjecie, center, radius, cv::Scalar(0,0,255), 3, 8, 0 );
   }
}

void OpenCV::Wyswietl()
{
	cv::namedWindow("Wyniki", cv::WINDOW_NORMAL );
    cv::imshow("Wyniki", zdjecie);
    cv::waitKey(0);
}

void OpenCV::Video(bool zbieranie, char *nazwa, int interwal, bool obraz)
{
	std::vector<cv::Vec3f> wyniki;
	cv::VideoCapture cap(0);
	long int ile_iteracji=0;
	std::ofstream ofile;
	
	try
	{
		
		if(!cap.isOpened())
		{
			throw "nie można uruchomic urzadzenia!";
		}
	}
	catch(const char *er)
	{
		std::cerr << "Bład wykonania: " << er << std::endl;
		exit(3);
	}
	
	if(obraz)
	{
		cv::namedWindow("Podglad",1);
	}
	if(zbieranie)
	{
		ofile.open(nazwa);
		ofile << 0 << std::endl;
		ofile.close();
	}
	
	for(;;)
    {
        cv::Mat frame;
        cap >> frame; // get a new frame from camera
		zdjecie=frame;
		Konwersja();
		wyniki=Transformata();
		//Jesli ma zczytywac dane
		if(zbieranie && ile_iteracji>=interwal)
		{
			wyniki[0][2]=ile_iteracji/interwal;
			Zapisz_wek_txt(nazwa,wyniki,true);
			
		}
		if(obraz) 
		{
			Nanies_kolka(wyniki);
			cv::imshow("orginal", frame);
			cv::imshow("wynik", zdjecie);
		}
        if(cv::waitKey(30) == 27) break;
        ile_iteracji++;
    }
    
}

void OpenCV::Zapisz(char *nazwa)
{
	try
	{
		std::vector<int> compression_params;
		compression_params.push_back(CV_IMWRITE_JPEG_QUALITY);
		compression_params.push_back(95);
		imwrite(nazwa, zdjecie, compression_params);
	}
	catch(...)
	{
		std::cerr << "Bład zapisu grafiki!" << std::endl;
		exit(3);
	}
}

cv::Mat OpenCV::getMat()
{
	return zdjecie;
}

//Konstruktory:
OpenCV::OpenCV(char *nazwa)
{
	try
	{
		zdjecie = cv::imread( nazwa, 1);
		if ( !zdjecie.data )	
		{
			throw "Problem z odczytem zdjęcia";
		}
	}
	catch(const char *er)
	{
		std::cerr << "Bład wykonania, powód: " << er << std::endl;
		exit(2);
	}
	
}
OpenCV::OpenCV(OpenCV &kopia)
{
	zdjecie=kopia.zdjecie;
}
OpenCV::~OpenCV()
{
	
}

//Funkcje zewnetrzne:
void Zapisz_wek_dat(char *nazwa, std::vector<cv::Vec3f> &dane)
{
	
}

void Zapisz_wek_txt(char *nazwa, std::vector<cv::Vec3f> &dane,bool dopisz)
{
	std::fstream ofile;
	if(dopisz)
	{
		ofile.open(nazwa,std::ios_base::in | std::ios_base::out);
		ofile.seekg(0, std::ios::beg);
		ofile << (int) dane[0][2] << std::endl;
		ofile.seekg(0, std::ios::end); 
	}
	else
	{
		ofile.open(nazwa,std::fstream::out);
		ofile << dane.size() << std::endl;
	}
	for(unsigned int i=0; i<dane.size(); i++)
	{
		if(dopisz && i==0)
		continue;
		ofile << dane[i][2]/320*1000 << std::endl; //dla 640x480 w um

	}
	ofile.close();
}
