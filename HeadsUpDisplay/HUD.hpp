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
    void addTextList(int index);
    void addTextList();
    void addBarGraph(int x, int y, int scaleValues, int height, int r, int g, int b, int alpha, int index);
    void addBarGraph(int x, int y, int scaleValues, int height, int r, int g, int b, int alpha);
    void addBarGraph(int index);
    void addBarGraph();
    Gauge removeGauge(int index);
    TextList removeTextList(int index);
    BarGraph removeBarGraph(int index);
    Gauge replaceGauge(int index, Gauge replaceGauge);
    TextList replaceTextList(int index, TextList replaceList);
    BarGraph replaceBarGraph(int index, BarGraph replaceBargraph);
    Gauge frontGauge();
    TextList frontTextList();
    BarGraph frontBarGraph();
    Gauge backGauge();
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
