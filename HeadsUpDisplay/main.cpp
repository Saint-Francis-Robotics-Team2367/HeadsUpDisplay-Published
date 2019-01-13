//
//  main.cpp
//  HeadsUpDisplay
//
//  Created by Jeevan Prakash on 11/24/18.
//  Copyright © 2018 Jeevan Prakash. All rights reserved.
//

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <tuple>
#include "gauge.hpp"
#include "textList.hpp"

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    
    
    Mat image = imread("/Users/jeevanprakash/Documents/FRCCode/HeadsUpDisplay-Published/HeadsUpDisplay/HUD_Test_Image.jpg");
    Mat overlay(image.size().height, image.size().width, CV_8UC4);
    
    Gauge *gauge = new Gauge(5,5,5,5,50,255,0,0);
    TextList *list = new TextList();
    
    image.copyTo(overlay);
    double alpha = 0;
    list->addText("stuff");
    list->editText(0, "BRUH");
    Mat textImage = list->drawList();
    //cout<<textImage<<endl;testing to see what exists inside the textImage Mat
    //I tested using textImage in the below function and it throws a runtime error
    //I think I am handling how to pass a Mat object incorrectly in my textList.cpp and here in main.cpp on line 37
    addWeighted(overlay, alpha, image, 1 - alpha, 0, image);//this function blends the two images together
    gauge->drawGauge(5,image);
    
    
    imshow("Test", image);
    waitKey(0);//41 42 46
    delete gauge;
    delete list;
    return 0;
}
