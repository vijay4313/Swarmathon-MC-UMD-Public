#ifndef AVOID_BEHAVIOR_H
#define AVOID_BEHAVIOR_H

#include "../behaviors/BehaviorInterface.h"
#include "SearchBehavior.h"
#include <time.h>

class AvoidBehavior : public Behavior{
    enum Stage{
        WAIT = 0,
        TURN,
        DRIVE
    };
    Stage stage;

    bool isTimeInit = false;

    int waitTime;
    time_t initTime;


    float emergencyTurnStop = 0.3;
    float emergencyStop = 0.4;
    float clearDistance = 0.7; // 1 meter means clear

    float directionToDrive = 0;

    bool turnLock = false;
    bool isLeftTurn = false;

    int switchTurnCount = 0;
    bool isReverse = false;



    public:
        AvoidBehavior() : Behavior(AVOID_BEHAVIOR_TYPE){
            waitTime = 1;
            stage = WAIT;
        }
        bool tick();


};









#endif
