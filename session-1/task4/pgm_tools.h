//given
typedef struct PGMImage
{
    int width;
    int height;
    int maxGrey;
    unsigned char** pixels;  /* 2D array of pixel values */
}
PGMImage;