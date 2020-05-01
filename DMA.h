/*
 * DMA.h
 *
 *  Created on: May 1, 2020
 *      Author: sergio_mndz
 */

#ifndef DIAZ_DE_SANDI_MENDEZ_T14_DMA_H_
#define DIAZ_DE_SANDI_MENDEZ_T14_DMA_H_

#define SYSTEM_CLOCK (21000000u)

void DMA0_IRQHandler(void);

void DMA_clock_gating(void);

void DMA_init(void);

#endif /* DIAZ_DE_SANDI_MENDEZ_T14_DMA_H_ */
