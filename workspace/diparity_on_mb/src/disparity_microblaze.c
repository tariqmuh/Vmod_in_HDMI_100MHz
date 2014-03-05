/* disp.c - disparity map generator
 * Author: Yu Ting Chen
 * Date: Feb 26/14
 */

/* include files */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "xparameters.h"    /* generated system parameters                  */
#include "xbasic_types.h"   /* Xilinx basic types for device drivers        */
#include "xutil.h"

// Image format
#define RGB565  2 // number of pixels stored at each address
#define RGB888  1
#define YUV             1

/* User Parameters */
#define WIN0    1
#define WIN1    3
#define WIN2    5
#define WIN3    7
#define WINMAX  WIN3
#define THRESH1 144
#define THRESH2 200
#define THRESH3 196

/* Width/Height in number of pixels */
#define WIDTH   640
#define HEIGHT  480

#define FORMAT  RGB565
#define DMIN    0
#define DMAX    63
#define DRANGE  64
#define MAX_SAD 12495

/**********************************************
 * define if in DEBUG mode - not for MicroBlaze *
 **********************************************/
//#define DEBUG

/******************************************************************************************
 * PARAMETERIZED VARIABLES WHICH NEED TO BE DEFINED LATER WILL START WITH NAME param_NAME *
 ******************************************************************************************/
#ifndef DEBUG
#define param_REF_ADDR	0xA0200000  /* define the reference image address */
#define param_SCH_ADDR 	0xA0300000  /* define the search image address */
#define param_LV_ADDR   0xA0400000  /* define the local variation matrix address */
#define param_SAD_ADDR  0xA1000000	/* define the SAD matrix address */
#define param_DM_ADDR   0xA0600000	/* define the DM matrix address */
#endif

/* Functions */
void disparity(uint32_t *ref, uint32_t *sch, uint32_t *lv, uint32_t *sad, uint32_t *dm, int format);
// void image_pre_filter();
void get_local_variation(uint32_t *ref, uint32_t *lv, int format);
void get_sad(uint32_t *ref, uint32_t *sch, uint32_t *lv, uint32_t *sad, int format);
void get_pixel_disparity(uint32_t *sad, uint32_t *dm);
// void dm_post_filter();
uint32_t get_rgb565_pixel(uint32_t *addr, int i, int j);
void set_rgb565_pixel(uint32_t *addr, int i, int j, uint16_t val);
void print_matrix2(uint32_t *mat, char *str, int debug, int format);
void print_matrix3(uint32_t *mat, char *str, int debug, int format);
#ifdef DEBUG
void print_matrix2_to_file(uint32_t *mat, char *str, int debug, FILE *fp, int format);
void print_matrix3_to_file(uint32_t *mat, char *str, int debug, FILE *fp, int format);
#endif

/* begin main function */
int main()
{
        #ifdef DEBUG
        assert(argc == 5); // 1 lv output file, 2 dm output file, 3 ref image, 4 sch image
        printf("Attempting to open file %s\n", argv[1]);
        FILE *lvfp = fopen(argv[1], "w");
        assert(lvfp != NULL);
        printf("Attempting to open file %s\n", argv[2]);
        FILE *dmfp = fopen(argv[2], "w");
        assert(dmfp != NULL);
        printf("Attempting to open file %s\n", argv[3]);
        FILE *rfp = fopen(argv[3], "r");
        assert(rfp != NULL);
        printf("Attempting to open file %s\n", argv[4]);
        FILE *sfp = fopen(argv[4], "r");
        assert(sfp != NULL);
        #endif

        /* initialize addresses */
        volatile uint32_t *ref, *sch;
        volatile uint32_t *lv;
        volatile uint32_t *sad;
        volatile uint32_t *dm;

        int i,j,k;

        volatile int *ddr_addr = (volatile int *) XPAR_MCB_DDR2_S0_AXI_BASEADDR;
        volatile int *ddr_addr2 = (volatile int *) 0xA0100000;
        volatile int *ref_image = (volatile int *) param_REF_ADDR;
        volatile int *search_image = (volatile int *) param_SCH_ADDR;

        volatile int *hdmi_addr = (volatile int *) XPAR_HDMI_OUT_0_BASEADDR;

        i = 0;
        while(i<0xFFFFFFFF)
        	i++;

    	int f_pixel, /*s_pixel,*/ pixels, f_grayscale, s_grayscale, grayscale;
    	int f_red, f_green, f_blue;
    	int s_red, s_green, s_blue;
        /* START - Copy one image from each stream*/
        for(i=0; i<(320*480) ; i++){
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
			ref_image[i] = grayscale;

			pixels = ddr_addr2[i];
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
			search_image[i] = grayscale;

        	//ref_image[i] = ddr_addr[i];
        	//search_image[i] = ddr_addr2[i];
        }
        /* END - Copy one image from each stream*/
    	// set stride
   		hdmi_addr[0] = 640; // hdmi_addr[0] corresponds to slv_reg2
   		// set frame base address
   		hdmi_addr[1] = (int)search_image; // hdmi_addr[1] corresponds to slv_reg1
   		// go
   		hdmi_addr[2] = 1;


#ifdef DEBUG
        if (FORMAT == RGB565) {
                ref = (uint32_t *)malloc((WIDTH*HEIGHT/2)*sizeof(uint32_t));
                sch = (uint32_t *)malloc((WIDTH*HEIGHT/2)*sizeof(uint32_t));
        } else {
                ref = (uint32_t *)malloc(WIDTH*HEIGHT*sizeof(uint32_t));
                sch = (uint32_t *)malloc(WIDTH*HEIGHT*sizeof(uint32_t));
        }
        lv = (uint32_t *)malloc(WIDTH*HEIGHT*sizeof(uint32_t));
        sad = (uint32_t *)malloc(WIDTH*HEIGHT*DRANGE*sizeof(uint32_t));
        dm = (uint32_t *)malloc(WIDTH*HEIGHT*sizeof(uint32_t));
#else
        ref = param_REF_ADDR;
        sch = param_SCH_ADDR;
        lv = param_LV_ADDR;
        sad = param_SAD_ADDR;
        dm = param_DM_ADDR;
#endif

        //int i, j, k;
        /* initialize matrices */
        for (i = 0; i < HEIGHT; i++) {
                for (j = 0; j < WIDTH; j++) {
                        *(lv + (i*WIDTH + j)) = 1;
                        *(dm + (i*WIDTH + j)) = 0;
                        for (k = 0; k < DRANGE; k++) {
                                *(sad + k*WIDTH*HEIGHT + i*WIDTH + j) = MAX_SAD; // initialize to very large value
                        }
                }
        }

        int c = 0;
        /* initialize reference image and search image matrices */
        for (i = 0; i < HEIGHT; i++) {
                for (j = 0; j < WIDTH; j++) {
                        int rval, sval;
                        #ifdef DEBUG
                        assert(fscanf(rfp, "%d\n", &rval) != EOF);
                        assert(fscanf(sfp, "%d\n", &sval) != EOF);
                        #endif
                                if (FORMAT == RGB565) {
                                        set_rgb565_pixel(ref, i, j, rval);
                                        set_rgb565_pixel(sch, i, j, sval);
                                } else {
                                        *(ref + (i*WIDTH + j)) = rval;
                                        *(sch + (i*WIDTH + j)) = sval;
                                }
                }
        }

        printf("Begin disparity map generation\n");

        print_matrix2(ref, "ref 0", 0, FORMAT);
        print_matrix2(sch, "sch 0", 0, FORMAT);
        //print_matrix2(lv, "lv 0", 0, FORMAT);

        disparity(ref, sch, lv, sad, dm, FORMAT);

        print_matrix2(lv, "lv 1", 0, FORMAT);
        //print_matrix3(sad, "sad 1", 0, FORMAT);
        //print_matrix2(dm, "dm 1", 0, FORMAT);
        #ifdef DEBUG
        print_matrix2_to_file(lv, "lv 1", 0, lvfp, FORMAT);
        print_matrix2_to_file(dm, "dm 1", 0, dmfp, FORMAT);
        fclose(lvfp);
        fclose(dmfp);
        fclose(rfp);
        fclose(sfp);
        #endif

        //printf("Finished disparity map generation\n");

        return;
}


/* disparity() - generates the disparity map for a pair of stereoscopic images
 * ref - address of first pixel of reference image
 * sch - address of first pixel of search image
 * lv - address of lv matrix
 * dm - address of disparity map
 * format - image format (RGB565, RGB888, YUV, etc)
 */
void disparity(uint32_t *ref, uint32_t *sch, uint32_t *lv, uint32_t *sad, uint32_t *dm, int format)
{

        /* pre-processing filter */
        // image_pre_filter();

        /* adaptive window sizing */
        get_local_variation(ref, lv, format);

        /* sum of absolute differences cost function calculation */
        get_sad(ref, sch, lv, sad, format);

        /* disparity map generation from sad pixel matching */
        get_pixel_disparity(sad, dm);

        /* post processing filter */
        // dm_post_filter();

}


/* get_local_variation() - generates the local variation sizing for the reference image, store
 * it in memory (BRAM). Each element of the lv matrix represents the appropriate window size
 * ref - address of first pixel of reference image
 * lv - address of lv matrix
 * format - image format
 */
void get_local_variation(uint32_t *ref, uint32_t *lv, int format)
{
        /* format specifies the number of pixels stored in 1 word */
        int i, j, wsum1, wsum2, wsum3;
        int wavg1, wavg2, wavg3; // only need int
        for (i = WINMAX/2; i < WIDTH - WINMAX/2; i++) {
                for (j = WINMAX/2; j < HEIGHT - WINMAX/2; j++) {
                        int u, v;
                        uint32_t ref_pixel;
                        wavg1 = 0;
                        wavg2 = 0;
                        wavg3 = 0;
                        wsum1 = 0;
                        wsum2 = 0;
                        wsum3 = 0;
                        for (u = -WINMAX/2; u <= WINMAX/2; u++) {
                                for (v = -WINMAX/2; v <= WINMAX/2; v++) {
                                        /* add to win3 sum */
                                        if (format == RGB565) {
                                                ref_pixel = get_rgb565_pixel(ref, i+u, j+v);
                                        } else {
                                                ref_pixel = *(ref + ((i+u)*WIDTH + j+v));
                                        }
                                        wavg3 += ref_pixel;
                                        if (u >= -WIN2/2 && u <= WIN2/2 && v >= -WIN2/2 && v <= WIN2/2) {
                                                wavg2 += ref_pixel;
                                                if (u >= -WIN1/2 && u <= WIN1/2 && v >= -WIN1/2 && v <= WIN1/2) {
                                                        wavg1 += ref_pixel;
                                                }
                                        }
                                }
                        }
                        wavg1 /= WIN1*WIN1;
                        wavg2 /= WIN2*WIN2;
                        wavg3 /= WIN3*WIN3;

                        for (u = -WINMAX/2; u <= WINMAX/2; u++) {
                                for (v = -WINMAX/2; v <= WINMAX/2; v++) {
                                        /* add to win3 sum */
                                        if (format == RGB565) {
                                                ref_pixel = get_rgb565_pixel(ref, i+u, j+v);
                                        } else {
                                                ref_pixel = *(ref + ((i+u)*WIDTH + j+v));
                                        }
                                        wsum3 += abs(ref_pixel - wavg3);
                                        if (u >= -WIN2/2 && u <= WIN2/2 && v >= -WIN2/2 && v <= WIN2/2) {
                                                wsum2 += abs(ref_pixel - wavg2);
                                                if (u >= -WIN1/2 && u <= WIN1/2 && v >= -WIN1/2 && v <= WIN1/2) {
                                                        wsum1 += abs(ref_pixel - wavg1);
                                                }
                                        }
                                }
                        }

                        if (wsum1 > THRESH1) {
                                //printf("win1, %d > %d\n", wsum1, THRESH1);
                                *(lv + (i*WIDTH + j)) = WIN0;
                        } else if (wsum2 > THRESH2) {
                                //printf("win2\n");
                                *(lv + (i*WIDTH + j)) = WIN1;
                        } else if (wsum3 > THRESH3) {
                                //printf("win3\n");
                                *(lv + (i*WIDTH + j)) = WIN2;
                        } else {
                                //printf("win4\n");
                                *(lv + (i*WIDTH + j)) = WIN3;
                        }
                }
        }
}


/* given the reference and search matrix, local variation window matrix and 3D sad matrix
 * compute the sum of absolute difference for pixels within disparity range dmin and dmax
 * for each pixel in reference image not near the border
 */
void get_sad(uint32_t *ref, uint32_t *sch, uint32_t *lv, uint32_t *sad, int format)
{
        int i, j, d, u, v;
        int wsize, w;
        for (i = 0; i < HEIGHT; i++) {
                for (j = 0; j < WIDTH; j++) {
                        /* determine window size */
                        wsize = *(lv + (i*WIDTH + j));
                        w = wsize/2;
                        /* for each disparity value */
                        for (d = DMIN; d <= DMAX; d++) {
                                /* calculate sum of absolute difference for window */
                                //*(sad + i*WIDTH*HEIGHT + j*WIDTH + d) = 0; // set to zero
                                int tmp = 0;
                                for (u = w; u >= -w; u--) {
                                        for (v = w; v >= -w; v--) {
                                                if (i + u < 0 || i + u > HEIGHT || j + v - d < 0 || j + v - d > WIDTH) {
                                                        // reset back to large value
                                                        continue;
                                                }
                                                if (format == RGB565) {
                                                        tmp += abs(get_rgb565_pixel(ref, i+u, j+v) - get_rgb565_pixel(sch, i+u, j+v-d));
                                                } else {
                                                        tmp += abs(*(ref + (i+u)*WIDTH + (j+v)) - *(sch + (i+u)*WIDTH + (j+v-d)));
                                                }
                                        }
                                }
                                *(sad + d*WIDTH*HEIGHT + i*WIDTH + j) = tmp;
                        }
                }
        }
}


/* get_pixel_disparity() - fill the dm matrix with the disparity values
 * sad - 3D matrix of dimension: WIDTHxHEIGHTxDRANGE storing sum of absolute difference
 * between pixels d pixels away from the reference on the epipolar plane
 * dm - 2D matrix for storing disparity map
 */
void get_pixel_disparity(uint32_t *sad, uint32_t *dm)
{
        int i, j, d;
        for (i = 0; i < HEIGHT; i++) {
                for (j = 0; j < WIDTH; j++) {
                        int min = MAX_SAD + 1;
                        int min_idx = 0;
                        for (d = 0; d < DRANGE; d++) {
                                uint32_t tmp = *(sad + d*WIDTH*HEIGHT + i*WIDTH + j);
                                if (tmp < min) {
                                        min = tmp;
                                        min_idx = d;
                                }
                        }
                        *(dm + i*WIDTH + j) = min_idx;
                }
        }
        return;
}


/* get rgb565 pixel value
 *
 */
uint32_t get_rgb565_pixel(uint32_t *addr, int i, int j)
{
        assert(addr != NULL);
        int m, n;
        m = i;
        n = j/2;
        if (j % 2) {
                /* odd pixel */
                return ((*(addr + (m*WIDTH/2 + n))) >> 16) & 0x0000FFFF;
        } else {
                /* even pixel */
                return ((*(addr + (m*WIDTH/2 + n))) & 0x0000FFFF);
        }
}


/*
 *
 */
void set_rgb565_pixel(uint32_t *addr, int i, int j, uint16_t val)
{
        assert(addr != NULL);
        int m, n;
        m = i;
        n = j/2;
        if (j % 2) {
                /* set odd pixel */
                *(addr + (m*WIDTH/2 + n)) = (*(addr + (m*WIDTH/2 + n)) & 0x0000FFFF) | ((val) << 16);
        } else {
                /* set even pixel */
                *(addr + (m*WIDTH/2 + n)) = *(addr + (m*WIDTH/2 + n)) & 0xFFFF0000 | val;
        }
        return;
}


/* prints 2d matrix
 *
 */
void print_matrix2(uint32_t *mat, char *str, int debug, int format)
{
        int i, j;
        printf("%s\n", str);
        for (i = 0; i < HEIGHT; i++) {
                for (j = 0; j < WIDTH; j++) {
                        if (debug == 1) {
                                printf("(%d,%d) ", i, j);
                        }
                        if (format == RGB565 && (strspn(str, "ref") == 3 || strspn(str, "sch") == 3)) {
                                printf("%d ", get_rgb565_pixel(mat, i, j));
                        } else {
                                printf("%d ", *(mat + (i*WIDTH + j)));
                        }
                }
                printf("\n");
        }
}


/* prints 3d matrix
 *
 */
void print_matrix3(uint32_t *mat, char *str, int debug, int format)
{
        int i, j, k;
        for (k = 0; k < DRANGE; k++) {
                printf("%s - dimension %d\n", str, k+1);
                for (i = 0; i < HEIGHT; i++) {
                        for (j = 0; j < WIDTH; j++) {
                                if (debug == 1) {
                                        printf("(%d,%d,%d) ", i, j, k);
                                }
                                printf("%d ", *(mat + k*WIDTH*HEIGHT + i*WIDTH + j));
                        }
                        printf("\n");
                }
        }
}


#ifdef DEBUG
/* prints 2d matrix to file
 *
 */
void print_matrix2_to_file(uint32_t *mat, char *str, int debug, FILE *fp, int format)
{
        assert(fp != NULL);
        int i, j;
        printf("Writing %s to file\n", str);
        for (i = 0; i < HEIGHT; i++) {
                for (j = 0; j < WIDTH; j++) {
                        if (debug == 1) {
                                fprintf(fp, "(%d,%d) ", i, j);
                        }
                        if (format == RGB565 && (strspn(str, "ref") == 3 || strspn(str, "sch") == 3)) {
                                fprintf(fp, "%d ", get_rgb565_pixel(mat, i, j));
                        } else {
                                fprintf(fp, "%d ", *(mat + (i*WIDTH + j)));
                        }
                }
                fprintf(fp, "\n");
        }
}


/* prints 3d matrix to file
 *
 */
void print_matrix3_to_file(uint32_t *mat, char *str, int debug, FILE *fp, int format)
{
        assert(fp != NULL);
        int i, j, k;
        printf("Writing %s to file\n", str);
        for (k = 0; k < DRANGE; k++) {
                fprintf(fp, "dim %d\n", k+1);
                for (i = 0; i < HEIGHT; i++) {
                        for (j = 0; j < WIDTH; j++) {
                                if (debug == 1) {
                                        fprintf(fp, "(%d,%d,%d) ", i, j, k);
                                }
                                fprintf(fp, "%d ", *(mat + k*WIDTH*HEIGHT + i*WIDTH + j));
                        }
                        fprintf(fp, "\n");
                }
        }
}
#endif
