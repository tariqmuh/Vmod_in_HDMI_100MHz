/*
 * main.c
 *
 *  Created on: Jan 24, 2013
 *      Author: Victor Zhang
 */

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "xparameters.h"    /* generated system parameters                  */
#include "xbasic_types.h"   /* Xilinx basic types for device drivers        */
#include "xutil.h"

#define printf xil_printf   /* a smaller footprint printf */
#define NUM_TEST_WORDS 8
#define TEST_VECTOR 0x12345678 /* random word */

#define AVERAGE
//#define LUMINOSITY
int main() {

	volatile int *ddr_addr = (volatile int *) XPAR_MCB_DDR2_S0_AXI_BASEADDR;
	volatile int *ddr_addr2 = (volatile int *) 0xA0500000;

	volatile int *vmod_addr = (volatile int *) XPAR_VMODCAM_0_BASEADDR;
	volatile int *hdmi_addr = (volatile int *) XPAR_HDMI_OUT_0_BASEADDR;

	vmod_addr[4] = XPAR_MCB_DDR2_S0_AXI_BASEADDR;
	vmod_addr[5] = XPAR_MCB_DDR2_S0_AXI_BASEADDR+1600*1200*4;
	vmod_addr[6] = 1;

	//strspn();
	//ddr_addr[0] = 0xDEADBEEF;
	//ddr_addr[1] = 0xFEEBDAED;
	int i;
	//int j;
//	for(j = 0; j<1600*1200 ; j++){
//		ddr_addr[j] = 0;
//	}

	// set stride
		hdmi_addr[0] = 640; // hdmi_addr[0] corresponds to slv_reg2
		// set frame base address
		hdmi_addr[1] = (int)ddr_addr; // hdmi_addr[1] corresponds to slv_reg1
		// go
		hdmi_addr[2] = 1;

//	printf(
//			"32-bit test: %s\n\r",
//			(XST_SUCCESS == XUtil_MemoryTest32((u32 *)ddr_addr, NUM_TEST_WORDS,
//					TEST_VECTOR, XUT_ALLMEMTESTS)) ? "passed" : "failed");
//	printf(
//				"32-bit test: %d\n\r",
//				(XST_SUCCESS == XUtil_MemoryTest32((u32 *)ddr_addr, NUM_TEST_WORDS,
//						TEST_VECTOR, XUT_ALLMEMTESTS)));

	printf("HELLO\n\r");

	printf("vmod - slvreg0: %d, slvreg1: %d slvreg2: %d\n\r", vmod_addr[4], vmod_addr[5], vmod_addr[6]);
	printf("hdmi - slvreg0: %d, slvreg1: %d slvreg2: %d\n\r", hdmi_addr[0], hdmi_addr[1], hdmi_addr[2]);


	int f_pixel, /*s_pixel,*/ pixels, f_grayscale, s_grayscale, grayscale;
	int f_red, f_green, f_blue;
	int s_red, s_green, s_blue;
	while(1){

		//for(j = 0; j<480 ; j++){
			//j = 0;
			for(i=0; i<(320*480) ; i++){
#ifdef AVERAGE
				pixels = ddr_addr[i];
				//f_pixel = pixels & 0x0000FFFF;
				f_red = ((pixels >> 11) & 0x0000001F) << 3;
				f_green = ((pixels >> 5) & 0x0000003F) << 2;
				f_blue = ((pixels) & 0x0000001F) << 3;
				f_grayscale = ( (f_red) + (f_green) + (f_blue) ) / 3;
				f_grayscale = ( ((f_grayscale >> 3) & 0x0000001F)  << 11) | ( ((f_grayscale >> 2) & 0x0000003F) << 5) | ( ((f_grayscale >> 3) & 0x0000001F) );

				//s_pixel = pixels >> 16;
				s_red = ((pixels >> 27) & 0x0000001F) << 3;
				s_green = ((pixels >> 21) & 0x0000003F) << 2;
				s_blue = ((pixels >> 16) & 0x0000001F) << 3;
				s_grayscale = ( (s_red) + (s_green) + (s_blue) ) / 3;
				s_grayscale = ( ((s_grayscale >> 3) & 0x0000001F)  << 27) | ( ((s_grayscale >> 2) & 0x0000003F) << 21) | ( ((s_grayscale >> 3) & 0x0000001F) << 16);

				//f_grayscale = ( /*Red*/ (f_pixel >> 11) + /*Green*/ ( (f_pixel >> 6) & 0x0000001F) + /*Blue*/ ( f_pixel & 0x0000001F) ) / 3;
//				s_grayscale = ( /*Red*/ (pixels >> 27) + /*Green*/ ( (pixels >> 22) & 0x0000001F) + /*Blue*/ (( pixels >> 16) & 0x0000001F) ) / 3;
				//grayscale = (s_grayscale << 27) | (s_grayscale << 22) | (s_grayscale << 16) | (f_grayscale << 11) | (f_grayscale << 6) | (f_grayscale);
				grayscale = s_grayscale | f_grayscale;
				ddr_addr2[i] = grayscale;
				//ddr_addr2[i] = pixels;
#elif defined(LUMINOSITY)
				pixels = ddr_addr[i];
				//f_pixel = pixels & 0x0000FFFF;
				f_red = ((pixels >> 11) & 0x0000001F) << 3;
				f_green = ((pixels >> 5) & 0x0000003F) << 2;
				f_blue = ((pixels) & 0x0000001F) << 3;
				f_grayscale = ( (f_red)*0.21 + (f_green)*0.71 + (f_blue)*0.07 );
				f_grayscale = ( ((f_grayscale >> 3) & 0x0000001F)  << 11) | ( ((f_grayscale >> 2) & 0x0000003F) << 5) | ( ((f_grayscale >> 3) & 0x0000001F) );

				//s_pixel = pixels >> 16;
				s_red = ((pixels >> 27) & 0x0000001F) << 3;
				s_green = ((pixels >> 21) & 0x0000003F) << 2;
				s_blue = ((pixels >> 16) & 0x0000001F) << 3;
				s_grayscale = ( (s_red)*0.21 + (s_green)*0.71 + (s_blue)*0.07 );
				s_grayscale = ( ((s_grayscale >> 3) & 0x0000001F)  << 27) | ( ((s_grayscale >> 2) & 0x0000003F) << 21) | ( ((s_grayscale >> 3) & 0x0000001F) << 16);

				//f_grayscale = ( /*Red*/ (f_pixel >> 11) + /*Green*/ ( (f_pixel >> 6) & 0x0000001F) + /*Blue*/ ( f_pixel & 0x0000001F) ) / 3;
//				s_grayscale = ( /*Red*/ (pixels >> 27) + /*Green*/ ( (pixels >> 22) & 0x0000001F) + /*Blue*/ (( pixels >> 16) & 0x0000001F) ) / 3;
				//grayscale = (s_grayscale << 27) | (s_grayscale << 22) | (s_grayscale << 16) | (f_grayscale << 11) | (f_grayscale << 6) | (f_grayscale);
				grayscale = s_grayscale | f_grayscale;
				ddr_addr2[i] = grayscale;
				//ddr_addr2[i] = pixels;
#endif
//				printf ("i: %d, f_grayscale: 0x%X, s_grayscale: 0x%X\n\r", i, f_grayscale, s_grayscale);
//				printf ("i: %d, pixels: 0x%X, grayscale: 0x%X\n\r", i, pixels, grayscale);
//				printf ("ddr_addr2: 0x%X\n\r", ddr_addr2[i]);
			}
		//}
	}



	printf("Exiting\n\r");

	return 0;
}
