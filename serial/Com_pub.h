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
* This file is public header of the component "Serial".
*********************************************************************************
*/

#ifndef _COM_PUB_H_
#define _COM_PUB_H_

/*
****************************************************************************************
* define
****************************************************************************************
*/



/*
****************************************************************************************
* type defs and enums
****************************************************************************************
*/
/* Return value of these function UART */
enum Uart_ReturnType : uint8 {
    UART_OK,
    UART_ERROR
};

/*
****************************************************************************************
* Prototypes
****************************************************************************************
*/

class UART {
private:
	
	uint32 m_baudRate;			/* baudrate for transmision 		   		 */
	std::queue<uint8>* m_txbuf;	/* Tx buffer after push into Shift Register  */
	std::queue<uint8>* m_rxbuf;	/* Rx buffer before push into Shift Register */
	
public:
	/* Constructor */
	UART(uint32 baudRate) : m_baudRate{baudRate} { /* Do nothing */ }
	/* Send data via UART protocol to Tx line */
	Uart_ReturnType sendData(const std::vector<uint8>& Data);
	/* Read data via UART protocol from Tx line */
	Uart_ReturnType receiveData(std::vector<uint8>& Data, uint8 DataLength);
	/* Mapping 2 device to connect UART */
	friend void mapping(UART& device1, UART& device2){
		device1.m_txbuf = device2.m_rxbuf;
		device2.m_txbuf = device1.m_rxbuf;
	}
};

#endif //_COM_PUB_H_