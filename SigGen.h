/*
 * SigGen.h
 *
 *  Created on: May 1, 2020
 *      Author: sergio_mndz
 */

#ifndef DIAZ_DE_SANDI_MENDEZ_T14_SIGGEN_H_
#define DIAZ_DE_SANDI_MENDEZ_T14_SIGGEN_H_

#include <stdint.h>
#include "bits.h"

/** Complete waveform size */
#define MAX 100
/** Sampling time for 5Hz signals */
#define Delay_2ms  0.0004

void DAC0_clock_gating( );

void DAC0_config( );

/** Generating 5 Hz signals */
void Wait_2ms();

void DAC_FSM_signals(void);

void DAC_plot(uint16_t element);

#endif /* DIAZ_DE_SANDI_MENDEZ_T14_SIGGEN_H_ */
