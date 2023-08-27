#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_BRUSH_SIZE ((unsigned short) 600)
#define MAX_TEXTURE_LENGTH ((unsigned char) 255)
int minX = -700, maxX = 700, size = 8, spacing = 2;
//minX - The minimum X value
//maxX - The maximum X value
//size - The size of the plot point (cod units)
//spacing - Increment through X values by this amount. Cannot be <= 0

double f(double x) {
    return x * x * (x/10000); //REPLACE RETURN FUNCTION HERE
    //return sin((x/100))*100;
    // replace with user input at some point
}

struct brush6 {
    int x, y, z, l, w, h;
    char texture[MAX_TEXTURE_LENGTH];

    // generated data
    char *bottomPlane;
    char *topPlane;
    char *sidePlane1;
    char *sidePlane2;
    char *sidePlane3;
    char *sidePlane4;
};

void printBrush6(struct brush6 *b) {
    printf("%s\n%s\n%s\n%s\n%s\n%s", b->bottomPlane, b->topPlane, b->sidePlane1, b->sidePlane2, b->sidePlane3,
           b->sidePlane4);
}

void genBrush6(struct brush6 *b) {
    char footer[] = "64 64 0 0 0 0 lightmap_gray 16384 16384 0 0 0 0";
    char format[] = " ( %d %d %d ) ( %d %d %d ) ( %d %d %d ) %s %s";

    //calculate the length of the formatted string
    int len = snprintf(NULL, 0, format,
                       b->l + b->x,
                       b->w + b->y,
                       b->z, // line1
                       b->x,
                       b->w + b->y,
                       b->z, // line2
                       b->x,
                       b->y,
                       b->z, // line3
                       b->texture,
                       footer);
    len++; //add 1 for the null-terminator

    // Allocate memory for the planes
    b->bottomPlane = (char *)malloc(len * sizeof(char));
    b->topPlane = (char *)malloc(len * sizeof(char));
    b->sidePlane1 = (char *)malloc(len * sizeof(char));
    b->sidePlane2 = (char *)malloc(len * sizeof(char));
    b->sidePlane3 = (char *)malloc(len * sizeof(char));
    b->sidePlane4 = (char *)malloc(len * sizeof(char));

    // Generate the planes
    snprintf(b->bottomPlane, len, format,
             b->l + b->x,
             b->w + b->y,
             b->z, // line1
             b->x,
             b->w + b->y,
             b->z, // line2
             b->x,
             b->y,
             b->z, // line3
             b->texture,
             footer);

    snprintf(b->topPlane, len, format,
             b->x,
             b->y,
             b->h + b->z, // line1
             b->x,
             b->w + b->y,
             b->h + b->z, // line2
             b->l + b->x,
             b->w + b->y,
             b->h + b->z, // line3
             b->texture,
             footer);

    snprintf(b->sidePlane1, len, format,
             b->x,
             b->y,
             b->h + b->z, // line1
             b->l + b->x,
             b->y,
             b->h + b->z, // line2
             b->l + b->x,
             b->y,
             b->z, // line3
             b->texture,
             footer);

    snprintf(b->sidePlane2, len, format,
             b->l + b->x,
             b->y,
             b->h + b->z, // line1
             b->l + b->x,
             b->w + b->y,
             b->h + b->z, // line2
             b->l + b->x,
             b->w + b->y,
             b->z, // line3
             b->texture,
             footer);

    snprintf(b->sidePlane3, len, format,
             b->l + b->x,
             b->y + b->w,
             b->h + b->z, // line1
             b->x,
             b->w + b->y,
             b->h + b->z, // line2
             b->x,
             b->w + b->y,
             b->z, // line3
             b->texture,
             footer);

    snprintf(b->sidePlane4, len, format,
             b->x,
             b->y + b->w,
             b->h + b->z, // line1
             b->x,
             b->y,
             b->h + b->z, // line2
             b->x,
             b->y,
             b->z, // line3
             b->texture,
             footer);
}

struct brush6 *createBrush6(int l, int w, int h, int x, int y, int z, char *texture) {
    struct brush6 *b = malloc(sizeof(struct brush6));
    b->l = l;
    b->w = w;
    b->h = h;
    b->x = x;
    b->y = y;
    b->z = z;
    strcpy(b->texture, texture);
    return b;
}

int main() {
    if(spacing <= 0) {
        printf("Spacing too small");
        return 1;
    }
    for (int x = minX; x < maxX; x+=spacing) {
        struct brush6 *b = createBrush6(size, size, size, x, f(x), 0, "caulk");
        genBrush6(b);
        printf("{\n");
        printBrush6(b);
        printf("\n}\n");

        //free the allocated memory
        free(b->bottomPlane);
        free(b->topPlane);
        free(b->sidePlane1);
        free(b->sidePlane2);
        free(b->sidePlane3);
        free(b->sidePlane4);
        free(b);
    }
    return 0;
}
