//
//  HUD.hpp
//  HeadsUpDisplay
//
//  Created by Jeevan Prakash on 11/24/18.
//  Copyright © 2018 Jeevan Prakash. All rights reserved.
//

#ifndef HUD_H
#define HUD_H

#include <stdio.h>

#include "barGraph.hpp"
#include "gauge.hpp"
#include "textList.hpp"
#include <list>

using namespace std;

class HUD{
    
public:
    HUD();
    /*
     1. addGauge, addTextList, etc.
     2. removeGauge, removeTextList, etc.
     3. updateTickerValue, printText, etc.
     */
    
    void addGauge(int x, int y, int lowerRange, int upperRange, int size, int r, int g, int b, double increment, int _startingValue, int index, bool _showMin = false, bool _showMax = false);
     void addGauge(int x, int , int _lowerRange, int _upperRange, int _size, int _r, int _g, int _b, double _increment, int _startingValue, bool _showMin = false, bool _showMax = false);
    void addGauge(int x, int y, int lowerRange, int _upperRange, int _size, int _r, int _g, int _b, int index);
    void addGauge(int x, int y, int lowerRange, int _upperRange, int _size, int _r, int _g, int _b);
    void addGauge(int index);
    void addGauge();
    void addTextList(int x, int y, int scaleTextSize,  int r, int g, int b, int numOfItems, int index);
    void addTextList(int x, int y, int scaleTextSize, int r, int g, int b, int _numOfItems);
    void addTextList(int index);
    void addTextList();
    void addBarGraph(int xPos, int yPos, int scaleValues, int height, int index);
    void addBarGraph(int xPos, int yPos, int scaleValues, int height);
    void addBarGraph(int index);
    void addBarGraph();
    Gauge removeGauge(int index);
    TextList removeTextList(int index);
    BarGraph removeBarGraph(int index);
    Gauge replaceGauge(int index, Gauge gauge);
    TextList replaceTextList(int index, TextList list);
    BarGraph replaceBarGraph(int index, BarGraph bargraph);
    Gauge frontGauge();
    TextList frontTextList();
    BarGraph frontBarGraph();
    Gauge backGauge();
    TextList backTextList();
    BarGraph backBarGraph();
    Gauge atGauge(int index);
    TextList atTextList(int index);
    BarGraph atBarGraph(int index);
    
private:
    vector<BarGraph> _bargraphs;
    vector<Gauge> _gauges;//I can have multiple "orientations" for one of the constructors or something so that they aren't forced  to input the start and end angles
    vector<TextList> _lists;
    //I think I need to use vectors instead?
    //methods
    
};

#endif /* HUD_hpp */
