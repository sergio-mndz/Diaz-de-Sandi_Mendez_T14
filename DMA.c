/*
 * DMA.c
 *
 *  Created on: May 1, 2020
 *      Author: sergio_mndz
 */

#include "DMA.h"
#include "MK64F12.h"
#include <stdio.h>

#define NUM_STEPS (1u)
#define ARRAY_SIZE (16u)
#define DMA_CH0 (0x01u)
#define DMA_SOURCE_MUX (63u)

/** defines destination data space */
uint16_t g_data_desti[4*ARRAY_SIZE];

extern const uint16_t DAC_SquareWaveForm[100];
extern const uint16_t DAC_SineWaveForm[100];
extern const uint16_t DAC_TriangleForm[100];

void DMA_clock_gating(void)
{
	SIM->SCGC7 |= SIM_SCGC7_DMA_MASK;
	SIM->SCGC6 |= SIM_SCGC6_DMAMUX_MASK;
}

void DMA_init(void)
{

	DMAMUX->CHCFG[0] = 0;
						/*Enables DMA MUX channel*/
	DMAMUX->CHCFG[0] = DMAMUX_CHCFG_ENBL_MASK |
					   DMAMUX_CHCFG_TRIG_MASK |
					   DMAMUX_CHCFG_SOURCE(DMA_SOURCE_MUX);
						/*Source is FTM0 channel 0*/

	/** Enables DMA0 request */
	DMA0->ERQ = 0x01;

	/*Defines the addres of data source*/
	DMA0->TCD[0].SADDR = (uint32_t)(&DAC_SquareWaveForm[0]);
	/*Source address signed offset, in number of bytes*/
	DMA0->TCD[0].SOFF = 1;
	/*Defines address of destination data*/
	DMA0->TCD[0].DADDR = (uint32_t)(&g_data_desti[0]);
	/*Destination address signed offset, in number of bytes*/
	DMA0->TCD[0].DOFF = 1;
	/*CITER represents the number of minor loops that compose a major loop,
	 * every time a minor loop is completed CITTER is decremented by one.
	 * Once CITTER is 0 the DMA copy BITTER into CITTER and adjust SADDR and
	 * DADDR with the values specified in SLAST and DLAST_SGA respectively
	 *  SADDR  = SADDR + SLAST and DADDR + DLAST_SGA*/
	DMA0->TCD[0].CITER_ELINKNO = DMA_CITER_ELINKNO_CITER(NUM_STEPS);
	/* Once a major loop is completed, BITTER is copy to CITTER*/
	DMA0->TCD[0].BITER_ELINKNO = DMA_BITER_ELINKNO_BITER(NUM_STEPS);
	/*Byte Number*/
	DMA0->TCD[0].NBYTES_MLNO = 2;

	/*Size of transfer is 8 bit, from user manual*/
	DMA0->TCD[0].ATTR = 0x101;
	/** Restoring the source address to the initial value in the amount of
	 * bytes to restore*/
	DMA0->TCD[0].SLAST = 0;
	/*restores the destination address to the initial value, which is
	 * expressed in the amount of bytes to restore*/
	DMA0->TCD[0].DLAST_SGA = 0;
	/*The end of major loop interruption is enabled*/
	DMA0->TCD[0].CSR = DMA_CSR_INTMAJOR_MASK;
}
