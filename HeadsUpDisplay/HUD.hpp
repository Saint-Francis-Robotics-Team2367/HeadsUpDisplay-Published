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
    void addGauge(int x, int y, int size, int r, int g, int b, double increment, int startingValue, bool showMin, bool showMax, int index);
    void addGauge(int x, int y, int size, int r, int g, int b, double increment, int startingValue, bool showMin, bool showMax);
    void addGauge(int x, int y, int size, int r, int g, int b, int index);
    void addGauge(int x, int y, int size, int r, int g, int b);
    void addGauge(int x, int y, int size, int r, int g, int b,  int startingValue, double angleIncrement, int endAngle, int index);
    void addGauge(int x, int y, int size, int r, int g, int b,  int startingValue, double angleIncrement, int endAngle);
    void addGauge(int index);
    void addGauge();
    void addTextList(int x, int y, double scaleTextSize,  int r, int g, int b, int alpha, int index);
    void addTextList(int x, int y, double scaleTextSize, int r, int g, int b, int alpha);
    void addTextList(int index);
    void addTextList();
    void addBarGraph(int x, int y, int scaleValues, int width, int height, int r, int g, int b, int alpha, int index);
    void addBarGraph(int x, int y, int scaleValues, int width, int height, int r, int g, int b, int alpha);
    void addBarGraph(int index);
    void addBarGraph();
    void removeGauge(int index);
    void removeTextList(int index);
    void removeBarGraph(int index);
    Gauge replaceGauge(int index, Gauge replaceGauge);
    TextList replaceTextList(int index, TextList replaceList);
    BarGraph replaceBarGraph(int index, BarGraph replaceBargraph);
    Gauge* frontGauge();
    TextList* frontTextList();
    BarGraph* frontBarGraph();
    Gauge* backGauge();
    TextList* backTextList();
    BarGraph* backBarGraph();
    Gauge* atGauge(int index);
    TextList* atTextList(int index);
    BarGraph* atBarGraph(int index);
    void drawGauges(Mat img);
    void drawBarGraphs(Mat img);
    void drawTextLists(Mat img);
    void drawAll();
    static const Gauge *MISSING_GAUGE;
    
private:
    vector<BarGraph> _bargraphs;
    vector<Gauge> _gauges;
    vector<TextList> _lists;
    VideoCapture _capture;
    
};

#endif /* HUD.hpp */
