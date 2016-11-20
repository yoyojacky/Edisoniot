GCC_MRAA_FLAG=-lmraa -lpthread
GXX_OPENCV_FLAG=-lopencv_core -lopencv_highgui -lopencv_video -lopencv_calib3d -lopencv_contrib -lopencv_stitching -lopencv_superres -lopencv_legacy -lopencv_nonfree -lopencv_videostab -lopencv_gpu -lopencv_photo -lopencv_flann -lopencv_features2d -lopencv_ml -lopencv_imgproc -lopencv_objdetect

build: main.o mycam.o
	gcc main.o mycam.o -lstdc++ $(GXX_OPENCV_FLAG) $(GCC_MRAA_FLAG) -o main

run: build
	./main

main.o: main.c
	gcc -c $(GCC_MRAA_FLAG) main.c

mycam.o: mycam.cpp
	g++ -c $(GXX_OPENCV_FLAG) mycam.cpp

clean:
	-rm main *~ *.o *.png
