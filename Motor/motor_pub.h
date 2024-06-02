#ifndef _MOTOR_PUB_H_
#define _MOTOR_PUB_H_

/*
*********************************************************************************
* define
*********************************************************************************
*/

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

class Motor {
private:
    std::string  m_model{};         /* Name of the Motor's model */
    status       m_stPower;         /* Status of Motor's power   */
    PhysStPower  m_stPowerHigh;     /* Status of power high pin  */
    PhysStPower  m_stPowerLow;      /* Status of power low pin   */

public:
    /* Constructor */
    Motor(std::string model, status stPower = OFF, PhysStPower stPowerHigh = PHYS_POWER_LOW, PhysStPower stPowerLow = PHYS_POWER_LOW)
        : m_model{ model }, m_stPower{ stPower }, m_stPowerHigh{ stPowerHigh }, m_stPowerLow{ stPowerLow }
    {
        /* Do nothing */
    }
    /* -------------- Access function Set value for pin power high -------------------------------- */
    void getstPinHigh(PhysStPower stPowerHigh) { m_stPowerHigh = stPowerHigh; };
    /* -------------- Access function Get value of pin power high  -------------------------------- */
    PhysStPower getstPinHigh() const { return m_stPowerHigh; };
    /* -------------- Access function Set value for pin power high -------------------------------- */
    void getstPinLow(PhysStPower stPowerLow) { m_stPowerLow = stPowerLow; };
    /* -------------- Access function Get value of pin power high  -------------------------------- */
    PhysStPower getstPinLow() const { return m_stPowerLow; };
    /* -------------- Access function Set status driver's power ----------------------------------- */
    void setstPower(status stPower) { m_stPower = stPower; };

};

#endif //_MOTOR_PUB_H_