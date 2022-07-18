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

// A3 REDECLARATIONS
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


/* task 03 */

/*
  Save the entire 2D array im into a file called 'filename' in a .ppm
  text file image format. Returns zero on success, or a non-zero error
  code on failure. Arrays of length 0 should produce an empty output file.

  Make sure you validate the parameters before you use them.
*/
int img_save_ppm(img_t* im, const char* filename);
