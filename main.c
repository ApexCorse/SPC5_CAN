/****************************************************************************
*
* Copyright © 2015-2021 STMicroelectronics - All Rights Reserved
*
* This software is licensed under SLA0098 terms that can be found in the
* DM00779817_1_0.pdf file in the licenses directory of this software product.
* 
* THIS SOFTWARE IS DISTRIBUTED "AS IS," AND ALL WARRANTIES ARE DISCLAIMED, 
* INCLUDING MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*
*****************************************************************************/

/* Inclusion of the main header files of all the imported components in the
   order specified in the application wizard. The file is generated
   automatically.*/
#include "components.h"
#include "can_lld_cfg.h"
#include "vera/vera.h"
#include "vera/vera_autodevkit.h"

void mcanconf_receive_callback(uint32_t msgbuf, CANRxFrame crfp)  {
	vera_decoded_signal_t signals[8];
	vera_decoding_result_t res = {
			.decoded_signals = &signals
	};
	vera_err_t err = vera_decode_autodevkit_rx_frame(&crfp, &res);
}

/*
 * Application entry point.
 */
int main(void) {

  /* Initialization of all the imported components in the order specified in
     the application wizard. The function is generated automatically.*/
  componentsInit();

  /* Uncomment the below routine to Enable Interrupts. */
  irqIsrEnable();

  can_lld_init();
  can_lld_start(&CAND1, &can_config_mcanconf);
  can_lld_start(&CAND3, &can_config_mcanconf1);

  CANTxFrame tx;
  uint64_t counter = 1ULL;

  
  /* Application main loop.*/
  for ( ; ; ) {
	  vera_err_t err = vera_encode_autodevkit_EMDL_Status(&tx, counter++, 0ULL, 0ULL, 0ULL, 0ULL);
	  if (err != vera_err_ok) break;

	  uint32_t result = can_lld_transmit(&CAND3, CAN_ANY_TXBUFFER, &tx);
	  osalThreadDelayMilliseconds(100);
	  if (result != CAN_MSG_OK) break;
  }

  can_lld_stop(&CAND1);
  can_lld_stop(&CAND3);
}
