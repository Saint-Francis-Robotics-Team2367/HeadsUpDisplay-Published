//
//  main.cpp
//  HeadsUpDisplay
//
//  Created by Jeevan Prakash on 11/24/18.
//  Copyright © 2018 Jeevan Prakash. All rights reserved.
//

#include "HUD.hpp"

using namespace cv;
using namespace std;

int main(int argc, const char * argv[]) {
    
    HUD *hud = new HUD();

    hud->addTextList(50, 50, 1, 55, 50, 250, 255);//int x, int y, int scaleTextSize, int r, int g, int b, int alpha
    //hud->addGauge(300, 200, 0, 100, 100, 50, 200, 244, 255);//int x, int y, int lowerRange, int upperRange, int size, int r, int g, int b
    hud->addGauge(200, 200, 100, 50, 200, 244, 0, 320, 90);//int x, int y, int size, int r, int g, int b,  int startingValue, double angleIncrement, int endAngle
    hud->atGauge(0)->setGaugeValue(100);
    hud->addBarGraph(200, 350, 1, 20, 100, 0, 250, 200, 255);//int x, int y, int scaleValues, int width, int height, int r, int g, int b, int alpha
    hud->drawAll();
    
    return 0;
}
