/*********************************************************
 * config.h - Configuration data for the driver.c program.
 *********************************************************/
#ifndef _CONFIG_H_
#define _CONFIG_H_

/* 
 * CPEs for the baseline (naive) version of the rotate function that
 * was handed out to the students. Rd is the measured CPE for a dxd
 * image. Run the driver.c program on your system to get these
 * numbers.  
 */
#define R64    3.8
#define R128   5.3
#define R256   7.6
#define R512   11.7
#define R1024  44.8

/* 
 * CPEs for the baseline (naive) version of the smooth function that
 * was handed out to the students. Sd is the measure CPE for a dxd
 * image. Run the driver.c program on your system to get these
 * numbers.  
 */
#define S32   146.8
#define S64   146.9
#define S128  147.0
#define S256  128.4
#define S512  132.0


#endif /* _CONFIG_H_ */
