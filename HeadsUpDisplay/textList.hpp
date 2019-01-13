//
//  textList.hpp
//  HeadsUpDisplay
//
//  Created by Jeevan Prakash on 11/24/18.
//  Copyright © 2018 Jeevan Prakash. All rights reserved.
//

#ifndef TEXTLIST_H
#define TEXTLIST_H

#include <stdio.h>
#include <iostream>
#include <string>

#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

class TextList
{
    
public:
    TextList();
    TextList(int x, int y, int scaleTextSize, int r, int g, int b);
    
    void addText(string newText);
    Mat drawList();
    string editText(int index, string newText);
    void setX(int x);
    int getX();
    void setY(int y);
    int getY();
    void setColor(Scalar color);
    Scalar getColor();
    
    
private:
    int _xPos;
    int _yPos;
    int _scaleTextSize;
    int _r;
    int _g;
    int _b;
    vector<string> list;
    Mat img;
    
    //std::string categories[5];//I can have a String array with the length of the number of different things I want to display
    //not sure how to add an array member to this header class without already predefining the length of the array...
    
    void _drawText();
    void _drawBorder(int _widthBorder, int _heightBorder);
    int _maxStringLength();//give length in pixels

    
};

#endif /* textList_hpp */
