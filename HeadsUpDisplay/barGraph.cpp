//
//  barGraph.cpp
//  HeadsUpDisplay
//
//  Created by Jeevan Prakash on 11/24/18.
//  Copyright © 2018 Jeevan Prakash. All rights reserved.
//

#include "barGraph.hpp"

    //constructor 1
    BarGraph::BarGraph(){
        this->_x = 0;
        this->_y = 0;
        this->_scaleValues = 1;
        this->_height = 50;
        this->_rInner = 0;
        this->_gInner = 0;
        this->_bInner = 0;
        this->_rOuter = 0;
        this->_gOuter = 0;
        this->_bOuter = 0;
        this->_increment = 1;
        this->_alpha = 0;
        this->_thickness = 4;
        this->_fill = 10;
        this->_showInner = true;
        this->_showOuter = true;
        _drawInitialBarGraph();
    }

    //constructor 2
    BarGraph::BarGraph(int x, int y, int scaleValues, int width, int height, int r, int g, int b, int alpha){
        this->_x = x;
        this->_y = y;
        this->_scaleValues = scaleValues;
        this->_width = width;
        this->_height = height;
        this->_rInner = r;
        this->_gInner = g;
        this->_bInner = b;
        this->_rOuter = r;
        this->_gOuter = g;
        this->_bOuter = b;
        this->_increment = 1;
        this->_alpha = alpha;
        this->_thickness = 4;
        this->_fill = 10;
        this->_showInner = true;
        this->_showOuter = true;
        _drawInitialBarGraph();
    }

    void BarGraph::_drawInitialBarGraph(){
        _updateOuterRectangle();
        _updateInnerRectangle();
    }

    void BarGraph::drawBarGraph(Mat img){
        _drawInnerRectangle(img);
        _drawOuterRectangle(img);
    }

    void BarGraph::_drawInnerRectangle(Mat img){
        Mat image_roi; //roi of output image
        int x = getX();
        int y = getY() + (this->_height - this->_heightOfInnerRectangle);
        
        //check that the outer rectangle is in frame so the bitwise operations don't crash
        if(x < 0 || y < 0 || x + this->_innerRectangleAlpha.size().width > img.size().width || y + this->_innerRectangleAlpha.size().height > img.size().height || !this->_showInner){
            cout <<"[WARNING] Outer Rectangle goes out of frame or is hidden"<<endl;
        }
        
        else{
            image_roi = img(Rect(x, y, this->_innerRectangleAlpha.size().width, this->_innerRectangleAlpha.size().height));
            bitwise_and(image_roi, Scalar(0), image_roi, this->_innerRectangleAlpha);
            bitwise_or(image_roi, this->_innerRectangleForeground, image_roi,this->_innerRectangleAlpha);
        }
        
    }

    void BarGraph::_updateInnerRectangle(){
        //release memory
        this->_innerRectangleForeground.release();
        this->_innerRectangleAlpha.release();
        
        if(this->_fill < 0) this->_fill = this->_fill * -1;
        else while(this->_fill > 100) this->_fill = this->_fill - 100;
        
        this->_heightOfInnerRectangle = this->_height * this->_fill/100;
        if(this->_heightOfInnerRectangle>this->_height) this->_heightOfInnerRectangle = this->_height;
        
        this->_innerRectangleForeground = Mat(this->_heightOfInnerRectangle + this->_thickness, this->_width + this->_thickness, CV_8UC3, getInnerRectangleColor());
        this->_innerRectangleAlpha = Mat(this->_heightOfInnerRectangle + this->_thickness, this->_width + this->_thickness, CV_8UC1, Scalar(0));
        _drawLocalInnerRectangle();
    }

    void BarGraph::_drawLocalInnerRectangle(){
        int shift = 0;
        rectangle(this->_innerRectangleAlpha, Point(0,0), Point(this->_innerRectangleAlpha.size().width,this->_innerRectangleAlpha.size().height), Scalar(255), CV_FILLED, LINE_8, shift);
    }

    /*void BarGraph::_drawBaseLine(){not sure if I really need baseline as of right now
        int thickness = 1;
        int shift = 0;
        line(this->_img, Point(this->_x+20, this->_y+50), Point(this->_x, this->_y), Scalar(0,255,255), thickness, LINE_8, shift);Make it apparent in the documentation that you put in the percentage of fill for the bargraph, and I need to implement the gauge the same way and make it apparent in the documentation
     }*/

    void BarGraph::_drawOuterRectangle(Mat img){
        Mat image_roi; //roi of output image
        
        //check that the outer rectangle is in frame so the bitwise operations don't crash
        if(getX() < 0 || getY() < 0 || getX()+this->_outerRectangleAlpha.size().width > img.size().width || getY() + this->_outerRectangleAlpha.size().height > img.size().height || !this->_showOuter){
            cout <<"[WARNING] Outer Rectangle goes out of frame or is hidden"<<endl;
        }
        
        else
        {
            image_roi = img(Rect(getX(), getY(), this->_outerRectangleAlpha.size().width, this->_outerRectangleAlpha.size().height));
            bitwise_and(image_roi, Scalar(0), image_roi, this->_outerRectangleAlpha);
            bitwise_or(image_roi, this->_outerRectangleForeground, image_roi,this->_outerRectangleAlpha);
        }
        
    }

    void BarGraph::_updateOuterRectangle(){
        //release memory
        this->_outerRectangleForeground.release();
        this->_outerRectangleAlpha.release();
        
        this->_outerRectangleForeground = Mat(this->_height + this->_thickness, this->_width + this->_thickness, CV_8UC3, getOuterRectangleColor());
        this->_outerRectangleAlpha = Mat(this->_height + this->_thickness, this->_width + this->_thickness, CV_8UC1, Scalar(0));
        
        _drawLocalOuterRectangle();
    }

    void BarGraph::_drawLocalOuterRectangle(){
        int shift = 0;
        
        rectangle(this->_outerRectangleAlpha, Point(0,0), Point(this->_outerRectangleAlpha.size().width,this->_outerRectangleAlpha.size().height), Scalar(255), this->_thickness, LINE_8, shift);
    }

    int BarGraph::getX(){
        return this->_x;
    }

    void BarGraph::setX(int x){
        this->_x = x;
    }

    int BarGraph::getY(){
        return this->_y;
    }

    void BarGraph::setY(int y){
        this->_y = y;
    }

    int BarGraph::getCurrentFill(){
        return this->_fill;
    }

    void BarGraph::setCurrentFill(int newFill){
        this->_fill = newFill;
        _updateInnerRectangle();
    }

    int BarGraph::getIncrement(){
        return this->_increment;
    }

    void BarGraph::setIncrement(int increment){
        this->_increment = increment;
    }

    Scalar BarGraph::getInnerRectangleColor(){
        return Scalar(this->_bInner,this->_gInner,this->_rInner);
    }

    void BarGraph::setInnerRectangleColor(int r, int g, int b){
        this->_rInner = r;
        this->_gInner = g;
        this->_bInner = b;
    }

    Scalar BarGraph::getOuterRectangleColor(){
        return Scalar(this->_bOuter,this->_gOuter,this->_rOuter);
    }

    void BarGraph::setOuterRectangleColor(int r, int g, int b){
        this->_rOuter = r;
        this->_gOuter = g;
        this->_bOuter = b;
    }

    int BarGraph::getBarGraphWidth(){
        return this->_width;
    }

    int BarGraph::getBarGraphHeight(){
        return this->_height;
    }

    void BarGraph::setBarGraphSize(int width, int height){
        this->_width = width;
        this->_height = height;
        _updateOuterRectangle();
        _updateInnerRectangle();
    }

    void BarGraph::showInner(){
        this->_showInner = true;
    }

    void BarGraph::showOuter(){
        this->_showOuter = true;
    }

    void BarGraph::hideInner(){
        this->_showInner = false;
    }

    void BarGraph::hideOuter(){
        this->_showOuter = false;
    }
