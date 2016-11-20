#include <stdio.h>
#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/video/background_segm.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/legacy/legacy.hpp"
#include "opencv2/video/tracking.hpp"
#include "opencv2/photo/photo.hpp"

using namespace std;

extern "C" void take_photo(char *str);
void take_photo(char *str)
{
    IplImage *frame = NULL;
    int num = 0;
    int key;
    CvCapture *input_camera = cvCaptureFromCAM(0);
    frame = cvQueryFrame(input_camera);
    while(frame != NULL)
    {
        num++;
 //       cout<<"i see you" <<endl;
        frame = cvQueryFrame(input_camera);
        if(num == 20)
        {
            cvSaveImage(str,frame);
            break;

        }
    }
    cvReleaseCapture(&input_camera);
}
