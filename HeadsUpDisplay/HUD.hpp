//
//  HUD.hpp
//  HeadsUpDisplay
//
//  Created by Jeevan Prakash on 11/24/18.
//  Copyright © 2018 Jeevan Prakash. All rights reserved.
//

#ifndef HUD_H
#define HUD_H

#include "barGraph.hpp"
#include "gauge.hpp"
#include "textList.hpp"
#include <iostream>
#include <string>
#include <sys/time.h>
#include <time.h>
#include <vector>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace std;
using namespace cv;

class HUD{
    
public:
    HUD();
    void addGauge(int x, int y, int lowerRange, int upperRange, int size, int r, int g, int b, int alpha, double increment, int startingValue, int index);
     void addGauge(int x, int y, int lowerRange, int upperRange, int size, int r, int g, int b, int alpha, double increment, int startingValue, bool showMin, bool showMax);
    void addGauge(int x, int y, int lowerRange, int upperRange, int size, int r, int g, int b, int alpha, int index);
    void addGauge(int x, int y, int lowerRange, int upperRange, int size, int r, int g, int b, int alpha);
    void addGauge(int index);
    void addGauge();
    void addTextList(int x, int y, int scaleTextSize,  int r, int g, int b, int alpha, int index);
    void addTextList(int x, int y, int scaleTextSize, int r, int g, int b, int alpha);
    void addTextList(int index); //adds a TextList() object before the given index in the vector for TextLists
    void addTextList(); //adds a TextList() object at the end of the vector for TextLists
    void addBarGraph(int x, int y, int scaleValues, int width, int height, int r, int g, int b, int alpha, int index);
    void addBarGraph(int x, int y, int scaleValues, int width, int height, int r, int g, int b, int alpha);
    void addBarGraph(int index);
    void addBarGraph();
    Gauge removeGauge(int index); //removes Gauge() element from _gauges at specified index
    TextList removeTextList(int index); //removes TextList() element from _lists at specified index
    BarGraph removeBarGraph(int index); //removes BarGraph() element from _bargraphs at specified index
    Gauge replaceGauge(int index, Gauge replaceGauge); //replaces Gauge() with a new instance of the class at specified index
    TextList replaceTextList(int index, TextList replaceList); //replaces TextList() at specified index
    BarGraph replaceBarGraph(int index, BarGraph replaceBargraph); //replaces BarGraph() at specified index
    Gauge frontGauge(); //returns first reference to a Gauge in _gauges
    TextList frontTextList(); //returns first reference to a TextList() in _lists
    BarGraph frontBarGraph(); //returns first reference to a BarGraph in _bargraphs
    Gauge backGauge(); //returns first reference to a Gauge in _gauges
    TextList backTextList();
    BarGraph backBarGraph();
    Gauge atGauge(int index);
    TextList atTextList(int index);
    BarGraph atBarGraph(int index);
    void drawGauges(Mat img);
    void drawBarGraphs(Mat img);
    void drawTextLists(Mat img);
    void drawAll();
    
private:
    vector<BarGraph> _bargraphs;
    vector<Gauge> _gauges;//I can have multiple "orientations" for one of the constructors or something so that they aren't forced  to input the start and end angles
    vector<TextList> _lists;
    VideoCapture _capture;
    //methods
    
};

#endif /* HUD_hpp */
