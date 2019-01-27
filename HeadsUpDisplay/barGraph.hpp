//
//  barGraph.hpp
//  HeadsUpDisplay
//
//  Created by Jeevan Prakash on 11/24/18.
//  Copyright © 2018 Jeevan Prakash. All rights reserved.
//

#ifndef BARGRAPH_H
#define BARGRAPH_H

#include <stdio.h>
#include <iostream>
#include <string>

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

class BarGraph
{
    
public:
    BarGraph();//done
    BarGraph(int x, int y, int scaleValues, int height, int r, int g, int b, int alpha);//done
    Mat drawBarGraph(Mat img);//done
    void updateGraph(int fill);//done
    int getX();
    void setX(int x);
    int getY();
    void setY(int y);
    int getCurrentFill();
    void setCurrentFill();
    int getIncrement();
    void setIncrement(double increment);
    Scalar getBackgroundColor();
    void setBackgroundColor(int r, int g, int b, Mat img);
    int getBarGraphSize();
    void setBarGraphSize(int size, Mat img);
    //gotta add all the mat files in maybe an array since you will have a finite amount per bargraph
    //add setters and getters
    
private:
    int _x;
    int _y;
    int _fill;
    int _r;
    int _g;
    int _b;
    int _alpha;
    double _scaleValues;
    int _scaleSize;
    int _height;
    int _thickness;
    Mat _img;
    
    void _drawInnerRectangle(int fill);
    void _drawOuterRectangle();
    void _drawBaseLine();
    
};

#endif /* barGraph_hpp */
