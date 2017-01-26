/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*
 * nordic.h
 *  Created on: Nov 1, 2016
 *  
 */

#ifndef INCLUDES_NORDIC_H_
#define INCLUDES_NORDIC_H_

#include<stdint.h>
#define __IO volatile

#define NRF_CS_ENABLE() (PTC_BASE_PTR->PCOR |= 1<<4)
#define NRF_CS_DISABLE() (PTC_BASE_PTR->PSOR |= 1<<4)

#define CE_HIGH() (PTC_BASE_PTR->PCOR |= 1<<8)
#define CE_LOW() (PTC_BASE_PTR->PSOR |= 1<<8)

#define WAIT_SPTEF ( !(SPI_S_REG(SPI0) & SPI_S_SPTEF_MASK))
#define WAIT_SPRF ( !(SPI_S_REG(SPI0) & SPI_S_SPRF_MASK))

// SPI Command Names
#define NORDIC_R_REGISTER     (0x00)		//Read command and status registers. AAAAA = 5 bit register map address. 1-5 data bytes, LSByte first
#define NORDIC_W_REGISTER     (0x20)		//Write command and status registers. AAAAA = 5 bit register map address. 1-5 data bytes,  LSByte first
#define NORDIC_R_RX_PAYLOAD   (0x61)		//Read RX payload. 1-32 data bytes, LSByte first
#define NORDIC_W_TX_PAYLOAD   (0xA0)		//Write TX payload. 1-32 data bytes, LSByte first
#define NORDIC_FLUSH_TX       (0xE1)		//Flush TX mode. 0 data bytes
#define NORDIC_FLUSH_RX       (0xE2)		//Flush RX mode. 0 data bytes
#define NORDIC_REUSE_TX_PL    (0xE3)		//Reuse last transmitted payload. 0 data bytes
#define NORDIC_NOP            (0xFF)		//No operation. 0 data bytes

/*
// Peripheral NORDIC base address
#define NORDIC_BASE                                (0x00u)
// Peripheral NORDIC base pointer
#define NORDIC                                     ((NORDIC_Type *)NORDIC_BASE)
#define NORDIC_BASE_PTR                            (NORDIC)
#define NORDIC_BASE_ADDRS							{ NORDIC_BASE }
#define NORDIC_BASE_PTRS                            { NORDIC }


// NORDIC - Register Layout Typedef
typedef struct {
  __IO uint8_t NORDIC_CONFIG;
  __IO uint8_t NORDIC_EN_AA;
  __IO uint8_t NORDIC_EN_RXADDR;
  __IO uint8_t NORDIC_SETUP_AW;
  __IO uint8_t NORDIC_SETUP_RETR;
  __IO uint8_t NORDIC_RF_CH;
  __IO uint8_t NORDIC_RF_SETUP;
  __IO uint8_t NORDIC_STATUS;
  __IO uint8_t NORDIC_OBSERVE_TX;
  __IO uint8_t NORDIC_CD;
  __IO uint8_t NORDIC_RX_ADDR_P0;
  __IO uint8_t NORDIC_RX_ADDR_P1;
  __IO uint8_t NORDIC_RX_ADDR_P2;
  __IO uint8_t NORDIC_RX_ADDR_P3;
  __IO uint8_t NORDIC_RX_ADDR_P4;
  __IO uint8_t NORDIC_RX_ADDR_P5;
  __IO uint8_t NORDIC_TX_ADDR;
  __IO uint8_t NORDIC_RX_PW_P0;
  __IO uint8_t NORDIC_RX_PW_P1;
  __IO uint8_t NORDIC_RX_PW_P2;
  __IO uint8_t NORDIC_RX_PW_P3;
  __IO uint8_t NORDIC_RX_PW_P4;
  __IO uint8_t NORDIC_RX_PW_P5;
  __IO uint8_t NORDIC_FIFO_STATUS;
  	  		uint8_t RESERVED_1[5];
  __IO uint8_t NORDIC_DYNPD;
  __IO uint8_t NORDIC_FEATURE;
} NORDIC_Type, *NORDIC_MemMapPtr;



// NORDIC - Register accessors
#define NORDIC_CONFIG_REG(base)         	((base)->NORDIC_CONFIG)
#define NORDIC_EN_AA_REG(base)				((base)->NORDIC_EN_AA)
#define NORDIC_EN_RXADDR_REG(base)			((base)->NORDIC_EN_RXADDR)
#define NORDIC_SETUP_AW_REG(base)			((base)->NORDIC_SETUP_AW)
#define NORDIC_SETUP_RETR_REG(base)			((base)->NORDIC_SETUP_RETR)
#define NORDIC_RF_CH_REG(base)				((base)->NORDIC_RF_CH)
#define NORDIC_RF_SETUP_REG(base)			((base)->NORDIC_RF_SETUP)
#define NORDIC_STATUS_REG(base)				((base)->NORDIC_STATUS)
#define NORDIC_OBSERVE_TX_REG(base)			((base)->NORDIC_OBSERVE_TX)
#define NORDIC_CD_REG(base)					((base)->NORDIC_CD)
#define NORDIC_RX_ADDR_P0_REG(base)			((base)->NORDIC_RX_ADDR_P0)
#define NORDIC_RX_ADDR_P1_REG(base)			((base)->NORDIC_RX_ADDR_P1)
#define NORDIC_RX_ADDR_P2_REG(base)			((base)->NORDIC_RX_ADDR_P2)
#define NORDIC_RX_ADDR_P3_REG(base)			((base)->NORDIC_RX_ADDR_P3)
#define NORDIC_RX_ADDR_P4_REG(base)			((base)->NORDIC_RX_ADDR_P4)
#define NORDIC_RX_ADDR_P5_REG(base)			((base)->NORDIC_RX_ADDR_P5)
#define NORDIC_TX_ADDR_REG(base)			((base)->NORDIC_TX_ADDR)
#define NORDIC_RX_PW_P0_REG(base)			((base)->NORDIC_RX_PW_P0)
#define NORDIC_RX_PW_P1_REG(base)			((base)->NORDIC_RX_PW_P1)
#define NORDIC_RX_PW_P2_REG(base)			((base)->NORDIC_RX_PW_P2)
#define NORDIC_RX_PW_P3_REG(base)			((base)->NORDIC_RX_PW_P3)
#define NORDIC_RX_PW_P4_REG(base)			((base)->NORDIC_RX_PW_P4)
#define NORDIC_RX_PW_P5_REG(base)			((base)->NORDIC_RX_PW_P5)
#define NORDIC_FIFO_STATUS_REG(base) 		((base)->NORDIC_FIFO_STATUS)
#define NORDIC_DYNPD_REG(base)				((base)->NORDIC_DYNPD)
#define NORDIC_FEATURE_REG(base)			((base)->NORDIC_FEATURE)

*/
// ----------------------------------------------------------------------------
//   -- NORDIC - Register accessor macros
//   ----------------------------------------------------------------------------


//CONFIG REGISTER
#define NORDIC_CONFIG_MASK_RX_DR(x)  	(((uint8_t)(x))<<6)
#define NORDIC_CONFIG_MASK_TX_DS(x)  	(((uint8_t)(x))<<5)
#define NORDIC_CONFIG_MASK_MAX_RT(x) 	(((uint8_t)(x))<<4)
#define NORDIC_CONFIG_EN_CRC(x) 		(((uint8_t)(x))<<3)
#define NORDIC_CONFIG_CRCO(x) 			(((uint8_t)(x))<<2)
#define NORDIC_CONFIG_PWR_UP(x)			(((uint8_t)(x))<<1)
#define NORDIC_CONFIG_PRIM_RX(x)		(((uint8_t)(x))<<0)
#define NORDIC_POWER_UP 				(0x01)
#define NORDIC_POWER_UP_MASK 			(0x02)
#define NORDIC_POWER_DOWN_MASK 			(0x00)

//EN_AA REGISTER
#define NORDIC_ENA_P5(x)				(((uint8_t)(x))<<5)
#define NORDIC_ENA_P4(x)				(((uint8_t)(x))<<4)
#define NORDIC_ENA_P3(x)				(((uint8_t)(x))<<3)
#define NORDIC_ENA_P2(x)				(((uint8_t)(x))<<2)
#define NORDIC_ENA_P1(x)				(((uint8_t)(x))<<1)
#define NORDIC_ENA_P0(x)				(((uint8_t)(x))<<0)

//EN_RXADDR REGISTER
#define NORDIC_ERX_P5(x)				(((uint8_t)(x))<<5)
#define NORDIC_ERX_P4(x)				(((uint8_t)(x))<<4)
#define NORDIC_ERX_P3(x)				(((uint8_t)(x))<<3)
#define NORDIC_ERX_P2(x)				(((uint8_t)(x))<<2)
#define NORDIC_ERX_P1(x)				(((uint8_t)(x))<<1)
#define NORDIC_ERX_P0(x)				(((uint8_t)(x))<<0)

//SETUP_AW REGISTER
#define NORDIC_AW(x)					(((uint8_t)(x))<<1)

//SETUP_RETR REGISTER
#define NORDIC_ARD(x)					(((uint8_t)(x))<<7)
#define NORDIC_ARC(x)					(((uint8_t)(x))<<3)

//RF_CH REGISTER
#define NORDIC_RF_CH_MASK(x)			(((uint8_t)(x))<<6)

//RF_SETUP REGISTER
#define NORDIC_PLL_LOCK(x)				(((uint8_t)(x))<<4)
#define NORDIC_RF_DR(x)					(((uint8_t)(x))<<3)
#define NORDIC_RF_PWR(x)				((uint8_t)(x))
#define NORDIC_LNA_HCURR(x)				(((uint8_t)(x))<<0)
#define NORDIC_RF_PWR_MASK_MAX			(0x03)
#define NORDIC_RF_PWR_MASK_MIN			(0X00)

//STATUS REGISTER
#define NORDIC_RX_DR(x)					(((uint8_t)(x))<<6)
#define NORDIC_TX_DS(x)					(((uint8_t)(x))<<5)
#define NORDIC_MAX_RT(x)				(((uint8_t)(x))<<4)
#define NORDIC_RX_P_NO(x)				(((uint8_t)(x))<<3)
#define NORDIC_TX_FULL(x)				(((uint8_t)(x))<<0)

//OBSERVE_TX REGISTER
#define NORDIC_PLOS_CNT(x)				(((uint8_t)(x))<<7)
#define NORDIC_ARC_CNT(x)				(((uint8_t)(x))<<3)

//CD REGISTER
#define NORDIC_CD_MASK(x)				(((uint8_t)(x))<<0)

//RX_PW_P0 REGISTER
#define NORDIC_RX_PW_P0_MASK(x)			(((uint8_t)(x))<<5)

//RX_PW_P1 REGISTER
#define NORDIC_RX_PW_P1_MASK(x)			(((uint8_t)(x))<<5)

//RX_PW_P2 REGISTER
#define NORDIC_RX_PW_P2_MASK(x)			(((uint8_t)(x))<<5)

//RX_PW_P3 REGISTER
#define NORDIC_RX_PW_P3_MASK(x)			(((uint8_t)(x))<<5)

//RX_PW_P4 REGISTER
#define NORDIC_RX_PW_P4_MASK(x)			(((uint8_t)(x))<<5)

//RX_PW_P5 REGISTER
#define NORDIC_RX_PW_P5_MASK(x)			(((uint8_t)(x))<<5)


//DYNPD REGISTER
#define NORDIC_DPL_P5(x)				(((uint8_t)(x))<<5)
#define NORDIC_DPL_P4(x)				(((uint8_t)(x))<<4)
#define NORDIC_DPL_P3(x)				(((uint8_t)(x))<<3)
#define NORDIC_DPL_P2(x)				(((uint8_t)(x))<<2)
#define NORDIC_DPL_P1(x)				(((uint8_t)(x))<<1)
#define NORDIC_DPL_P0(x)				(((uint8_t)(x))<<0)

//FEATURE REGISTER
#define NORDIC_EN_DPL(x)				(((uint8_t)(x))<<2)
#define NORDIC_EN_ACK_PAY(x)			(((uint8_t)(x))<<1)
#define NORDIC_EN_DYN_ACK(x)			(((uint8_t)(x))<<0)


//REGISTER MAP
#define NORDIC_CONFIG_BASE		(0x00)
#define NORDIC_EN_AA_BASE		(0X01)
#define NORDIC_EN_RXADDR_BASE	(0X02)
#define NORDIC_SETUP_AW_BASE	(0x03)
#define NORDIC_SETUP_RETR_BASE	(0x04)
#define NORDIC_RF_CH_BASE		(0x05)
#define NORDIC_RF_SETUP_BASE	(0x06)
#define NORDIC_STATUS_BASE		(0x07)
#define NORDIC_OBSERVE_TX_BASE	(0x08)
#define NORDIC_CD_BASE			(0x09)
#define NORDIC_RX_ADDR_P0_BASE	(0x0A)
#define NORDIC_RX_ADDR_P1_BASE	(0x0B)
#define NORDIC_RX_ADDR_P2_BASE	(0x0C)
#define NORDIC_RX_ADDR_P3_BASE	(0x0D)
#define NORDIC_RX_ADDR_P4_BASE	(0x0E)
#define NORDIC_RX_ADDR_P5_BASE	(0x0F)
#define NORDIC_TX_ADDR_BASE		(0x10)
#define NORDIC_RX_PW_P0_BASE	(0x11)
#define NORDIC_RX_PW_P1_BASE	(0x12)
#define NORDIC_RX_PW_P2_BASE	(0x13)
#define NORDIC_RX_PW_P3_BASE	(0x14)
#define NORDIC_RX_PW_P4_BASE	(0x15)
#define NORDIC_RX_PW_P5_BASE	(0x16)
#define NORDIC_FIFO_STATUS_BASE (0x17)
#define NORDIC_DYNPD_BASE		(0x1C)
#define NORDIC_FEATURE_BASE		(0x1D)

/*
// NORDIC - Register instance definitions
#define NORDIC_CONFIG                   NORDIC_CONFIG_REG(NORDIC_BASE_PTR)
#define NORDIC_EN_AA					NORDIC_EN_AA_REG(NORDIC_BASE_PTR)
#define NORDIC_EN_RXADDR				NORDIC_EN_RXADDR_REG(NORDIC_BASE_PTR)
#define NORDIC_SETUP_AW					NORDIC_SETUP_AW_REG(NORDIC_BASE_PTR)
#define NORDIC_SETUP_RETR				NORDIC_SETUP_RETR_REG(NORDIC_BASE_PTR)
#define NORDIC_RF_CH					NORDIC_RF_CH_REG(NORDIC_BASE_PTR)
#define NORDIC_RF_SETUP					NORDIC_RF_SETUP_REG(NORDIC_BASE_PTR)
#define NORDIC_STATUS					NORDIC_STATUS_REG(NORDIC_BASE_PTR)
#define NORDIC_OBSERVE					NORDIC_OBSERVE_REG(NORDIC_BASE_PTR)
#define NORDIC_CD					 	NORDIC_CD_REG(NORDIC_BASE_PTR)
#define NORDIC_RX_ADDR_P0				NORDIC_RX_ADDR_P0_REG(NORDIC_BASE_PTR)
#define NORDIC_RX_ADDR_P1				NORDIC_RX_ADDR_P1_REG(NORDIC_BASE_PTR)
#define NORDIC_RX_ADDR_P2				NORDIC_RX_ADDR_P2_REG(NORDIC_BASE_PTR)
#define NORDIC_RX_ADDR_P3				NORDIC_RX_ADDR_P3_REG(NORDIC_BASE_PTR)
#define NORDIC_RX_ADDR_P4				NORDIC_RX_ADDR_P4_REG(NORDIC_BASE_PTR)
#define NORDIC_RX_ADDR_P5				NORDIC_RX_ADDR_P5_REG(NORDIC_BASE_PTR)
#define NORDIC_TX_ADDR					NORDIC_TX_ADDR_REG(NORDIC_BASE_PTR)
#define NORDIC_RX_PW_P0					NORDIC_RX_PW_P0_REG(NORDIC_BASE_PTR)
#define NORDIC_RX_PW_P1					NORDIC_RX_PW_P1_REG(NORDIC_BASE_PTR)
#define NORDIC_RX_PW_P2					NORDIC_RX_PW_P2_REG(NORDIC_BASE_PTR)
#define NORDIC_RX_PW_P3					NORDIC_RX_PW_P3_REG(NORDIC_BASE_PTR)
#define NORDIC_RX_PW_P4 				NORDIC_RX_PW_P4_REG(NORDIC_BASE_PTR)
#define NORDIC_RX_PW_P5					NORDIC_RX_PW_P5_REG(NORDIC_BASE_PTR)
#define NORDIC_FIFO_STATUS 				NORDIC_FIFO_STATUS_REG(NORDIC_BASE_PTR)
#define NORDIC_DYNPD					NORDIC_DYNPD_REG(NORDIC_BASE_PTR)
#define NORDIC_FEATURE					NORDIC_FEATURE_REG(NORDIC_BASE_PTR)


#define NORDIC_CONFIG_REG (0x00)
#define NORDIC_TXADDR_REG (0x10)
#define NORDIC_POWER_UP (0x01)
#define NORDIC_POWER_UP_MASK (0x02)
#define NORDIC_POWER_DOWN_MASK (0x00)
#define NORDIC_EN_AA_REG (0x01)
#define NORDIC_EN_RXADDR_REG (0x02)
#define NORDIC_SETUP_AW_REG (0x03)
#define NORDIC_SETUP_RETR_REG (0x04)
#define NORDIC_RF_CH_REG (0x05)
#define NORDIC_RF_SETUP_REG (0x06)
#define NORDIC_STATUS_REG (0x07)
#define RX_ADDR_P0_REG (0x0A)
#define TX_ADDR (0x10)
#define FIFO_STATUS_REG (0x17)
#define NRF_PIPESIZE (0X11)
#define NRF_ENRXADDR (0x02)
#define W_TXPAYLOAD (0xA0)
#define R_RXPAYLOAD (0x61)
*/

//FUNCTION DECLARATIONS
uint8_t nrf_status_read();
uint8_t nrf_read_register(uint8_t reg);
void nrf_write_register(uint8_t reg, uint8_t value);
void nrf_write_multiple(uint8_t register1, uint8_t *loc, uint8_t size);
void nrf_RF_Setup(void);

#endif /* INCLUDES_NORDIC_H_ */
