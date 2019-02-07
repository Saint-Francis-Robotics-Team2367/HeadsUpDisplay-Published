//
//  textList.cpp
//  HeadsUpDisplay
//
//  Created by Jeevan Prakash on 11/24/18.
//  Copyright © 2018 Jeevan Prakash. All rights reserved.
//

#include "textList.hpp"

    //constructor 1
    TextList::TextList(){
        this->_xPos = 0;
        this->_yPos = 0;
        this->_scaleTextSize = 1;
        this->_rText = 0;
        this->_gText = 0;
        this->_bText = 0;
        this->_rBorder = 0;
        this->_gBorder = 0;
        this->_bBorder = 0;
        this->_thickness = 2;
        this->_text = "";
        this->_tBoxBorderThickness = 1;
        this->_tBoxFont = FONT_HERSHEY_COMPLEX_SMALL;
        this->_tBoxBaseline = 0;
        this->_tBoxFontScale = 1;
        this->_showText = true;
        this->_showBorder = true;
        _drawInitialTextList();
    }

    //constructor 2
    TextList::TextList(int x, int y, double scaleTextSize, int r, int g, int b, int alpha){
        this->_xPos = x;
        this->_yPos = y;
        this->_scaleTextSize = scaleTextSize;
        this->_rText = r;
        this->_gText = g;
        this->_bText = b;
        this->_rBorder = r;
        this->_gBorder = g;
        this->_bBorder = b;
        this->_thickness = 2;
        this->_text = "";
        this->_tBoxBorderThickness = 1;
        this->_tBoxFont = FONT_HERSHEY_COMPLEX_SMALL;
        this->_tBoxBaseline = 0;
        this->_tBoxFontScale = 1;
        this->_showText = true;
        this->_showBorder = true;
        _drawInitialTextList();
    }

    void TextList::_drawInitialTextList(){
        _updateText();
        _updateBorder();
    }

    void TextList::drawTextList(Mat img){
        _drawText(img);
        _drawBorder(img);
    }

    string TextList::editText(string newText){
        string previousString = this->_text;
        this->_text = newText;
        _updateText();
        _updateBorder();
        return previousString;
    }

    int TextList::getX(){
        return this->_xPos;
    }

    void TextList::setX(int x){
        this->_xPos = x;
        _updateText();
        _updateBorder();
    }
    int TextList::getY(){
        return this->_yPos;
    }

    void TextList::setY(int y){
        this->_yPos = y;
        _updateText();
        _updateBorder();
    }

    Scalar TextList::getTextColor(){
        return Scalar(this->_bText, this->_gText, this->_rText);
    }

    void TextList::setTextColor(int r, int g, int b){
        this->_rText = r;
        this->_gText = g;
        this->_bText = b;
    }

    Scalar TextList::getBorderColor(){
        return Scalar(this->_bBorder, this->_gBorder, this->_rBorder);
    }

    void TextList::setBorderColor(int r, int g, int b){
        this->_rBorder = r;
        this->_gBorder = g;
        this->_bBorder = b;
    }

    int TextList::getTextFontScale(){
        return this->_tBoxFontScale;
    }

    void TextList::setTextFontScale(int newScale){
        this->_tBoxFontScale = newScale;
        _updateText();
        _updateBorder();
    }

    void TextList::_drawText(Mat img){
        
        Mat image_roi; //roi of output image
        
        int x = getX() + 2;
        int y = getY() + 2;
        
        //check that the text is in frame so the bitwise ops don't crash
        if(x<0 || y<0 || x + this->_textAlpha.size().width > img.size().width || y + this->_textAlpha.size().height > img.size().height || !this->_showText)
        {
            cout << "[WARNING] Text goes out of frame or is hidden" <<endl;
        }
        
        else
        {
            image_roi = img(Rect(x, y, this->_textAlpha.size().width, this->_textAlpha.size().height));
            bitwise_and(image_roi, Scalar(0), image_roi, this->_textAlpha);
            bitwise_or(image_roi, this->_textForeground, image_roi, this->_textAlpha);
        }
        
    }

    void TextList::_updateText(){
        //release memory
        this->_textForeground.release();
        this->_textAlpha.release();
        
        //calc dependant varsmak
        Size tBoxBorderSize;
        
        //calc size of image needed to draw text
        tBoxBorderSize = getTextSize(this->_text,this->_tBoxFont,this->_scaleTextSize, this->_thickness, &this->_tBoxBaseline);
        
        //allocate images based on text settings
        
        this->_textForeground = Mat(tBoxBorderSize.height + this->_tBoxBaseline, tBoxBorderSize.width,CV_8UC3,getTextColor());
        this->_textAlpha = Mat(tBoxBorderSize.height + this->_tBoxBaseline, tBoxBorderSize.width,CV_8UC1,Scalar(0));
        _drawLocalText();
    }

    void TextList::_drawLocalText(){
        //draw text onto alpha layer
        putText(this->_textAlpha, this->_text, Point(0,this->_textAlpha.size().height-this->_tBoxBaseline), this->_tBoxFont, this->_scaleTextSize, Scalar(255), this->_thickness);
    }

    void TextList::_drawBorder(Mat img){
        
        Mat image_roi; //roi of output image
        
        int x = getX() - this->_thickness;
        int y = getY() - this->_thickness;
        
        //check that the text is in frame so the bitwise ops don't crash
        if(x < 0 || y<0 || x + this->_borderAlpha.size().width > img.size().width || y + this->_borderAlpha.size().height > img.size().height || !this->_showBorder)
        {
            cout << "[WARNING] Border goes out of frame or is hidden" <<endl;
        }
        
        else
        {
            image_roi = img(Rect(x, y, this->_borderAlpha.size().width, this->_borderAlpha.size().height));
            bitwise_and(image_roi, Scalar(0), image_roi, this->_borderAlpha);
            bitwise_or(image_roi, this->_borderForeground, image_roi, this->_borderAlpha);
        }
    }

    void TextList::_updateBorder(){
        //release memory
        this->_borderForeground.release();
        this->_borderAlpha.release();
        
        this->_borderForeground = Mat(_textAlpha.size().height + this->_thickness, _textAlpha.size().width + this->_thickness,CV_8UC3,getBorderColor());
        this->_borderAlpha = Mat(_textAlpha.size().height + this->_thickness, _textAlpha.size().width + this->_thickness,CV_8UC1,Scalar(0));
        
        _drawLocalBorder();
    }

    void TextList::_drawLocalBorder(){
        int shift = 0;
        
        //draw border for text onto alpha layer
        rectangle(this->_borderAlpha, Point(0,0), Point(this->_borderAlpha.size().width, this->_borderAlpha.size().height), Scalar(255), this->_thickness, LINE_8, shift);
    }

    int TextList::getStringLength(){
        return this->_text.length();
    }

    void TextList::showText(){
        this->_showText = true;
    }

    void TextList::showBorder(){
        this->_showBorder = true;
    }

    void TextList::hideText(){
        this->_showText = false;
    }

    void TextList::hideBorder(){
        this->_showBorder = false;
    }
