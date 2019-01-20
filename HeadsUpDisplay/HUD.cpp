//
//  HUD.cpp
//  HeadsUpDisplay
//
//  Created by Jeevan Prakash on 11/24/18.
//  Copyright © 2018 Jeevan Prakash. All rights reserved.
//

#include "HUD.hpp"

    HUD::HUD(){
        
    }

    void HUD::addGauge(int x, int y, int lowerRange, int upperRange, Size size, int r, int g, int b, int alpha, double increment, int startingValue, int index){
        Gauge gauge(x, y, lowerRange, upperRange, size, r, g, b, alpha);
        try{
            this->_gauges.insert(this->_gauges.begin()+index, gauge);
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
        }
    }
    void HUD::addGauge(int x, int y, int lowerRange, int upperRange, Size size, int r, int g, int b, int alpha, double increment, int startingValue, bool showMin, bool showMax){
        Gauge gauge(x, y, lowerRange, upperRange, size, r, g, b, alpha, increment, startingValue, showMin, showMax);
        this->_gauges.push_back(gauge);
    }
    void HUD::addGauge(int x, int y, int lowerRange, int upperRange, Size size, int r, int g, int b, int alpha, int index){
        Gauge gauge(x, y, lowerRange, upperRange, size, r, g, b, alpha);
        try{
            this->_gauges.insert(this->_gauges.begin()+index, gauge);
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
        }
    }
    void HUD::addGauge(int x, int y, int lowerRange, int upperRange, Size size, int r, int g, int b, int alpha){
        Gauge gauge(x, y, lowerRange, upperRange, size, r, g, b, alpha);
        this->_gauges.push_back(gauge);
    }
    void HUD::addGauge(int index){
        Gauge gauge;
        try{
            this->_gauges.insert(this->_gauges.begin()+index, gauge);
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
        }
    }
    void HUD::addGauge(){
        Gauge gauge;
        this->_gauges.push_back(gauge);
    }
    void HUD::addTextList(int x, int y, int scaleTextSize,  int r, int g, int b, int alpha, int index){
        TextList list(x, y, scaleTextSize, r, g, b, alpha);
        try{
            this->_lists.insert(this->_lists.begin()+index, list);
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
        }
    }
    void HUD::addTextList(int x, int y, int scaleTextSize, int r, int g, int b, int alpha){
        TextList list(x, y, scaleTextSize, r, g, b, alpha);
        this->_lists.push_back(list);
    }
    void HUD::addTextList(int index){//adds a TextList() object before the given index in the vector for TextLists
        TextList list;
        try {
            this->_lists.insert(this->_lists.begin()+index, list);
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
        }
    }
    void HUD::addTextList(){//adds a TextList() object at the end of the vector for TextLists
        TextList list;
        this->_lists.push_back(list);
    }
    void HUD::addBarGraph(int x, int y, int scaleValues, int height, int r, int g, int b, int alpha, int index){
        BarGraph bargraph(x, y, scaleValues, height, r, g, b, alpha);
        try{
            this->_bargraphs.insert(this->_bargraphs.begin()+index, bargraph);
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
        }
    }
    void HUD::addBarGraph(int x, int y, int scaleValues, int height, int r, int g, int b, int alpha){
        BarGraph bargraph(x, y, scaleValues, height, r, g, b, alpha);
        this->_bargraphs.push_back(bargraph);
    }
    void HUD::addBarGraph(int index){
        BarGraph bargraph;
        try{
            this->_bargraphs.insert(this->_bargraphs.begin()+index, bargraph);
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
        }
    }
    void HUD::addBarGraph(){
        BarGraph bargraph;
        this->_bargraphs.push_back(bargraph);
    }
    Gauge HUD::removeGauge(int index){//removes Gauge() element from _gauges at specified index
        //need to do some error handling in case they ask to replace an index out of bounds
        Gauge gauge;
        try{
            Gauge gauge = this->_gauges[index];
            this->_gauges.erase(this->_gauges.begin()+index-1);
            return gauge;
        } catch (std::out_of_range exception) {
            cout << exception.what() << endl;
        }
        return gauge;
    }
    TextList HUD::removeTextList(int index){//removes TextList() element from _lists at specified index
        //need to do some error handling in case they ask to replace an index out of bounds
        TextList list;
        try{
            TextList list = this->_lists[index];
            this->_lists.erase(this->_lists.begin()+index-1);
            return list;
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
        }
        return list;
    }
    BarGraph HUD::removeBarGraph(int index){//removes BarGraph() element from _bargraphs at specified index
        //need to do some error handling in case they ask to replace an index out of bounds
        BarGraph bargraph;
        try{
            BarGraph bargraph = this->_bargraphs[index];
            this->_bargraphs.erase(this->_bargraphs.begin()+index-1);
            return bargraph;
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
        }
        return bargraph;
    }
    Gauge HUD::replaceGauge(int index, Gauge replaceGauge){//replaces Gauge() at specified index
        //need to do some error handling in case they ask to replace an index out of bounds
        Gauge oldgauge;
        try{
            Gauge oldgauge = this->_gauges[index];
            this->_gauges[index] = replaceGauge;
            return oldgauge;
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
        }
        return oldgauge;
    }
    TextList HUD::replaceTextList(int index, TextList replaceList){//replaces TextList() at specified index
        //need to do some error handling in case they ask to replace an index out of bounds
        TextList oldList;
        try{
            TextList oldList = this->_lists[index];
            this->_lists[index] = replaceList;
            return oldList;
        } catch (out_of_range exception) {
            cout << exception.what() << endl;
        }
        return oldList;
    }
    BarGraph HUD::replaceBarGraph(int index, BarGraph replaceBargraph){
        //need to do some error handling in case they ask to replace an index out of bounds
        BarGraph oldbargraph = this->_bargraphs[index];
        this->_bargraphs[index] = replaceBargraph;
        return oldbargraph;
    }
    Gauge HUD::frontGauge(){
        return this->_gauges.front();
    }
    TextList HUD::frontTextList(){
        return this->_lists.front();
    }
    BarGraph HUD::frontBarGraph(){
        return this->_bargraphs.front();
    }
    Gauge HUD::backGauge(){
        return this->_gauges.back();
    }
    TextList HUD::backTextList(){
        return this->_lists.back();
    }
    BarGraph HUD::backBarGraph(){
        return this->_bargraphs.back();
    }
    Gauge HUD::atGauge(int index){
        //need to do some error handling in case they ask to replace an index out of bounds
        return this->_gauges.at(index);
    }
    TextList HUD::atTextList(int index){
        //need to do some error handling in case they ask to replace an index out of bounds
        return this->_lists.at(index);
    }
    BarGraph HUD::atBarGraph(int index){
        //need to do some error handling in case they ask to replace an index out of bounds
        return this->_bargraphs.at(index);
    }

    void HUD::drawGauges(Mat img){
        for(int i=0; i<this->_gauges.size(); i++) this->_gauges[i].drawGauge(0, img);
    }

    void HUD::drawBarGraphs(Mat img){
        for(int i=0; i<this->_bargraphs.size(); i++) this->_bargraphs[i].drawBarGraph();
    }

    void HUD::drawTextLists(Mat img){
        for(int i=0; i<this->_lists.size(); i++) this->_lists[i].drawList(img);
    }

    void HUD::drawAll(){
        String text = "Test";
        
        clock_t startTime=clock(), currTime=clock();
        
        struct timeval currFrameTime,lastFrameTime;
        gettimeofday(&currFrameTime, NULL);
        
        Mat img;
        img = imread("/Users/jeevanprakash/Desktop/Funny/IMG_0620.PNG");
        this->addTextList();
        //this->_capture.open(0);
        if(true){//this->_capture.isOpened()
            cout << "Capture is opened" << endl;
            while(waitKey(10) != 'q'){
                long int ms =(currFrameTime.tv_sec * 1000 + currFrameTime.tv_usec / 1000) - (lastFrameTime.tv_sec * 1000 + lastFrameTime.tv_usec / 1000);
                text = "Proc time: " + to_string((float)(currTime - startTime) / CLOCKS_PER_SEC) + " FPS: " + to_string((float)(1000.0 / ms));
                lastFrameTime = currFrameTime;
                this->_lists[0].editText(text);
                
                //if(i<=this->_lists.size()-1) this->_lists[0].addText(text);
                //i++;
                //log the cpu clock to see how long the alloc and draw takes
                startTime = clock();
                //this->_capture >> img;
                img = imread("/Users/jeevanprakash/Desktop/Funny/IMG_0620.PNG");
                if(img.empty()) break;
                //drawGauges(img); WIP
                //drawBarGraphs(img); WIP
                drawTextLists(img);
                
                //only release things when I am changing the actual image like updating it or something
                
                //log the cpu clock after alloc and draw
                currTime = clock();
                
                imshow("Sample", img);
            }
        }
    }
