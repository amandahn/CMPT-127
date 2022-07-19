// author: Amanda Ngo 
// date: July 18, 2021
// last modified: July 18, 2022
// input: void
// output: int
// description: Create a program to test the functions made in JSONImage.c

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "JSONImage.h"


int main(){
    printf("Running task 2 tests...\n");
    img_t* test_im = NULL;
    img_result_t test_result = IMG_OK;
    test_im = img_create(10, 10);  
    for (unsigned int i=0; i<test_im->rows; i++) {
        for (unsigned int j=0; j<test_im->cols; j++) {
            img_set(test_im, i, j, 10);
        }
    }

    // Test for successfull filled save
    assert(img_save_json(test_im, "task_2") == 0);

    // Test for unsuccessfull saves
    char* null_filename = NULL;
    assert(img_save_json(test_im, null_filename) == 1);
    img_t* test_empty = NULL;
    img_result_t test_empty_result = IMG_OK;
    assert(img_save_json(test_empty, "task_2_empty") == 1);

    test_empty = img_create(0,0);
    for (unsigned int i=0; i<test_im->rows; i++) {
        for (unsigned int j=0; j<test_im->cols; j++) {
            img_set(test_im, i, j, 0);
        }
    }
    // Test for successfull empty save
    assert(img_save_json(test_empty, "task_2_empty") == 0);

    printf("Task 2 tests passed!\n");
    img_destroy(test_empty);
    img_destroy(test_im);
}
