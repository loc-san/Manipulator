/*
*********************************************************************************
* Includes
*********************************************************************************
*/

#include "kinematics_inf.h"
#include "kinematics_priv.h"

/*
*********************************************************************************
* local Variables
*********************************************************************************
*/

/*
*********************************************************************************
* Implementation of ...
*********************************************************************************
*/

/*
****************************************************************************************
* Description : is used to calculate forward kinematics
* 
* Argument    :	set of angle value
* 
* Return      : location of gripper in 3 directions X, Y and Z
****************************************************************************************
*/

std::vector<float32> kinematics::forward(std::vector<float32>& angle) {
	std::vector<float32> posMan;

	return posMan;
}

/*
*********************************************************************************
* Description : is used to calculate inverse kinematics
*
* Argument    : location of gripper in 3 directions X, Y and Z
*
* Return      : set of angle value
*********************************************************************************
*/

std::vector<float32> kinematics::inverse(float32 CoorX, float32 CoorY, float32 CoorZ) {
	std::vector<float32> strdAngle;		/* array is used to store angle of each joint */

	return strdAngle;
}