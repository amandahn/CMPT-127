// author: Amanda Ngo 
// date: July 17, 2021
// last modified: July 18, 2022


#include <stdio.h>
#include <stdint.h>

/* Structure type that encapsulates our image: 2D array.
 * the rows represent the indices of the main array,
 * the cols represent the indices of the arrays pointed to by the pointers 
 * in the elements of the main array.
*/

typedef struct { 
    uint8_t** pixels;
    unsigned int rows;
    unsigned int cols;
} img_t;


/*
  Save the entire 2D array in im into a file called 'filename' in a binary
  file format that can be loaded by img_load_binary(). Returns
  zero on success, or a non-zero error code on failure. Arrays of
  length 0 should produce an output file containing an empty array.

  Make sure you validate the parameters before you use them.
*/

int img_save_binary(img_t* im, const char* filename);

/*
  Load a new 2D array from the file called 'filename', that was
  previously saved using img_save_binary(). Returns a pointer to a
  newly-allocated img_t on success, or NULL on failure.

  Make sure you validate the parameter before you use it.
*/

img_t* img_load_binary(const char* filename);


typedef enum {
    IMG_OK,
    IMG_BADINPUT,
    IMG_BADARRAY,
    IMG_BADCOL,
    IMG_BADROW,
    IMG_NOTFOUND
} img_result_t;

img_t* img_create(unsigned int rows, unsigned int cols);

void img_destroy(img_t* im);

img_result_t img_set(img_t* im, unsigned int row, unsigned int col, int val);

img_result_t img_get(const img_t* im, unsigned int row, unsigned int col, int* val);


