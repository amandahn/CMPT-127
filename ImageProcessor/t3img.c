// author: Amanda Ngo 
// date: July 19, 2021
// last modified: July 18, 2022
// description: Create a program to save an image object as a .ppm file

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "PPMImage.h" 

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

int img_save_ppm(img_t* im, const char* filename) {

    if(im == NULL || filename == NULL){
        return 1;
    }
    FILE* f = fopen(filename, "wb");
    fprintf(f, "P3\n");
    fprintf(f, "%d ", im->cols);
    fprintf(f, "%d",im->rows);
    fprintf(f, "\n");
    fprintf(f, "255\n");
   
    static unsigned char color[3];
    int val = 0;
    for(int i=0; i<im->rows; i++){
        for(int j=0; j< im->cols; j++){
            if(im->pixels[i][j] >= 0 && im->pixels[i][j] <= 255){
                int val = im -> pixels[i][j];
                color[0] = val;  /* red */
                color[1] = val;  /* green */
                color[2] = val;  /* blue */ 
                if(val < 10){
                    fprintf(f, "%d   %d   %d  ", color[0], color[1], color[2]);
                }
                if(val > 10 && val < 100){
                    fprintf(f, "%d  %d  %d ", color[0], color[1], color[2]);
                }
                if(val > 100){
                    fprintf(f, "%d %d %d", color[0], color[1], color[2]);
                }
            }
            else{
                return 2;
            }
            if(val < 10){
                fprintf(f, "   ");
            }
            if(val > 10 && val < 100){
                fprintf(f, "  ");
            }
            if(val > 100){
                fprintf(f, " ");
            }
        }
        fprintf(f,"\n");
    }

    fclose(f);
    return 0;
}
