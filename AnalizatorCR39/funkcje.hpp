#ifndef _funkcje_hpp_
#define _funkcje_hpp_

#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class OpenCV{
	
	cv::Mat zdjecie;
    
	public:
	//Metody:
	 std::vector<cv::Vec3f> Transformata();
	 void Konwersja();
	 void Nanies_kolka(std::vector<cv::Vec3f> naniesione);
	 void Wyswietl();
	 void Video(bool zbieranie=false, char *nazwa=NULL, int interwal=1000, bool obraz=true);	//interwal w iteracjach
	 void Zapisz(char *nazwa);
	 cv::Mat getMat();
	//Konstrultory:
	OpenCV(char *nazwa=NULL);
	OpenCV(OpenCV &kopia);
	~OpenCV();
};

void Zapisz_wek_dat(char *nazwa, std::vector<cv::Vec3f> &dane);
void Zapisz_wek_txt(char *nazwa, std::vector<cv::Vec3f> &dane,bool dopisz=false);

#endif
