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
        this->_upperRange = 10;
        this->_size = 50;
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

    Gauge::Gauge(int x, int y, int lowerRange, int upperRange, int size, int r, int g, int b, int alpha, double increment, int startingValue, bool showMin, bool showMax){//I shouldn't take in a Size() parameter, instead I should take in an integer since the width and height needs to be the same
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
    Gauge::Gauge(int x, int y, int lowerRange, int upperRange, int size, int r, int g, int b, int alpha){
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
        int thickness = 4;
        int lineType = LINE_8;
        int shift = 0;
        
        Mat
        gaugeForground,    //text color layer
        gaugeAlpha,        //text draw layer
        image_roi;        //roi of output image
        
        //release memory
        gaugeForground.release();
        gaugeAlpha.release();
        
        
        int x1, y1;//center point of gauge
        int degrees = value * 36;//might need to add the angleincrement to this so it might need to be a private member variable
        //int degrees  = 10;
        if(degrees>360) degrees -= 360;
        double radians = degrees * (M_PI/180);
        int size = getGaugeSize();
        int x2, y2;//point that touches the gauge
        int imageX, imageY;//top-left corner point of image_roi
        int tickerWidth, tickerHeight;
        //need some sort of logic to figure out what quadrant the things are
        //I have to make sure that negative angles are not inputted
        //I have to make sure that the end angle and angleIncrement does not go over 360 (I could just substract 360 from them)
        //I have to make sure that the start angle does not go over the end angle (I could just switch the values in my code)
        
        if(0<=degrees && degrees<=90){
            imageX = getX();
            imageY = getY() - round((sin(radians))*size);
            radians = degrees * (M_PI/180);
            if(degrees == 0){
                tickerWidth = round((cos(radians))*size);
                tickerHeight = round((sin(radians))*size) + 5;
                x1 = 0;
                y1 = 2;
                x2 = tickerWidth;
                y2 = 2;
            } else if(degrees == 90) {
                tickerWidth = round((cos(radians))*size) + 5;
                tickerHeight = round((sin(radians))*size);
                x1 = 2;
                y1 = tickerHeight;
                x2 = 2;
                y2 = 0;
            } else {
                tickerWidth = round((cos(radians))*size);
                tickerHeight = round((sin(radians))*size);
                x1 = 0;
                y1 = tickerHeight;
                x2 = tickerWidth;
                y2 = 0;
            }
        } else if(90<degrees && degrees<=180){
            degrees = 180 - degrees;
            radians = degrees * (M_PI/180);
            imageX = getX() - round((cos(radians))*size);
            imageY = getY() - round((sin(radians))*size);
            if(degrees == 0){
                tickerWidth = round((cos(radians))*size);
                tickerHeight = round((sin(radians))*size) + 5;
                x1 = tickerWidth;
                y1 = 2;
                x2 = 0;
                y2 = 2;
            } else {
                tickerWidth = round((cos(radians))*size);
                tickerHeight = round((sin(radians))*size);
                x1 = tickerWidth;
                y1 = tickerHeight;
                x2 = 0;
                y2 = 0;
            }
        } else if(180<degrees && degrees<=270){
            degrees = degrees - 180;
            radians = degrees * (M_PI/180);
            imageX = getX() - round((cos(radians))*size);
            imageY = getY();
            if(degrees == 90){
                tickerWidth = round((cos(radians))*size) + 5;
                tickerHeight = round((sin(radians))*size);
                x1 = 2;
                y1 = 0;
                x2 = 2;
                y2 = tickerHeight;
            } else {
                tickerWidth = round((cos(radians))*size);
                tickerHeight = round((sin(radians))*size);
                x1 = tickerWidth;
                y1 = 0;
                x2 = 0;
                y2 = tickerHeight;
            }
        } else {
            degrees = 360 - degrees;
            radians = degrees * (M_PI/180);
            imageX = getX();
            imageY = getY();
            if(degrees == 0){
                tickerWidth = round((cos(radians))*size);
                tickerHeight = round((sin(radians))*size) + 5;
                x1 = 0;
                y1 = 2;
                x2 = tickerWidth;
                y2 = 2;
            } else {
                tickerWidth = round((cos(radians))*size);
                tickerHeight = round((sin(radians))*size);
                x1 = 0;
                y1 = 0;
                x2 = tickerWidth;
                y2 = tickerHeight;
            }
        }
        
        //allocate images based on text settings
        gaugeForground = Mat(tickerHeight, tickerWidth, CV_8UC3, getBackgroundColor());//need to edit the instantiation based upon the new dimensions and x,y coordinate of the alpha layer that the ellipse needs to fit in
        gaugeAlpha = Mat(tickerHeight, tickerWidth, CV_8UC1, Scalar(0));//need to edit the instantiation based upon the new dimensions and x,y coordinate of the alpha layer that the ellipse needs to fit in
        
        //draw line onto alpha layer
        line(gaugeAlpha, Point(x1, y1), Point(x2,y2), getBackgroundColor(), thickness, lineType, shift);//I need to fix the starting point :facepalm:
        //it all depends on what quadrant it is so yeet
        
        //ellipse(textAlpha, Point(0,textAlpha.size().height/2+20), getGaugeSize(), angleIncrement, startAngle, endAngle, Scalar(255), thickness, lineType, shift);
        
        
        
        //check that the ellipse is in frame so the bitwise operations don't crash
        if(imageX < 0 || imageY < 0 || imageX + tickerWidth > img.size().width || imageY + tickerHeight > img.size().height)
        {//need to edit the conditional based upon the new dimensions and x,y coordinate of the alpha layer that the ellipse needs to fit in
            cout <<"[WARNING] Gauge goes out of frame"<<endl;
        }
        
        else
        {
            image_roi = img(Rect(imageX, imageY, gaugeAlpha.size().width, gaugeAlpha.size().height));//need to edit the instantiation of the Rect based upon the new dimensions and x,y coordinate of the alpha layer that the ellipse needs to fit in
            bitwise_and(image_roi, Scalar(0), image_roi, gaugeAlpha);
            bitwise_or(image_roi, gaugeForground, image_roi,gaugeAlpha);
        }
        
        imshow("Alpha: Ticker", gaugeAlpha);
        
    }

    void Gauge::_drawArc(Mat img){
        
        this->_width = img.size().width;
        this->_height = img.size().height;
        int thickness = 4;
        int shift = 0;
        int lineType = LINE_8;
        int angleIncrement = 0;
        int startAngle = 0;
        int endAngle = 360;
        
        //opencv data vars
        //VideoCapture capture; //camera feed
        
        Mat
        gaugeForground,    //text color layer
        gaugeAlpha,        //text draw layer
        image_roi;        //roi of output image
        
        //release memory
        gaugeForground.release();
        gaugeAlpha.release();
        
        /*
         int x1, x2, x3, y1, y2, y3;
        x1 = getX();
        //need some sort of logic to figure out what quadrant the things are
        //I have to make sure that negative angles are not inputted (I could just add 360 to the inputted angle)
        //I have to make sure that the end angle and angleIncrement does not go over 360 (I could just substract 360 from them)
        //I have to make sure that the start angle does not go over the end angle (I could just switch the values in my code)
        
        if(0<=angleIncrement+startAngle && angleIncrement+startAngle<=90){
            x2 = getX() + abs(cos(angleIncrement)*getGaugeSize().width);
            y2 = getY() - abs(sin(angleIncrement)*getGaugeSize().width);
            if(angleIncrement+(endAngle-startAngle)<=90){
                x3 = getX() + cos(angleIncrement)*getGaugeSize().width;
                y3 = getY() - sin(angleIncrement)*getGaugeSize().width;
            }
        }
        if(90<angleIncrement+startAngle && angleIncrement+startAngle<=180){
            x2 = getX() - abs(cos(angleIncrement)*getGaugeSize().width);
            y2 = getY() - abs(sin(angleIncrement)*getGaugeSize().width);
        }
        if(180<angleIncrement+startAngle && angleIncrement+startAngle<=270){
            x2 = getX() - abs(cos(angleIncrement)*getGaugeSize().width);
            y2 = getY() + abs(sin(angleIncrement)*getGaugeSize().width);
        }
        else{
            x2 = getX() + abs(cos(angleIncrement)*getGaugeSize().width);
            y2 = getY() + abs(sin(angleIncrement)*getGaugeSize().width);
        }
        x2 = getX();
        y1 = getY();
        
        */
        int size = getGaugeSize();
        //allocate images based on text settings
        gaugeForground = Mat(size*2, size*2, CV_8UC3, getBackgroundColor());//need to edit the instantiation based upon the new dimensions and x,y coordinate of the alpha layer that the ellipse needs to fit in
        gaugeAlpha = Mat(size*2, size*2, CV_8UC1, Scalar(0));//need to edit the instantiation based upon the new dimensions and x,y coordinate of the alpha layer that the ellipse needs to fit in
        
        //draw ellipses onto alpha layer
        ellipse(gaugeAlpha, Point(size,size), Size(size, size), angleIncrement, startAngle, endAngle, Scalar(255), thickness, lineType, shift);
        //ellipse(textAlpha, Point(0,textAlpha.size().height/2+20), getGaugeSize(), angleIncrement, startAngle, endAngle, Scalar(255), thickness, lineType, shift);
        
        
        
        //check that the ellipse is in frame so the bitwise operations don't crash
        if(getX()-gaugeAlpha.size().width/2 < 0 || getY()-gaugeAlpha.size().height/2 < 0 || getX()-gaugeAlpha.size().width/2 + gaugeAlpha.size().width > img.size().width || getY() + gaugeAlpha.size().height > img.size().height)
        {//need to edit the conditional based upon the new dimensions and x,y coordinate of the alpha layer that the ellipse needs to fit in
            cout <<"[WARNING] Gauge goes out of frame"<<endl;
        }
        
        else
        {
            image_roi = img(Rect(getX()-gaugeAlpha.size().width/2, getY()-gaugeAlpha.size().height/2, gaugeAlpha.size().width, gaugeAlpha.size().height));//need to edit the instantiation of the Rect based upon the new dimensions and x,y coordinate of the alpha layer that the ellipse needs to fit in
            bitwise_and(image_roi, Scalar(0), image_roi, gaugeAlpha);
            bitwise_or(image_roi, gaugeForground, image_roi,gaugeAlpha);
        }
        
        imshow("Alpha: Gauge", gaugeAlpha);
        
    }

    void Gauge::_gaugeLogic(int x1, int x2, int x3, int y1, int y2, int y3){
        bool a = x1<x2;
        bool b = x2<x3;
        bool c = x1<x3;
        bool d = y1<y2;
        bool e = y2<y3;
        bool f = y1<y3;
        int minX;//6 5 7
        int minY;
        int maxX;//
        int maxY;
        
        if(a){
            if(c){
                minX = x1;
                if(b){
                    maxX = x3;
                } else {
                    maxX = x2;
                }
            } else {
                minX = x3;
                maxX = x2;
            }
            
        } else {
            if(b){
                minX = x2;
                if(!c){
                    maxX = x1;
                } else {
                    maxX = x3;
                }
            } else {
                maxX = x1;
                minX = x3;
            }
        }
        
        if(d){
            if(f){
                minY = y1;
                if(e){
                    maxY = y3;
                } else {
                    maxY = y2;
                }
            } else {
                minY = y3;
                maxY = y2;
            }
            
        } else {
            if(e){
                minY = y2;
                if(!f){
                    maxY = y1;
                } else {
                    maxY = y3;
                }
            } else {
                maxY = y1;
                minY = y3;
            }
        }
        
        cout<<"Your min X:"<<minX<<endl;
        cout<<"Your min Y:"<<minY<<endl;
        cout<<"Your max X:"<<maxX<<endl;
        cout<<"Your max Y:"<<maxY<<endl;
        
        
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

    int Gauge::getGaugeSize(){
        return this->_size;
    }

    void Gauge::setGaugeSize(int size, Mat img){
        this->_size = size;
        drawGauge(getGaugeValue(), img);
    }
