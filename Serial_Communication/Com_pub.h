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


/*
****************************************************************************************
* Prototypes
****************************************************************************************
*/

namespace UART {
	uint8  Init(const uint32 boundrate);	/* Initialize the UART connection		   */
	void   Write(const std::string data);	/* Send data via UART protocol		       */
	uint8  Data_Ready();					/* Check data is exited in transmit buffer */
	uint32 Read();							/* Read data from transmit buffer		   */
}

#endif //_COM_PUB_H_