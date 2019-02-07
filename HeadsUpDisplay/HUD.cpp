//
//  HUD.cpp
//  HeadsUpDisplay
//
//  Created by Jeevan Prakash on 11/24/18.
//  Copyright © 2018 Jeevan Prakash. All rights reserved.
//

#include "HUD.hpp"

    HUD::HUD(){
        //static Gauge *MISSING_GAUGE = new Gauge(-1, -1, -1, -1, -1, -1, -1, -1, -1); Don't know how to implement this yet
    }

    void HUD::addGauge(int x, int y, int size, int r, int g, int b,  int startingValue, double angleIncrement, int endAngle, int index){
        Gauge gauge(x, y, size, r, g, b, startingValue, angleIncrement, endAngle);
        try{
            this->_gauges.insert(this->_gauges.begin()+index, gauge);
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
            cout << "[Error] Desired index is out of bounds of vector" << endl;
        }
    }

    void HUD::addGauge(int x, int y, int size, int r, int g, int b,  int startingValue, double angleIncrement, int endAngle){
        Gauge gauge(x, y, size, r, g, b, startingValue, angleIncrement, endAngle);
        this->_gauges.push_back(gauge);
    }

    void HUD::addGauge(int x, int y, int size, int r, int g, int b, double increment, int startingValue, bool showMin, bool showMax, int index){
        Gauge gauge(x, y, size, r, g, b, increment, startingValue, showMin, showMax);
        try{
            this->_gauges.insert(this->_gauges.begin()+index, gauge);
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
            cout << "[Error] Desired index is out of bounds of vector" << endl;
        }
    }

    void HUD::addGauge(int x, int y, int size, int r, int g, int b, double increment, int startingValue, bool showMin, bool showMax){
        Gauge gauge(x, y, size, r, g, b, increment, startingValue, showMin, showMax);
        this->_gauges.push_back(gauge);
    }

    void HUD::addGauge(int x, int y, int size, int r, int g, int b, int index){
        Gauge gauge(x, y, size, r, g, b);
        try{
            this->_gauges.insert(this->_gauges.begin()+index, gauge);
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
        }
    }
    void HUD::addGauge(int x, int y, int size, int r, int g, int b){
        Gauge gauge(x, y, size, r, g, b);
        this->_gauges.push_back(gauge);
    }

    void HUD::addGauge(int index){
        Gauge gauge;
        try{
            this->_gauges.insert(this->_gauges.begin()+index, gauge);
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
            cout << "[Error] Desired index is out of bounds of vector" << endl;
        }
    }
    void HUD::addGauge(){
        Gauge gauge;
        this->_gauges.push_back(gauge);
    }
    void HUD::addTextList(int x, int y, double scaleTextSize,  int r, int g, int b, int alpha, int index){
        TextList list(x, y, scaleTextSize, r, g, b, alpha);
        try{
            this->_lists.insert(this->_lists.begin()+index, list);
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
            cout << "[Error] Desired index is out of bounds of vector" << endl;
        }
    }
    void HUD::addTextList(int x, int y, double scaleTextSize, int r, int g, int b, int alpha){
        TextList list(x, y, scaleTextSize, r, g, b, alpha);
        this->_lists.push_back(list);
    }
    void HUD::addTextList(int index){
        TextList list;
        try {
            this->_lists.insert(this->_lists.begin()+index, list);
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
            cout << "[Error] Desired index is out of bounds of vector" << endl;
        }
    }
    void HUD::addTextList(){
        TextList list;
        this->_lists.push_back(list);
    }
    void HUD::addBarGraph(int x, int y, int scaleValues, int width, int height, int r, int g, int b, int alpha, int index){
        BarGraph bargraph(x, y, scaleValues, width, height, r, g, b, alpha);
        try{
            this->_bargraphs.insert(this->_bargraphs.begin()+index, bargraph);
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
            cout << "[Error] Desired index is out of bounds of vector" << endl;
        }
    }
    void HUD::addBarGraph(int x, int y, int scaleValues, int width, int height, int r, int g, int b, int alpha){
        BarGraph bargraph(x, y, scaleValues, width, height, r, g, b, alpha);
        this->_bargraphs.push_back(bargraph);
    }
    void HUD::addBarGraph(int index){
        BarGraph bargraph;
        try{
            this->_bargraphs.insert(this->_bargraphs.begin()+index, bargraph);
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
            cout << "[Error] Desired index is out of bounds of vector" << endl;
        }
    }
    void HUD::addBarGraph(){
        BarGraph bargraph;
        this->_bargraphs.push_back(bargraph);
    }
    void HUD::removeGauge(int index){
        try{
            this->_gauges.erase(this->_gauges.begin()+index-1);
        } catch (std::out_of_range exception) {
            cout << exception.what() << endl;
            cout << "[Error] Desired index is out of bounds of vector" << endl;
        }
    }

    void HUD::removeTextList(int index){
        try{
            this->_lists.erase(this->_lists.begin()+index-1);
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
            cout << "[Error] Desired index is out of bounds of vector" << endl;
        }
    }

    void HUD::removeBarGraph(int index){
        try{
            this->_bargraphs.erase(this->_bargraphs.begin()+index-1);
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
            cout << "[Error] Desired index is out of bounds of vector" << endl;
        }
    }

    Gauge HUD::replaceGauge(int index, Gauge replaceGauge){
        Gauge oldgauge;
        try{
            Gauge oldgauge = this->_gauges[index];
            this->_gauges[index] = replaceGauge;
            return oldgauge;
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
            cout << "[Error] Desired index is out of bounds of vector" << endl;
        }
        return oldgauge;
    }

    TextList HUD::replaceTextList(int index, TextList replaceList){
        TextList oldList;//if the index is messed up then the program will return a Gauge with all negative values
        try{
            TextList oldList = this->_lists[index];
            this->_lists[index] = replaceList;
            return oldList;
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
            cout << "[Error] Desired index is out of bounds of vector" << endl;
        }
        return oldList;
    }
    BarGraph HUD::replaceBarGraph(int index, BarGraph replaceBargraph){
        BarGraph oldbargraph;
        try{
            BarGraph oldbargraph = this->_bargraphs[index];
            this->_bargraphs[index] = replaceBargraph;
            return oldbargraph;
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
            cout << "[Error] Desired index is out of bounds of vector" << endl;
        }
        return oldbargraph;
    }
    Gauge* HUD::frontGauge(){
        return &this->_gauges.front();
    }
    TextList* HUD::frontTextList(){
        return &this->_lists.front();
    }
    BarGraph* HUD::frontBarGraph(){
        return &this->_bargraphs.front();
    }
    Gauge* HUD::backGauge(){
        return &this->_gauges.back();
    }
    TextList* HUD::backTextList(){
        return &this->_lists.back();
    }
    BarGraph* HUD::backBarGraph(){
        return &this->_bargraphs.back();
    }
    Gauge* HUD::atGauge(int index){
        Gauge missingGauge;
        try{
            return &this->_gauges.at(index);
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
            cout << "[Error] Desired index is out of bounds of vector" << endl;
        }
        return &missingGauge;
    }
    TextList* HUD::atTextList(int index){
        TextList missingTextList;
        try{
            return &this->_lists.at(index);
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
            cout << "[Error] Desired index is out of bounds of vector" << endl;
        }
        return &missingTextList;
    }
    BarGraph* HUD::atBarGraph(int index){
        BarGraph missingBarGraph;
        try{
            return &this->_bargraphs.at(index);
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
            cout << "[Error] Desired index is out of bounds of vector" << endl;
        }
        return &missingBarGraph;
    }

    void HUD::drawGauges(Mat img){
        for(int i=0; i<this->_gauges.size(); i++) this->_gauges[i].drawGauge(img);
    }

    void HUD::drawBarGraphs(Mat img){
        for(int i=0; i<this->_bargraphs.size(); i++) this->_bargraphs[i].drawBarGraph(img);
    }

    void HUD::drawTextLists(Mat img){
        for(int i=0; i<this->_lists.size(); i++) this->_lists[i].drawTextList(img);
    }

    void HUD::getMat()
    {
        while(true)
        {
            _mutex.lock();
            _img = imread("/Users/jeevanprakash/Documents/FRCCode/HeadsUpDisplay-Published/HeadsUpDisplay/nicebg.png");
            _mutex.unlock();
        }
    }

    void HUD::drawAll(){
        String text = "Test";
        
        clock_t startTime=clock(), currTime=clock();
        
        struct timeval currFrameTime,lastFrameTime;
        gettimeofday(&currFrameTime, NULL);
        
        _getter = thread(&HUD::getMat, this);
        
        //this->_capture.open(0); //VideoCapture code is commented out till Apple comes with fix of allowing access to the camera through xcode...
        int j = 1;
        int multiplier = 1;
        int multiplier2 = 1;
        int i = 1;
        int r=0, g=0, b=0;
        if(true){//this->_capture.isOpened()
            cout << "Capture is opened" << endl;
            while(waitKey(10) != 'q'){
                _mutex.lock();
                gettimeofday(&currFrameTime, NULL);
                long int ms = (currFrameTime.tv_sec * 1000 + currFrameTime.tv_usec / 1000) - (lastFrameTime.tv_sec * 1000 + lastFrameTime.tv_usec / 1000);
                text = "Proc time: " + to_string((float)(currTime - startTime) / CLOCKS_PER_SEC) + " FPS: " + to_string((float)(1000.0 / ms));
                lastFrameTime = currFrameTime;
                this->_lists[0].editText(text);
                
                //I need to make a class that can read image files and update the HUD whenever it gets the chance
                //The class needs to have a very specific thread that it uses when it is connected to the server, and by the fact that it has that very specific string as it's tag so to speak it will, it will receive the raw image
                //It is going to be a completely different project
                //_img = imread("/Users/jeevanprakash/Documents/FRCCode/HeadsUpDisplay-Published/HeadsUpDisplay/nicebg.png");
                
                //log the cpu clock to see how long the alloc and draw takes
                startTime = clock();
                //this->_capture >> img;
                if(_img.empty()) break;
                drawGauges(this->_img);
                this->_gauges[0].setGaugeValue(j);
                if(j%1==0){
                    r = (rand() % 256);
                    g = (rand() % 256);
                    b = (rand() % 256);
                }
                //this->_gauges[0].setTickerColor(r, g, b);
                //this->_gauges[0].setGaugeColor(r, g, b);
                this->_gauges[0].setEndAngle(j);
                drawTextLists(this->_img);
                drawBarGraphs(this->_img);
                //this->_lists[0].setTextColor(r, g, b);
                //this->_lists[0].setBorderColor(r, g, b);
                //this->_lists[0].setTextFontScale(i);
                //this->_bargraphs[0].setInnerRectangleColor(r, g, b);
                this->_bargraphs[0].setCurrentFill(j);
                this->_bargraphs[0].setBarGraphSize(50, j);
                //this->_bargraphs[0].setOuterRectangleColor(r, g, b);
                j += multiplier;
                i += multiplier2;
                if(j>=100 || j <=1) multiplier *= -1;
                if(i>=12 || i<=1) multiplier2 *= -1;
                
                //log the cpu clock after allocations, update functions, and draw functions
                currTime = clock();
                
                imshow("Heads Up Display", this->_img);
                _mutex.unlock();
            }
        }
    }
