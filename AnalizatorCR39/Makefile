#Makefile Bartłomiej Kliś v.2.0

CXX = g++ -g
CFLAGS = -Wall -pedantic -O2 -std="c++11"
LIBS = -pthread -I/usr/include/opencv -lopencv_shape -lopencv_stitching -lopencv_superres -lopencv_videostab -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_cvv -lopencv_dnn -lopencv_dpm -lopencv_fuzzy -lopencv_hdf -lopencv_line_descriptor -lopencv_optflow -lopencv_plot -lopencv_reg -lopencv_saliency -lopencv_stereo -lopencv_structured_light -lopencv_rgbd -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_text -lopencv_face -lopencv_video -lopencv_ximgproc -lopencv_calib3d -lopencv_features2d -lopencv_flann -lopencv_xobjdetect -lopencv_objdetect -lopencv_ml -lopencv_xphoto -lopencv_highgui -lopencv_videoio -lopencv_imgcodecs -lopencv_photo -lopencv_imgproc -lopencv_core

OBJ = main.o funkcje.o pliki.o komunikacja.o

all:	program czysc
program:	$(OBJ)
		$(CXX) $(CFLAGS) $(LIBS) $^ -o $@
czysc:
		rm *.o
clear:
		rm -f *.o program *.hpp.gch
.PHONY: all clear
