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
* This file is C-file of the component "MCU".
*********************************************************************************
*/

/*
*********************************************************************************
* Includes
*********************************************************************************
*/

#include "mcu_inf.h"
#include "mcu_priv.h"

/*
*********************************************************************************
* local Variables
*********************************************************************************
*/




/*
*********************************************************************************
* Description	: Implementation of behavior function set_bit
*
* Argument		: port			:
*				  bit_position	:
*
* Return		: none
*********************************************************************************
*/
void MCU::set_bit(PORT port, PIN pinPos) {
    switch (port) {
    case PORTA:
        SetBitInMsk(m_PortA, pinPos);
        break;
    case PORTB:
        SetBitInMsk(m_PortB, pinPos);
        break;
    case PORTC:
        SetBitInMsk(m_PortC, pinPos);
        break;
    case PORTD:
        SetBitInMsk(m_PortD, pinPos);
        break;
    case PORTE:
        SetBitInMsk(m_PortE, pinPos);
        break;
    default:
        /* need implement assert to warning */
        break;
    }
    /* Set value of other device connected to this pin */
    for (uint8 index = 0u; index < 6u; index++) {
        /* Check if port are store in data buffer */
        if (m_mapping.port[index] == port) {
            /* Then, check if pin's mcu (may be high signal pin) of port above is stored in data buffer or not */
            if (m_mapping.firstPin[index] == pinPos && m_mapping.CnctdDrvr[index] != nullptr) {
                m_mapping.CnctdDrvr[index]->setstPinHigh(PHYS_LOGIC_HIGH);
            }
            /* Else, check if pin's mcu (may be high signal pin) of port above is stored in data buffer or not */
            else if (m_mapping.secondPin[index] == pinPos && m_mapping.CnctdDrvr[index] != nullptr) {
                m_mapping.CnctdDrvr[index]->setstPinLow(PHYS_LOGIC_HIGH);
            }
        }
    }
}	/* End of function MCU::set_bit */

/*
*********************************************************************************
* Description	: Implementation of behavior function reset_bit
*
* Argument		: port			:
*				  bit_position	:
*
* Return		: none
*********************************************************************************
*/
void MCU::reset_bit(PORT port, PIN pinPos) {
    switch (port) {
    case PORTA:
        ClearBitInMsk(m_PortA, pinPos);
        break;
    case PORTB:
        ClearBitInMsk(m_PortB, pinPos);
        break;
    case PORTC:
        ClearBitInMsk(m_PortC, pinPos);
        break;
    case PORTD:
        ClearBitInMsk(m_PortD, pinPos);
        break;
    case PORTE:
        ClearBitInMsk(m_PortE, pinPos);
        break;
    default:
        /* need implement assert to warning */
        break;
    }

    /* Set value of other device connected to this pin */
    for (uint8 index = 0u; index < 6u; index++) {
        /* Check if port are store in data buffer */
        if (m_mapping.port[index] == port) {
            /* Then, check if pin's mcu (may be high signal pin) of port above is stored in data buffer or not */
            if (m_mapping.firstPin[index] == pinPos && m_mapping.CnctdDrvr[index] != nullptr) {
                /* If yes, update value for high signal pin of driver */
                m_mapping.CnctdDrvr[index]->setstPinHigh(PHYS_LOGIC_LOW);
            }
            /* Else, check if pin's mcu (may be high signal pin) of port above is stored in data buffer or not */
            else if (m_mapping.secondPin[index] == pinPos && m_mapping.CnctdDrvr[index] != nullptr) {
                m_mapping.CnctdDrvr[index]->setstPinLow(PHYS_LOGIC_LOW);
            }
        }
    }
}	/* End of function MCU::reset_bit */

/*
*********************************************************************************
* Description	: Implementation of behavior function flip_bit
*
* Argument		: port			:
*				  bit_position	:
*
* Return		: none
*********************************************************************************
*/
void MCU::flip_bit(PORT port, PIN pinPos) {
    switch (port) {
    case PORTA:
        FlipBitInMsk(m_PortA, pinPos);
        break;
    case PORTB:
        FlipBitInMsk(m_PortB, pinPos);
        break;
    case PORTC:
        FlipBitInMsk(m_PortC, pinPos);
        break;
    case PORTD:
        FlipBitInMsk(m_PortD, pinPos);
        break;
    case PORTE:
        FlipBitInMsk(m_PortE, pinPos);
        break;
    default:
        /* need implement assert to warning */
        break;
    }
    /* Set value of other device connected to this pin */
    for (uint8 index = 0; index < 6u; index++) {
        /* Check if port are store in data buffer */
        if (m_mapping.port[index] == port) {
            /* Then, check if pin's mcu (may be high signal pin) of port above is stored in data buffer or not */
            if (m_mapping.firstPin[index] == pinPos && m_mapping.CnctdDrvr[index] != nullptr) {
                /* If yes, update value for high signal pin of driver */
                m_mapping.CnctdDrvr[index]->setstPinHigh((m_mapping.CnctdDrvr[index]->getstPinHigh() == PHYS_LOGIC_HIGH) ? PHYS_LOGIC_LOW : PHYS_LOGIC_HIGH);
            }
            /* Else, check if pin's mcu (may be high signal pin) of port above is stored in data buffer or not */
            else if (m_mapping.secondPin[index] == pinPos && m_mapping.CnctdDrvr[index] != nullptr) {
                m_mapping.CnctdDrvr[index]->setstPinLow((m_mapping.CnctdDrvr[index]->getstPinHigh() == PHYS_LOGIC_HIGH) ? PHYS_LOGIC_LOW : PHYS_LOGIC_HIGH);
            }
        }
    }
}	/* End of function MCU::flip_bit */


/*
********************************************************************************************
* Description	: This function reserve to connect PORT/PIN of MCU and logic signal high
*                 pin and low pin of driver
*
* Argument		: MCU& mcu  	 : MCU
*                 PORT port 	 : which port contains pins are mapped
*				  PIN  firstPin  : high signal pin
*                 PIN  secondPin : low signal pin
*                 Driver& driver : driver which we want to connect
*
* Return		: E_OK			 : if mapping between MCU and Driver successfully
*				: E_NOT_OK		 : if pins are stored in the data buffer
*                                  it means these pins are connected to other devices before
********************************************************************************************
*/
uint8 MpgPinLogic(MCU& mcu, PORT port, PIN firstPin, PIN secondPin, Driver& driver) {

    /* Check firstPin and secondPin of port are connected before or not */
    for (uint8 index = 0u; index < 6u; index++) {
        /* Check if port is existed in data buffer */
        if (mcu.m_mapping.port[index] == port) {
            /* Check if firstPin first is connected or not */
            if (mcu.m_mapping.firstPin[index] == firstPin || mcu.m_mapping.secondPin[index] == secondPin) {
                std::cout << firstPin << " of " << port << " is connected before, please use another PIN." << std::endl;
                return E_NOT_OK;	/* Mapping unsuccessfull */
            }
            /* Then check secondPin */
            if (mcu.m_mapping.secondPin[index] == firstPin || mcu.m_mapping.secondPin[index] == secondPin) {
                std::cout << secondPin << " of " << port << " is connected before, please use another PIN." << std::endl;
                return E_NOT_OK;	/* Mapping unsuccessfull */
            }
        }
    }

    /* Updated information relating to connection into data buffer */
    for (uint8 index = 0u; index < 6u; index++) {
        /* Check if data buffer contains any blank slot */
        if (mcu.m_mapping.CnctdDrvr[index] == nullptr) {
            /* Update Port, Pin, ref Driver into data buffer */
            mcu.m_mapping.port[index] = port;
            mcu.m_mapping.firstPin[index] = firstPin;
            mcu.m_mapping.secondPin[index] = secondPin;
            mcu.m_mapping.CnctdDrvr[index] = &driver;
            std::cout << "Mapping PIN " << firstPin << " and PIN " << secondPin << " of PORT " << port <<" to driver successfully" << std::endl;
            return E_OK;	/* Mapping successfull */
        }
    }
    std::cout << "Need to update more mapping connection" << std::endl;
    return E_NOT_OK;	/* Mapping unsuccessfull */
}	/* End of function MpgPinLogic */


