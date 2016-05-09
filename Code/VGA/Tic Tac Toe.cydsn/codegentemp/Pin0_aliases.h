/*******************************************************************************
* File Name: Pin0.h  
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

#if !defined(CY_PINS_Pin0_ALIASES_H) /* Pins Pin0_ALIASES_H */
#define CY_PINS_Pin0_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*              Constants        
***************************************/
#define Pin0_0			(Pin0__0__PC)
#define Pin0_0_INTR	((uint16)((uint16)0x0001u << Pin0__0__SHIFT))

#define Pin0_1			(Pin0__1__PC)
#define Pin0_1_INTR	((uint16)((uint16)0x0001u << Pin0__1__SHIFT))

#define Pin0_2			(Pin0__2__PC)
#define Pin0_2_INTR	((uint16)((uint16)0x0001u << Pin0__2__SHIFT))

#define Pin0_3			(Pin0__3__PC)
#define Pin0_3_INTR	((uint16)((uint16)0x0001u << Pin0__3__SHIFT))

#define Pin0_4			(Pin0__4__PC)
#define Pin0_4_INTR	((uint16)((uint16)0x0001u << Pin0__4__SHIFT))

#define Pin0_5			(Pin0__5__PC)
#define Pin0_5_INTR	((uint16)((uint16)0x0001u << Pin0__5__SHIFT))

#define Pin0_INTR_ALL	 ((uint16)(Pin0_0_INTR| Pin0_1_INTR| Pin0_2_INTR| Pin0_3_INTR| Pin0_4_INTR| Pin0_5_INTR))

#endif /* End Pins Pin0_ALIASES_H */


/* [] END OF FILE */
