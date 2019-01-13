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
        this->img = img;
        this->_xPos = 0;
        this->_yPos = 0;
        this->_scaleValues = 1;
        this->_height = 50;
    }

    BarGraph::BarGraph(int xPos, int yPos, int scaleValues, int height){
        this->_xPos = xPos;
        this->_yPos = yPos;
        this->_scaleValues = scaleValues;
        this->_height = height;
    }

    void BarGraph::drawGraph(){
        _drawInnerRectangle(0);
        _drawOuterRectangle();
        _drawBaseLine();
    }
    void BarGraph::updateGraph(int fill){
        _drawInnerRectangle(fill);
    }

    void BarGraph::_drawBaseLine(){
        int thickness = 1;
        int shift = 0;
        line(this->img, Point(this->_xPos+20, this->_yPos+50), Point(this->_xPos, this->_yPos), Scalar(0,255,255), thickness, LINE_8, shift);
    }

    void BarGraph::_drawInnerRectangle(int fill){
        
    }
    void BarGraph::_drawOuterRectangle(){
        int thickness = 1;
        int shift = 0;
        rectangle(this->img, Point(400,400), Point(500,500), Scalar(0,0,255), thickness, LINE_8, shift);
    }
