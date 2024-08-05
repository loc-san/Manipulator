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
* This file is C-file of the component "Kinematics".
*********************************************************************************
*/

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
* Implementation of forward kinematics and inverse kinematics
*********************************************************************************
*/

/*
****************************************************************************************
* Description : is used to calculate forward kinematics
*
* Argument    :	Array (5 elements corresponding to 5 joints) of rotation angles
*
* Return      : Returns the position of the manipulator in three directions x,
*y, z
****************************************************************************************
*/

std::array<float32, 3> kinematics::forward(const std::array<float32, 5>& rtnAngle) {

  /* Update value for each rotation angle */
  theta1.set(rtnAngle);
  theta2.set(rtnAngle);
  theta3.set(rtnAngle);
  theta4.set(rtnAngle);
  theta5.set(rtnAngle);

  /* Clean the transfomation matrix */
  for (uint8 idx_row = 0; idx_row < row; idx_row++){
  for (uint8 idx_col = 0; idx_col < col; idx_col++){
    trafoMtrx[idx_row][idx_col] = 0;
  }
  }  

  /* Calculate the position of gripper via transfomation matrix */
  Mul2Dimension(trafoMtrx, trafoMtrx01, trafoMtrx12);
  Mul2Dimension(trafoMtrx, trafoMtrx23, trafoMtrx34);
  Mul2Dimension(trafoMtrx, trafoMtrx45, trafoMtrx56);

  /* Update the position that calculated into buffer */
  posGripper.at(0) = trafoMtrx[0][3];
  posGripper.at(1) = trafoMtrx[1][3];
  posGripper.at(2) = trafoMtrx[2][3];

  return posGripper;
}	/* End of function kinematics::forward */

/*
*********************************************************************************
* Description : is used to calculate inverse kinematics
*
* Argument    : location of gripper in three directions x, y, z
*
* Return      : Returns the rotation angle of the machine arm joints based on
*the input position of the gripper
*********************************************************************************
*/

std::array<float32, 5> kinematics::inverse(float32 coorX, float32 coorY, float32 coorZ) {
  /* local variable */
  float32 temp1;
  float32 temp2;
  float32 temp3;
  float32 temp4;
  float32 sin_theta2;
  float32 cos_theta2;
  float32 sin_theta3;
  float32 cos_theta3;

  /* theta1's calculation */
  strdAgRad.at(0) = atan2(coorY,coorX);
  theta1.set(strdAgRad.at(0)*180/PI);

  /* theta3's calculation */
  temp1 = coorX*cos(strdAgRad.at(0)) + coorY*sin(strdAgRad.at(0));
  temp2 = coorZ - d1;
  cos_theta3 = (temp1^2 + temp2^2 - a2^2 - d4^2)/(2*a2*d4);
  sin_theta3 = sqrt(1 - cos_theta3^2);
  strdAgRad.at(2) = atan2(sin_theta3,cos_theta3);
  theta3.set(strdAgRad.at(2)*180/PI);

  /* theta2's calculation */
  temp3 = d4*sin(strdAgRad.at(2));
  temp4 = a2 +d4*cos(strdAgRad.at(2));
  sin_theta2 = -(temp1*temp4 + temp2*temp3)/(temp3^2 + temp4^2);
  cos_theta2 = (temp2*temp4 - temp1*temp3)/(temp3^2 + temp4^2);
  strdAgRad.at(1) = atan2(sin_theta2,cos_theta2);
  theta3.set(strdAgRad.at(1)*180/PI);

  /* theta4's calculation */


  /* theta5's calculation */


  return strdAgRad;
}	/* End of function kinematics::inverse */

/*
*********************************************************************************
* Description: Function is used to muptiple 2 current matrix size [4][4]
*********************************************************************************
*/

void Mul2Dimension(float32& mtrx[][], float32 mtrx1[][], float32 mtrx2[][]){
  uint8 row = 4;	/* number of matrix's row    */
  uint8 col = 4;	/* number of matrix's column */

  /* Multiple between transfomation matrix */
  for (uint8 idx_row = 0; idx_row < row; idx_row++){
    for (uint8 idx_col = 0; idx_col < col; idx_col++){
      for (uint8 idx_temp = 0; idx_temp < 4; idx_temp++){
        /* Calculate element of matrix mtrx at position [idx_row,idx_col] */
        mtrx[idx_row][idx_col] += mtrx1[idx_row][idx_temp]*mtrx2[idx_temp][idx_col];
      }
    }
  }
}	/* End of function Mul2Dimension */