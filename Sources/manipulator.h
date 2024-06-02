#ifndef _MANIPULATOR_H_
#define _MANIPULATOR_H_


/*
*********************************************************************************
* include standard library
*********************************************************************************
*/

#ifndef _ALIAS_TYPES_H_
#include "AliasTypes.h"
#endif

#ifndef _IOSTREAM_
#include <iostream>
#endif

#ifndef _THREAD_
#include <thread>
#endif

#ifndef _ATOMIC_ 
#include <atomic>
#endif

#ifndef _CHRONO_ 
#include <chrono>
#endif

/*
*********************************************************************************
* global variable definition
*********************************************************************************
*/


/*
*********************************************************************************
* include all atomic components inside the structural component
*********************************************************************************
*/

#include "driver_pub.h"
#include "motor_pub.h"
#include "mcu_pub.h"
#include "Com_pub.h"
#include "kinematics_pub.h"
#include "manipulator_pub.h"






#endif // _MANIPULATOR_H_
