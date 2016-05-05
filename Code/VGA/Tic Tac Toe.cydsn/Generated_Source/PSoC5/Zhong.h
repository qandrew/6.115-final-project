/*******************************************************************************
* File Name: Zhong.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Zhong_H)
#define CY_CLOCK_Zhong_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
* Conditional Compilation Parameters
***************************************/

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component cy_clock_v2_20 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */


/***************************************
*        Function Prototypes
***************************************/

void Zhong_Start(void) ;
void Zhong_Stop(void) ;

#if(CY_PSOC3 || CY_PSOC5LP)
void Zhong_StopBlock(void) ;
#endif /* (CY_PSOC3 || CY_PSOC5LP) */

void Zhong_StandbyPower(uint8 state) ;
void Zhong_SetDividerRegister(uint16 clkDivider, uint8 restart) 
                                ;
uint16 Zhong_GetDividerRegister(void) ;
void Zhong_SetModeRegister(uint8 modeBitMask) ;
void Zhong_ClearModeRegister(uint8 modeBitMask) ;
uint8 Zhong_GetModeRegister(void) ;
void Zhong_SetSourceRegister(uint8 clkSource) ;
uint8 Zhong_GetSourceRegister(void) ;
#if defined(Zhong__CFG3)
void Zhong_SetPhaseRegister(uint8 clkPhase) ;
uint8 Zhong_GetPhaseRegister(void) ;
#endif /* defined(Zhong__CFG3) */

#define Zhong_Enable()                       Zhong_Start()
#define Zhong_Disable()                      Zhong_Stop()
#define Zhong_SetDivider(clkDivider)         Zhong_SetDividerRegister(clkDivider, 1u)
#define Zhong_SetDividerValue(clkDivider)    Zhong_SetDividerRegister((clkDivider) - 1u, 1u)
#define Zhong_SetMode(clkMode)               Zhong_SetModeRegister(clkMode)
#define Zhong_SetSource(clkSource)           Zhong_SetSourceRegister(clkSource)
#if defined(Zhong__CFG3)
#define Zhong_SetPhase(clkPhase)             Zhong_SetPhaseRegister(clkPhase)
#define Zhong_SetPhaseValue(clkPhase)        Zhong_SetPhaseRegister((clkPhase) + 1u)
#endif /* defined(Zhong__CFG3) */


/***************************************
*             Registers
***************************************/

/* Register to enable or disable the clock */
#define Zhong_CLKEN              (* (reg8 *) Zhong__PM_ACT_CFG)
#define Zhong_CLKEN_PTR          ((reg8 *) Zhong__PM_ACT_CFG)

/* Register to enable or disable the clock */
#define Zhong_CLKSTBY            (* (reg8 *) Zhong__PM_STBY_CFG)
#define Zhong_CLKSTBY_PTR        ((reg8 *) Zhong__PM_STBY_CFG)

/* Clock LSB divider configuration register. */
#define Zhong_DIV_LSB            (* (reg8 *) Zhong__CFG0)
#define Zhong_DIV_LSB_PTR        ((reg8 *) Zhong__CFG0)
#define Zhong_DIV_PTR            ((reg16 *) Zhong__CFG0)

/* Clock MSB divider configuration register. */
#define Zhong_DIV_MSB            (* (reg8 *) Zhong__CFG1)
#define Zhong_DIV_MSB_PTR        ((reg8 *) Zhong__CFG1)

/* Mode and source configuration register */
#define Zhong_MOD_SRC            (* (reg8 *) Zhong__CFG2)
#define Zhong_MOD_SRC_PTR        ((reg8 *) Zhong__CFG2)

#if defined(Zhong__CFG3)
/* Analog clock phase configuration register */
#define Zhong_PHASE              (* (reg8 *) Zhong__CFG3)
#define Zhong_PHASE_PTR          ((reg8 *) Zhong__CFG3)
#endif /* defined(Zhong__CFG3) */


/**************************************
*       Register Constants
**************************************/

/* Power manager register masks */
#define Zhong_CLKEN_MASK         Zhong__PM_ACT_MSK
#define Zhong_CLKSTBY_MASK       Zhong__PM_STBY_MSK

/* CFG2 field masks */
#define Zhong_SRC_SEL_MSK        Zhong__CFG2_SRC_SEL_MASK
#define Zhong_MODE_MASK          (~(Zhong_SRC_SEL_MSK))

#if defined(Zhong__CFG3)
/* CFG3 phase mask */
#define Zhong_PHASE_MASK         Zhong__CFG3_PHASE_DLY_MASK
#endif /* defined(Zhong__CFG3) */

#endif /* CY_CLOCK_Zhong_H */


/* [] END OF FILE */
