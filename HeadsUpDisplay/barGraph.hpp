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
    BarGraph(int x, int y, int scaleValues, int width, int height, int r, int g, int b, int alpha);//done
    void drawBarGraph(Mat img);//done
    int getX();
    void setX(int x);
    int getY();
    void setY(int y);
    int getCurrentFill();
    void setCurrentFill(int newFill);
    int getIncrement();
    void setIncrement(int increment);//does it really matter if it is an int or a double
    Scalar getInnerRectangleColor();//change the name of this in Gauge and here and wherever else it shows up
    void setInnerRectangleColor(int r, int g, int b);
    Scalar getOuterRectangleColor();//change the name of this in Gauge and here and wherever else it shows up
    void setOuterRectangleColor(int r, int g, int b);
    int getBarGraphWidth();
    int getBarGraphHeight();
    void setBarGraphSize(int width, int height);
    //gotta add all the mat files in maybe an array since you will have a finite amount per bargraph
    //add setters and getters
    
private:
    int _x;
    int _y;
    int _fill;
    int _rInner;
    int _gInner;
    int _bInner;
    int _rOuter;
    int _gOuter;
    int _bOuter;
    int _width;
    int _height;
    int _heightOfInnerRectangle;
    int _increment;
    int _alpha;
    double _scaleValues;
    int _scaleSize;
    int _thickness;
    Mat _innerRectangleForeground;
    Mat _innerRectangleAlpha;
    Mat _outerRectangleForeground;
    Mat _outerRectangleAlpha;
    
    void _drawInnerRectangle(Mat img);//done
    void _updateInnerRectangle();//done
    void _drawLocalInnerRectangle();//done
    void _drawOuterRectangle(Mat img);//done
    void _updateOuterRectangle();//done
    void _drawLocalOuterRectangle();//done
    void _drawInitialBarGraph();
    //void _drawBaseLine(); not sure if this is absolutely necessary
    
};

#endif /* barGraph_hpp */
