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
* This file is main source code.
*********************************************************************************
*/

#include "manipulator.h"

/* variable that control thread tiOSScheduler() */
std::atomic<bool> running(true);

/* counter for timer */
std::atomic<uint32> tiStrdTimer{ 0 };

/*
********************************************************************************************
* Description	: This function is used to create a sequence 1ms that serve for struct timer
*
* Argument		: none
*
* Return		: none
********************************************************************************************
*/
void tiOSScheduler() {
    auto start = std::chrono::high_resolution_clock::now();
    /* Check if thread is running or not */
    while (running.load()) {
        /* Get current couting's value */
        auto current = std::chrono::high_resolution_clock::now();
        /* Calculate the duration is equal to scheduler that we set */
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(current - start);
        if (duration.count() >= 1) {
            ++tiStrdTimer;
            start = current;  /* Update value for starting point */
        }
    }
}

int main(int argc, char* argv[]) {
    /* Initialize the timer thread */
    std::thread timerThread(tiOSScheduler);

    /* Initialize Motor       */
    Motor motor1{ "42HS4017A4",    OFF, PHYS_POWER_LOW, PHYS_POWER_LOW };
    Motor motor2{ "57HS11242A4D8", OFF, PHYS_POWER_LOW, PHYS_POWER_LOW };
    Motor motor3{ "42HS4013A4Y3",  OFF, PHYS_POWER_LOW, PHYS_POWER_LOW };
    Motor motor4{ "42HS4013A4Y3",  OFF, PHYS_POWER_LOW, PHYS_POWER_LOW };
    Motor motor5{ "42HS4013A4Y3",  OFF, PHYS_POWER_LOW, PHYS_POWER_LOW };
    Motor motor6{ "35HS3408A4",    OFF, PHYS_POWER_LOW, PHYS_POWER_LOW };

    /* Initialize Driver      */
    Driver driver1{ "TB6600", OFF, FULL_STEP , PHYS_LOGIC_LOW , PHYS_LOGIC_LOW , &motor1 };
    Driver driver2{ "TB6600", OFF, FULL_STEP , PHYS_LOGIC_LOW , PHYS_LOGIC_LOW , &motor2 };
    Driver driver3{ "TB6600", OFF, FULL_STEP , PHYS_LOGIC_LOW , PHYS_LOGIC_LOW , &motor3 };
    Driver driver4{ "TB6600", OFF, FULL_STEP , PHYS_LOGIC_LOW , PHYS_LOGIC_LOW , &motor4 };
    Driver driver5{ "TB6600", OFF, FULL_STEP , PHYS_LOGIC_LOW , PHYS_LOGIC_LOW , &motor5 };
    Driver driver6{ "TB6600", OFF, FULL_STEP , PHYS_LOGIC_LOW , PHYS_LOGIC_LOW , &motor6 };

    /* Initialize MCU         */
    MCU MicroController("PIC16F887", OFF);

    /* Mapping PIN0 and PIN1 of PORTA's MCU with driver 1 */
    (void)MpgPinLogic(MicroController, PORTA, PIN_POSITION_0, PIN_POSITION_1, driver1);
    /* Mapping PIN2 and PIN3 of PORTA's MCU with driver 2 */
    (void)MpgPinLogic(MicroController, PORTA, PIN_POSITION_2, PIN_POSITION_3, driver2);
    /* Mapping PIN5 and PIN6 of PORTB's MCU with driver 3 */
    (void)MpgPinLogic(MicroController, PORTB, PIN_POSITION_5, PIN_POSITION_6, driver3);
    /* Mapping PIN3 and PIN4 of PORTC's MCU with driver 4 */
    (void)MpgPinLogic(MicroController, PORTC, PIN_POSITION_3, PIN_POSITION_4, driver4);
    /* Mapping PIN1 and PIN2 of PORTC's MCU with driver 5 */
    (void)MpgPinLogic(MicroController, PORTC, PIN_POSITION_1, PIN_POSITION_2, driver5);
    /* Mapping PIN4 and PIN5 of PORTD's MCU with driver 6 */
    (void)MpgPinLogic(MicroController, PORTD, PIN_POSITION_4, PIN_POSITION_5, driver6);

    /* Initialize Joint       */
    JointBase       Joint1("Joint1", &driver1, &motor1);
    Joint           Joint2("Joint2", &driver2, &motor2);
    Joint           Joint3("Joint3", &driver3, &motor3);
    Joint           Joint4("Joint4", &driver4, &motor4);
    Joint           Joint5("Joint5", &driver5, &motor5);
    JointGripper    Joint6("Joint6", &driver6, &motor6);

    /* Initialize Manipulator */
    Manipulator ABB("IRB 4600", {800,600,500}, &MicroController);
    ABB.addJoint(&Joint1);  /* Assemble Joint 1 into Manipulator */
    ABB.addJoint(&Joint2);  /* Assemble Joint 2 into Manipulator */
    ABB.addJoint(&Joint3);  /* Assemble Joint 3 into Manipulator */
    ABB.addJoint(&Joint4);  /* Assemble Joint 4 into Manipulator */
    ABB.addJoint(&Joint5);  /* Assemble Joint 5 into Manipulator */
    ABB.addJoint(&Joint6);  /* Assemble Joint 6 into Manipulator */

    /* Init baudrate UART */
    UART::Init(9600);

    /* Initialize control cabinet  */
    ControlCabinet ctrlCabinet("IRC5", ON, &ABB);

    if (ctrlCabinet.getstPower() == ON) {
        ABB.setstPower(ON);
        MicroController.setstPower(ON);
        driver1.setstPower(ON);
        driver2.setstPower(ON);
        driver3.setstPower(ON);
        driver4.setstPower(ON);
        driver5.setstPower(ON);
        driver6.setstPower(ON);
        motor1.setstPower(ON);
        motor2.setstPower(ON);
        motor3.setstPower(ON);
        motor4.setstPower(ON);
        motor5.setstPower(ON);
        motor6.setstPower(ON);
    }

    /* Command to control Gripper move to Point (700, 800, 400)*/
    ctrlCabinet.MoveManToPoint(700, 800, 400);


    /* End of main function */
    running.store(false);  
    if (timerThread.joinable()) {
        timerThread.join();  /* waiting to Thread end */
    }
	return 0;
}