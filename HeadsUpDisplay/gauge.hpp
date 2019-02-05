//
//  gauge.hpp
//  HeadsUpDisplay
//
//  Created by Jeevan Prakash on 11/24/18.
//  Copyright © 2018 Jeevan Prakash. All rights reserved.
//

#ifndef GAUGE_H
#define GAUGE_H

#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

class Gauge{
    
public:
    Gauge();
    Gauge(int x, int y, int size, int r, int g, int b, double increment, int startingValue, bool showMin, bool showMax);
    Gauge(int x, int y, int size, int r, int g, int b);
    Gauge(int x, int y, int size, int r, int g, int b, int startingValue, double angleIncrement, int endAngle);
    void drawGauge(Mat img);
    int getX();
    int getY();
    void setX(int x);
    void setY(int y);
    int getIncrement();
    void setIncrement(double increment);
    int getGaugeValue();
    void setGaugeValue(int value);
    Scalar getGaugeColor();
    void setGaugeColor(int r, int g, int b);
    Scalar getTickerColor();
    void setTickerColor(int r, int g, int b);
    int getLowerRange();
    void setLowerRange(int lowerRange);
    int getUpperRange();
    void setUpperRange(int upperRange);
    int getGaugeSize();
    void setGaugeSize(int size);
    int getThickness();
    void setThickness(int thickness);
    int getAngleIncrement();
    void setAngleIncrement(int angleIncrement);
    int getEndAngle();
    void setEndAngle(int endAngle);
    void showGauge();
    void showTicker();
    void hideGauge();
    void hideTicker();
    
    
private:
    int _xPos;
    int _yPos;
    int _lowerRange;
    int _upperRange;
    int _size;
    double _increment;
    int _angleIncrement;
    int _endAngle;
    int _width;
    int _height;
    int _currentValue;
    int _r;
    int _g;
    int _b;
    int _alpha;
    int _rTicker;
    int _gTicker;
    int _bTicker;
    int _thickness;
    int _startingXTicker;
    int _startingYTicker;
    int _endingXTicker;
    int _endingYTicker;
    int _tickerAlphaX;
    int _tickerAlphaY;
    int _tickerWidth;
    int _tickerHeight;
    Mat _gaugeForeground;
    Mat _gaugeAlpha;
    Mat _tickerForeground;
    Mat _tickerAlpha;
    bool _showMin;
    bool _showMax;
    bool _showGauge;
    bool _showTicker;
    
    void _drawInitialGauge();
    void _drawTicker(Mat img);
    void _drawLocalTicker();
    void _drawArc(Mat img);
    void _drawLocalArc();
    void _updateTicker();
    void _updateGauge();
    void _gaugeLogic(int x1, int x2, int x3, int y1, int y2, int y3);
    
};

#endif /* gauge.hpp */
