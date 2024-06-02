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
* Implementation of setting pre-config for initialize UART
* 
* Parameter :   boundrate   : 
* 
* Return    :   1 : indicate Successful Completion
*               0 : indicate UART initialization failed
*********************************************************************************
*/

uint8 UART::Init(const uint32 boundrate) {

    /* Setting Asynchronous Mode */

    /* Enables Serial Port */

    /* Enables Transmission */

    /* Returns 1 to indicate Successful Completion */
    return 1;
    /* Returns 0 to indicate UART initialization failed */
}

/*
*********************************************************************************
* Description : Implementation of function Write of UART
*
* Argument    :     data    :   
*
* Return      :     none
*********************************************************************************
*/

void UART::Write(const std::string data)
{
    /* Check UART is ready to transmit */

    /* write data into UART transmitted buffer */

}

/*
*********************************************************************************
* Description : is used to check data is available in transmit buffer
*
* Argument    : none
*
* Return      : 1 : to indicate data is existed 
*               0 : to indicate data is not existed
*********************************************************************************
*/
uint8  UART::Data_Ready() {
    /* Check data is existed in transmit buffer */

    /* Return 1 to indicate data is existed */
    return 1;
    /* Return 0 to indicate no data is existed */
}


/*
*********************************************************************************
* Description : is used to read data from UART transmit buffer
*
* Argument    : none
*
* Return      : 1 : to indicate data is read successful
*               0 : to indicate data is read is not successful
*********************************************************************************
*/
uint32 UART::Read() {
    return 1;
}


