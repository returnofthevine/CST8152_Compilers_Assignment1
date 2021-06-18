/*
File name: buffer.h
Compiler: MS Visual Studio 2019
Author: Divine Omorogieva, ID# 040897820
Course: CST 8152 – Compilers, Lab Section: 013
Assignment: 1
Date: June 8th, 2020
Professor: Svillen Ranev
Purpose: Header file for the buffer program, include declaration of functions with constant definitions
Function list: b_allocate, b_addc, b_clear, b_free, b_isfull, b_limit, b_capacity, b_mark, b_mode,
               b_incfactor, b_load, b_isempty, b_getc, b_eob, b_print
*/

/*
*/
#ifndef BUFFER_H_
#define BUFFER_H_

/*#pragma warning(1:4001) *//*to enforce C89 type comments  - to make //comments an warning */

/*#pragma warning(error:4001)*//* to enforce C89 comments - to make // comments an error */

/* standard header files */
#include <stdio.h>  /* standard input/output */
#include <malloc.h> /* for dynamic memory allocation*/
#include <limits.h> /* implementation-defined data type ranges and limits */

/* constant definitions */
#define RT_FAIL_1 (-1)         /* operation failure return value 1 */
#define RT_FAIL_2 (-2)         /* operation failure return value 2 */
#define LOAD_FAIL (-2)         /* load fail return value */

#define DEFAULT_INIT_CAPACITY 200   /* default initial buffer capacity */
#define DEFAULT_INC_FACTOR 15       /* default increment factor */


/* You should add your own constant definitions here */
/*For B_ISFULL macro function*/
#ifdef B_ISFULL
#undef B_ISFULL
#define B_ISFULL(a) ((a == NULL)? -1:((short)(a->addc_offset*sizeof(char)) == a->capacity)? 1:0)
#endif
#ifndef B_ISFULL
#define B_ISFULL(a) b_isfull(a)
#endif

/*Maximum capacity*/
#define MAX_CAPACITY (SHRT_MAX - 1)

/*Return b_incfactor failure value*/
#define INC_FACTOR_FAIL 0x100

/*Return TRUE/FALSE value*/
#define TRUE 1
#define FALSE 0

/*For inc_factor value boundaries*/
#define INC_FACTOR_ADD_MAX 255
#define INC_FACTOR_ADD_MIN 1
#define INC_FACTOR_MULTI_MAX 100
#define INC_FACTOR_MULTI_MIN 1
#define INC_FACTOR_A_M 15
#define INC_FACTOR_F 0

/*For buffer operational mode indicator*/
#define MODE_FIXED 0
#define MODE_ADD 1
#define MODE_MULTI (-1)

/* Add your bit-masks constant definitions here */
#define DEFAULT_FLAGS  0xFFF9 /*1111 1111 1111 1001*/
#define SET_EOB  0x0002 /*0000 0000 0000 0010*/
#define RESET_EOB 0xFFFD /*1111 1111 1111 1101*/
#define CHECK_EOB 0x0002 /*0000 0000 0000 0010*/
#define SET_R_FLAG 0x0004 /*0000 0000 0000 0100*/
#define RESET_R_FLAG 0xFFFB /*1111 1111 1111 1011*/
#define CHECK_R_FLAG 0x0004 /*0000 0000 0000 0100*/
#define DEFAULTZ    0x0000   /* 0000 0000 0000 0000 */

/* user data type declarations */
typedef struct BufferDescriptor {
    char* cb_head;   /* pointer to the beginning of character array (character buffer) */
    short capacity;    /* current dynamic memory size (in bytes) allocated to character buffer */
    short addc_offset;  /* the offset (in chars) to the add-character location */
    short getc_offset;  /* the offset (in chars) to the get-character location */
    short markc_offset; /* the offset (in chars) to the mark location */
    char  inc_factor; /* character array increment factor */
    char  mode;       /* operational mode indicator*/
    unsigned short flags;     /* contains character array reallocation flag and end-of-buffer flag */
} Buffer, * pBuffer;
/*typedef Buffer *pBuffer;*/

/* function declarations */
/*
Place your function declarations here.
Do not include the function header comments here.
Place them in the buffer.c file
*/

Buffer* b_allocate(short init_capacity, char inc_factor, char o_mode);

pBuffer b_addc(pBuffer const pBD, char symbol);

int b_clear(Buffer* const pBD);

void b_free(Buffer* const pBD);

int b_isfull(Buffer* const pBD);

short b_addcoffset(Buffer* const pBD);

short b_capacity(Buffer* const pBD);

short b_markc(pBuffer const pBD, short mark);

int b_mode(Buffer* const pBD);

size_t b_incfactor(Buffer* const pBD);

int b_load(FILE* const fi, Buffer* const pBD);

int b_isempty(Buffer* const pBD);

char b_getc(Buffer* const pBD);

int b_eob(Buffer* const pBD);

int b_print(Buffer* const pBD, char nl);

Buffer* b_compact(Buffer* const pBD, char symbol);

char b_rflag(Buffer* const pBD);

short b_retract(Buffer* const pBD);

short b_reset(Buffer* const pBD);

short b_getcoffset(Buffer* const pBD);

int b_rewind(Buffer* const pBD);

char* b_location(Buffer* const pBD, short loc_offset);

#endif

