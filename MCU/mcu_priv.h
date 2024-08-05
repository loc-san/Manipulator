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
* This file is private header of the component "MCU".
*********************************************************************************
*/

#ifndef _MCU_PRIV_H_
#define _MCU_PRIV_H_

/*
*********************************************************************************
* Type definition
*********************************************************************************
*/


/*
*********************************************************************************
* Prtotypes
*********************************************************************************
*/


/*
*********************************************************************************
* Defines
*********************************************************************************
*/



/*
*********************************************************************************
* Extern declarations
*********************************************************************************
*/


/*
*********************************************************************************
* Inline function
*********************************************************************************
*/
#define SetBitInMsk(base, mask)		(base |= (1u << mask))
#define ClearBitInMsk(base, mask)	(base &= ~( 1u << mask))
#define TestBitInMsk(base, mask)	((base & (1u << mask)) != 0u) ? TRUE : FALSE
#define FlipBitInMsk(base, mask)	(base ^= (1u << mask))

#endif //_MCU_PRIV_H_