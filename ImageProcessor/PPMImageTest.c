// author: Amanda Ngo 
// date: July 19, 2021
// last modified: July 18, 2022
// input: void
// output: int
// description: Create a program to test the functions made in PPMImage.c


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "PPMImage.h"

int main(){
    printf("Running task 3 tests...\n");

    // Test for sample image in assig nment
    img_t* test_im = NULL;
    img_result_t test_result = IMG_OK;
    test_im = img_create(4,5);
    for (unsigned int i=0; i<test_im->rows; i++) {
        for (unsigned int j=0; j<test_im->cols; j++) {
            img_set(test_im, i, j, 0);
        }
    }
    img_set(test_im, 3, 0, 255);
    img_set(test_im, 1, 1,7);
    img_set(test_im, 2, 2, 15);
    img_set(test_im, 0, 3, 15);
    assert(img_save_ppm(test_im,"task_3.ppm") == 0);
    
    // Test for white image
    img_t* test_white = NULL;
    img_result_t test_white_result = IMG_OK;
    test_white = img_create(100,100);
    for (unsigned int i=0; i<test_white->rows; i++) {
        for (unsigned int j=0; j<test_white->cols; j++) {
            img_set(test_white, i, j, 255);
        }
    }
    assert(img_save_ppm(test_white,"task_3_white.ppm") == 0);

    // Test for invalid inputs
    img_t* test_invalid = NULL;
    img_result_t test_invalid_result = IMG_OK;
    char* null_filename = NULL;

    assert(img_save_ppm(test_invalid, "task_3_invalid.ppm") == 1);
    assert(img_save_ppm(test_im, null_filename) == 1);

    // Test for empty array
    test_invalid = img_create(0,0);
    assert(img_save_ppm(test_invalid, "task_3_empty.ppm") == 0);

    printf("Task 3 tests passed!\n");
    img_destroy(test_invalid);
    img_destroy(test_white);
    img_destroy(test_im);

}
