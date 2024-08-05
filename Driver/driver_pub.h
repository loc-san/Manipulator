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
* This file is public header of the component "Driver".
*********************************************************************************
*/

#ifndef _DRIVER_PUB_H_
#define _DRIVER_PUB_H_

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

enum resolution : uint8 {
    FULL_STEP = 1,
    HALF_STEP = 2,
    QUARTER_STEP = 4,
    EIGHTH_STEP = 8,
    SIXTEENTH_STEP = 16,
    THIRTY_SECOND_STEP = 32,
};

enum PhysStLogic : uint8 {
    PHYS_LOGIC_LOW,
    PHYS_LOGIC_HIGH
};

enum status : uint8 {
    OFF,
    ON
};

enum PhysStPower : uint8 {
    PHYS_POWER_LOW,
    PHYS_POWER_HIGH
};

/*
*********************************************************************************
* Prototypes
*********************************************************************************
*/

/* Prototype class Motor */
class Motor;

struct StrdDrvrCnctn {
    Motor* CnctdMotor; /* CnctdMotor[0] : 
                           * CnctdMotor[1] : 
                           *********************************************/
};

class Driver {
private:
    std::string     m_model{};                          /* Name of the Driver's model */
    status          m_stPower = OFF;                    /* Status of Driver's power   */ 
    resolution      m_res;                              /* Resolution mode of Driver  */
    PhysStLogic     m_stlogicHigh;                      /* Status of logic high pin   */
    PhysStLogic     m_stlogicLow;                       /* Status of logic low pin    */
    PhysStPower     m_stPowerHigh = PHYS_POWER_LOW;     /* Status of power high pin   */
    PhysStPower     m_stPowerLow  = PHYS_POWER_LOW;     /* Status of power low pin    */
    StrdDrvrCnctn   m_CnctdMotor;                       /* Connect to motor           */  

public:
    /* Constructor */
    Driver(std::string model, status stPower, resolution res, PhysStLogic stlogicHigh = PHYS_LOGIC_LOW, PhysStLogic stlogicLow = PHYS_LOGIC_LOW, Motor* motor = nullptr)
        : m_model{ model }, m_stPower{ stPower }, m_res { res }, m_stlogicHigh{ stlogicHigh }, m_stlogicLow{ stlogicLow }
    {
        /* Do nothing */
        m_CnctdMotor.CnctdMotor = motor;
    }

    /* -------------- Access function Set value for pin logic high -------------------------------- */
    void setstPinHigh(PhysStLogic stlogicHigh) { m_stlogicHigh = stlogicHigh; };
    /* -------------- Access function Set value for pin logic low --------------------------------- */
    void setstPinLow(PhysStLogic stlogicLow) { m_stlogicLow = stlogicLow; };
    /* -------------- Access function Get value of pin logic high --------------------------------- */
    PhysStLogic getstPinHigh() const { return m_stlogicHigh; };
    /* -------------- Access function Get value of pin logic low ---------------------------------- */
    PhysStLogic getstPinLow() const { return m_stlogicLow; };
    /* -------------- Access function Set status driver's power ----------------------------------- */
    void setstPower(status stPower) { m_stPower = stPower; };
    
};

#endif //_DRIVER_PUB_H_