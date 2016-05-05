/*******************************************************************************
* File Name: PinNoise.h  
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

#if !defined(CY_PINS_PinNoise_H) /* Pins PinNoise_H */
#define CY_PINS_PinNoise_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "PinNoise_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 PinNoise__PORT == 15 && ((PinNoise__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    PinNoise_Write(uint8 value);
void    PinNoise_SetDriveMode(uint8 mode);
uint8   PinNoise_ReadDataReg(void);
uint8   PinNoise_Read(void);
void    PinNoise_SetInterruptMode(uint16 position, uint16 mode);
uint8   PinNoise_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the PinNoise_SetDriveMode() function.
     *  @{
     */
        #define PinNoise_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define PinNoise_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define PinNoise_DM_RES_UP          PIN_DM_RES_UP
        #define PinNoise_DM_RES_DWN         PIN_DM_RES_DWN
        #define PinNoise_DM_OD_LO           PIN_DM_OD_LO
        #define PinNoise_DM_OD_HI           PIN_DM_OD_HI
        #define PinNoise_DM_STRONG          PIN_DM_STRONG
        #define PinNoise_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define PinNoise_MASK               PinNoise__MASK
#define PinNoise_SHIFT              PinNoise__SHIFT
#define PinNoise_WIDTH              1u

/* Interrupt constants */
#if defined(PinNoise__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PinNoise_SetInterruptMode() function.
     *  @{
     */
        #define PinNoise_INTR_NONE      (uint16)(0x0000u)
        #define PinNoise_INTR_RISING    (uint16)(0x0001u)
        #define PinNoise_INTR_FALLING   (uint16)(0x0002u)
        #define PinNoise_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define PinNoise_INTR_MASK      (0x01u) 
#endif /* (PinNoise__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define PinNoise_PS                     (* (reg8 *) PinNoise__PS)
/* Data Register */
#define PinNoise_DR                     (* (reg8 *) PinNoise__DR)
/* Port Number */
#define PinNoise_PRT_NUM                (* (reg8 *) PinNoise__PRT) 
/* Connect to Analog Globals */                                                  
#define PinNoise_AG                     (* (reg8 *) PinNoise__AG)                       
/* Analog MUX bux enable */
#define PinNoise_AMUX                   (* (reg8 *) PinNoise__AMUX) 
/* Bidirectional Enable */                                                        
#define PinNoise_BIE                    (* (reg8 *) PinNoise__BIE)
/* Bit-mask for Aliased Register Access */
#define PinNoise_BIT_MASK               (* (reg8 *) PinNoise__BIT_MASK)
/* Bypass Enable */
#define PinNoise_BYP                    (* (reg8 *) PinNoise__BYP)
/* Port wide control signals */                                                   
#define PinNoise_CTL                    (* (reg8 *) PinNoise__CTL)
/* Drive Modes */
#define PinNoise_DM0                    (* (reg8 *) PinNoise__DM0) 
#define PinNoise_DM1                    (* (reg8 *) PinNoise__DM1)
#define PinNoise_DM2                    (* (reg8 *) PinNoise__DM2) 
/* Input Buffer Disable Override */
#define PinNoise_INP_DIS                (* (reg8 *) PinNoise__INP_DIS)
/* LCD Common or Segment Drive */
#define PinNoise_LCD_COM_SEG            (* (reg8 *) PinNoise__LCD_COM_SEG)
/* Enable Segment LCD */
#define PinNoise_LCD_EN                 (* (reg8 *) PinNoise__LCD_EN)
/* Slew Rate Control */
#define PinNoise_SLW                    (* (reg8 *) PinNoise__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define PinNoise_PRTDSI__CAPS_SEL       (* (reg8 *) PinNoise__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define PinNoise_PRTDSI__DBL_SYNC_IN    (* (reg8 *) PinNoise__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define PinNoise_PRTDSI__OE_SEL0        (* (reg8 *) PinNoise__PRTDSI__OE_SEL0) 
#define PinNoise_PRTDSI__OE_SEL1        (* (reg8 *) PinNoise__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define PinNoise_PRTDSI__OUT_SEL0       (* (reg8 *) PinNoise__PRTDSI__OUT_SEL0) 
#define PinNoise_PRTDSI__OUT_SEL1       (* (reg8 *) PinNoise__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define PinNoise_PRTDSI__SYNC_OUT       (* (reg8 *) PinNoise__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(PinNoise__SIO_CFG)
    #define PinNoise_SIO_HYST_EN        (* (reg8 *) PinNoise__SIO_HYST_EN)
    #define PinNoise_SIO_REG_HIFREQ     (* (reg8 *) PinNoise__SIO_REG_HIFREQ)
    #define PinNoise_SIO_CFG            (* (reg8 *) PinNoise__SIO_CFG)
    #define PinNoise_SIO_DIFF           (* (reg8 *) PinNoise__SIO_DIFF)
#endif /* (PinNoise__SIO_CFG) */

/* Interrupt Registers */
#if defined(PinNoise__INTSTAT)
    #define PinNoise_INTSTAT            (* (reg8 *) PinNoise__INTSTAT)
    #define PinNoise_SNAP               (* (reg8 *) PinNoise__SNAP)
    
	#define PinNoise_0_INTTYPE_REG 		(* (reg8 *) PinNoise__0__INTTYPE)
#endif /* (PinNoise__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_PinNoise_H */


/* [] END OF FILE */
