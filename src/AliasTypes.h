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
* This file is public header of the "Alias Type".
*********************************************************************************
*/

#ifndef _ALIAS_TYPES_H_
#define _ALIAS_TYPES_H_

#ifndef TRUE
#define TRUE (1 != 0)
#endif

#ifndef FALSE
#define FALSE (0 != 0)
#endif

/*
*********************************************************************************
* ALIAS Integer Data Types
*********************************************************************************
*/

/* The alias for data type of 8 bit signed.                 */
using sint8 = signed char;      /* Range : -128 .. +127     */

/* The alias for data type of 8 bit unsigned.               */
using uint8 = unsigned char;    /* Range : 0 .. 255         */

/* The alias for data type of 16 bit signed.                */
using sint16 = signed short;    /* Range : -32768 .. +32767 */

/* The alias for data type of 16 bit unsigned.              */
using uint16 = unsigned short;  /* Range : 0 .. 65535       */

/* The alias for data type of 32 bit signed.                */
using sint32 = signed long;     /*Range : -2147483648 .. +2147483647   */

/* The alias for data type of 64 bit signed.                */
using sint64 = signed long long;    /*Range: -9223372036854775808..+9223372036854775807*/

/* The alias for data type of 32 bit unsigned.              */
using uint32 = unsigned long;   /* Range:  0 .. 4294967295  */

/* The alias for data type of 64 bit unsigned. */
using uint64 = unsigned long long;  /* Range :   0 ..18446744073709551615  */


/*
*********************************************************************************
* ALIAS Float Data Types
*********************************************************************************
*/
/* The alias for data type of 32-bit binary interchange format */
using float32 = float;

/* The alias for data type of 64-bit binary interchange format */
using float64 = double;

#endif // _ALIAS_TYPES_H