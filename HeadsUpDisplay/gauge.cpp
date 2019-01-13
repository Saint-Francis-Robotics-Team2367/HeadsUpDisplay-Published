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
        this->_size = 50;
        this->_r = 0;
        this->_g = 0;
        this->_b = 0;
        this->_rTicker = 0;
        this->_gTicker = 0;
        this->_bTicker = 0;
        this->_increment = 1;
        this->_currentValue = 0;
    }

    Gauge::Gauge(int x, int y, int lowerRange, int upperRange, int size, int r, int g, int b, double increment, int startingValue, bool showMin, bool showMax){
        this->_xPos = x;
        this->_yPos = y;
        this->_lowerRange = lowerRange;
        this->_upperRange = upperRange;
        this->_size = size;
        this->_r = r;
        this->_g = g;
        this->_b = b;
        this->_rTicker = r;
        this->_gTicker = g;
        this->_bTicker = b;
        this->_increment = increment;
        this->_currentValue = startingValue;
        //need to instantiate the img that this gauge will be drawn on
    }
    Gauge::Gauge(int x, int y, int lowerRange, int upperRange, int size, int r, int g, int b){
        this->_xPos = x;
        this->_yPos = y;
        this->_lowerRange = lowerRange;
        this->_upperRange = upperRange;
        this->_size = size;
        this->_r = r;
        this->_g = g;
        this->_b = b;
        this->_rTicker = r;
        this->_gTicker = g;
        this->_bTicker = b;
        this->_increment = 1.0;
        this->_currentValue = 0;
        //need to instantiate the img that this gauge will be drawn on
    }
    
    void Gauge::drawGauge(int value, Mat img){
        cout<<img.size().width<<endl;
        this->_width = img.size().width;
        this->_height = img.size().height;
        int thickness = 10;
        int shift = 0;
        int lineType = LINE_8;
        int angleIncrement = 0;
        int startAngle = 0;
        int endAngle = 90;
        cout<<getImageWidth()<<endl;//why does this print out 0800 instead of 800?
        cout<<getImageHeight()<<endl;
        
        ellipse(img, Point((getImageWidth()/3)-20,(getImageHeight()/3)+70), Size(getSizeGauge(),getSizeGauge()), angleIncrement, startAngle, endAngle, getBackgroundColor(), thickness, lineType, shift);//Scalar(b,g,r)
        //ellipse(img, Point((getImageWidth()/3)-40,(getImageHeight()/3)+70), Size(50,50), angleIncrement+77, startAngle, endAngle, Scalar(b,g,r), thickness, lineType, shift);
        
        _drawTicker(value);
    }
    
    void Gauge::_drawInitialGauge(int value, int r, int g, int b){
        //what was the purpose of this again
    }
    
    void Gauge::_drawTicker(int value){
        //need a drawLine function here
    }

    void Gauge::_updateBackground(int r, int g, int b){
        //not sure what this one is meant to do
    }

    int Gauge::getX(){
        return this->_xPos;
    }

    int Gauge::getY(){
        return this->_yPos;
    }

    void Gauge::setX(int x){
        this->_xPos = x;
    }

    void Gauge::setY(int y){
        this->_yPos = y;
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
    }

    Scalar Gauge::getBackgroundColor(){
        return Scalar(this->_b,this->_g,this->_r);
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
        _drawTicker(0);
    }

    int Gauge::getImageWidth(){
        return this->_width;
    }

    int Gauge::getImageHeight(){
        return this->_height;
    }

    int Gauge::getSizeGauge(){
        return this->_size;
    }

    void Gauge::setSizeGauge(int size, Mat img){
        this->_size = size;
        drawGauge(getGaugeValue(), img);
    }
