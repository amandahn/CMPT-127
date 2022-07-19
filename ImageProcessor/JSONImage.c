// author: Amanda Ngo 
// date: July 18, 2021
// last modified: July 18, 2022
// input: void
// output: int
// description: Create a program which saves an image object as a JSON file

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "JSONImage.h"

img_t* img_create(unsigned int rows, unsigned int cols){
    unsigned int empty = 0;
    assert(rows >= empty && cols >= empty);
    img_t* ptr = malloc(sizeof(img_t));
    if (ptr != NULL){
        ptr -> pixels = malloc(rows*sizeof(uint8_t*));
        if(ptr -> pixels != NULL){
            for(int i=0; i<rows; i++){
                ptr -> pixels[i] = malloc(cols*sizeof(uint8_t));
            }
            ptr -> rows = rows;
            ptr -> cols = cols;
            return ptr;
        }
    }
    return NULL;
}

void img_destroy(img_t* im){
    if(im != NULL){
        int cols = im -> cols;
        for(int i=0; i<cols; i++){
            free(im -> pixels[i]);
        }
        free(im -> pixels);
        free(im);
    }
}

img_result_t img_set(img_t* im, unsigned int row, unsigned int col, int val){
    int row_total = im -> rows;
    int col_total = im -> cols;
    const int empty = 0;
    if(im == NULL){
        return IMG_BADARRAY;
    }
    if(row < empty || row >= row_total){
        return IMG_BADROW;
    }
    if(col < empty || col >= col_total){
        return IMG_BADCOL;
    }
    im -> pixels[row][col] = val;
    return IMG_OK;
}

img_result_t img_get(const img_t* im, unsigned int row, unsigned int col, int* val){
    int row_total = im -> rows;
    int col_total = im -> cols;
    int empty = 0;
    if(im == NULL){
        return IMG_BADARRAY;
    }
    if(row < empty || row >= row_total){
        return IMG_BADROW;
    }
    if(col < empty || col >= col_total){
        return IMG_BADCOL;
    }
    if(val == NULL){
        return IMG_BADINPUT;
    }
    *val = im -> pixels[row][col];
    return IMG_OK;
}


int img_save_json(img_t* im, const char* filename){
    if (im == NULL || filename == NULL){
        return 1;
    }
    FILE* f = fopen(filename, "w");

    if (f == NULL){
        return 2;
    }

    fprintf(f, "[");
    for(int i=0; i<im->rows; i++){
        fprintf(f, "[");
        for(int j=0; j< im->cols;j++){
            if(j == im->cols-1){
                fprintf(f, "%d", im -> pixels[i][j]);
            }
            else{
                fprintf(f, "%d,", im -> pixels[i][j]);
            }
        }
        if(i == im->rows-1){
            fprintf(f, "]");
        }
        else{
            fprintf(f, "]\n");
        }
    }
    fprintf(f, "]");
    fclose(f);
    return 0;
}
