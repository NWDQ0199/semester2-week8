//given
typedef struct PGMImage
{
    int width;
    int height;
    int maxGray;
    unsigned char** pixels;  /* 2D array of pixel values */
}
PGMImage;