#ifndef _MANIPULATOR_PUB_H_
#define _MANIPULATOR_PUB_H_

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

class Joint {
private:
    std::string m_name{};               /* Name of Joint                          */
    Driver*     m_driver;               /* driver is used in this joint           */
    Motor*      m_motor;                /* motor is used in this joint            */       

public:
    /* Constructor */
    Joint(std::string name, Driver* driver, Motor* motor)
        : m_name{ name }, m_driver{ driver }, m_motor{ motor }
    {
        /* Do nothing */
    }
};

class JointBase : public Joint {
private:
    std::vector<float32> m_pos;         /* Position of Joint Base                */
    /* Implement for connect to Track Motion Platform IRBT 2005 
     * Implement in the next release  */

public:
    /* Constructor */
    JointBase(std::string name, Driver* driver, Motor* motor)
        : Joint(name, driver, motor)
    {
        /* Do nothing */
    };
    /* ---------- Access function set the value of JointBase's position -------- */
    void setposJointBase(const std::vector<float32> pos) { m_pos = pos; };
    /* ---------- Access function get the value of JointBase's position -------- */
    std::vector<float32> getposJointBase() const { return m_pos; };

    /* ---------- next release ------------------------------------------------- */

};

class JointGripper : public Joint {
private:
    std::vector<float32> m_Gripper;     /* Location of the Gripper               */
    /* Implement for connect to the proximity sensor 
     * Implement in the next release */

    /* Implement for connect to the class Gripper 
     * Implement in the next release */

public:
    /* Constructor */
    JointGripper(std::string name, Driver* driver, Motor* motor)
        : Joint(name, driver, motor)
    {
        /* Do nothing */
    };
    /* ---------- Access function set the value of JointBase's position -------- */
    void setposJointGripper(const std::vector<float32> Gripper) { m_Gripper = Gripper; };
    /* ---------- Access function get the value of JointBase's position -------- */
    std::vector<float32> getposJointGripper() const { return m_Gripper; };

    /* ---------- next release ------------------------------------------------- */
};


class Manipulator {
private:
    std::string             m_model{};          /* Name of manipulator's model             */
    status                  m_stPower = OFF;    /* Status of manipulator's power           */
    std::vector<float32>    m_posMan;           /* Store position of manipulator           */
    std::vector<float32>    m_posGripper;       /* Store position of manipulator's Gripper */
    std::vector<Joint*>     m_joints;           /* Joints of manipulator                   */ 
    MCU*                    m_mcu;              /* MCU is used in manipulator              */    

public:
    /* Constructor */
    Manipulator(std::string model, std::vector<float32> posMan, MCU* mcu)
                : m_model{model}, m_posMan{posMan}, m_mcu{mcu}
    {
        /* Do nothing */
    }
    /* assemble each Joint into Manipulator's model */
    void addJoint(Joint* joint) { m_joints.push_back(joint); }
    /* ----------- Access Function set value for Manipulator's power ---------------------- */
    void setstPower(const status stPower) { m_stPower = stPower ;};
    /* ----------- Access Function get value for Manipulator's power ---------------------- */
    status getstPower() { return m_stPower; };


};

class ControlCabinet {
private:
    std::string  m_model{};             /* Name of ControlCabinet's model                   */
    status       m_stPower = OFF;       /* Status of ControlCabinet's power                 */
    Manipulator* m_manipulator;         /* Joints of manipulator                            */ 
    bool         m_stRequest = FALSE;   /* Status request sending data            
                                         * TRUE : request is sent, and waiting from Manipulator
                                         * FALSE: no request is sent                        */   

public:
    /* Contructor */
    ControlCabinet(std::string model, status stPower, Manipulator* manipulator)
        : m_model{ model }, m_stPower{ stPower }, m_manipulator{ manipulator }
    {
        /* Do nothing */
    }

    /* Control manipulator's gripper move to Point (CoorX, CoorY, CoorZ) */
    void MoveManToPoint(float32 CoorX, float32 CoorY, float32 CoorZ);
    /* -------------- Access Function set for the status cabiet's power ------------------- */
    void setstPower(const status stPower) { m_stPower = stPower; };
    /* -------------- Access Function get for the status cabinet's power ------------------ */
    status getstPower() const { return m_stPower; };
    /* -------------- Access Function set for the status request of Cabinet --------------- */
    void setstRequest(const bool stRequest) { m_stRequest = stRequest; };
    /* -------------- Access Function get for the status request of Cabinet --------------- */
    bool getstRequest() const { return m_stRequest; };
};



#endif //_MANIPULATOR_PUB_H_