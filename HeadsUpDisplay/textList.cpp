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
        this->img = img;
        this->_xPos = 0;
        this->_yPos = 0;
        this->_scaleTextSize = 1;
        this->_r = 0;
        this->_g = 0;
        this->_b = 0;
    }

    TextList::TextList(int x, int y, int scaleTextSize, int r, int g, int b){
        Mat img(Size(800,600), CV_8UC4, Scalar(0,255,0,0));//is there a better way to implement creating a Mat like this into the line below?
        this->img = img;
        //Mat img2(Size(800,600), Scalar(0,255,0));
        //this->list;do I not need to instantiate the vector?
        this->_xPos = x;
        this->_yPos = y;
        this->_scaleTextSize = scaleTextSize;
        this->_r = r;
        this->_g = g;
        this->_b = b;
    }

    Mat TextList::drawList(){
        _drawText();
        _drawBorder(500, 500);
        return this->img;
    }

    void TextList::_drawText(){
        string testString;
        //putText puts stuff on the image
        for(int i=0;i<list.size();i++){
            testString = this->list.at(i);
            putText(img, testString, Point(600,50+(i*20)), FONT_HERSHEY_COMPLEX, 1, Scalar(0,0,255));//putText puts stuff on the image
        }
    }
    void TextList::_drawBorder(int _widthBorder, int _heightBorder){//need to figure out the size of the characters on the screen
        int thickness = 4;
        int shift = 0;
        //can have a method called max string length called here to figure out what size to actually make the border rect
        rectangle(img, Point(400,400), Point(500,500), Scalar(0,0,255), thickness, LINE_8, shift);//need to calculate the space the strings inputted take
    }

    int TextList::_maxStringLength(){
        //for loop to figure out the max length
        int maxSize=0;
        for(int i=0; i<this->list.size();i++){
            if(list[i].length()>maxSize) maxSize = list[i].length();//still need to multiply the character length by some scale value to get the actual pixel of the string
        }
        return maxSize;
    }

    void TextList::addText(string newText){
        this->list.push_back(newText);
    }

    string TextList::editText(int index, string newText){
        string previousString = this->list[index];
        this->list[index]=newText;
        return previousString;
    }

