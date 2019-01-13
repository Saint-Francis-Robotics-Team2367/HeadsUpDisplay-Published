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
    BarGraph();
    BarGraph(int xPos, int yPos, int scaleValues, int height);
    void drawGraph();
    void updateGraph(int fill);
    //gotta add all the mat files in maybe an array since you will have a finite amount per bargraph
    //add setters and getters
    
private:
    int _xPos;
    int _yPos;
    int _fill;
    double _scaleValues;
    int _scaleSize;
    int _height;
    cv::Mat img;
    
    void _drawInnerRectangle(int fill);
    void _drawOuterRectangle();
    void _drawBaseLine();
    
};

#endif /* barGraph_hpp */
