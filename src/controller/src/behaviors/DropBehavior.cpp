#include "DropBehavior.h"

bool DropBehavior::tick(){
    switch(stage){
        case INIT:
        {
            x = OdometryHandler::instance()->getX();
            y = OdometryHandler::instance()->getY();
            stage = DRIVE_TO_CENTER;
            SonarHandler::instance()->setEnable(false);
            break;
        }
        case DRIVE_TO_CENTER:
        {
            //Drive forward for a meter
            //get current location
            double currX= OdometryHandler::instance()->getX();
            double currY = OdometryHandler::instance()->getY();

            cout<<"CENTERDRIVE: "<<hypot(x - currX, y - currY)<<endl;

            //While disnace driven is less than 0.3 of a meter
            if(hypot(x - currX, y - currY) < 0.3){
                // Drive forwards
                DriveController::instance()->sendDriveCommand(slowDrive, slowDrive);
            } else {
                 DriveController::instance()->stop();
                 stage = DROP_CUBE;
            }

            break;
        }
        case DROP_CUBE:
        {
            // Drop the cube
            ClawController::instance()->fingerOpen();
            ClawController::instance()->wristUp();
            stage = DRIVE_BACK;

            x = OdometryHandler::instance()->getX();
            y = OdometryHandler::instance()->getY();

            //if the offset is greater than 2.5 meter
            if(fabs(hypot(x - OffsetController::instance()->centerX, y - OffsetController::instance()->centerY)) > 0.7){
                //reset odom
                OffsetController::instance()->sendOffsets(0, 0, IMUHandler::instance()->w, IMUHandler::instance()->z);
                OffsetController::instance()->centerX = 0;
                OffsetController::instance()->centerY = 0;

                //Get theta rotation by converting quaternion orientation to pitch/roll/yaw
                tf::Quaternion q(IMUHandler::instance()->x, IMUHandler::instance()->y, IMUHandler::instance()->z, IMUHandler::instance()->w);
                tf::Matrix3x3 m(q);
                double roll, pitch, yaw;
                m.getRPY(roll, pitch, yaw);

                OffsetController::instance()->centerTheta =yaw;
            } else {
                //Record the center
                OffsetController::instance()->centerX = x;
                OffsetController::instance()->centerY = y;
                OffsetController::instance()->centerTheta = OdometryHandler::instance()->getTheta();
            }


            break;
        }
        case DRIVE_BACK:
        {
            TargetHandler::instance()->setEnabled(false);
            //Drive back a meter
            double currX= OdometryHandler::instance()->getX();
            double currY = OdometryHandler::instance()->getY();

            //While disnace driven is less than a meter
            if(fabs(hypot(x - currX, y - currY)) < 1){
                // Drive back
                DriveController::instance()->sendDriveCommand(-slowDrive, -slowDrive);
            } else {
                stage = TURN;
                theta = OdometryHandler::instance()->getTheta() + M_PI;
            }

            break;
        }
        case TURN:
        {
            if(DriveController::instance()->turnToTheta(theta)){
                TargetHandler::instance()->setHasCube(false);
                DriveController::instance()->stop();
                TargetHandler::instance()->setEnabled(true);
                SonarHandler::instance()->setEnable(true);
                return true;
            }
            break;
        }

    }

    return false;
}
