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
#include <sys/time.h>
#include <time.h>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

class TextList{
    
public:
    TextList();
    TextList(int x, int y, double scaleTextSize, int r, int g, int b, int alpha);
    void drawTextList(Mat img);
    string editText(string newText);
    int getX();
    void setX(int x);
    int getY();
    void setY(int y);
    Scalar getTextColor();
    void setTextColor(int r, int g, int b);
    Scalar getBorderColor();
    void setBorderColor(int r, int g, int b);
    int getTextFontScale();
    void setTextFontScale(int newScale);
    int getStringLength();
    void showText();
    void showBorder();
    void hideText();
    void hideBorder();
    
private:
    int _xPos;
    int _yPos;
    double _scaleTextSize;
    int _rText;
    int _gText;
    int _bText;
    int _rBorder;
    int _gBorder;
    int _bBorder;
    int _thickness;
    int _tBoxBorderThickness;
    int _tBoxFont;
    int _tBoxBaseline;
    double _tBoxFontScale;
    Mat _img;
    Mat _textForeground;
    Mat _textAlpha;
    Mat _borderForeground;
    Mat _borderAlpha;
    string _text;
    bool _showText;
    bool _showBorder;
    
    void _drawText(Mat img);
    void _updateText();
    void _drawLocalText();
    void _drawBorder(Mat img);
    void _updateBorder();
    void _drawLocalBorder();
    void _drawInitialTextList();
    
};

#endif /* textList.hpp */
