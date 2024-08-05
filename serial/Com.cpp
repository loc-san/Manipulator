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
* This file is C-file of the component "Serial".
*********************************************************************************
*/


/*
*********************************************************************************
* Includes
*********************************************************************************
*/

#include "Com_inf.h"
#include "Com_priv.h"

/*
*********************************************************************************
* local Variables
*********************************************************************************
*/


/*
*********************************************************************************
* Description : Implementation of function Send data of UART
*
* Argument    : DataBuffer    :
*               DataLength    :                
*
* Return      : UART_OK,
*               UART_ERROR
*
* Flow for Transmitter Side:
*
*  +------------+   +-------------+   +-------------+   +-----------+
*  |   DATA     |-->|  SHIFT      |-->| TRANSMITTER |-->| TX LINE   |
*  |   (Parallel|   |  REGISTER   |   |             |   |           |
*  |   Data)    |   | (Parallel to|   | (Serial Data|   | (Serial   |
*  |            |   |  Serial)    |   |  Transmit)  |   |  Data)    |
*  +------------+   +-------------+   +-------------+   +-----------+
*                                                             |
*                                                         TX LINE (Serial Data)
*********************************************************************************
*/

Uart_ReturnType UART::sendData(const std::vector<uint8>& Data) {
  /* Check each byte that want to transmit */
  for (auto& byte : Data){
	std::bitset<10> frame;
	/* Start transmission byte by pull bit start to 0 */
	frame[0] = 0;
	/* Data bit */
	for (uint8 index = 0; index < 8; index++){
		frame[index+1] = (byte >> index) & 1;
	}
	/* Stop transmission byte by push the bit stop to 1 */
	frame[9] = 1;
	
	/* Update data of each byte into Tx buffer */
	for (uint8 index = 0; index < 10; index++){
		m_txbuf.push(frame[index]);
	}
  }
  return UART_OK;
}	// End of UART::sendData

/*
*********************************************************************************
* Description : is used to read data from UART transmit buffer
*
* Argument    : DataBuffer    :
*               DataLength    :                
*
* Return      : UART_OK,
*               UART_ERROR
*
* Flow for Receiver Side:
*
*  RX LINE (Serial Data)
*        |
*  +-----------+   +-------------+   +-------------+   +------------+
*  | RX LINE   |-->| RECEIVER    |-->|  SHIFT      |-->|   DATA     |
*  | (Serial   |   |             |   |  REGISTER   |   |  (Parallel |
*  |  Data)    |   | (Serial Data|   | (Serial to  |   |    Data)   |
*  |           |   |  Receive)   |   |  Parallel)  |   |            |
*  +-----------+   +-------------+   +-------------+   +------------+
*                                                    
*********************************************************************************
*/

Uart_ReturnType UART::receiveData(std::vector<uint8>& Data, uint8 DataLength){
  for(uint8 idxLen = 0;idxLen < DataLength; idxLen++){
	  uint8 = byte;
	  std::bitset<10> frame;
	  /* Check data or Rx line is empty or not */
	  if(!m_rxbuf.empty()){
		/* Update Rx buffer into frame buffer */
		for(uint8 idxBuf = 0; idxBuf < 10; idxBuf++){
			/* get the front of the queue */
			frame[idxBuf] = m_rxbuf.front();
			/* remove the front element out of the Rx buffer */
			m_rxbuf.pop();
		}
	  }
	  /* Update frame buffer into byte data */
	  for (uint8 idxbyte = 0; idxbyte < 8; idxbyte++){
		Data[idxLen] |= frame[idxbyte + 1] << idxbyte;
	  }
  }
  return UART_OK;
}	// End of UART::ReceiveData
