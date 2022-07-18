#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "t1img.h"

// DECLARATIONS OF FUNCTIONS FROM PREVIOUS ASSIGNMENT 

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

// END OF PREVIOUS FUNCTION DECLARATIONS

int img_save_binary(img_t* im, const char* filename){

    if( im == NULL || filename == NULL){
        return 1;
    }

    FILE* f = fopen(filename, "w");

    if(f == NULL){
        return 2;
    }

    if(fwrite(&im -> rows, sizeof(unsigned int), 1, f) != 1){
        return 3;
    }
    if(fwrite(im -> pixels, sizeof(uint8_t*), im->rows, f) != im -> rows){
        return 4;
    }

    if(fwrite(&im -> cols, sizeof(unsigned int), 1, f) != 1){
        return 5;
    }
    for(int i=0; i<im->rows; i++){
        if(fwrite(im -> pixels[i], sizeof(uint8_t), im -> cols, f) != im -> cols){
            return 6;
        }
    }

    fclose(f);
    return 0;
}

img_t* img_load_binary(const char* filename){

    if (filename == NULL){
        return NULL;
    }

    FILE* f = fopen(filename, "r");

    img_t* im = malloc(sizeof(img_t));
    
    if(fread(&im -> rows, sizeof(unsigned int), 1, f) != 1){
       return NULL; 
    }
    im -> pixels = malloc(sizeof(uint8_t*)*im->rows);
    if(fread(im -> pixels, sizeof(uint8_t*), im->rows, f) != im -> rows){
        return NULL;
    }

    if(fread(&im -> cols, sizeof(unsigned int), 1, f) != 1){
        return NULL;
    }
    for(int i=0; i<im->rows; i++){
        im -> pixels[i] = malloc(sizeof(uint8_t)*im->cols);
    }    
    for(int i=0; i<im->rows; i++){
        if(fread(im -> pixels[i], sizeof(uint8_t), im -> cols, f) != im -> cols){
            return NULL;
        }
    }

    fclose(f);
    return im;
}