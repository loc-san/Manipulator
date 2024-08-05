/*
*********************************************************************************
*
* Copyright (c) 2024, Dinh Tuan Loc <dinhtuanloc1100@gmail.com>
*  
*********************************************************************************
*           __         _ _ _ _      _ _ _ _  
*          / /        /  _ _  /    /  _ _ _/
*         / /        / /   / /    / /   
*        / /_ _ _   / /_ _/ /    / /_ _ _
*       /_ _ _ _/  /_ _ _ _/    /_ _ _ _/
*
*
* This file is private header of the component "Kinematics".
*********************************************************************************
*/

#ifndef _KINEMATICS_PRIV_H_
#define _KINEMATICS_PRIV_H_

/*
*********************************************************************************
* Type definition
*********************************************************************************
*/

/* Values of Moveo's geometric parameters in milimenter (mm) */
#define a2			221.12		/* Length of Joint ...			           */
#define d1			230.5    	/* Length of Joint ...			           */			
#define d4			222.5  		/* Length of Joint ...			           */	
#define d6			170    		/*                                     	   */

/*
*********************************************************************************
* Prtotypes
*********************************************************************************
*/


/*
*********************************************************************************
* Defines
*********************************************************************************
*/

/* Defines rotation angles for each joint and initialize the initial value for them */
rtnAngle theta1{0, -180, 180};  /* rotation angle of joint 1 */
rtnAngle theta2{0, - 90,  90};  /* rotation angle of joint 2 */
rtnAngle theta3{0,  -10, 190};  /* rotation angle of joint 3 */
rtnAngle theta4{0, -180, 180};  /* rotation angle of joint 4 */
rtnAngle theta5{0,  -90,  90};  /* rotation angle of joint 5 */

/* Define array buffer for matrix T06 */
float32 trafoMtrx[4][4];
/* Define array buffer for position of gripper */
std::array<float32, 3> posGripper;
/* Define array buffer for rotation angle of each joint */
std::array<float32, 5> strdAgRad;	/* Unit: Rad */

/* Define transformation matrix for 2 consecutive joint
 * These matrix is used to serve calculating the forward kinematics */
float32 trafoMtrx01[4][4] = {	/* Transformation matrix T01 */
  {cos(theta1.get()), 0,  sin(theta1.get()),  0},
  {sin(theta1.get()), 0, -cos(theta1.get()),  0},
  {          	   0, 1,            	  0, d1},
  {          	   0, 0,            	  0,  1}
};

float32 trafoMtrx12[4][4] = { /* Transformation matrix T12 */
  {-sin(theta2.get()), -cos(theta2.get()),  0,  -a2*sin(theta2.get())},
  { cos(theta2.get()), -sin(theta2.get()),  0,   a2*cos(theta2.get())},
  {           		0, 					1,  0, 		   			    0},
  {           		0, 					0,  0,	 	  			    1}
};

float32 trafoMtrx23[4][4] = { /* Transformation matrix T23 */
  { sin(theta3.get()),  0, cos(theta3.get()), 0},
  {-cos(theta3.get()),  0, sin(theta3.get()), 0},
  {           		0, -1,           	   0, 0},
  {           		0,  0,           	   0, 1} 	
};

float32 trafoMtrx34[4][4] = { /* Transformation matrix T34 */
  { cos(theta4.get()),  0,  sin(theta4.get()),  0},
  { sin(theta4.get()),  0, -cos(theta4.get()),  0},
  {           		0,  1,            		0, d4},
  {           		0,  0,            		0,  1} 	
};

float32 trafoMtrx45[4][4] = { /* Transformation matrix T45 */
  { cos(theta5.get()),  0, -sin(theta5.get()),  0},
  { sin(theta5.get()),  0,  cos(theta5.get()),  0},
  {           		0, -1,            		0,  0},
  {           		0,  0,            		0,  1} 	
};

float32 trafoMtrx56[4][4] = { /* Transformation matrix T56 */
  { 1,  0,  0,  0},
  { 0,  1,  0,  0},
  { 0,  0,  1, d6},
  { 0,  0,  0,  1} 	
};

/*
*********************************************************************************
* Extern declarations
*********************************************************************************
*/



#endif //_KINEMATICS_PRIV_H_