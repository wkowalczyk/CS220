/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/* 
 * Please fill in the following team struct 
 */
team_t team = {
    "kaPOW",              /* Team name */

    "Weronika Kowalczyk",     /* First member full name */
    "wkowalc1@binghamton.edu",  /* First member email address */

    "",                   /* Second member full name (leave blank if none) */
    ""                    /* Second member email addr (leave blank if none) */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/* 
 * naive_rotate - The naive baseline version of rotate 
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
	for (j = 0; j < dim; j++)
	    dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
}

/* 
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst) 
{
int blockSize = 32;
	int i, j, ii, jj;
		for(jj = 0; jj < dim; jj += blockSize)
			for(ii = 0; ii < dim; ii += blockSize)
				for (j = jj; j < jj + blockSize; j++)
					for (i = ii; i < ii + blockSize; i++)
						dst[RIDX(dim-1-j, i, dim)] = src[RIDX(i, j, dim)];
}

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_rotate_functions() 
{
    add_rotate_function(&naive_rotate, naive_rotate_descr);   
    add_rotate_function(&rotate, rotate_descr);   
    /* ... Register additional test functions here */
}


/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
    int red;
    int green;
    int blue;
    int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/* 
 * initialize_pixel_sum - Initializes all fields of sum to 0 
 */
static void initialize_pixel_sum(pixel_sum *sum) 
{
    sum->red = sum->green = sum->blue = 0;
    sum->num = 0;
    return;
}

/* 
 * accumulate_sum - Accumulates field values of p in corresponding 
 * fields of sum 
 */
static void accumulate_sum(pixel_sum *sum, pixel p) 
{
    sum->red += (int) p.red;
    sum->green += (int) p.green;
    sum->blue += (int) p.blue;
    sum->num++;
    return;
}

/* 
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel 
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) 
{
    current_pixel->red = (unsigned short) (sum.red/sum.num);
    current_pixel->green = (unsigned short) (sum.green/sum.num);
    current_pixel->blue = (unsigned short) (sum.blue/sum.num);
    return;
}

/* 
 * avg - Returns averaged pixel value at (i,j) 
 */
static pixel avg(int dim, int i, int j, pixel *src) 
{
    int ii, jj;
    pixel_sum sum;
    pixel current_pixel;

	initialize_pixel_sum(&sum);

	//top left corner
	if((i == 0) && (j == 0)){
		for(ii = i; ii <= i+1; i++)
		for(jj = j; jj <= j+1; j++)
			accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);
	} else if((i == dim-1) && (j == 0)){// bottom left corner
		for(ii = i-1; ii <= i; i++)
		for(jj = j; jj <= j+1; j++)
			accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);
	} else if((i == 0) && (j == dim-1)){ //top right corner
		for(ii = i; ii <= i+1; i++)
		for(jj = j-1; jj <= j; j++)
			accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);
	} else if((i == dim-1) && (j == dim-1)){ //bottom right corner
		for(ii = i-1; ii <= i; i++)
		for(jj = j-1; jj <= j; j++)
			accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);
	} else if(j == 0){//left edge
		for(ii = i-1; ii <= i+1; i++)
		for(jj = j; jj <= j+1; j++)
			accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);
	} else if(j == dim-1){//right edge
		for(ii = i-1; ii <= i+1; i++)
		for(jj = j-1; jj <= j; j++)
			accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);
	} else if(i == 0){//top edge
		for(ii = i; ii <= i+1; i++)
		for(jj = j-1; jj <= j+1; j++)
			accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);
	} else if(i == dim-1){//bottom edge
		for(ii = i-1; ii <= i; i++)
		for(jj = j-1; jj <= j+1; j++)
			accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);
	}else{

	//pass in left edge, right edge, top edge, bottom edge
	//make it dependent on that
    //initialize_pixel_sum(&sum);
    //for(ii = max(i-1, 0); ii <= min(i+1, dim-1); ii++) 
	//for(jj = max(j-1, 0); jj <= min(j+1, dim-1); jj++) 
	   // accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

   // initialize_pixel_sum(&sum);
    for(ii = i-1; ii <= i+1; ii++) 
	for(jj = j-1; jj <= j+1; jj++) 
	    accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);
	}


    assign_sum_to_pixel(&current_pixel, sum);
    return current_pixel;
}
	

static void cornerAvg(pixel *dst, pixel *one, pixel *two, pixel
*three, pixel *four){
		dst->red = (one->red + two->red + three->red + four->red)/4;
		dst->green = (one->green + two->green + three->green + four->green)/4;
		dst->blue = (one->blue + two->blue + three->blue + four->blue)/4;
}

static void edgeAvg(pixel *dst, pixel *one, pixel *two, pixel *three,
pixel *four, pixel *five, pixel *six){
		dst->red = (one->red + two->red + three->red + four->red + five->red + six->red)/6;
		dst->green = (one->green + two->green + three->green + four->green + five->green + six->green)/6;
		dst->blue = (one->blue + two->blue + three->blue + four->blue + five->blue + six->blue)/6;
}

static void middleAvg(pixel *dst, pixel *one, pixel *two, pixel
*three, pixel *four, pixel *five, pixel *six, pixel *seven, pixel
*eight, pixel *nine){
		dst->red = (one->red + two->red + three->red + four->red + five->red + six->red + seven->red + eight->red + nine->red)/9;
		dst->green = (one->green + two->green + three->green + four->green + five->green + six->green + seven->green + eight->green + nine->green)/9;
		dst->blue = (one->blue + two->blue + three->blue + four->blue + five->blue + six->blue + seven->blue + eight->blue + nine->blue)/9;
}


//make the avg separate for the top right, left and bottom right, left


/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth 
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) 
{
    int i, j;

    for (i = 0; i < dim; i++)
		for (j = 0; j < dim; j++)   
	    	dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}


/*
 * smooth - Your current working version of smooth.
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst)
{
		int i, j;

		//all 4 corners
		//for(i=0; i < dim; i++){
			//for()
		
		//top left corner
		cornerAvg(&dst[RIDX(0,0,dim)], &src[RIDX(0,0,dim)], &src[RIDX(0,1,dim)], &src[RIDX(1,0,dim)], &src[RIDX(1,1,dim)]);
		
		//for the top edge
		for(j=1; j < dim-1; j++)
			edgeAvg(&dst[RIDX(0,j,dim)], &src[RIDX(0,j-1,dim)], &src[RIDX(0,j,dim)], &src[RIDX(0,j+1,dim)], &src[RIDX(1,j-1,dim)], &src[RIDX(1,j,dim)], &src[RIDX(1,j+1,dim)]);
		
		//for the top right corner
		cornerAvg(&dst[RIDX(0,dim-1,dim)], &src[RIDX(0,dim-1,dim)],&src[RIDX(0,dim-2,dim)], &src[RIDX(1,dim-2,dim)], &src[RIDX(1,dim-1,dim)]);
		
		//for the left edge and the middle and the right edge
		for(i=1; i < dim-1; i++){
			edgeAvg(&dst[RIDX(i,0,dim)], &src[RIDX(i,0,dim)], &src[RIDX(i-1,0,dim)], &src[RIDX(i-1,1,dim)], &src[RIDX(i,1,dim)], &src[RIDX(i+1,1,dim)], &src[RIDX(i+1,0,dim)]);
			for(j=1; j < dim-1; j++){
			middleAvg(&dst[RIDX(i,j,dim)], &src[RIDX(i-1,j-1,dim)], &src[RIDX(i-1,j,dim)], &src[RIDX(i-1,j+1,dim)], &src[RIDX(i,j-1,dim)], &src[RIDX(i,j,dim)], &src[RIDX(i,j+1,dim)], &src[RIDX(i+1,j-1,dim)], &src[RIDX(i+1,j,dim)], &src[RIDX(i+1,j+1,dim)]);
			}
			edgeAvg(&dst[RIDX(i,dim-1,dim)], &src[RIDX(i,dim-1,dim)], &src[RIDX(i+1,dim-1,dim)], &src[RIDX(i+1,dim-2,dim)], &src[RIDX(i,dim-2,dim)], &src[RIDX(i-1,dim-2,dim)], &src[RIDX(i-1,dim-1,dim)]);
		}

		//for the bottom row
		//bottom left corner
		cornerAvg(&dst[RIDX(dim-1,0,dim)], &src[RIDX(dim-1,0,dim)], &src[RIDX(dim-1,1,dim)], &src[RIDX(dim-2,0,dim)], &src[RIDX(dim-2,1,dim)]);

		//the bottom edge
		for(j=1; j < dim-1; j++){
			edgeAvg(&dst[RIDX(dim-1,j,dim)], &src[RIDX(dim-1,j,dim)], &src[RIDX(dim-1,j-1,dim)], &src[RIDX(dim-2,j-1,dim)], &src[RIDX(dim-2,j,dim)], &src[RIDX(dim-1,j+1,dim)], &src[RIDX(dim-2,j+1,dim)]);
		}

		//bottom right corner
		cornerAvg(&dst[RIDX(dim-1,dim-1,dim)], &src[RIDX(dim-1,dim-1,dim)], &src[RIDX(dim-1,dim-2,dim)], &src[RIDX(dim-2,dim-2,dim)], &src[RIDX(dim-2,dim-1,dim)]);
		
}


/********************************************************************* 
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.  
 *********************************************************************/

void register_smooth_functions() {
    add_smooth_function(&smooth, smooth_descr);
    add_smooth_function(&naive_smooth, naive_smooth_descr);
    /* ... Register additional test functions here */
}

