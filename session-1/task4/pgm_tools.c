/**
 * @file activity3-pgm_tools_refactored.c
 * @brief Tools for manipulating PGM (Portable Gray Map) image files
 * 
 * COMP1850 Structures Activity 3
 * 
 * Your task is to refactor this file to use a PGMImage structure.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pgm_tools.h"

/* TODO: Define a PGMImage structure that encapsulates:
   - width and height
   - max_gray value
   - 2D array of pixel values (pixels)
*/


/* TODO: Update these function prototypes to use your PGMImage structure */
/* Function prototypes */
PGMImage* allocate_image_array(int height, int width);
void free_image_array(PGMImage* image);
//unsigned char **read_pgm_image(const char *filename, int *height, int *width, int *max_gray);
PGMImage* read_pgm_image(const char* filename);
void print_image_info(const char *filename, int height, int width, int max_gray);
//void print_image_values(unsigned char **pixels, int height, int width);
void print_image_values(PGMImage* image);
//unsigned char **invert_image_colors(unsigned char **original_image, int height, int width, int max_gray);
PGMImage* invert_image_colors(PGMImage* original_image);
//unsigned char **rotate_image(unsigned char **original_image, int height, int width, int degrees);
PGMImage* rotate_image(PGMImage* original_image,int degrees);
//int save_pgm_image(const char *filename, unsigned char **pixels, int height, int width, int max_gray);
int save_pgm_image(const char* filename, PGMImage* image);
int get_user_menu_choice(const char *message);
void display_menu(void);

int main(int argc, char** argv)
{
    // Check command line arguments
    if(argc!=2)
	{
        printf("Usage: %s <image_path>\n", argv[0]);
        return 1;
    }

    // TODO: Refactor this section to use your PGMImage structure
    // Variables to store image dimensions and max gray value
    PGMImage* image;
    
    // Read the image
    image=read_pgm_image(argv[1]);
    
    // Check if image reading was successful
    if(image==NULL)
	{
        return 1;
    }
    
    // Display image information
    print_image_info(argv[1], image->height, image->width, image->maxGrey);

    int choice=-1;
    char output_filename[100];
    int rotation_degrees;
    PGMImage* processed_image=NULL;

    // Main program loop
    while(1)
	{
        choice=-1;
        display_menu();
        while (choice<1) choice=get_user_menu_choice("Enter choice");

        switch (choice)
		{
			case 1: 
				// View image
				print_image_values(image);
				break;
            
			case 2: 
				// Invert image
				// TODO: Refactor this section to use your PGMImage structure
				printf("Inverting image colours...\n");
				processed_image=invert_image_colors(image);
				
				printf("Enter output filename: ");
				scanf("%99s", output_filename);
				getchar(); // Consume newline
				
				if(save_pgm_image(output_filename, processed_image))
				{
					printf("Inverted image saved to %s\n", output_filename);
				}
				else
				{
					printf("Failed to save inverted image\n");
				}
				
				// Free the processed image memory
				free_image_array(processed_image);
				break;
            
			case 3:
				// Rotate image
				// TODO: Refactor this section to use your PGMImage structure
				printf("Enter rotation in degrees (90, 180, or 270): ");
				scanf("%d",&rotation_degrees);
				getchar(); // Consume newline
				
				// Validate rotation degrees
				if(rotation_degrees!=90&&rotation_degrees!=180&&rotation_degrees!=270)
				{
					printf("Invalid rotation angle. Please use 90, 180, or 270 degrees.\n");
					break;
				}
				
				printf("Rotating image by %d degrees...\n", rotation_degrees);
				processed_image=rotate_image(image, rotation_degrees);
				
				printf("Enter output filename: ");
				scanf("%99s", output_filename);
				getchar(); // Consume newline
				
				// For 90 and 270 degree rotations, height and width are swapped
				if(rotation_degrees==90||rotation_degrees==270)
				{
					if(save_pgm_image(output_filename,processed_image))
					{
						printf("Rotated image saved to %s\n", output_filename);
					}
					else
					{
						printf("Failed to save rotated image\n");
					}
					free_image_array(processed_image);
				}
				else
				{
					// 180 degrees
					if(save_pgm_image(output_filename, processed_image))
					{
						printf("Rotated image saved to %s\n", output_filename);
					}
					else
					{
						printf("Failed to save rotated image\n");
					}
					free_image_array(processed_image);
				}
				break;
            
			case 4: /* Quit */
				printf("Exiting program...\n");
				/* Free the original image memory before exiting */
				free_image_array(image);
				return 0;
            
			default:
				printf("Invalid choice, please try again\n");
				break;
        }
    }
}

/**
 * @brief Gets user menu choice from standard input
 * 
 * @param message The prompt message to display
 * @return int The user's choice, or -1 if invalid input
 */
int get_user_menu_choice(const char *message)
{
    char buffer[100];
    int choice;
    printf("%s: ", message);
    fgets(buffer, 100, stdin);
    int check = sscanf(buffer, "%d", &choice);
    if (!check) {
        return -1;
    }
    return choice;
}

/**
 * @brief Displays the main program menu
 */
void display_menu(void)
{
    printf("\n----- PGM Image Tool Menu -----\n");
    printf("1 - View PGM Image\n");
    printf("2 - Invert Image\n");
    printf("3 - Rotate Image\n");
    printf("4 - Quit\n");
}

/**
 * @brief Allocates a 2D array for storing the image pixels
 * 
 * @param height Number of rows in the image
 * @param width Number of columns in the image
 * @return unsigned char** 2D array of image pixels, or NULL if allocation fails
 */
PGMImage* allocate_image_array(int height, int width)
{
    /* TODO: Refactor this to use your PGMImage structure */
	/* Allocate memory for the image structure */
	PGMImage* image=(PGMImage*)malloc(sizeof(PGMImage));
	if(image==NULL)
	{
        printf("Error: Memory allocation failed for image\n");
		return NULL;
	}

	/* Allocate memory for the rows */
	image->pixels=(unsigned char**)malloc(height*sizeof(unsigned char*));
	if(image->pixels==NULL)
	{
        printf("Error: Memory allocation failed for image array\n");
		free(image);
		return NULL;
	}

	/* Allocate memory for each row */
	for(int i=0;i<height;i++)
	{
		image->pixels[i]=(unsigned char*)malloc(width*sizeof(unsigned char));
		if(image->pixels[i]==NULL)
		{
            printf("Error: Memory allocation failed for image row %d\n", i);
			for(int j=0;j<i;j++)
			{
				free(image->pixels[j]);
			}
			free(image->pixels);
			free(image);
			return NULL;
		}
	}
	image->height=height;
	image->width=width;
    return image;
}

/*unsigned char** allocate_image_array(int height, int width)
{
    //TODO: Refactor this to use your PGMImage structure
    unsigned char **array = calloc(height, sizeof(unsigned char *));
    if (array == NULL)
	{
        printf("Error: Memory allocation failed for image array\n");
        return NULL;
    }
    
    for (int i = 0; i < height; i++)
	{
        array[i] = calloc(width, sizeof(unsigned char));
        if (array[i] == NULL) {
            //Free previously allocated memory if this allocation fails
            for (int j = 0; j < i; j++) {
                free(array[j]);
            }
            free(array);
            printf("Error: Memory allocation failed for image row %d\n", i);
            return NULL;
        }
    }

    return array;
}*/

/**
 * @brief Frees memory allocated for a 2D image array
 * 
 * @param image The 2D image array to free
 * @param height Number of rows in the image
 */
void free_image_array(PGMImage* image)
{
    //TODO: Refactor this to use your PGMImage structure
    if(image==NULL) return;
	if(image->pixels==NULL)
	{
		//if the image isn't null but the array is
		//free(image); //not sure if this should be freed
		return;
	}

    for(int i=0;i<image->height;i++)
	{
        free(image->pixels[i]);
    }
	free(image->pixels);
    free(image);
}

/*void free_image_array(unsigned char **image, int height)
{
    //TODO: Refactor this to use your PGMImage structure
    if (image == NULL) return;
    
    for (int i = 0; i < height; i++)
	{
        free(image[i]);
    }
    free(image);
}*/

/**
 * @brief Reads a PGM image from a file
 * 
 * @param filename Path to the PGM file
 * @param height Pointer to store the image height
 * @param width Pointer to store the image width
 * @param max_gray Pointer to store the max gray value
 * @return unsigned char** 2D array of image pixels, or NULL if reading fails
 */
PGMImage* read_pgm_image(const char* filename)
{
    //TODO: Refactor this to use your PGMImage structure
    FILE* file=fopen(filename, "r");
    if(file==NULL)
	{
        printf("Error: Could not open file %s\n",filename);
        return NULL;
    }
    
    // Read PGM header
    char magic_number[3];
    if(fscanf(file, "%2s", magic_number)!=1)
	{
        printf("Error: Invalid PGM file format\n");
        fclose(file);
        return NULL;
    }
    
    if(strcmp(magic_number,"P2")!=0)
	{
        printf("Error: File is not a valid PGM file (P2 format)\n");
        fclose(file);
        return NULL;
    }
    
	int width;
	int height;
    if(fscanf(file,"%d %d",width,height)!=2)
	{
        printf("Error: Could not read image dimensions\n");
        fclose(file);
        return NULL;
    }
    
	int max_grey;
    if(fscanf(file,"%d",max_grey)!=1)
	{
        printf("Error: Could not read max gray value\n");
        fclose(file);
        return NULL;
    }
    
    // Allocate memory for the pixel array
    PGMImage* image=allocate_image_array(height,width);
    if(image==NULL)
	{
        fclose(file);
        return NULL;
    }
    
    //Read pixel values
    int pixel_value;
    for(int i=0;i<height;i++)
	{
        for(int j=0;j<width;j++)
		{
            if(fscanf(file,"%d",&pixel_value)!=1)
			{
                printf("Error: Could not read pixel value at position (%d,%d)\n",j,i);
                free_image_array(image);
                fclose(file);
                return NULL;
            }
            image->pixels[i][j]=(unsigned char)pixel_value;
        }
    }
    
    fclose(file);
	image->height=height;
	image->width=width;
	image->maxGrey=max_grey;
    return image;
}

/*unsigned char** read_pgm_image(const char* filename, int *height, int *width, int *max_gray)
{
    //TODO: Refactor this to use your PGMImage structure
    FILE* file=fopen(filename, "r");
    if(file==NULL)
	{
        printf("Error: Could not open file %s\n",filename);
        return NULL;
    }
    
    // Read PGM header
    char magic_number[3];
    if(fscanf(file, "%2s", magic_number)!=1)
	{
        printf("Error: Invalid PGM file format\n");
        fclose(file);
        return NULL;
    }
    
    if(strcmp(magic_number,"P2")!=0)
	{
        printf("Error: File is not a valid PGM file (P2 format)\n");
        fclose(file);
        return NULL;
    }
    
    if(fscanf(file,"%d %d",width,height)!=2)
	{
        printf("Error: Could not read image dimensions\n");
        fclose(file);
        return NULL;
    }
    
    if(fscanf(file,"%d",max_gray)!=1)
	{
        printf("Error: Could not read max gray value\n");
        fclose(file);
        return NULL;
    }
    
    // Allocate memory for the pixel array
    unsigned char** pixels=allocate_image_array(*height,*width);
    if(pixels==NULL)
	{
        fclose(file);
        return NULL;
    }
    
    //Read pixel values
    int pixel_value;
    for(int i=0;i<*height;i++)
	{
        for(int j=0;j<*width;j++)
		{
            if(fscanf(file,"%d",&pixel_value)!=1)
			{
                printf("Error: Could not read pixel value at position (%d,%d)\n",j,i);
                free_image_array(pixels,*height);
                fclose(file);
                return NULL;
            }
            pixels[i][j]=(unsigned char)pixel_value;
        }
    }
    
    fclose(file);
    return pixels;
}*/

/**
 * @brief Prints information about the PGM image
 * 
 * @param filename Name of the image file
 * @param height Image height
 * @param width Image width
 * @param max_gray Maximum gray value
 */
void print_image_info(const char* filename, int height, int width, int max_gray)
{
    /* TODO: Refactor this to use your PGMImage structure */
    printf("Image: %s\n", filename);
    printf("Dimensions: %d x %d pixels\n", width, height);
    printf("Max Gray Value: %d\n", max_gray);
}

/**
 * @brief Prints the pixel values of the image
 * 
 * @param pixels The 2D array of image pixels
 * @param height Image height
 * @param width Image width
 */
void print_image_values(PGMImage* image)
{
    printf("\nImage Pixel Values (%dx%d):\n", image->width, image->height);
    for(int i=0;i<image->height;i++)
	{
        for(int j=0;j<image->width;j++)
		{
            printf("%3d ",image->pixels[i][j]);
        }
        printf("\n");
    }
}

/*void print_image_values(unsigned char** pixels, int height, int width)
{
    // TODO: Refactor this to use your PGMImage structure
    printf("\nImage Pixel Values (%dx%d):\n", width, height);
    for(int i=0;i<height;i++)
	{
        for(int j=0;j<width;j++)
		{
            printf("%3d ",pixels[i][j]);
        }
        printf("\n");
    }
}*/



/**
 * @brief Inverts the colours of the image (255-value)
 * 
 * @param original_image Original image pixels
 * @param height Image height
 * @param width Image width
 * @param max_gray Maximum gray value
 * @return unsigned char** New image with inverted colours
 */
PGMImage* invert_image_colors(PGMImage* original_image)
{
	int height=original_image->height;
	int width=original_image->width;
	int max_grey=original_image->maxGrey;
    /* TODO: Refactor this to use your PGMImage structure */
    /* Allocate memory for the inverted image */
    PGMImage* inverted_image=allocate_image_array(height,width);
    if(inverted_image==NULL)
	{
        return NULL;
    }
    
    /* Invert each pixel (max_gray - value) */
    for(int i=0;i<height;i++)
	{
        for(int j=0;j<width;j++)
		{
            inverted_image->pixels[i][j]=max_grey-original_image->pixels[i][j];
        }
    }
    
    return inverted_image;
}

/*unsigned char** invert_image_colors(unsigned char** original_image, int height, int width, int max_gray)
{
    // TODO: Refactor this to use your PGMImage structure
    // Allocate memory for the inverted image
    unsigned char** inverted_image=allocate_image_array(height, width);
    if(inverted_image==NULL)
	{
        return NULL;
    }
    
    // Invert each pixel (max_gray - value)
    for(int i=0;i<height;i++)
	{
        for(int j=0;j<width;j++)
		{
            inverted_image[i][j]=max_gray-original_image[i][j];
        }
    }
    
    return inverted_image;
}*/

/**
 * @brief Rotates the image by the specified angle
 * 
 * @param original_image Original image pixels
 * @param height Image height
 * @param width Image width
 * @param degrees Rotation angle (90, 180, or 270 degrees)
 * @return unsigned char** New rotated image
 */
PGMImage* rotate_image(PGMImage* original_image,int degrees)
{
    /* TODO: Refactor this to use your PGMImage structure */
    PGMImage* rotated_image;
	int height=original_image->height;
	int width=original_image->width;
    
    switch(degrees)
	{
        case 90:
            /* For 90 degrees, width and height are swapped */
            rotated_image=allocate_image_array(width, height);
            if(rotated_image==NULL)
			{
                return NULL;
            }
            
            /* 90 degree rotation algorithm */
            for(int i=0;i<height;i++)
			{
                for(int j=0;j<width;j++)
				{
                    rotated_image->pixels[j][height-1-i]=original_image->pixels[i][j];
                }
            }
            break;
            
        case 180:
            rotated_image=allocate_image_array(height, width);
            if(rotated_image==NULL)
			{
                return NULL;
            }
            
            /* 180 degree rotation algorithm */
            for(int i=0;i<height;i++)
			{
                for(int j=0;j<width;j++)
				{
                    rotated_image->pixels[height-1-i][width-1-j]=original_image->pixels[i][j];
                }
            }
            break;
            
        case 270:
            /* For 270 degrees, width and height are swapped */
            rotated_image=allocate_image_array(width, height);
            if(rotated_image==NULL)
			{
                return NULL;
            }
            
            /* 270 degree rotation algorithm */
            for(int i=0;i<height;i++)
			{
                for(int j=0;j<width;j++)
				{
                    rotated_image->pixels[width-1-j][i]=original_image->pixels[i][j];
                }
            }
            break;
            
        default:
            printf("Error: Invalid rotation angle\n");
            return NULL;
    }
    
    return rotated_image;
}

/*unsigned char** rotate_image(unsigned char** original_image,int height,int width,int degrees)
{
    //TODO: Refactor this to use your PGMImage structure
    unsigned char** rotated_image;
    
    switch(degrees)
	{
        case 90:
            // For 90 degrees, width and height are swapped
            rotated_image=allocate_image_array(width, height);
            if(rotated_image==NULL)
			{
                return NULL;
            }
            
            // 90 degree rotation algorithm
            for(int i=0;i<height;i++)
			{
                for(int j=0;j<width;j++)
				{
                    rotated_image[j][height-1-i]=original_image[i][j];
                }
            }
            break;
            
        case 180:
            rotated_image=allocate_image_array(height, width);
            if(rotated_image==NULL)
			{
                return NULL;
            }
            
            // 180 degree rotation algorithm
            for(int i=0;i<height;i++)
			{
                for(int j=0;j<width;j++)
				{
                    rotated_image[height-1-i][width-1-j]=original_image[i][j];
                }
            }
            break;
            
        case 270:
            // For 270 degrees, width and height are swapped
            rotated_image=allocate_image_array(width, height);
            if(rotated_image==NULL)
			{
                return NULL;
            }
            
            // 270 degree rotation algorithm
            for(int i=0;i<height;i++)
			{
                for(int j=0;j<width;j++)
				{
                    rotated_image[width-1-j][i]=original_image[i][j];
                }
            }
            break;
            
        default:
            printf("Error: Invalid rotation angle\n");
            return NULL;
    }
    
    return rotated_image;
}*/

/**
 * @brief Saves a PGM image to a file
 * 
 * @param filename Output filename
 * @param pixels Image pixel array
 * @param height Image height
 * @param width Image width
 * @param max_gray Maximum gray value
 * @return int 1 if successful, 0 if failed
 */
int save_pgm_image(const char* filename, PGMImage* image)
{
	int height=image->height;
	int width=image->width;
	int max_grey=image->maxGrey;
    // TODO: Refactor this to use your PGMImage structure
    FILE* file=fopen(filename,"w");
    if(file==NULL)
	{
        printf("Error: Could not create output file %s\n",filename);
        return 0;
    }
    
    // Write PGM header
    fprintf(file, "P2\n");
    fprintf(file, "%d %d\n", width, height);
    fprintf(file, "%d\n", max_grey);
    
    /* Write pixel values */
    for(int i=0;i<height;i++)
	{
        for(int j=0;j<width;j++)
		{
            fprintf(file,"%d ",image->pixels[i][j]);
        }
        fprintf(file,"\n");
    }
    
    fclose(file);
    return 1;
}

/*int save_pgm_image(const char* filename, unsigned char** pixels, int height, int width, int max_gray)
{
    // TODO: Refactor this to use your PGMImage structure
    FILE* file=fopen(filename,"w");
    if(file==NULL)
	{
        printf("Error: Could not create output file %s\n",filename);
        return 0;
    }
    
    // Write PGM header
    fprintf(file, "P2\n");
    fprintf(file, "%d %d\n", width, height);
    fprintf(file, "%d\n", max_gray);
    
    // Write pixel values
    for(int i=0;i<height;i++)
	{
        for(int j=0;j<width;j++)
		{
            fprintf(file,"%d ",pixels[i][j]);
        }
        fprintf(file,"\n");
    }
    
    fclose(file);
    return 1;
}*/