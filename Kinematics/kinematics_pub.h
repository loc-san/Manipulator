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
* This file is public header of the component "Kinematics".
*********************************************************************************
*/

#ifndef _KINEMATICS_PUB_H_
#define _KINEMATICS_PUB_H_

#include <vector>

/*
*********************************************************************************
* define
*********************************************************************************
*/

#define 	PI		3.14	/* PI numeric */

/*
*********************************************************************************
* type defs and enums
*********************************************************************************
*/


/*
*********************************************************************************
* Prototypes
*********************************************************************************
*/


/*
*********************************************************************************
* Description: Class store value of rotation angle of Joint
* Member     : m_theta : is the rotation angle of this Joint	(Unit: rad)
*              m_min   : is the low limit of m_theta			(Unit: rad)
*              m_max   : is the high limit of m_theta			(Unit: rad)
*********************************************************************************
*/
class rtnAngle {
private:
	float32 m_theta;
	float32 m_min;
	float32 m_max;
public:
	/* ----------- Constructor ----------- */
	rtnAngle(float32 theta, float32 min, float32 max): 
					m_theta{theta*PI/180}, m_min{min*PI/180}, m_max{max*PI/180} 
	{
		/* Make sure theta is always in range [min,max] */
		if (m_theta < m_min){
			/* Assign value m_min to m_theta */
			m_theta = m_min;
			std::cout<<"Value of m_theta input is lower than min("<<m_min<<")"<<endl;
		}
		else if (m_theta > max){
			/* Assign value m_max to m_theta */
			m_theta = m_max;
			std::cout<<"Value of m_theta input is higher than max("<<m_max<<")"<<endl;
		}
		else{
			/* Do nothing */
		}
	};

	/* ----------- Access Function get value for rotation Angle ----------- */
	float32 get() { return m_theta; };

	/* ----------- Access Function set value for rotation Angle ----------- */
	void set(float32 theta) {

		/* conversion for theta */
		theta = theta*PI/180;

		/* Make sure theta is always in range [min,max] */
		if (m_theta < m_min){
			/* Assign value m_min to m_theta */
			m_theta = m_min;
			std::cout<<"Value of m_theta input is lower than min("<<m_min<<")"<<endl;
		}
		else if (m_theta > max){
			/* Assign value m_max to m_theta */
			m_theta = m_max;
			std::cout<<"Value of m_theta input is higher than max("<<m_max<<")"<<endl;
		}
		else{
			/* Do nothing */
		}
	};
};

namespace kinematics {
	/* Returns the position of the manipulator in three directions x, y, z */
	std::array<float32, 3> forward(const std::array<float32, 5>& rtnAngle);

	/* Returns the rotation angle of the machine arm joints based on the input position of the gripper */
	std::array<float32, 5> inverse(float32 coorX, float32 coorY, float32 coorZ);

}

#endif //_KINEMATICS_PUB_H_