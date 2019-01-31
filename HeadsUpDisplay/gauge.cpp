//
//  gauge.cpp
//  HeadsUpDisplay
//
//  Created by Jeevan Prakash on 11/24/18.
//  Copyright © 2018 Jeevan Prakash. All rights reserved.
//

#include "gauge.hpp"

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
        this->_thickness = 4;
        this->_angleIncrement = 0;
        this->_endAngle = 360;
        this->_showMin = false;
        this->_showMax = false;
        this->_showGauge = true;
        this->_showTicker = true;
        _drawInitialGauge();
    }

    Gauge::Gauge(int x, int y, int lowerRange, int upperRange, int size, int r, int g, int b, int alpha, double increment, int startingValue, bool showMin, bool showMax){
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
        this->_showGauge = true;
        this->_showTicker = true;
        this->_thickness = 4;
        _drawInitialGauge();
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
        this->_showGauge = true;
        this->_showTicker = true;
        this->_thickness = 4;
        _drawInitialGauge();
    }
    
    void Gauge::drawGauge(Mat img){
        _drawArc(img);
        _drawTicker(img);
    }
    
    void Gauge::_drawInitialGauge(){
        _updateGauge();
        _updateTicker();
    }
    
    void Gauge::_drawTicker(Mat img){
        Mat image_roi; //roi of output image
        
        //check that the ticker is in frame so the bitwise operations don't crash
        if(this->_tickerAlphaX < 0 || this->_tickerAlphaY < 0 || this->_tickerAlphaX + this->_tickerWidth > img.size().width || this->_tickerAlphaY + this->_tickerHeight > img.size().height || !this->_showGauge){
            cout <<"[WARNING] Ticker goes out of frame or disabled"<<endl;
        } else {
            image_roi = img(Rect(this->_tickerAlphaX, this->_tickerAlphaY, this->_tickerAlpha.size().width, this->_tickerAlpha.size().height));
            bitwise_and(image_roi, Scalar(0), image_roi, this->_tickerAlpha);
            bitwise_or(image_roi, this->_tickerForeground, image_roi, this->_tickerAlpha);
        }
        
    }

    void Gauge::_drawArc(Mat img){
        //camera feed
        //VideoCapture capture;
        
        Mat image_roi; //roi of output image
        
        //check that the ellipse is in frame so the bitwise operations don't crash
        if(getX()-this->_gaugeAlpha.size().width/2 < 0 || getY()-this->_gaugeAlpha.size().height/2 < 0 || getX()-this->_gaugeAlpha.size().width/2 + this->_gaugeAlpha.size().width > img.size().width || getY() + this->_gaugeAlpha.size().height > img.size().height || !this->_showGauge){
            cout <<"[WARNING] Gauge goes out of frame or disabled"<<endl;
        } else {
            image_roi = img(Rect(getX()-this->_gaugeAlpha.size().width/2, getY()-this->_gaugeAlpha.size().height/2, this->_gaugeAlpha.size().width, this->_gaugeAlpha.size().height));
            bitwise_and(image_roi, Scalar(0), image_roi, this->_gaugeAlpha);
            bitwise_or(image_roi, this->_gaugeForeground, image_roi,this->_gaugeAlpha);
        }
        
    }

    void Gauge::_gaugeLogic(int x1, int x2, int x3, int y1, int y2, int y3){
        //simple logic to find the max and min x and y values
        bool a = x1<x2;
        bool b = x2<x3;
        bool c = x1<x3;
        bool d = y1<y2;
        bool e = y2<y3;
        bool f = y1<y3;
        int minX;
        int minY;
        int maxX;
        int maxY;
        
        if(a){
            if(c){
                minX = x1;
                if(b) maxX = x3;
                else maxX = x2;
            } else {
                minX = x3;
                maxX = x2;
            }
            
        } else {
            if(b){
                minX = x2;
                if(!c) maxX = x1;
                else maxX = x3;
            } else {
                maxX = x1;
                minX = x3;
            }
        }
        
        if(d){
            if(f){
                minY = y1;
                if(e) maxY = y3;
                else maxY = y2;
            } else {
                minY = y3;
                maxY = y2;
            }
            
        } else {
            if(e){
                minY = y2;
                if(!f) maxY = y1;
                else maxY = y3;
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

    void Gauge::_updateTicker(){
        //release memory
        this->_tickerForeground.release();
        this->_tickerAlpha.release();
        
        //ensures that the degrees inputted into sin and cos functions does not exceed 360 or go below 0
        if(getGaugeValue()<0) setGaugeSize(getGaugeValue() + 360);
        else while(getGaugeValue()>360) setGaugeValue(getGaugeValue()-360);
        
        int degrees = getGaugeValue();//might need to add the angleincrement to this so it might need to be a private member variable
        //I need to make it so that the user inputs a percent of the total gauge, also the user needs to be able to input how many degrees the gauge needs to go
        //The angle increment and all that can be changed later in more methods (probably going to have more member variables and setters and getters *sigh*
        //convert degrees into radians
        double radians = degrees * (M_PI/180);
        int size = getGaugeSize();//wouldn't it be easier to just use this->_size everywhere instead of this?
        //also doesn't cpp not garbage collect including variables even when we leave scope of the method...sooooo this is super inefficient???
        
        //Objeectives of below conditionals:
        //1. I have to figure out the x and y coordinate of where the alpha/foreground layer of the ticker is going to be placed on the screen
        //2. I have to figure out the width and height of the alpha/foreground layer of the ticker
        //3. I have to figure out the starting and ending Point()s inside the alpha/foreground layer of the ticker
        
        if(0<=degrees && degrees<=90){
             this->_tickerAlphaX = this->_xPos;
             this->_tickerAlphaY = this->_yPos - round((sin(radians))*size);
             radians = degrees * (M_PI/180);
             if(degrees == 0){
                 this->_tickerWidth = round((cos(radians))*size);
                 this->_tickerHeight = round((sin(radians))*size) + 5;
                 this->_startingXTicker = 0;
                 this->_startingYTicker = 2;
                 this->_endingXTicker = this->_tickerWidth;
                 this->_endingYTicker = 2;
             } else if(degrees == 90) {
                 this->_tickerWidth = round((cos(radians))*size) + 5;
                 this->_tickerHeight = round((sin(radians))*size);
                 this->_startingXTicker = 2;
                 this->_startingYTicker = this->_tickerHeight;
                 this->_endingXTicker = 2;
                 this->_endingYTicker = 0;
             } else {
                 this->_tickerWidth = round((cos(radians))*size);
                 this->_tickerHeight = round((sin(radians))*size);
                 this->_startingXTicker = 0;
                 this->_startingYTicker = this->_tickerHeight;
                 this->_endingXTicker = this->_tickerWidth;
                 this->_endingYTicker = 0;
            }
         } else if(90<degrees && degrees<=180){
             degrees = 180 - degrees;
             radians = degrees * (M_PI/180);
             this->_tickerAlphaX = this->_xPos - round((cos(radians))*size);
             this->_tickerAlphaY = this->_yPos - round((sin(radians))*size);
             if(degrees == 0){
                 this->_tickerWidth = round((cos(radians))*size);
                 this->_tickerHeight = round((sin(radians))*size) + 5;
                 this->_startingXTicker = this->_tickerWidth;
                 this->_startingYTicker = 2;
                 this->_endingXTicker = 0;
                 this->_endingYTicker = 2;
            } else {
             this->_tickerWidth = round((cos(radians))*size);
             this->_tickerHeight = round((sin(radians))*size);
             this->_startingXTicker = this->_tickerWidth;
             this->_startingYTicker = this->_tickerHeight;
             this->_endingXTicker = 0;
             this->_endingYTicker = 0;
            }
         } else if(180<degrees && degrees<=270){
             degrees = degrees - 180;
             radians = degrees * (M_PI/180);
             this->_tickerAlphaX = this->_xPos - round((cos(radians))*size);
             this->_tickerAlphaY = this->_yPos;
             if(degrees == 90){
                 this->_tickerWidth = round((cos(radians))*size) + 5;
                 this->_tickerHeight = round((sin(radians))*size);
                 this->_startingXTicker = 2;
                 this->_startingYTicker = 0;
                 this->_endingXTicker = 2;
                 this->_endingYTicker = this->_tickerHeight;
             } else {
                 this->_tickerWidth = round((cos(radians))*size);
                 this->_tickerHeight = round((sin(radians))*size);
                 this->_startingXTicker = this->_tickerWidth;
                 this->_startingYTicker = 0;
                 this->_endingXTicker = 0;
                 this->_endingYTicker = this->_tickerHeight;
            }
         } else {
             degrees = 360 - degrees;
             radians = degrees * (M_PI/180);
             this->_tickerAlphaX = this->_xPos;
             this->_tickerAlphaY = this->_yPos;
             if(degrees == 0){
                 this->_tickerWidth = round((cos(radians))*size);
                 this->_tickerHeight = round((sin(radians))*size) + 5;
                 this->_startingXTicker = 0;
                 this->_startingYTicker = 2;
                 this->_endingXTicker = this->_tickerWidth;
                 this->_endingYTicker = 2;
             } else {
                 this->_tickerWidth = round((cos(radians))*size);
                 this->_tickerHeight = round((sin(radians))*size);
                 this->_startingXTicker = 0;
                 this->_startingYTicker = 0;
                 this->_endingXTicker = this->_tickerWidth;
                 this->_endingYTicker = this->_tickerHeight;
            }
         }
        
        
        //allocate images based upon the new dimensions and x,y coordinate of the alpha layer that the ticker needs to fit in
        this->_tickerForeground = Mat(this->_tickerHeight, this->_tickerWidth, CV_8UC3, getTickerColor());
        this->_tickerAlpha = Mat(this->_tickerHeight, this->_tickerWidth, CV_8UC1, Scalar(0));
        _drawLocalTicker();
    }

    void Gauge::_drawLocalTicker(){
        int lineType = LINE_8;
        int shift = 0;
        
        //draw line onto alpha layer dependent on the angle of the line
        line(this->_tickerAlpha, Point(this->_startingXTicker, this->_startingYTicker), Point(this->_endingXTicker, this->_endingYTicker), Scalar(255), getThickness(), lineType, shift);
    }

    void Gauge::_updateGauge(){
        //release memory
        this->_gaugeForeground.release();
        this->_gaugeAlpha.release();
        
        int size = getGaugeSize();
        
        //allocate images based on gauge settings
        this->_gaugeForeground = Mat(size*2, size*2, CV_8UC3, getGaugeColor());//need to edit the instantiation based upon the new dimensions and x,y coordinate of the alpha layer that the ellipse needs to fit in
        this->_gaugeAlpha = Mat(size*2, size*2, CV_8UC1, Scalar(0));
        
        _drawLocalArc();
    }

    void Gauge::_drawLocalArc(){
        int shift = 0;
        int lineType = LINE_8;
        int angleIncrement = 0;//this should be able to change
        int startAngle = 0;//always starts at 0
        int endAngle = 360;//this can change but must always be greater 0 and never greater 360
        
        //allocate ellipse based upon the new dimensions and x,y coordinate of the alpha layer that the gauge needs to fit in
        ellipse(this->_gaugeAlpha, Point(this->_gaugeAlpha.size().width/2,this->_gaugeAlpha.size().width/2), Size(getGaugeSize(), getGaugeSize()), angleIncrement, startAngle, endAngle, Scalar(255), getThickness(), lineType, shift);
    }

    int Gauge::getX(){
        return this->_xPos;
    }

    int Gauge::getY(){
        return this->_yPos;
    }

    void Gauge::setX(int x){
        this->_xPos = x;
        _updateGauge();
        _updateTicker();
        //will need to redraw the entire gauge
    }

    void Gauge::setY(int y){
        this->_yPos = y;
        _updateGauge();
        _updateTicker();
        //will need to redraw the entire gauge
    }

    int Gauge::getLowerRange(){
        return this->_lowerRange;
    }

    void Gauge::setLowerRange(int lowerRange){
        this->_lowerRange = lowerRange;
        _updateGauge();
        _updateTicker();
    }

    int Gauge::getUpperRange(){
        return this->_upperRange;
    }

    void Gauge::setUpperRange(int upperRange){
        this->_upperRange = upperRange;
        _updateGauge();
        _updateTicker();
    }

    int Gauge::getIncrement(){
        return this->_increment;
    }

    void Gauge::setIncrement(double increment){
        this->_increment = increment;
        _updateGauge();
        _updateTicker();
    }

    int Gauge::getGaugeValue(){
        return this->_currentValue;
    }

    void Gauge::setGaugeValue(int value){
        this->_currentValue = value;
        _updateTicker();
    }

    Scalar Gauge::getGaugeColor(){
        return Scalar(this->_b,this->_g,this->_r);
    }

    void Gauge::setGaugeColor(int r, int g, int b){
        this->_r = r;
        this->_g = g;
        this->_b = b;
        _updateGauge();
        _updateTicker();
    }

    Scalar Gauge::getTickerColor(){
        return Scalar(this->_bTicker, this->_gTicker, this->_rTicker);
    }

    void Gauge::setTickerColor(int r, int g, int b){
        this->_rTicker = r;
        this->_gTicker = g;
        this->_bTicker = b;
        _updateTicker();
    }

    int Gauge::getGaugeSize(){
        return this->_size;
    }

    void Gauge::setGaugeSize(int size){
        this->_size = size;
        _updateGauge();
        _updateTicker();
    }

    int Gauge::getThickness(){
        return this->_thickness;
    }

    void Gauge::setThickness(int thickness){
        this->_thickness = thickness;
        _updateGauge();
        _updateTicker();
    }

    void Gauge::showGauge(){
        this->_showGauge = true;
    }

    void Gauge::showTicker(){
        this->_showTicker = true;
    }

    void Gauge::hideGauge(){
        this->_showGauge = false;
    }

    void Gauge::hideTicker(){
        this->_showTicker = false;
    }

    int Gauge::getAngleIncrement(){
        return this->_angleIncrement;
    }

    void Gauge::setAngleIncrement(int angleIncrement){
        this->_angleIncrement = angleIncrement;
    }

    int Gauge::getEndAngle(){
        return this->_endAngle;
    }

    void Gauge::setEndAngle(int endAngle){
        this->_endAngle = endAngle;
    }
