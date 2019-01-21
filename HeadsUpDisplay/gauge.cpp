//
//  gauge.cpp
//  HeadsUpDisplay
//
//  Created by Jeevan Prakash on 11/24/18.
//  Copyright © 2018 Jeevan Prakash. All rights reserved.
//

#include "gauge.hpp"
    
    double scaleValues;//not sure what this variable is for

    Gauge::Gauge(){
        this->_xPos = 0;
        this->_yPos = 0;
        this->_lowerRange = 0;
        this->_upperRange = 100;
        this->_size = Size(50,50);
        this->_r = 0;
        this->_g = 0;
        this->_b = 0;
        this->_rTicker = 0;
        this->_gTicker = 0;
        this->_bTicker = 0;
        this->_increment = 1;
        this->_currentValue = 0;
        Mat img(Size(800,600), CV_8UC4, Scalar(0,255,0));//is there a better way to implement creating a Mat like this into the line below?
        this->_img = img;
    }

    Gauge::Gauge(int x, int y, int lowerRange, int upperRange, Size size, int r, int g, int b, int alpha, double increment, int startingValue, bool showMin, bool showMax){
        this->_xPos = x;
        this->_yPos = y;
        this->_lowerRange = lowerRange;
        this->_upperRange = upperRange;
        this->_size = size;
        this->_r = r;
        this->_g = g;
        this->_b = b;
        this->_alpha = alpha;
        this->_rTicker = r;
        this->_gTicker = g;
        this->_bTicker = b;
        this->_increment = increment;
        this->_currentValue = startingValue;
        this->_showMin = showMin;
        this->_showMax = showMax;
        Mat img(Size(800,600), CV_8UC4, Scalar(0,255,0));//is there a better way to implement creating a Mat like this into the line below?
        this->_img = img;
    }
    Gauge::Gauge(int x, int y, int lowerRange, int upperRange, Size size, int r, int g, int b, int alpha){
        this->_xPos = x;
        this->_yPos = y;
        this->_lowerRange = lowerRange;
        this->_upperRange = upperRange;
        this->_size = size;
        this->_r = r;
        this->_g = g;
        this->_b = b;
        this->_alpha = alpha;
        this->_rTicker = r;
        this->_gTicker = g;
        this->_bTicker = b;
        this->_increment = 1.0;
        this->_currentValue = 0;
        this->_showMin = false;
        this->_showMax = false;
        Mat img(Size(800,600), CV_8UC4, Scalar(0,255,0));//is there a better way to implement creating a Mat like this into the line below?
        this->_img = img;
    }
    
    Mat Gauge::drawGauge(int value, Mat img){
        _drawArc(img);
        _drawTicker(value, img);
        
        return this->_img;
    }
    
    void Gauge::_drawInitialGauge(int value, int r, int g, int b, Mat img){
        //I need to have a flag in this class that can tell if the draw function has been drawn before or not
    }
    
    void Gauge::_drawTicker(int value, Mat img){
        //need a drawLine function here
    }

    void Gauge::_drawArc(Mat img){
        
        this->_width = img.size().width;
        this->_height = img.size().height;
        int thickness = 4;
        int shift = 0;
        int lineType = LINE_8;
        int angleIncrement = 0;
        int startAngle = 0;
        int endAngle = 90;
        
        //opencv data vars
        //VideoCapture capture; //camera feed
        
        Mat
        gaugeForground,    //text color layer
        gaugeAlpha,        //text draw layer
        image_roi;        //roi of output image
        
        //release memory
        gaugeForground.release();
        gaugeAlpha.release();
        
        //allocate images based on text settings
        gaugeForground = Mat(getGaugeSize().height+200, getGaugeSize().width+200, CV_8UC3, getBackgroundColor());//need to edit the instantiation based upon the new dimensions and x,y coordinate of the alpha layer that the ellipse needs to fit in
        gaugeAlpha = Mat(getGaugeSize().height+200, getGaugeSize().width+200, CV_8UC1, Scalar(0));//need to edit the instantiation based upon the new dimensions and x,y coordinate of the alpha layer that the ellipse needs to fit in
        
        //draw ellipses onto alpha layer
        ellipse(gaugeAlpha, Point(0,gaugeAlpha.size().height/2), getGaugeSize(), angleIncrement, startAngle, endAngle, Scalar(255), thickness, lineType, shift);
        //ellipse(textAlpha, Point(0,textAlpha.size().height/2+20), getGaugeSize(), angleIncrement, startAngle, endAngle, Scalar(255), thickness, lineType, shift);
        
        //check that the ellipse is in frame so the bitwise operations don't crash
        if(getX() + gaugeAlpha.size().width > img.size().width || getY() + gaugeAlpha.size().height > img.size().height)
        {//need to edit the conditional based upon the new dimensions and x,y coordinate of the alpha layer that the ellipse needs to fit in
            cout <<"[WARNING] Gauge goes out of frame"<<endl;
        }
        
        else
        {
            image_roi = img(Rect(getX(), getY(), gaugeAlpha.size().width, gaugeAlpha.size().height));//need to edit the instantiation of the Rect based upon the new dimensions and x,y coordinate of the alpha layer that the ellipse needs to fit in
            bitwise_and(image_roi, Scalar(0), image_roi, gaugeAlpha);
            bitwise_or(image_roi, gaugeForground, image_roi,gaugeAlpha);
        }
        
    }

    void Gauge::_updateBackground(int r, int g, int b){
        //not sure what this one is meant to do
        //I think it just update every component of the gauge
    }

    int Gauge::getX(){
        return this->_xPos;
    }

    int Gauge::getY(){
        return this->_yPos;
    }

    void Gauge::setX(int x){
        this->_xPos = x;
        //will need to redraw the entire gauge
    }

    void Gauge::setY(int y){
        this->_yPos = y;
        //will need to redraw the entire gauge
    }

    int Gauge::getLowerRange(){
        return this->_lowerRange;
    }

    void Gauge::setLowerRange(int lowerRange, Mat img){
        this->_lowerRange = lowerRange;
        drawGauge(getGaugeValue(), img);
    }

    int Gauge::getUpperRange(){
        return this->_upperRange;
    }

    void Gauge::setUpperRange(int upperRange, Mat img){
        this->_upperRange = upperRange;
        drawGauge(getGaugeValue(), img);
    }

    int Gauge::getIncrement(){
        return this->_increment;
    }

    void Gauge::setIncrement(double increment){
        this->_increment = increment;
    }

    int Gauge::getGaugeValue(){
        return this->_currentValue;
    }

    void Gauge::setGaugeValue(int value){
        this->_currentValue = value;
        _drawTicker(this->_currentValue, this->_img);
    }

    Scalar Gauge::getBackgroundColor(){
        return Scalar(this->_r,this->_g,this->_b);
    }

    void Gauge::setBackgroundColor(int r, int g, int b, Mat img){
        this->_r = r;
        this->_g = g;
        this->_b = b;
        drawGauge(getGaugeValue(), img);
    }

    Scalar Gauge::getTickerColor(){
        return Scalar(this->_bTicker, this->_gTicker, this->_rTicker);
    }

    void Gauge::setTickerColor(int r, int g, int b){
        this->_rTicker = r;
        this->_gTicker = g;
        this->_bTicker = b;
        _drawTicker(0, this->_img);
    }

    int Gauge::getImageWidth(){
        return this->_width;
    }

    int Gauge::getImageHeight(){
        return this->_height;
    }

    Size Gauge::getGaugeSize(){
        return this->_size;
    }

    void Gauge::setGaugeSize(Size size, Mat img){
        this->_size = size;
        drawGauge(getGaugeValue(), img);
    }
