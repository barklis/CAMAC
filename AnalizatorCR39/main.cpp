#include "funkcje.hpp"
#include "pliki.hpp"
#include "komunikacja.hpp"



int main(int argc, char** argv )
{
	
	Zadania jakies(argc,argv);
	OpenCV grafika(jakies.getwej());
	
	Wodz(jakies);
	
	/*
	cv::VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;

    cv::Mat edges;
    cv::namedWindow("edges",1);
    for(;;)
    {
        cv::Mat frame;
        cap >> frame; // get a new frame from camera
        cv::cvtColor(frame, edges, cv::COLOR_BGR2GRAY);
        cv::GaussianBlur(edges, edges, cv::Size(7,7), 1.5, 1.5);
        Canny(edges, edges, 0, 30, 3);
        imshow("edges", edges);
        if(cv::waitKey(30) >= 0) break;
    }
	*/
	
	/*
	OpenCV szare(grafika);
	szare.Konwersja();
	
	std::vector<cv::Vec3f> Slady; 
	Slady=szare.Transformata();
	
	grafika.Nanies_kolka(Slady);
	grafika.Zapisz(jakies.getjpg());
	*/
	
    return 0;
}
