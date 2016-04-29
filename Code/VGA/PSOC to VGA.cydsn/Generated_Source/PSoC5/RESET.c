/*******************************************************************************
* File Name: RESET.c  
* Version 1.70
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2010, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#include "cytypes.h"
#include "RESET.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RESET__PORT == 15 && (RESET__MASK & 0xC0))

/*******************************************************************************
* Function Name: RESET_Write
********************************************************************************
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  void 
*  
*******************************************************************************/
void RESET_Write(uint8 value) 
{
    uint8 staticBits = RESET_DR & ~RESET_MASK;
    RESET_DR = staticBits | ((value << RESET_SHIFT) & RESET_MASK);
}


/*******************************************************************************
* Function Name: RESET_SetDriveMode
********************************************************************************
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to this drive mode.
*
* Return: 
*  void
*
*******************************************************************************/
void RESET_SetDriveMode(uint8 mode) 
{
	CyPins_SetPinDriveMode(RESET_0, mode);
}


/*******************************************************************************
* Function Name: RESET_Read
********************************************************************************
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro RESET_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 RESET_Read(void) 
{
    return (RESET_PS & RESET_MASK) >> RESET_SHIFT;
}


/*******************************************************************************
* Function Name: RESET_ReadDataReg
********************************************************************************
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  void 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 RESET_ReadDataReg(void) 
{
    return (RESET_DR & RESET_MASK) >> RESET_SHIFT;
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(RESET_INTSTAT) 

    /*******************************************************************************
    * Function Name: RESET_ClearInterrupt
    ********************************************************************************
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  void 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 RESET_ClearInterrupt(void) 
    {
        return (RESET_INTSTAT & RESET_MASK) >> RESET_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 

#endif
/* [] END OF FILE */ 
