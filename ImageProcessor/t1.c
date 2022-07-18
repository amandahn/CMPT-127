// author: Amanda Ngo 301433193
// date: July 17, 2021
// input: void
// output: int
// description: Create a program to test the functions made in t1img.c

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "t1img.h"

// helper function that prints the content of the img
void print_img(img_t* im) {
    if (im == NULL) {
        printf("Invalid img (null).\n");
        return;
    }

    printf("Printing img of row length %d and col length %d:\n", im->rows, im->cols);
    for (unsigned int i=0; i<im->rows; i++) {
        for (unsigned int j=0; j<im->cols; j++) {
            printf("%d ", im->pixels[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    printf("Running task 1 tests...\n");
    img_t* test_im = NULL;
    img_result_t test_result = IMG_OK;
    test_im = img_create(10, 10);  
    for (unsigned int i=0; i<test_im->rows; i++) {
        for (unsigned int j=0; j<test_im->cols; j++) {
            img_set(test_im, i, j, 10);
        }
    }
    
    // Tests for valid parameters
    img_save_binary(test_im,"task_1");
    assert(img_save_binary(test_im,"task_1") == 0);
    img_t* load = img_load_binary("task_1");
    assert(load -> rows == 10);
    assert(load -> cols == 10);
    for (unsigned int i=0; i<load->rows; i++) {
        for (unsigned int j=0; j<load->cols; j++) {
            assert(load -> pixels[i][j] == 10);
        }
    }

    // Tests for invalid parameters
    img_t* test_null = NULL;
    char* null_filename = NULL;
    assert(img_save_binary(test_im, null_filename) == 1);
    assert(img_save_binary(test_null, "null") == 1);
    assert(img_load_binary(null_filename) == NULL);

    printf("Task 1 tests passed!\n");
    img_destroy(test_null);
    img_destroy(load);
    img_destroy(test_im);

    img_t* test_invalid = NULL;
    img_result_t test_invalid_result = IMG_OK;
}
