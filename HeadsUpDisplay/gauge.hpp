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

class Gauge
{
    
public:
    Gauge();
    Gauge(int x, int y, int lowerRange, int upperRange, int size, int r, int g, int b, int alpha, double increment, int startingValue, bool showMin, bool showMax);//done
    Gauge(int x, int y, int lowerRange, int upperRange, int size, int r, int g, int b, int alpha);//done
    Mat drawGauge(Mat img);//done
    int getX();//done
    int getY();
    void setX(int x);
    void setY(int y);
    int getIncrement();
    void setIncrement(double increment);
    int getGaugeValue();
    void setGaugeValue(int value);//done
    Scalar getBackgroundColor();
    void setBackgroundColor(int r, int g, int b, Mat img);
    Scalar getTickerColor();
    void setTickerColor(int r, int g, int b);
    int getImageWidth();//in pixels
    int getImageHeight();//in pixels
    int getLowerRange();
    void setLowerRange(int lowerRange, Mat img);
    int getUpperRange();
    void setUpperRange(int upperRange, Mat img);
    int getGaugeSize();
    void setGaugeSize(int size, Mat img);
    
    
private:
    int _xPos;
    int _yPos;
    int _lowerRange;
    int _upperRange;
    int _size;
    double _increment;
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
    Mat _img;
    bool _showMin;
    bool _showMax;
    
    
    void _drawInitialGauge(int value, int r, int g, int b, Mat img);
    void _drawTicker(Mat img);
    void _drawArc(Mat img);
    void _updateBackground(int r, int g, int b);//will use current value for redrawing ticker
    void _gaugeLogic(int x1, int x2, int x3, int y1, int y2, int y3);
    
};

#endif // GAUGE_H
