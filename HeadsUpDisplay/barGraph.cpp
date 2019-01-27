//
//  barGraph.cpp
//  HeadsUpDisplay
//
//  Created by Jeevan Prakash on 11/24/18.
//  Copyright © 2018 Jeevan Prakash. All rights reserved.
//

#include "barGraph.hpp"
//make setters and getters
    BarGraph::BarGraph(){
        Mat img(Size(800,600), CV_8UC4, Scalar(0,255,0,0));//is there a better way to implement creating a Mat like this into the line below?
        this->_img = img;
        this->_x = 0;
        this->_y = 0;
        this->_scaleValues = 1;
        this->_height = 50;
        this->_thickness = 4;
    }

    BarGraph::BarGraph(int x, int y, int scaleValues, int height, int r, int g, int b, int alpha){
        this->_x = x;
        this->_y = y;
        this->_scaleValues = scaleValues;
        this->_height = height;
        this->_r = r;
        this->_g = g;
        this->_b = b;
        this->_alpha = alpha;
        this->_thickness = 4;
    }

    Mat BarGraph::drawBarGraph(Mat img){
        _drawInnerRectangle(0);
        _drawOuterRectangle();
        _drawBaseLine();
        return this->_img;
    }
    void BarGraph::updateGraph(int fill){
        _drawInnerRectangle(fill);
    }

    void BarGraph::_drawBaseLine(){
        int thickness = 1;
        int shift = 0;
        line(this->_img, Point(this->_x+20, this->_y+50), Point(this->_x, this->_y), Scalar(0,255,255), thickness, LINE_8, shift);
    }

    void BarGraph::_drawInnerRectangle(int fill){
        //need to draw a filled rectangle CV_FILLED
        int shift = 0;
        rectangle(this->_img, Point(400,400), Point(500,500), Scalar(0,0,255), CV_FILLED, LINE_8, shift);
    }

    void BarGraph::_drawOuterRectangle(){
        int thickness = 1;
        int shift = 0;
        rectangle(this->_img, Point(400,400), Point(500,500), Scalar(0,0,255), thickness, LINE_8, shift);
    }
