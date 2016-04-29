/*******************************************************************************
* File Name: Pin3.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Pin3_ALIASES_H) /* Pins Pin3_ALIASES_H */
#define CY_PINS_Pin3_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define Pin3_0			(Pin3__0__PC)
#define Pin3_0_INTR	((uint16)((uint16)0x0001u << Pin3__0__SHIFT))

#define Pin3_1			(Pin3__1__PC)
#define Pin3_1_INTR	((uint16)((uint16)0x0001u << Pin3__1__SHIFT))

#define Pin3_2			(Pin3__2__PC)
#define Pin3_2_INTR	((uint16)((uint16)0x0001u << Pin3__2__SHIFT))

#define Pin3_3			(Pin3__3__PC)
#define Pin3_3_INTR	((uint16)((uint16)0x0001u << Pin3__3__SHIFT))

#define Pin3_4			(Pin3__4__PC)
#define Pin3_4_INTR	((uint16)((uint16)0x0001u << Pin3__4__SHIFT))

#define Pin3_5			(Pin3__5__PC)
#define Pin3_5_INTR	((uint16)((uint16)0x0001u << Pin3__5__SHIFT))

#define Pin3_6			(Pin3__6__PC)
#define Pin3_6_INTR	((uint16)((uint16)0x0001u << Pin3__6__SHIFT))

#define Pin3_7			(Pin3__7__PC)
#define Pin3_7_INTR	((uint16)((uint16)0x0001u << Pin3__7__SHIFT))

#define Pin3_INTR_ALL	 ((uint16)(Pin3_0_INTR| Pin3_1_INTR| Pin3_2_INTR| Pin3_3_INTR| Pin3_4_INTR| Pin3_5_INTR| Pin3_6_INTR| Pin3_7_INTR))

#endif /* End Pins Pin3_ALIASES_H */


/* [] END OF FILE */
