//
//  main.cpp
//  HeadsUpDisplay
//
//  Created by Jeevan Prakash on 11/24/18.
//  Copyright © 2018 Jeevan Prakash. All rights reserved.
//
/*
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
*/

#include <iostream>
#include <string>
#include <vector>

#include "HUD.hpp"

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    
    HUD *hud = new HUD();

    hud->addTextList();
    hud->addGauge(100, 100, 0, 100, 100, 50, 250, 100, 255);//int x, int y, int lowerRange, int upperRange, int size, int r, int g, int b, int alpha, int index)
    //There needs to be a minimum size of 5 or something for the gauge because things start to get hairy once you go below that
    hud->drawAll();
    /*
    //text settings
    string text = "Test String";
    
    int tBoxPosX = 20,
    tBoxPosY = 20,
    tBoxBorderThickness = 1,
    tBoxFont = FONT_HERSHEY_COMPLEX_SMALL,
    tBoxBaseline = 0;
    
    double tBoxFontScale =1;
    
    Scalar textColor(255,50,55);
    
    //calc dependant varsmak
    Size tBoxBorderSize;
    
    //opencv data vars
    VideoCapture capture; //camera feed
    Mat          //output Image
    textForground,    //text color layer
    textAlpha,        //text draw layer
    image_roi;        //roi of output image
    
    Mat currImg;//output Image
    currImg = imread("/Users/jeevanprakash/Desktop/Funny/IMG_0620.PNG");
    
    //timing variables to check performace
    clock_t startTime=clock(), currTime=clock();
    
    struct timeval currFrameTime,lastFrameTime;
    gettimeofday(&currFrameTime, NULL);
    
    
    //capture.open(0);
    
    if(true)//capture.isOpened()
    {
        cout << "Capture is opened" << endl;
        while(waitKey(10) != 'q')
        {
            gettimeofday(&currFrameTime, NULL);
            //calculate timing data
            long int ms =(currFrameTime.tv_sec * 1000 + currFrameTime.tv_usec / 1000) - (lastFrameTime.tv_sec * 1000 + lastFrameTime.tv_usec / 1000) ;
            text =   "Proc time: "+ to_string((float)(currTime - startTime) /CLOCKS_PER_SEC) + " FPS: " + to_string((float)(1000.0/ ms));
            lastFrameTime = currFrameTime;
            
            //log the cpu clock to see how long the alloc and draw takes
            startTime = clock();
            
            //grab image from camera
            //capture >> currImg;
            currImg = imread("/Users/jeevanprakash/Desktop/Funny/IMG_0620.PNG");
            
            if(currImg.empty())
                break;
            
            //calc size of image needed to draw text
            tBoxBorderSize = getTextSize(text,tBoxFont,tBoxFontScale, tBoxBorderThickness, &tBoxBaseline);
            
            //release memory
            textForground.release();
            textAlpha.release();
            
            //allocate images based on text settings
            textForground = Mat(tBoxBorderSize.height +tBoxBaseline, tBoxBorderSize.width,CV_8UC3,textColor);
            textAlpha = Mat(tBoxBorderSize.height+tBoxBaseline, tBoxBorderSize.width,CV_8UC1,Scalar(0));
            
            //draw text onto alpha layer
            putText(textAlpha, text, Point(0,textAlpha.size().height-tBoxBaseline), tBoxFont, tBoxFontScale, Scalar(255), tBoxBorderThickness);
            
            //check that the text is in frame so the bitwise ops don't crash
            if(tBoxPosX + textAlpha.size().width > currImg.size().width || tBoxPosY + textAlpha.size().height > currImg.size().height)
            {
                cout << "[WARNING] Text goes out of frame" <<endl;
            }
            
            else
            {
                image_roi = currImg(Rect(tBoxPosX, tBoxPosY, textAlpha.size().width, textAlpha.size().height));
                bitwise_and(image_roi, Scalar(0), image_roi, textAlpha);
                bitwise_or(image_roi, textForground, image_roi,textAlpha);
            }
            
            //log the cpu clock after alloc and draw
            currTime = clock();
            
            //show images
            imshow("Sample", currImg);
            imshow("alpha", textAlpha);
            
            cout << text << endl;
            
        }
    }
    */
    
    /*
    Mat image = imread("/Users/jeevanprakash/Documents/FRCCode/HeadsUpDisplay-Published/HeadsUpDisplay/HUD_Test_Image.jpg");
    //Mat overlay(image.size().height, image.size().width, CV_8UC4);
    Mat overlay(Size(800,600), CV_8UC4, Scalar(00,00,100,100));
    Mat img(Size(800,600), CV_8UC4, Scalar(100,0,0,100));//lower the value, the more opaque it is

    vector<Mat> channel;

    Gauge *gauge = new Gauge(5,5,5,5,50,0,0,0,0);
    TextList *list = new TextList(100,100,1,255,0,0);
    cout<<list->getColor()<<endl;
    //image.copyTo(overlay);
    //double alpha = 0;
    list->addText("stuff");
    list->editText(0, "Testing");
    cout<<list->getColor()<<endl;
    Mat textImage = list->drawList(img);
    //cout<<textImage<<endl;testing to see what exists inside the textImage Mat
    //I tested using textImage in the below function and it throws a runtime error
    //I think I am handling how to pass a Mat object incorrectly in my textList.cpp and here in main.cpp on line 37
    Mat gaugeImage = gauge->drawGauge(5, overlay);
    int baseLine = 0;
    cout<<getTextSize("Hello World", FONT_HERSHEY_COMPLEX, 1, 4, &baseLine)<<endl;//outputs width and height of the string in pixels
    //addWeighted(gaugeImage, 1 - alpha, image, 1 - alpha, 0, image);//this function blends the two images together
    //addWeighted(textImage, 1 - alpha, image, 1 - alpha, 0, image);//this function blends the two images together
    
    
    Mat backgroundimg (Size(800,600), CV_8UC4, Scalar(30,30,30,0));
    imshow("img", img);
    split(overlay, channel);
    imshow("overlay", channel[3]);
    Mat finalimg = img + overlay;
    //finalimg = finalimg + backgroundimg;
    
    imshow("Test", finalimg);
    //imshow("Test2", overlay);
    waitKey(0);//41 42 46
    delete gauge;
    delete list;
     */
    
    return 0;
}
