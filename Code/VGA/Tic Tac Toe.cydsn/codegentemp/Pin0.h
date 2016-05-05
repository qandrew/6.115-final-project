/*******************************************************************************
* File Name: Pin0.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Pin0_H) /* Pins Pin0_H */
#define CY_PINS_Pin0_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "Pin0_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 Pin0__PORT == 15 && ((Pin0__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    Pin0_Write(uint8 value);
void    Pin0_SetDriveMode(uint8 mode);
uint8   Pin0_ReadDataReg(void);
uint8   Pin0_Read(void);
void    Pin0_SetInterruptMode(uint16 position, uint16 mode);
uint8   Pin0_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the Pin0_SetDriveMode() function.
     *  @{
     */
        #define Pin0_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define Pin0_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define Pin0_DM_RES_UP          PIN_DM_RES_UP
        #define Pin0_DM_RES_DWN         PIN_DM_RES_DWN
        #define Pin0_DM_OD_LO           PIN_DM_OD_LO
        #define Pin0_DM_OD_HI           PIN_DM_OD_HI
        #define Pin0_DM_STRONG          PIN_DM_STRONG
        #define Pin0_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define Pin0_MASK               Pin0__MASK
#define Pin0_SHIFT              Pin0__SHIFT
#define Pin0_WIDTH              2u

/* Interrupt constants */
#if defined(Pin0__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Pin0_SetInterruptMode() function.
     *  @{
     */
        #define Pin0_INTR_NONE      (uint16)(0x0000u)
        #define Pin0_INTR_RISING    (uint16)(0x0001u)
        #define Pin0_INTR_FALLING   (uint16)(0x0002u)
        #define Pin0_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define Pin0_INTR_MASK      (0x01u) 
#endif /* (Pin0__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Pin0_PS                     (* (reg8 *) Pin0__PS)
/* Data Register */
#define Pin0_DR                     (* (reg8 *) Pin0__DR)
/* Port Number */
#define Pin0_PRT_NUM                (* (reg8 *) Pin0__PRT) 
/* Connect to Analog Globals */                                                  
#define Pin0_AG                     (* (reg8 *) Pin0__AG)                       
/* Analog MUX bux enable */
#define Pin0_AMUX                   (* (reg8 *) Pin0__AMUX) 
/* Bidirectional Enable */                                                        
#define Pin0_BIE                    (* (reg8 *) Pin0__BIE)
/* Bit-mask for Aliased Register Access */
#define Pin0_BIT_MASK               (* (reg8 *) Pin0__BIT_MASK)
/* Bypass Enable */
#define Pin0_BYP                    (* (reg8 *) Pin0__BYP)
/* Port wide control signals */                                                   
#define Pin0_CTL                    (* (reg8 *) Pin0__CTL)
/* Drive Modes */
#define Pin0_DM0                    (* (reg8 *) Pin0__DM0) 
#define Pin0_DM1                    (* (reg8 *) Pin0__DM1)
#define Pin0_DM2                    (* (reg8 *) Pin0__DM2) 
/* Input Buffer Disable Override */
#define Pin0_INP_DIS                (* (reg8 *) Pin0__INP_DIS)
/* LCD Common or Segment Drive */
#define Pin0_LCD_COM_SEG            (* (reg8 *) Pin0__LCD_COM_SEG)
/* Enable Segment LCD */
#define Pin0_LCD_EN                 (* (reg8 *) Pin0__LCD_EN)
/* Slew Rate Control */
#define Pin0_SLW                    (* (reg8 *) Pin0__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define Pin0_PRTDSI__CAPS_SEL       (* (reg8 *) Pin0__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define Pin0_PRTDSI__DBL_SYNC_IN    (* (reg8 *) Pin0__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define Pin0_PRTDSI__OE_SEL0        (* (reg8 *) Pin0__PRTDSI__OE_SEL0) 
#define Pin0_PRTDSI__OE_SEL1        (* (reg8 *) Pin0__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define Pin0_PRTDSI__OUT_SEL0       (* (reg8 *) Pin0__PRTDSI__OUT_SEL0) 
#define Pin0_PRTDSI__OUT_SEL1       (* (reg8 *) Pin0__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define Pin0_PRTDSI__SYNC_OUT       (* (reg8 *) Pin0__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(Pin0__SIO_CFG)
    #define Pin0_SIO_HYST_EN        (* (reg8 *) Pin0__SIO_HYST_EN)
    #define Pin0_SIO_REG_HIFREQ     (* (reg8 *) Pin0__SIO_REG_HIFREQ)
    #define Pin0_SIO_CFG            (* (reg8 *) Pin0__SIO_CFG)
    #define Pin0_SIO_DIFF           (* (reg8 *) Pin0__SIO_DIFF)
#endif /* (Pin0__SIO_CFG) */

/* Interrupt Registers */
#if defined(Pin0__INTSTAT)
    #define Pin0_INTSTAT            (* (reg8 *) Pin0__INTSTAT)
    #define Pin0_SNAP               (* (reg8 *) Pin0__SNAP)
    
	#define Pin0_0_INTTYPE_REG 		(* (reg8 *) Pin0__0__INTTYPE)
	#define Pin0_1_INTTYPE_REG 		(* (reg8 *) Pin0__1__INTTYPE)
#endif /* (Pin0__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_Pin0_H */


/* [] END OF FILE */
