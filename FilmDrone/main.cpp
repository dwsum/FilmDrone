#include <iostream>
#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui_c.h>
#include <opencv2/imgproc.hpp>
#include "math.h"

#include <chrono>

#define CHOSEN_WINDOW 85 //350 for pi, 60 for computer          //note in milliseconds. NOTE: This is milliseconds per frame
#define FRAMES_PER_SECOND ((1.0 / CHOSEN_WINDOW) * 1000)        //note, this is the frames per second used in some caluclations

#define DESIRED_TIME 15            //IN SECONDS

#define VIDEO_LENGTH (DESIRED_TIME * 1 / FRAMES_PER_SECOND)

#define VIDEO_WIDTH 640
#define VIDEO_HEIGHT 480


using namespace std;
using namespace cv;

VideoCapture cap(0);

int main() {
    int cntr = 0;




    //set up camera
    if(!cap.isOpened()) {
        std::cout << "Error opening video stream or file" << std::endl;
    }
    cap.set(CAP_PROP_FRAME_WIDTH, VIDEO_WIDTH);
    cap.set(CAP_PROP_FRAME_HEIGHT, VIDEO_HEIGHT);


    //set up things for saving video
    VideoWriter writer;

    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    char buffer [80];
    strftime (buffer,80,"%Y-%m-%d.",now);

    auto codec = VideoWriter::fourcc('m', 'p', '4', 'v');
    auto fps = FRAMES_PER_SECOND;
    auto filename = buffer;

    writer.open(filename, codec, fps, {VIDEO_WIDTH, VIDEO_HEIGHT}, true);

    if(!writer.isOpened()) {
        std::cout << "writer didn't open..." << std::endl;
    }

    //recording
    while(cntr < VIDEO_LENGTH) {
        auto start = chrono::high_resolution_clock::now();
        Mat frame;

        //frame << cap;

        char c = (char)waitKey(25);
        if(c==27)
            break;

        auto end = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
        if(duration.count() > CHOSEN_WINDOW) {
            std::cout << "the chosen window is too small. The duration here is " << duration.count() << std::endl;
        }
        while (duration.count() < CHOSEN_WINDOW) {
            end = chrono::high_resolution_clock::now();
            duration = chrono::duration_cast<chrono::milliseconds>(end - start);
            std::cout << "duration " << duration.count() << std::endl;
        }
        cntr ++;
        writer.write(frame);
    }

    
    
    return 0;
}