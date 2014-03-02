/*
 * main.c
 *
 *  Created on: Jan 24, 2013
 *      Author: Victor Zhang
 */

#include <stdio.h>
#include <stdbool.h>
#include "xparameters.h"    /* generated system parameters                  */
#include "xbasic_types.h"   /* Xilinx basic types for device drivers        */
#include "xutil.h"

#define printf xil_printf   /* a smaller footprint printf */
#define NUM_TEST_WORDS 8
#define TEST_VECTOR 0x12345678 /* random word */


int main() {

	volatile int *ddr_addr = (volatile int *)  XPAR_MCB_DDR2_S0_AXI_BASEADDR;
	volatile int *ddr_addr2 = (volatile int *) 0xA0500000;

//	volatile int *vmod_addr = (volatile int *) XPAR_VMODCAM_0_BASEADDR;
	volatile int *hdmi_addr = (volatile int *) XPAR_HDMI_OUT_0_BASEADDR;

//	vmod_addr[4] = XPAR_MCB_DDR2_S0_AXI_BASEADDR;
//	vmod_addr[5] = XPAR_MCB_DDR2_S0_AXI_BASEADDR+1600*1200*4;
//	vmod_addr[6] = 1;

	//ddr_addr[0] = 0xDEADBEEF;
	//ddr_addr[1] = 0xFEEBDAED;
	int i, j;
//	for(j = 0; j<640*480 ; j++){
//
//		ddr_addr[j] = i;
//	}

//		for (j = 0; j < 720; j++) {
//			for (i = 0; i < 1280; i++) {
//				ddr_addr2[j * 1280 + i] = (j / 8 % 32) << 11 /* red */ | (i * 25 / 2048 % 64) << 5 /* green */ | (i / 8 % 32) /* blue */;
//			}
//		}

	// set stride
		//hdmi_addr[0] = 1280; // hdmi_addr[0] corresponds to slv_reg2
		// set frame base address
		//hdmi_addr[1] = (int)ddr_addr; // hdmi_addr[1] corresponds to slv_reg1
		// go
		//hdmi_addr[2] = 1;

//	printf(
//			"32-bit test: %s\n\r",
//			(XST_SUCCESS == XUtil_MemoryTest32((u32 *)ddr_addr, NUM_TEST_WORDS,
//					TEST_VECTOR, XUT_ALLMEMTESTS)) ? "passed" : "failed");
//	printf(
//				"32-bit test: %d\n\r",
//				(XST_SUCCESS == XUtil_MemoryTest32((u32 *)ddr_addr, NUM_TEST_WORDS,
//						TEST_VECTOR, XUT_ALLMEMTESTS)));

//	printf("HELLO\n\r");
//
//	printf("vmod - slvreg0: %d, slvreg1: %d slvreg2: %d\n\r", vmod_addr[4], vmod_addr[5], vmod_addr[6]);
//	printf("hdmi - slvreg0: %d, slvreg1: %d slvreg2: %d\n\r", hdmi_addr[0], hdmi_addr[1], hdmi_addr[2]);


	int pixels, max_index;
	max_index = 640*480;
	printf(
				"32-bit test: %s\n\r",
				(XST_SUCCESS == XUtil_MemoryTest32((u32 *)0xA0500000, NUM_TEST_WORDS,
						TEST_VECTOR, XUT_ALLMEMTESTS)) ? "passed" : "failed");
	while(1){

		//for(j = 0; j<480 ; j++){
			j = 0;
			//for(i=0; i < max_index; i++){

				//pixels = ddr_addr[i];
				//ddr_addr2[j] = pixels & 0x0000FFFF;
				//ddr_addr2[i] = pixels;
				//j++;
				//printf("%x ", ddr_addr[i]);
				//ddr_addr2[j] = pixels >> 16;
				//j++;
				//printf("i: %d %x ", i, ddr_addr[i]);
				//printf("%x ", ddr_addr2[i]);

			//}
		//}

//			ddr_addr2[0] = 0xDEADBEEF;
//			ddr_addr2[1] = 0xBEEFDEAD;
//			ddr_addr2[2] = 0xFEEDBEEF;
//			printf("%x %x %x", ddr_addr2[0], ddr_addr2[1], ddr_addr2[2]);
//			for (j = 0; j < 480; j++) {
//				for (i = 0; i < 640; i++) {
//						printf ("%x ", ddr_addr[j * 640 + i]);
//				}
//			}
	}



	printf("Exiting\n\r");

	return 0;
}
