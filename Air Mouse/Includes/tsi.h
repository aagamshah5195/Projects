/***************************************************************************
* Copyrights 2016 Akshit Shah and Aagam Shah All Rights Reserved
* The information contained herein is property of the Authors.
* The copying and distribution of the files is prohibited except by express written agreement with the Authors.

* Authors: Akshit Shah and Aagam Shah
*
* **************************************************************************/

/*
 * tsi.h
 *
 *  Created on: Nov 30, 2016
 *  
 */

#ifndef INCLUDES_TSI_H_
#define INCLUDES_TSI_H_

#define NO_TOUCH                 0
#define SLIDER_LENGTH           40 //LENGTH in mm
#define TOTAL_ELECTRODE          2

#define TSI0a        0
#define TSI1         1
#define TSI2         2
#define TSI3         3
#define TSI4         4
#define TSI5         5
#define TSI6         6
#define TSI7         7
#define TSI8         8
#define TSI9         9
#define TSI10        10
#define TSI11        11
#define TSI12        12
#define TSI13        13
#define TSI14        14
#define TSI15        15

/*Chose the correct TSI channel for the electrode number*/
#define ELECTRODE0   TSI9
#define ELECTRODE1   TSI10
#define ELECTRODE2   TSI0a
#define ELECTRODE3   TSI1
#define ELECTRODE4   TSI2
#define ELECTRODE5   TSI3
#define ELECTRODE6   TSI4
#define ELECTRODE7   TSI5
#define ELECTRODE8   TSI6
#define ELECTRODE9   TSI7
#define ELECTRODE10  TSI8
#define ELECTRODE11  TSI11
#define ELECTRODE12  TSI12
#define ELECTRODE13  TSI13
#define ELECTRODE14  TSI14
#define ELECTRODE15  TSI15

#define THRESHOLD0   100
#define THRESHOLD1   100
#define THRESHOLD2   100
#define THRESHOLD3   100
#define THRESHOLD4   100
#define THRESHOLD5   100
#define THRESHOLD6   100
#define THRESHOLD7   100
#define THRESHOLD8   100
#define THRESHOLD9   100
#define THRESHOLD10   100
#define THRESHOLD11   100
#define THRESHOLD12   100
#define THRESHOLD13   100
#define THRESHOLD14   100
#define THRESHOLD15   100

static uint8_t total_electrode = TOTAL_ELECTRODE;
static uint8_t elec_array[16]={ELECTRODE0,ELECTRODE1,ELECTRODE2,ELECTRODE3,ELECTRODE4,ELECTRODE5,
                               ELECTRODE6,ELECTRODE7,ELECTRODE8,ELECTRODE9,ELECTRODE10,ELECTRODE11,
                               ELECTRODE12,ELECTRODE13,ELECTRODE14,ELECTRODE15};
static uint16_t gu16TSICount[16];
static uint16_t gu16Baseline[16];
static uint16_t gu16Threshold[16]={THRESHOLD0,THRESHOLD1,THRESHOLD2,THRESHOLD3,THRESHOLD4,THRESHOLD5,
                                   THRESHOLD6,THRESHOLD7,THRESHOLD8,THRESHOLD9,THRESHOLD10,THRESHOLD11,
                                   THRESHOLD12,THRESHOLD13,THRESHOLD14,THRESHOLD15};
static uint16_t gu16Delta[16];
static uint8_t ongoing_elec;
static uint8_t end_flag = 1;

static uint8_t SliderPercentegePosition[2] = {NO_TOUCH,NO_TOUCH};
static uint8_t SliderDistancePosition[2] = {NO_TOUCH,NO_TOUCH};
static uint32_t AbsolutePercentegePosition = NO_TOUCH;
static uint32_t AbsoluteDistancePosition = NO_TOUCH;

void TSISensor();
static void tsi_irq();
void selfCalibration(void);
void sliderRead(void);
float readPercentage(void);
uint8_t readDistance(void);
static void changeElectrode(void);




#endif /* INCLUDES_TSI_H_ */
