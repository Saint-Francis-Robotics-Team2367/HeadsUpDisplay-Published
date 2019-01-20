//
//  textList.cpp
//  HeadsUpDisplay
//
//  Created by Jeevan Prakash on 11/24/18.
//  Copyright © 2018 Jeevan Prakash. All rights reserved.
//

#include "textList.hpp"

    TextList::TextList(){
        Mat img(Size(800,600), CV_8UC4, Scalar(0,255,0,0));//is there a better way to implement creating a Mat like this into the line below?
        this->_img = img;
        this->_xPos = 0;
        this->_yPos = 0;
        this->_scaleTextSize = 1;
        this->_r = 0;
        this->_g = 0;
        this->_b = 0;
        this->_thickness = 4;
        this->_text = "";
    }

    TextList::TextList(int x, int y, int scaleTextSize, int r, int g, int b, int alpha){
        Mat img(Size(800,600), CV_8UC4, Scalar(0,255,0,0));//is there a better way to implement creating a Mat like this into the line below?
        this->_img = img;
        //Mat img2(Size(800,600), Scalar(0,255,0));
        //this->list;do I not need to instantiate the vector?
        this->_xPos = x;
        this->_yPos = y;
        this->_scaleTextSize = scaleTextSize;
        this->_r = r;
        this->_g = g;
        this->_b = b;
        this->_thickness = 4;
        this->_text = "";
    }

    Mat TextList::drawList(Mat img){
        _drawText(img);
        //_drawBorder(img);WIP
        return this->_img;
    }

    string TextList::editText(string newText){
        string previousString = this->_text;
        this->_text = newText;
        return previousString;
    }

    int TextList::getX(){
        return this->_xPos;
    }

    int TextList::getY(){
        return this->_yPos;
    }

    void TextList::setX(int x){
        this->_xPos = x;
    }

    void TextList::setY(int y){
        this->_yPos = y;
    }

    Scalar TextList::getColor(){
        return Scalar(this->_r, this->_g, this->_b);
    }

    void TextList::setColor(int r, int g, int b, Mat img){
        this->_r = r;
        this->_g = g;
        this->_b = b;
        drawList(this->_img);
    }

    void TextList::_drawText(Mat img){
        int tBoxPosX = 20,
        tBoxPosY = 20,
        tBoxBorderThickness = 1,
        tBoxFont = FONT_HERSHEY_COMPLEX_SMALL,
        tBoxBaseline = 0;
        
        double tBoxFontScale = 1;
        
        Scalar textColor(255,50,55);
        
        //calc dependant varsmak
        Size tBoxBorderSize;
        
        //opencv data vars
        //VideoCapture capture; //camera feed
        
        Mat
        textForground,    //text color layer
        textAlpha,        //text draw layer
        image_roi;        //roi of output image
        
        //calc size of image needed to draw text
        tBoxBorderSize = getTextSize(this->_text,tBoxFont,tBoxFontScale, tBoxBorderThickness, &tBoxBaseline);
        //release memory
        textForground.release();
        textAlpha.release();
        
        //allocate images based on text settings
        textForground = Mat(tBoxBorderSize.height +tBoxBaseline, tBoxBorderSize.width,CV_8UC3,textColor);
        textAlpha = Mat(tBoxBorderSize.height+tBoxBaseline, tBoxBorderSize.width,CV_8UC1,Scalar(0));
        
        //draw text onto alpha layer
        putText(textAlpha, this->_text, Point(0,textAlpha.size().height-tBoxBaseline), tBoxFont, tBoxFontScale, Scalar(255), tBoxBorderThickness);
        
        //check that the text is in frame so the bitwise ops don't crash
        if(tBoxPosX + textAlpha.size().width > img.size().width || tBoxPosY + textAlpha.size().height > img.size().height)
        {
            cout << "[WARNING] Text goes out of frame" <<endl;
        }
        
        else
        {
            image_roi = img(Rect(tBoxPosX, tBoxPosY, textAlpha.size().width, textAlpha.size().height));
            bitwise_and(image_roi, Scalar(0), image_roi, textAlpha);
            bitwise_or(image_roi, textForground, image_roi,textAlpha);
        }
        
    }

    void TextList::_drawBorder(){//need to figure out the size of the characters on the screen
        int shift = 0;
        //can have a method called max string length called here to figure out what size to actually make the border rect
        //rectangle(this->_img, Point(400,400), Point(500,500), Scalar(0,0,255), this->_thickness, LINE_8, shift);//need to calculate the space the strings inputted take
        rectangle(this->_img, Point(getX(),getY()), Point(getX()+200,getY()+50), Scalar(this->_r,this->_g,this->_b), this->_thickness, LINE_8, shift);//need to calculate the space the strings inputted take
    }

    int TextList::getStringLength(){
        return this->_text.length();
    }
