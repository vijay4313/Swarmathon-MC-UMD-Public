#ifndef SEARCH_BEHAVIOR_H
#define SEARCH_BEHAVIOR_H

#include "BehaviorInterface.h"
#include "../controllers/DriveController.h"
#include <cstdlib>
#include <ctime>
#include <random_numbers/random_numbers.h>

class SearchBehavior: public Behavior{
    bool first = true;
    bool second = true;
    bool third = true;
    float theta;
    float distance;

    float x;
    float y;

    int iterCount = 0;

    public:
        SearchBehavior() : Behavior(SEARCH_BEHAVIOR_TYPE){}
        bool tick();
        void nextPoint();
};

class RandomSearchBehavior: public Behavior{
    float theta;
    float distance;

    bool first;
    random_numbers::RandomNumberGenerator* rng;

    public:
        RandomSearchBehavior() : Behavior(SEARCH_BEHAVIOR_TYPE){
            rng = new random_numbers::RandomNumberGenerator();
            first = true;
        }
        bool tick();
        void nextPoint();
};



#endif
