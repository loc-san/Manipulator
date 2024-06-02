/*
*********************************************************************************
* Includes
*********************************************************************************
*/

#include "manipulator_inf.h"
#include "manipulator_priv.h"

/*
*********************************************************************************
* local Variables
*********************************************************************************
*/


/*
*********************************************************************************
* Description : is used to control manipulator'gripper move to Point (X, Y, Z) 
*
* Argument    : CoorX   : Point's location in X direction 
*               CoorY   : Point's location in Y direction
*               CoorZ   : Point's location in Z direction
*
* Return      : none
*********************************************************************************
*/
void ControlCabinet::MoveManToPoint(float32 CoorX, float32 CoorY, float32 CoorZ) {
    std::vector<float32> strdAngle;		/* array is used to store angle of each joint
                                         * value have unit is rad                    */

    /* calculate the value of each Joint via inverse kinematics */
    strdAngle = kinematics::inverse(CoorX, CoorY, CoorZ);

    /* round value of the array */
    for (size_t index = 0; index < strdAngle.size(); ++index) {
        strdAngle[index] = std::round(strdAngle[index]);
    }

    std::string m_strData;     /* store data that will be sent to manipulator
                                * data is a string hold value of each angle */

    /* Merge each angle into 1 string */
    for (size_t index = 0; index < strdAngle.size(); ++index) {
        /* explicit data type to string */
        std::string m_strDatatemp = std::to_string(strdAngle[index]);
        /* 000 00x 0xx xxx */
        if (m_strDatatemp.size() < 3) {
            m_strDatatemp = std::string(3 - m_strDatatemp.size(), '0') + m_strDatatemp;
        }
        m_strData += m_strDatatemp;
    }

    /* Send data via UART */
    UART::Write(m_strData);

    /* Set status request to indicate MoveManToPoint is on processing */
    m_stRequest = TRUE;
}