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

void mcanconf_receive_callback(uint32_t msgbuf, CANRxFrame crfp)  {

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

  CANTxFrame tx;
  tx.OPERATION = CAN_OP_NORMAL;
  tx.TYPE = CAN_ID_STD;
  tx.ID = 0x0001;
  tx.DLC = 8U;
  tx.data32[0] = 0x0032;
  uint32_t counter = 0;
  
  /* Application main loop.*/
  for ( ; ; ) {
	  tx.data32[1] = ++counter;
	  uint32_t result = can_lld_transmit(&CAND1, CAN_ANY_TXBUFFER, &tx);
	  osalThreadDelayMilliseconds(100);
	  if (result != CAN_MSG_OK) break;
	  if (counter > 10) break;
  }

  can_lld_stop(&CAND1);
}
