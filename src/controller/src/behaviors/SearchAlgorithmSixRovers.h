#ifndef SEARCH_ALGORITHM_SIX_ROVERS_BEHAVIOR_H
#define SEARCH_ALGORITHM_SIX_ROVERS_BEHAVIOR_H

#include "BehaviorInterface.h"
#include "../controllers/DriveController.h"
#include <cmath>
#include <math.h>

class SearchAlgorithmSixRoversBehavior: public Behavior{
    bool initialize = true;
    bool initialDrive = true;
    bool initialCheck = true;
    bool AlgorithmA = false;
    bool AlgorithmB = false;
    bool AlgorithmC = false;
    bool first = true;
    bool second = true;
    bool third = true;

    float initial_theta;

    float theta;
    float distance;
    float left;
    float center;
    float right;

    // intended algorithm coordinates
    float xi; 
    float yi;
    // intended algorithm coordinates corrected through rotation
    float x;
    float y;
    // x and y iterator
    float xiterator;
    float yiterator;



    int iterCount = 0;

    public:
        SearchAlgorithmSixRoversBehavior() : Behavior(SEARCH_ALGORITHM_SIX_ROVERS_BEHAVIOR_TYPE){
            xiterator = 0.0;
            yiterator = 0.5;
        }
        bool tick();
        void determineRovers();
};



#endif