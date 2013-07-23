#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL/glaux.h>		//Used for loading the textures
#include <windows.h>
#include <gl/glext.h>

#include <stdio.h>

#include <iostream>
#include <string.h>

using namespace std;

float object01_limits[6];
float object01_center[3];
float object01_size;
int Animated = 0;
int Wireframe = 0;
GLfloat rotLx = 0.0f; 
GLfloat rotLy = 0.0f;
GLfloat rotLz = 0.0f;
static GLfloat xRot = 0.0f;
static GLfloat yRot = 0.0f;

char path[50];
int pointerPath = 0;

//Background
GLuint bg1[2];  //belakang
GLuint bg2[2]; //samping kanan & kiri
GLuint bg3[2]; //lantai

//Kepala
GLuint texturekepala1[2]; //Muka
GLuint texturekepala2[2]; //Samping Kanan
GLuint texturekepala3[2]; //Belakang
GLuint texturekepala4[2]; //Samping Kiri
GLuint texturekepala5[2]; //Atas
GLuint texturekepala6[2]; //Bawah

//Kepala Yui
GLuint texturekepalaYui1[2]; //Muka
GLuint texturekepalaYui2[2]; //Samping Kanan
GLuint texturekepalaYui3[2]; //Belakang
GLuint texturekepalaYui4[2]; //Samping Kiri
GLuint texturekepalaYui5[2]; //Atas

//Kepala Mugi
GLuint texturekepalaMugi1[2]; //Muka
GLuint texturekepalaMugi2[2]; //Samping Kanan
GLuint texturekepalaMugi3[2]; //Belakang
GLuint texturekepalaMugi4[2]; //Samping Kiri
GLuint texturekepalaMugi5[2]; //Atas

//Badan Mio
GLuint texturebadan1[2]; //Depan
GLuint texturebadan2[2]; //Kanan
GLuint texturebadan3[2]; //Belakang
GLuint texturebadan4[2]; //Kiri
GLuint texturebadan5[2]; //Bawah

//Badan Yui
GLuint texturebadanYui1[2]; //Depan
GLuint texturebadanYui2[2]; //Belakang
GLuint texturebadanYui3[2]; //Bawah

//Badan Mugi
GLuint texturebadanMugi1[2]; //Depan
GLuint texturebadanMugi2[2]; //Kanan
GLuint texturebadanMugi3[2]; //Belakang

//Rok
GLuint textureRok[2]; //Depan

//Kaki
GLuint textureKaki1[2]; //Depan
GLuint textureKaki2[2]; //Samping
GLuint textureKaki3[2]; //Belakang

//Kaki Yui
GLuint textureKakiYui1[2]; //Depan
GLuint textureKakiYui2[2]; //Samping
GLuint textureKakiYui3[2]; //Belakang

//Kaki Mugi
GLuint textureKakiMugi1[2]; //Depan
GLuint textureKakiMugi2[2]; //Samping
GLuint textureKakiMugi3[2]; //Belakang

//Tangan Kanan
GLuint textureTangan1[2]; //Atas
GLuint textureTangan2[2]; //Kanan
GLuint textureTangan3[2]; //Bawah
GLuint textureTangan4[2]; //Bahu
GLuint textureTangan5[2]; //Jari

//Tangan Kiri
GLuint textureTangan7[2]; //Atas
GLuint textureTangan8[2]; //Kanan
GLuint textureTangan9[2]; //Bawah
GLuint textureTangan10[2]; //depan
GLuint textureTangan11[2]; //belakang

//Background
/*Image Belakang
  Image2 Samping Kanan & Kiri
  Image3 Lantai
*/
struct Background {
unsigned long sizeX;
unsigned long sizeY;
char *data;
};

//Kepala
/*Kepala1 Muka
  Kepala2 Samping Kanan
  Kepala3 Belakang
  Kepala4 Samping Kiri
  Kepala5 Atas
  Kepala6 Bawah
*/
struct Kepala {
unsigned long sizeX;
unsigned long sizeY;
char *data;
};

//Badan
/*Badan1 Depan
  Badan2 Samping Kanan
  Badan3 Belakang
  Badan4 Samping Kiri
  Badan5 Bawah
*/
struct Badan {
unsigned long sizeX;
unsigned long sizeY;
char *data;
};

//Rok
struct Rok {
unsigned long sizeX;
unsigned long sizeY;
char *data;
};

//Kaki
/*Kaki1 Depan
  Kaki2 Samping
  Kaki3 Belakang
*/
struct Kaki {
unsigned long sizeX;
unsigned long sizeY;
char *data;
};

//Tangan
/*Tangan1 Depan
  Tangan2 Samping
  Tangan3 Belakang
  Tangan4
  Tangan5
*/
struct Tangan {
unsigned long sizeX;
unsigned long sizeY;
char *data;
};

//Background
typedef struct Background Image,Image2,Image3;

//Kepala
typedef struct Kepala Kepala1,Kepala2,Kepala3,Kepala4,Kepala5,Kepala6,KepalaMugi1,KepalaMugi2,KepalaMugi3,KepalaMugi4,KepalaMugi5,KepalaMugi6,KepalaYui1,KepalaYui2,KepalaYui3,KepalaYui4,KepalaYui5;

//Badan
typedef struct Badan Badan1,Badan2,Badan3,Badan4,Badan5,BadanMugi1,BadanMugi2,BadanMugi3,BadanYui1,BadanYui2,BadanYui3,;

//Rok
typedef struct Rok Rok;

//Kaki
typedef struct Kaki Kaki1, Kaki2, Kaki3, KakiMugi1, KakiMugi2, KakiMugi3, KakiYui1, KakiYui2, KakiYui3;

//Tangan Kanan
typedef struct Tangan Tangan1, Tangan2, Tangan3, Tangan4, Tangan5;

//Tangan Kiri
typedef struct Tangan Tangan7, Tangan8, Tangan9, Tangan10, Tangan11;

#define checkImageWidth 600
#define checkImageHeight 600

GLubyte checkImage[checkImageWidth][checkImageHeight][3];

void makeCheckImage(void) {
    int i, j, c;
    for (i = 0; i < checkImageWidth; i++) {
        for (j = 0; j < checkImageHeight; j++) {
            c = ((((i&0x8)==0)^((j&0x8)==0)))*255;
            checkImage[i][j][0] = (GLubyte) c;
            checkImage[i][j][1] = (GLubyte) c;
            checkImage[i][j][2] = (GLubyte) c;
        }
    }
}

//[Image1]
int ImageLoad(char *filename, Image *image) {
    FILE *file;
    unsigned long size; // ukuran gambar dalam bytes.
    unsigned long i; // standard counter.
    unsigned short int planes; // jumlah of ukuran dalam gambar (harus 1)
    unsigned short int bpp; // jumlah byte per pixel (harus 24)
    char temp; // penyimpanan sementara untuk konversi warna bgr-rgb.
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&image->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&image->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // menghitung ukuran (dengan asumsi 24 bit atau 3 byte per pixel).
    size = image->sizeX * image->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    image->data = (char *) malloc(size);
    if (image->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(image->data, size, 1, file)) != 1) {
    printf("Error reading image data from %s.\n", filename);
    return 0;
    }
    for (i=0;i<size;i+=3) { // membalikkan semua warna. (bgr -> rgb)
        temp = image->data[i];
        image->data[i] = image->data[i+2];
        image->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[Image2]
int ImageLoad2 (char *filename, Image2 *image2) {
    FILE *file;
    unsigned long size; // ukuran gambar dalam bytes.
    unsigned long i; // standard counter.
    unsigned short int planes; // jumlah of ukuran dalam gambar (harus 1)
    unsigned short int bpp; // jumlah byte per pixel (harus 24)
    char temp; // penyimpanan sementara untuk konversi warna bgr-rgb.
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&image2->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&image2->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // menghitung ukuran (dengan asumsi 24 bit atau 3 byte per pixel).
    size = image2->sizeX * image2->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    image2->data = (char *) malloc(size);
    if (image2->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(image2->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = image2->data[i];
        image2->data[i] = image2->data[i+2];
        image2->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[Image3]
int ImageLoad3 (char *filename, Image3 *image3) {
    FILE *file;
    unsigned long size; 
    unsigned long i; .
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&image3->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&image3->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = image3->sizeX * image3->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    image3->data = (char *) malloc(size);
    if (image3->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(image3->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = image3->data[i];
        image3->data[i] = image3->data[i+2];
        image3->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[Kepala1] Muka
int ImageLoadKepala1 (char *filename, Kepala1 *kepala1) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; // temporary color storage for bgr-rgb conversion.
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&kepala1->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&kepala1->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = kepala1->sizeX * kepala1->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    kepala1->data = (char *) malloc(size);
    if (kepala1->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(kepala1->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = kepala1->data[i];
        kepala1->data[i] = kepala1->data[i+2];
        kepala1->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[Kepala2] Samping Kanan
int ImageLoadKepala2 (char *filename, Kepala2 *kepala2) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&kepala2->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&kepala2->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = kepala2->sizeX * kepala2->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    kepala2->data = (char *) malloc(size);
    if (kepala2->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(kepala2->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = kepala2->data[i];
        kepala2->data[i] = kepala2->data[i+2];
        kepala2->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[Kepala3] Belakang
int ImageLoadKepala3 (char *filename, Kepala3 *kepala3) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&kepala3->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&kepala3->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = kepala3->sizeX * kepala3->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    kepala3->data = (char *) malloc(size);
    if (kepala3->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(kepala3->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = kepala3->data[i];
        kepala3->data[i] = kepala3->data[i+2];
        kepala3->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[Kepala4] Samping Kiri
int ImageLoadKepala4 (char *filename, Kepala4 *kepala4) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&kepala4->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&kepala4->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = kepala4->sizeX * kepala4->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    kepala4->data = (char *) malloc(size);
    if (kepala4->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(kepala4->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = kepala4->data[i];
        kepala4->data[i] = kepala4->data[i+2];
        kepala4->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[Kepala5] Atas
int ImageLoadKepala5 (char *filename, Kepala5 *kepala5) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&kepala5->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&kepala5->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = kepala5->sizeX * kepala5->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    kepala5->data = (char *) malloc(size);
    if (kepala5->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(kepala5->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = kepala5->data[i];
        kepala5->data[i] = kepala5->data[i+2];
        kepala5->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[Kepala6] Bawah
int ImageLoadKepala6 (char *filename, Kepala6 *kepala6) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&kepala6->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&kepala6->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = kepala6->sizeX * kepala6->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    kepala6->data = (char *) malloc(size);
    if (kepala6->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(kepala6->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = kepala6->data[i];
        kepala6->data[i] = kepala6->data[i+2];
        kepala6->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[KepalaMugi1] Muka
int ImageLoadKepalaMugi1 (char *filename, KepalaMugi1 *kepalaMugi1) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&kepalaMugi1->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&kepalaMugi1->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = kepalaMugi1->sizeX * kepalaMugi1->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    kepalaMugi1->data = (char *) malloc(size);
    if (kepalaMugi1->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(kepalaMugi1->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = kepalaMugi1->data[i];
        kepalaMugi1->data[i] = kepalaMugi1->data[i+2];
        kepalaMugi1->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[KepalaMugi2] Samping Kanan
int ImageLoadKepalaMugi2 (char *filename, KepalaMugi2 *kepalaMugi2) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&kepalaMugi2->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&kepalaMugi2->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = kepalaMugi2->sizeX * kepalaMugi2->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    kepalaMugi2->data = (char *) malloc(size);
    if (kepalaMugi2->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(kepalaMugi2->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = kepalaMugi2->data[i];
        kepalaMugi2->data[i] = kepalaMugi2->data[i+2];
        kepalaMugi2->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[KepalaMugi3] Belakang
int ImageLoadKepalaMugi3 (char *filename, KepalaMugi3 *kepalaMugi3) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&kepalaMugi3->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&kepalaMugi3->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = kepalaMugi3->sizeX * kepalaMugi3->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    kepalaMugi3->data = (char *) malloc(size);
    if (kepalaMugi3->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(kepalaMugi3->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = kepalaMugi3->data[i];
        kepalaMugi3->data[i] = kepalaMugi3->data[i+2];
        kepalaMugi3->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[KepalaMugi4] Samping Kiri
int ImageLoadKepalaMugi4 (char *filename, KepalaMugi4 *kepalaMugi4) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&kepalaMugi4->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&kepalaMugi4->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = kepalaMugi4->sizeX * kepalaMugi4->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    kepalaMugi4->data = (char *) malloc(size);
    if (kepalaMugi4->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(kepalaMugi4->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = kepalaMugi4->data[i];
        kepalaMugi4->data[i] = kepalaMugi4->data[i+2];
        kepalaMugi4->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[KepalaMugi5] Atas
int ImageLoadKepalaMugi5 (char *filename, KepalaMugi5 *kepalaMugi5) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&kepalaMugi5->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&kepalaMugi5->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = kepalaMugi5->sizeX * kepalaMugi5->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    kepalaMugi5->data = (char *) malloc(size);
    if (kepalaMugi5->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(kepalaMugi5->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = kepalaMugi5->data[i];
        kepalaMugi5->data[i] = kepalaMugi5->data[i+2];
        kepalaMugi5->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[KepalaYui1] Muka
int ImageLoadKepalaYui1 (char *filename, KepalaYui1 *kepalaYui1) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&kepalaYui1->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&kepalaYui1->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = kepalaYui1->sizeX * kepalaYui1->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    kepalaYui1->data = (char *) malloc(size);
    if (kepalaYui1->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(kepalaYui1->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = kepalaYui1->data[i];
        kepalaYui1->data[i] = kepalaYui1->data[i+2];
        kepalaYui1->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[KepalaYui2] Samping Kanan
int ImageLoadKepalaYui2 (char *filename, KepalaYui2 *kepalaYui2) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&kepalaYui2->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&kepalaYui2->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = kepalaYui2->sizeX * kepalaYui2->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    kepalaYui2->data = (char *) malloc(size);
    if (kepalaYui2->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(kepalaYui2->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = kepalaYui2->data[i];
        kepalaYui2->data[i] = kepalaYui2->data[i+2];
        kepalaYui2->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[KepalaYui3] Belakang
int ImageLoadKepalaYui3 (char *filename, KepalaYui3 *kepalaYui3) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; .
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&kepalaYui3->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&kepalaYui3->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = kepalaYui3->sizeX * kepalaYui3->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    kepalaYui3->data = (char *) malloc(size);
    if (kepalaYui3->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(kepalaYui3->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = kepalaYui3->data[i];
        kepalaYui3->data[i] = kepalaYui3->data[i+2];
        kepalaYui3->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[KepalaYui4] Samping Kiri
int ImageLoadKepalaYui4 (char *filename, KepalaYui4 *kepalaYui4) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&kepalaYui4->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&kepalaYui4->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = kepalaYui4->sizeX * kepalaYui4->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    kepalaYui4->data = (char *) malloc(size);
    if (kepalaYui4->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(kepalaYui4->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = kepalaYui4->data[i];
        kepalaYui4->data[i] = kepalaYui4->data[i+2];
        kepalaYui4->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[KepalaYui5] Atas
int ImageLoadKepalaYui5 (char *filename, KepalaYui5 *kepalaYui5) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&kepalaYui5->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&kepalaYui5->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = kepalaYui5->sizeX * kepalaYui5->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    kepalaYui5->data = (char *) malloc(size);
    if (kepalaYui5->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(kepalaYui5->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = kepalaYui5->data[i];
        kepalaYui5->data[i] = kepalaYui5->data[i+2];
        kepalaYui5->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[Badan1] Depan
int ImageLoadBadan1 (char *filename, Badan1 *badan1) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&badan1->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, badan1->sizeX);
    
    // read the height
    if ((i = fread(&badan1->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, badan1->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = badan1->sizeX * badan1->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    badan1->data = (char *) malloc(size);
    if (badan1->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(badan1->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = badan1->data[i];
        badan1->data[i] = badan1->data[i+2];
        badan1->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[Badan2] Kanan
int ImageLoadBadan2 (char *filename, Badan2 *badan2) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&badan2->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&badan2->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = badan2->sizeX * badan2->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    badan2->data = (char *) malloc(size);
    if (badan2->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(badan2->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = badan2->data[i];
        badan2->data[i] = badan2->data[i+2];
        badan2->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[Badan3] Belakang
int ImageLoadBadan3 (char *filename, Badan3 *badan3) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&badan3->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&badan3->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = badan3->sizeX * badan3->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    badan3->data = (char *) malloc(size);
    if (badan3->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(badan3->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = badan3->data[i];
        badan3->data[i] = badan3->data[i+2];
        badan3->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[Badan4] Samping Kiri
int ImageLoadBadan4 (char *filename, Badan4 *badan4) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL){
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&badan4->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&badan4->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = badan4->sizeX * badan4->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    badan4->data = (char *) malloc(size);
    if (badan4->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(badan4->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = badan4->data[i];
        badan4->data[i] = badan4->data[i+2];
        badan4->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[Badan5] Bawah
int ImageLoadBadan5 (char *filename, Badan5 *badan5) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes;
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&badan5->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&badan5->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = badan5->sizeX * badan5->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    badan5->data = (char *) malloc(size);
    if (badan5->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(badan5->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = badan5->data[i];
        badan5->data[i] = badan5->data[i+2];
        badan5->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[BadanMugi1] Depan
int ImageLoadBadanMugi1 (char *filename, BadanMugi1 *badanMugi1) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&badanMugi1->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, badan1->sizeX);
    
    // read the height
    if ((i = fread(&badanMugi1->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, badan1->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = badanMugi1->sizeX * badanMugi1->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    badanMugi1->data = (char *) malloc(size);
    if (badanMugi1->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(badanMugi1->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = badanMugi1->data[i];
        badanMugi1->data[i] = badanMugi1->data[i+2];
        badanMugi1->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[BadanMugi2] Kanan
int ImageLoadBadanMugi2 (char *filename, BadanMugi2 *badanMugi2) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes;
    unsigned short int bpp;
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&badanMugi2->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&badanMugi2->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = badanMugi2->sizeX * badanMugi2->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    badanMugi2->data = (char *) malloc(size);
    if (badanMugi2->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(badanMugi2->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = badanMugi2->data[i];
        badanMugi2->data[i] = badanMugi2->data[i+2];
        badanMugi2->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[BadanMugi3] Belakang
int ImageLoadBadanMugi3 (char *filename, BadanMugi3 *badanMugi3) {
    FILE *file;
    unsigned long size; // size of the image in bytes.
    unsigned long i; // standard counter.
    unsigned short int planes; // number of planes in image (must be 1)
    unsigned short int bpp; // number of bits per pixel (must be 24)
    char temp; // temporary color storage for bgr-rgb conversion.
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&badanMugi3->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&badanMugi3->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = badanMugi3->sizeX * badanMugi3->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    badanMugi3->data = (char *) malloc(size);
    if (badanMugi3->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(badanMugi3->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = badanMugi3->data[i];
        badanMugi3->data[i] = badanMugi3->data[i+2];
        badanMugi3->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[BadanYui1] Depan
int ImageLoadBadanYui1 (char *filename, BadanYui1 *badanYui1) {
    FILE *file;
    unsigned long size; // size of the image in bytes.
    unsigned long i; // standard counter.
    unsigned short int planes; // number of planes in image (must be 1)
    unsigned short int bpp; // number of bits per pixel (must be 24)
    char temp; // temporary color storage for bgr-rgb conversion.
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&badanYui1->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, badan1->sizeX);
    
    // read the height
    if ((i = fread(&badanYui1->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, badan1->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = badanYui1->sizeX * badanYui1->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    badanYui1->data = (char *) malloc(size);
    if (badanYui1->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(badanYui1->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = badanYui1->data[i];
        badanYui1->data[i] = badanYui1->data[i+2];
        badanYui1->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[BadanYui2] Belakang
int ImageLoadBadanYui2 (char *filename, BadanYui2 *badanYui2) {
    FILE *file;
    unsigned long size; // size of the image in bytes.
    unsigned long i; // standard counter.
    unsigned short int planes; // number of planes in image (must be 1)
    unsigned short int bpp; // number of bits per pixel (must be 24)
    char temp; // temporary color storage for bgr-rgb conversion.
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&badanYui2->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&badanYui2->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = badanYui2->sizeX * badanYui2->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    badanYui2->data = (char *) malloc(size);
    if (badanYui2->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(badanYui2->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = badanYui2->data[i];
        badanYui2->data[i] = badanYui2->data[i+2];
        badanYui2->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[BadanYui3] Bawah
int ImageLoadBadanYui3 (char *filename, BadanYui3 *badanYui3) {
    FILE *file;
    unsigned long size; // size of the image in bytes.
    unsigned long i; // standard counter.
    unsigned short int planes; // number of planes in image (must be 1)
    unsigned short int bpp; // number of bits per pixel (must be 24)
    char temp; // temporary color storage for bgr-rgb conversion.
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&badanYui3->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&badanYui3->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = badanYui3->sizeX * badanYui3->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    badanYui3->data = (char *) malloc(size);
    if (badanYui3->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(badanYui3->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = badanYui3->data[i];
        badanYui3->data[i] = badanYui3->data[i+2];
        badanYui3->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[Rok]
int ImageLoadRok (char *filename, Rok *rok) {
    FILE *file;
    unsigned long size; // size of the image in bytes.
    unsigned long i; // standard counter.
    unsigned short int planes; // number of planes in image (must be 1)
    unsigned short int bpp; // number of bits per pixel (must be 24)
    char temp; // temporary color storage for bgr-rgb conversion.
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&rok->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&rok->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = rok->sizeX * rok->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    rok->data = (char *) malloc(size);
    if (rok->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(rok->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = rok->data[i];
        rok->data[i] = rok->data[i+2];
        rok->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[Kaki1] Depan
int ImageLoadKaki1 (char *filename, Kaki1 *kaki1) {
    FILE *file;
    unsigned long size; // size of the image in bytes.
    unsigned long i; // standard counter.
    unsigned short int planes; // number of planes in image (must be 1)
    unsigned short int bpp; // number of bits per pixel (must be 24)
    char temp; // temporary color storage for bgr-rgb conversion.
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL){
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&kaki1->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&kaki1->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = kaki1->sizeX * kaki1->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    kaki1->data = (char *) malloc(size);
    if (kaki1->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(kaki1->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = kaki1->data[i];
        kaki1->data[i] = kaki1->data[i+2];
        kaki1->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[Kaki2] Samping
int ImageLoadKaki2 (char *filename, Kaki2 *kaki2) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&kaki2->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&kaki2->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = kaki2->sizeX * kaki2->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    kaki2->data = (char *) malloc(size);
    if (kaki2->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(kaki2->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = kaki2->data[i];
        kaki2->data[i] = kaki2->data[i+2];
        kaki2->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[Kaki3] Belakang
int ImageLoadKaki3 (char *filename, Kaki3 *kaki3) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&kaki3->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&kaki3->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = kaki3->sizeX * kaki3->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    kaki3->data = (char *) malloc(size);
    if (kaki3->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(kaki3->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = kaki3->data[i];
        kaki3->data[i] = kaki3->data[i+2];
        kaki3->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[KakiMugi1] Depan
int ImageLoadKakiMugi1 (char *filename, KakiMugi1 *kakiMugi1) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL){
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&kakiMugi1->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&kakiMugi1->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = kakiMugi1->sizeX * kakiMugi1->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    kakiMugi1->data = (char *) malloc(size);
    if (kakiMugi1->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(kakiMugi1->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = kakiMugi1->data[i];
        kakiMugi1->data[i] = kakiMugi1->data[i+2];
        kakiMugi1->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[KakiMugi2] Samping
int ImageLoadKakiMugi2 (char *filename, KakiMugi2 *kakiMugi2) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&kakiMugi2->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&kakiMugi2->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = kakiMugi2->sizeX * kakiMugi2->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    kakiMugi2->data = (char *) malloc(size);
    if (kakiMugi2->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(kakiMugi2->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = kakiMugi2->data[i];
        kakiMugi2->data[i] = kakiMugi2->data[i+2];
        kakiMugi2->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[KakiMugi3] Belakang
int ImageLoadKakiMugi3 (char *filename, KakiMugi3 *kakiMugi3) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&kakiMugi3->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&kakiMugi3->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = kakiMugi3->sizeX * kakiMugi3->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    kakiMugi3->data = (char *) malloc(size);
    if (kakiMugi3->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(kakiMugi3->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = kakiMugi3->data[i];
        kakiMugi3->data[i] = kakiMugi3->data[i+2];
        kakiMugi3->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[KakiYui1] Depan
int ImageLoadKakiYui1 (char *filename, KakiYui1 *kakiYui1) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; )
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL){
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&kakiYui1->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&kakiYui1->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = kakiYui1->sizeX * kakiYui1->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    kakiYui1->data = (char *) malloc(size);
    if (kakiYui1->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(kakiYui1->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = kakiYui1->data[i];
        kakiYui1->data[i] = kakiYui1->data[i+2];
        kakiYui1->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[KakiYui2] Samping
int ImageLoadKakiYui2 (char *filename, KakiYui2 *kakiYui2) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&kakiYui2->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&kakiYui2->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = kakiYui2->sizeX * kakiYui2->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    kakiYui2->data = (char *) malloc(size);
    if (kakiYui2->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(kakiYui2->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = kakiYui2->data[i];
        kakiYui2->data[i] = kakiYui2->data[i+2];
        kakiYui2->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[KakiYui3] Belakang
int ImageLoadKakiYui3 (char *filename, KakiYui3 *kakiYui3) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&kakiYui3->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&kakiYui3->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = kakiYui3->sizeX * kakiYui3->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    kakiYui3->data = (char *) malloc(size);
    if (kakiYui3->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(kakiYui3->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = kakiYui3->data[i];
        kakiYui3->data[i] = kakiYui3->data[i+2];
        kakiYui3->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[Tangan1] Atas Kiri
int ImageLoadTangan1 (char *filename, Tangan1 *tangan1) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&tangan1->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&tangan1->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = tangan1->sizeX * tangan1->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    tangan1->data = (char *) malloc(size);
    if (tangan1->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(tangan1->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = tangan1->data[i];
        tangan1->data[i] = tangan1->data[i+2];
        tangan1->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[Tangan2] Kanan Kiri
int ImageLoadTangan2 (char *filename, Tangan2 *tangan2) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&tangan2->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&tangan2->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = tangan2->sizeX * tangan2->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    tangan2->data = (char *) malloc(size);
    if (tangan2->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(tangan2->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = tangan2->data[i];
        tangan2->data[i] = tangan2->data[i+2];
        tangan2->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[Tangan3] Bawah Kiri
int ImageLoadTangan3 (char *filename, Tangan3 *tangan3) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes;
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&tangan3->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&tangan3->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = tangan3->sizeX * tangan3->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    tangan3->data = (char *) malloc(size);
    if (tangan3->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(tangan3->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = tangan3->data[i];
        tangan3->data[i] = tangan3->data[i+2];
        tangan3->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[Tangan4] Bahu Kiri
    int ImageLoadTangan4 (char *filename, Tangan4 *tangan4) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&tangan4->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&tangan4->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = tangan4->sizeX * tangan4->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    tangan4->data = (char *) malloc(size);
    if (tangan4->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(tangan4->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = tangan4->data[i];
        tangan4->data[i] = tangan4->data[i+2];
        tangan4->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[Tangan5] Jari Kiri
int ImageLoadTangan5 (char *filename, Tangan5 *tangan5) {
    FILE *file;
    unsigned long size; 
    unsigned long i;
    unsigned short int planes; )
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&tangan5->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&tangan5->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = tangan5->sizeX * tangan5->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    tangan5->data = (char *) malloc(size);
    if (tangan5->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(tangan5->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = tangan5->data[i];
        tangan5->data[i] = tangan5->data[i+2];
        tangan5->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[Tangan7] Atas Kanan
int ImageLoadTangan7 (char *filename, Tangan7 *tangan7) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp;
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&tangan7->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&tangan7->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = tangan7->sizeX * tangan7->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    tangan7->data = (char *) malloc(size);
    if (tangan7->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(tangan7->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = tangan7->data[i];
        tangan7->data[i] = tangan7->data[i+2];
        tangan7->data[i+2] = temp;
    }
    // we're done.
    return 1;
}
//
//[Tangan8] Kanan Kanan
int ImageLoadTangan8 (char *filename, Tangan8 *tangan8) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&tangan8->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&tangan8->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = tangan8->sizeX * tangan8->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    tangan8->data = (char *) malloc(size);
    if (tangan8->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(tangan8->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = tangan8->data[i];
        tangan8->data[i] = tangan8->data[i+2];
        tangan8->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[Tangan9] Bawah Kanan
int ImageLoadTangan9 (char *filename, Tangan9 *tangan9) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; .
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&tangan9->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&tangan9->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = tangan9->sizeX * tangan9->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    tangan9->data = (char *) malloc(size);
    if (tangan9->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(tangan9->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = tangan9->data[i];
        tangan9->data[i] = tangan9->data[i+2];
        tangan9->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[Tangan10] Depan Kanan
int ImageLoadTangan10 (char *filename, Tangan10 *tangan10) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp; 
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&tangan10->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&tangan10->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = tangan10->sizeX * tangan10->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    tangan10->data = (char *) malloc(size);
    if (tangan10->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(tangan10->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = tangan10->data[i];
        tangan10->data[i] = tangan10->data[i+2];
        tangan10->data[i+2] = temp;
    }
    // we're done.
    return 1;
}


//[Tangan11] Belakang Kanan
int ImageLoadTangan11 (char *filename, Tangan11 *tangan11) {
    FILE *file;
    unsigned long size; 
    unsigned long i; 
    unsigned short int planes; 
    unsigned short int bpp;
    char temp; 
    // make sure the file is there.
    if ((file = fopen(filename, "rb"))==NULL) {
        printf("File Not Found : %s\n",filename);
        return 0;
    }
    // seek through the bmp header, up to the width/height:
    fseek(file, 18, SEEK_CUR);
    // read the width
    if ((i = fread(&tangan11->sizeX, 4, 1, file)) != 1) {
        printf("Error reading width from %s.\n", filename);
        return 0;
    }
    
    //printf("Width of %s: %lu\n", filename, image->sizeX);
    
    // read the height
    if ((i = fread(&tangan11->sizeY, 4, 1, file)) != 1) {
        printf("Error reading height from %s.\n", filename);
        return 0;
    }
    
    //printf("Height of %s: %lu\n", filename, image->sizeY);
    // calculate the size (assuming 24 bits or 3 bytes per pixel).
    size = tangan11->sizeX * tangan11->sizeY * 3;
    // read the planes
    if ((fread(&planes, 2, 1, file)) != 1) {
        printf("Error reading planes from %s.\n", filename);
        return 0;
    }
    if (planes != 1) {
        printf("Planes from %s is not 1: %u\n", filename, planes);
        return 0;
    }
    
    // read the bitsperpixel
    
    if ((i = fread(&bpp, 2, 1, file)) != 1) {
        printf("Error reading bpp from %s.\n", filename);
        return 0;
    }
    
    if (bpp != 24) {
        printf("Bpp from %s is not 24: %u\n", filename, bpp);
        return 0;
    }
    
    // seek past the rest of the bitmap header.
    
    fseek(file, 24, SEEK_CUR);
    // read the data.
    tangan11->data = (char *) malloc(size);
    if (tangan11->data == NULL) {
        printf("Error allocating memory for color-corrected image data");
        return 0;
    }
    
    if ((i = fread(tangan11->data, size, 1, file)) != 1) {
        printf("Error reading image data from %s.\n", filename);
        return 0;
    }
    for (i=0;i<size;i+=3) { // reverse all of the colors. (bgr -> rgb)
        temp = tangan11->data[i];
        tangan11->data[i] = tangan11->data[i+2];
        tangan11->data[i+2] = temp;
    }
    // we're done.
    return 1;
}

//[Load Image1]
Image * loadTexture() {

    Image *image1;
    
    // allocate space for texture1
    image1 = (Image *) malloc(sizeof(Image));
    if (image1 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoad("env/depan.bmp", image1)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return image1;
}

//[Load Image2]
Image2 * loadTexture2() {
    
    Image2 *image2;
    
    // allocate space for texture2
    image2 = (Image2 *) malloc(sizeof(Image2));
    if (image2 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoad2("env/samping.bmp", image2)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return image2;
}

//[Load Image3]
Image3 * loadTexture3() {

    Image3 *image3;
    
    // allocate space for texture3
    image3 = (Image3 *) malloc(sizeof(Image3));
    if (image3 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoad3("env/bawah.bmp", image3)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return image3;
}

//[Load Kepala1] Muka
Kepala1 * loadTextureKepala1() {
    
    Kepala1 *kepala1;
    
    // allocate space for texture2
    kepala1 = (Kepala1 *) malloc(sizeof(Kepala1));
    if (kepala1 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadKepala1("mio/muka_depan.bmp", kepala1)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return kepala1;
}

//[Load Kepala2] Samping Kanan
Kepala2 * loadTextureKepala2() {
    
    Kepala2 *kepala2;
    
    // allocate space for texture2
    kepala2 = (Kepala2 *) malloc(sizeof(Kepala2));
    if (kepala2 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadKepala2("mio/muka_samping_kanan.bmp", kepala2)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return kepala2;
}

//[Load Kepala3] Belakang
Kepala3 * loadTextureKepala3() {
    
    Kepala3 *kepala3;
    
    // allocate space for texture2
    kepala3 = (Kepala3 *) malloc(sizeof(Kepala3));
    if (kepala3 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadKepala3("mio/muka_belakang.bmp", kepala3)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return kepala3;
}

//[Load Kepala4] Samping Kiri
Kepala4 * loadTextureKepala4() {
    
    Kepala4 *kepala4;
    
    // allocate space for texture2
    kepala4 = (Kepala4 *) malloc(sizeof(Kepala4));
    if (kepala4 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadKepala4("mio/muka_samping_kiri.bmp", kepala4)) {
        printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return kepala4;
}

//[Load Kepala5] Atas
Kepala5 * loadTextureKepala5() {
    
    Kepala5 *kepala5;
    
    // allocate space for texture2
    kepala5 = (Kepala5 *) malloc(sizeof(Kepala5));
    if (kepala5 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadKepala5("mio/muka_atas.bmp", kepala5)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return kepala5;
}

//[Load Kepala6] Bawah
Kepala6 * loadTextureKepala6() {
    
    Kepala6 *kepala6;
    
    // allocate space for texture2
    kepala6 = (Kepala6 *) malloc(sizeof(Kepala6));
    if (kepala6 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadKepala6("mio/muka_bawah.bmp", kepala6)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return kepala6;
}

//[Load KepalaMugi1] Muka
KepalaMugi1 * loadTextureKepalaMugi1() {
    
    KepalaMugi1 *kepalaMugi1;
    
    // allocate space for texture2
    kepalaMugi1 = (KepalaMugi1 *) malloc(sizeof(KepalaMugi1));
    if (kepalaMugi1 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadKepalaMugi1("mugi/muka_depan.bmp", kepalaMugi1)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return kepalaMugi1;
}

//[Load KepalaMugi2] Samping Kanan
KepalaMugi2 * loadTextureKepalaMugi2() {
    
    KepalaMugi2 *kepalaMugi2;
    
    // allocate space for texture2
    kepalaMugi2 = (KepalaMugi2 *) malloc(sizeof(KepalaMugi2));
    if (kepalaMugi2 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadKepalaMugi2("mugi/muka_samping_kanan.bmp", kepalaMugi2)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return kepalaMugi2;
}

//[Load KepalaMugi3] Belakang
KepalaMugi3 * loadTextureKepalaMugi3() {
    
    KepalaMugi3 *kepalaMugi3;
    
    // allocate space for texture2
    kepalaMugi3 = (KepalaMugi3 *) malloc(sizeof(KepalaMugi3));
    if (kepalaMugi3 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadKepalaMugi3("mugi/muka_belakang.bmp", kepalaMugi3)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return kepalaMugi3;
}

//[Load KepalaMugi4] Samping Kiri
KepalaMugi4 * loadTextureKepalaMugi4() {
    
    KepalaMugi4 *kepalaMugi4;
    
    // allocate space for texture2
    kepalaMugi4 = (KepalaMugi4 *) malloc(sizeof(KepalaMugi4));
    if (kepalaMugi4 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadKepalaMugi4("mugi/muka_samping_kiri.bmp", kepalaMugi4)) {
        printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return kepalaMugi4;
}

//[Load KepalaMugi5] Atas
KepalaMugi5 * loadTextureKepalaMugi5() {
    
    KepalaMugi5 *kepalaMugi5;
    
    // allocate space for texture2
    kepalaMugi5 = (KepalaMugi5 *) malloc(sizeof(KepalaMugi5));
    if (kepalaMugi5 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadKepalaMugi5("mugi/muka_atas.bmp", kepalaMugi5)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return kepalaMugi5;
}

//[Load KepalaYui1] Muka
KepalaYui1 * loadTextureKepalaYui1() {
    
    KepalaYui1 *kepalaYui1;
    
    // allocate space for texture2
    kepalaYui1 = (KepalaYui1 *) malloc(sizeof(KepalaYui1));
    if (kepalaYui1 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadKepalaYui1("yui/muka_depan.bmp", kepalaYui1)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return kepalaYui1;
}

//[Load KepalaYui2] Samping Kanan
KepalaYui2 * loadTextureKepalaYui2() {
    
    KepalaYui2 *kepalaYui2;
    
    // allocate space for texture2
    kepalaYui2 = (KepalaYui2 *) malloc(sizeof(KepalaYui2));
    if (kepalaYui2 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadKepalaYui2("yui/muka_samping_kanan.bmp", kepalaYui2)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return kepalaYui2;
}

//[Load KepalaYui3] Belakang
KepalaYui3 * loadTextureKepalaYui3() {
    
    KepalaYui3 *kepalaYui3;
    
    // allocate space for texture2
    kepalaYui3 = (KepalaYui3 *) malloc(sizeof(KepalaYui3));
    if (kepalaYui3 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadKepalaYui3("yui/muka_belakang.bmp", kepalaYui3)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return kepalaYui3;
}

//[Load KepalaYui4] Samping Kiri
KepalaYui4 * loadTextureKepalaYui4() {
    
    KepalaYui4 *kepalaYui4;
    
    // allocate space for texture2
    kepalaYui4 = (KepalaYui4 *) malloc(sizeof(KepalaYui4));
    if (kepalaYui4 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadKepalaYui4("yui/muka_samping_kiri.bmp", kepalaYui4)) {
        printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return kepalaYui4;
}

//[Load KepalaYui5] Atas
KepalaYui5 * loadTextureKepalaYui5() {
    
    KepalaYui5 *kepalaYui5;
    
    // allocate space for texture2
    kepalaYui5 = (KepalaYui5 *) malloc(sizeof(KepalaYui5));
    if (kepalaYui5 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadKepalaYui5("yui/muka_atas.bmp", kepalaYui5)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return kepalaYui5;
}

//[Load Badan1] Depan
Badan1 * loadTextureBadan1() {

    Badan1 *badan1;
    
    // allocate space for texture2
    badan1 = (Badan1 *) malloc(sizeof(Badan1));
    if (badan1 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadBadan1("mio/badan_depan.bmp", badan1)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return badan1;
}

//[Load Badan2] Kanan
Badan2 * loadTextureBadan2() {

    Badan2 *badan2;
    
    // allocate space for texture2
    badan2 = (Badan2 *) malloc(sizeof(Badan2));
    if (badan2 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadBadan2("mio/badan_samping_kanan.bmp", badan2)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return badan2;
}

//[Load Badan3] Belakang
Badan3 * loadTextureBadan3() {

    Badan3 *badan3;
    
    // allocate space for texture2
    badan3 = (Badan3 *) malloc(sizeof(Badan3));
    if (badan3 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadBadan3("mio/badan_belakang.bmp", badan3)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return badan3;
}

//[Load Badan4] Samping Kiri
Badan4 * loadTextureBadan4() {

    Badan4 *badan4;
    
    // allocate space for texture2
    badan4 = (Badan4 *) malloc(sizeof(Badan4));
    if (badan4 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadBadan4("mio/badan_samping_kiri.bmp", badan4)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return badan4;
}

//[Load Badan5] Bawah
Badan5 * loadTextureBadan5() {

    Badan5 *badan5;
    
    // allocate space for texture2
    badan5 = (Badan5 *) malloc(sizeof(Badan5));
    if (badan5 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadBadan5("mio/badan_bawah.bmp", badan5)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return badan5;
}

//[Load BadanMugi1] Depan
BadanMugi1 * loadTextureBadanMugi1() {

    BadanMugi1 *badanMugi1;
    
    // allocate space for texture2
    badanMugi1 = (BadanMugi1 *) malloc(sizeof(BadanMugi1));
    if (badanMugi1 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadBadanMugi1("mugi/badan_depan.bmp", badanMugi1)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return badanMugi1;
}

//[Load BadanMugi2] Belakang
BadanMugi2 * loadTextureBadanMugi2() {

    BadanMugi2 *badanMugi2;
    
    // allocate space for texture2
    badanMugi2 = (BadanMugi2 *) malloc(sizeof(BadanMugi2));
    if (badanMugi2 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadBadanMugi2("mugi/badan_belakang.bmp", badanMugi2)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return badanMugi2;
}

//[Load BadanMugi3] Bawah
BadanMugi3 * loadTextureBadanMugi3() {

    BadanMugi3 *badanMugi3;
    
    // allocate space for texture2
    badanMugi3 = (BadanMugi3 *) malloc(sizeof(BadanMugi3));
    if (badanMugi3 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadBadanMugi3("mugi/badan_bawah.bmp", badanMugi3)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return badanMugi3;
}

//[Load BadanYui1] Depan
BadanYui1 * loadTextureBadanYui1() {

    BadanYui1 *badanYui1;
    
    // allocate space for texture2
    badanYui1 = (BadanYui1 *) malloc(sizeof(BadanYui1));
    if (badanYui1 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadBadanYui1("yui/badan_depan.bmp", badanYui1)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return badanYui1;
}

//[Load BadanYui2] Belakang
BadanYui2 * loadTextureBadanYui2() {

    BadanYui2 *badanYui2;
    
    // allocate space for texture2
    badanYui2 = (BadanYui2 *) malloc(sizeof(BadanYui2));
    if (badanYui2 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadBadanYui2("yui/badan_belakang.bmp", badanYui2)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return badanYui2;
}

//[Load BadanYui3] Bawah
BadanYui3 * loadTextureBadanYui3() {

    BadanYui3 *badanYui3;
    
    // allocate space for texture2
    badanYui3 = (BadanYui3 *) malloc(sizeof(BadanYui3));
    if (badanYui3 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadBadanYui3("yui/badan_bawah.bmp", badanYui3)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return badanYui3;
}

//[Load Rok]
Rok * loadTextureRok() {
    
    Rok *rok;
    
    // allocate space for texture2
    rok = (Rok *) malloc(sizeof(Rok));
    if (rok == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadRok("mio/rok.bmp", rok)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return rok;
}

//[Load Kaki1] Depan
Kaki1 * loadTextureKaki1() {
    
    Kaki1 *kaki1;
    
    // allocate space for texture2
    kaki1 = (Kaki1 *) malloc(sizeof(Kaki1));
    if (kaki1 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadKaki1("mio/kaki_depan.bmp", kaki1)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return kaki1;
}

//[Load Kaki2] Samping
Kaki2 * loadTextureKaki2() {
    
    Kaki2 *kaki2;
    
    // allocate space for texture2
    kaki2 = (Kaki2 *) malloc(sizeof(Kaki2));
    if (kaki2 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadKaki2("mio/kaki_samping.bmp", kaki2)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return kaki2;
}

//[Load Kaki3] Belakang
Kaki3 * loadTextureKaki3() {
    
    Kaki3 *kaki3;
    
    // allocate space for texture2
    kaki3 = (Kaki3 *) malloc(sizeof(Kaki3));
    if (kaki3 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadKaki3("mio/kaki_belakang.bmp", kaki3)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return kaki3;
}

//[Load KakiMugi1] Depan
KakiMugi1 * loadTextureKakiMugi1() {
    
    KakiMugi1 *kakiMugi1;
    
    // allocate space for texture2
    kakiMugi1 = (KakiMugi1 *) malloc(sizeof(KakiMugi1));
    if (kakiMugi1 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadKakiMugi1("mugi/kaki_depan.bmp", kakiMugi1)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return kakiMugi1;
}

//[Load KakiMugi2] Samping
Kaki2 * loadTextureKakiMugi2() {
    
    KakiMugi2 *kakiMugi2;
    
    // allocate space for texture2
    kakiMugi2 = (KakiMugi2 *) malloc(sizeof(KakiMugi2));
    if (kakiMugi2 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadKakiMugi2("mugi/kaki_samping.bmp", kakiMugi2)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return kakiMugi2;
}

//[Load KakiMugi3] Belakang
KakiMugi3 * loadTextureKakiMugi3() {
    
    KakiMugi3 *kakiMugi3;
    
    // allocate space for texture2
    kakiMugi3 = (KakiMugi3 *) malloc(sizeof(KakiMugi3));
    if (kakiMugi3 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadKakiMugi3("mugi/kaki_belakang.bmp", kakiMugi3)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return kakiMugi3;
}

//[Load KakiYui1] Depan
KakiYui1 * loadTextureKakiYui1() {
    
    KakiYui1 *kakiYui1;
    
    // allocate space for texture2
    kakiYui1 = (KakiYui1 *) malloc(sizeof(KakiYui1));
    if (kakiYui1 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadKakiYui1("yui/kaki_depan.bmp", kakiYui1)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return kakiYui1;
}

//[Load KakiYui2] Samping
KakiYui2 * loadTextureKakiYui2() {
    
    KakiYui2 *kakiYui2;
    
    // allocate space for texture2
    kakiYui2 = (KakiYui2 *) malloc(sizeof(KakiYui2));
    if (kakiYui2 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadKakiYui2("yui/kaki_samping.bmp", kakiYui2)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return kakiYui2;
}

//[Load KakiYui3] Belakang
KakiYui3 * loadTextureKakiYui3() {
    
    KakiYui3 *kakiYui3;
    
    // allocate space for texture2
    kakiYui3 = (KakiYui3 *) malloc(sizeof(KakiYui3));
    if (kakiYui3 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadKakiYui3("yui/kaki_belakang.bmp", kakiYui3)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return kakiYui3;
}

//[Load Tangan1] Atas
Tangan1 * loadTextureTangan1() {
    
    Tangan1 *tangan1;
    
    // allocate space for texture2
    tangan1 = (Tangan1 *) malloc(sizeof(Tangan1));
    if (tangan1 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadTangan1("mio/tangan_kiri_1.bmp", tangan1)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return tangan1;
}


//[Load Tangan2] Kanan
Tangan2 * loadTextureTangan2() {
    
    Tangan2 *tangan2;
    
    // allocate space for texture2
    tangan2 = (Tangan2 *) malloc(sizeof(Tangan2));
    if (tangan2 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadTangan2("mio/tangan_kiri_2.bmp", tangan2)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return tangan2;
}

//[Load Tangan3] Bawah
Tangan3 * loadTextureTangan3() {
    
    Tangan3 *tangan3;
    
    // allocate space for texture2
    tangan3 = (Tangan3 *) malloc(sizeof(Tangan3));
    if (tangan3 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadTangan3("mio/tangan_kiri_3.bmp", tangan3)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return tangan3;
}

//[Load Tangan4] Bahu
Tangan4 * loadTextureTangan4() {
    
    Tangan4 *tangan4;
    
    // allocate space for texture2
    tangan4 = (Tangan4 *) malloc(sizeof(Tangan4));
    if (tangan4 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadTangan4("mio/tangan_kiri_5.bmp", tangan4)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return tangan4;
}

//[Load Tangan5] Jari
Tangan5 * loadTextureTangan5() {
    
    Tangan5 *tangan5;
    
    // allocate space for texture2
    tangan5 = (Tangan5 *) malloc(sizeof(Tangan5));
    if (tangan5 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadTangan5("mio/tangan_kiri_4.bmp", tangan5)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return tangan5;
}

//[Load Tangan7] Atas
Tangan7 * loadTextureTangan7() {
    
    Tangan7 *tangan7;
    
    // allocate space for texture2
    tangan7 = (Tangan7 *) malloc(sizeof(Tangan7));
    if (tangan7 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadTangan7("mio/tangan_kanan_1.bmp", tangan7)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return tangan7;
}
//
//[Load Tangan8] Kanan
Tangan8 * loadTextureTangan8() {
    
    Tangan8 *tangan8;
    
    // allocate space for texture2
    tangan8 = (Tangan8 *) malloc(sizeof(Tangan8));
    if (tangan8 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadTangan8("mio/tangan_kanan_2.bmp", tangan8)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return tangan8;
}

//[Load Tangan9] Bawah
Tangan9 * loadTextureTangan9() {
    
    Tangan9 *tangan9;
    
    // allocate space for texture2
    tangan9 = (Tangan9 *) malloc(sizeof(Tangan9));
    if (tangan9 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadTangan9("mio/tangan_kanan_3.bmp", tangan9)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return tangan9;
}

//[Load Tangan10] Depan
Tangan10 * loadTextureTangan10() {
    
    Tangan10 *tangan10;
    
    // allocate space for texture2
    tangan10 = (Tangan10 *) malloc(sizeof(Tangan10));
    if (tangan10 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadTangan10("mio/tangan_kanan_4.bmp", tangan10)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return tangan10;
}

//[Load Tangan11] Belakang
Tangan11 * loadTextureTangan11() {
    
    Tangan11 *tangan11;
    
    // allocate space for texture2
    tangan11 = (Tangan11 *) malloc(sizeof(Tangan11));
    if (tangan11 == NULL) {
        printf("Error allocating space for image");
        exit(0);
    }
    
    if (!ImageLoadTangan11("mio/tangan_kanan_5.bmp", tangan11)) {
       printf("gambar wall.bmp tidak ditemukan ");
    }
    
    return tangan11;
}


void init(void) {
         
             
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 }; //parameter cahaya specular
    GLfloat mat_shininess[] = { 100.0 }; //parameter shininess
    GLfloat light_position[] = { 1.0, 0.5, 1.0, 1.0 }; //parameter posisi pencahayaan
    glClearColor (0.0, 0.0, 0.0, 0.0);//  fungsi ini digunakan untuk mengatur warna yang akan digunakan 
    //glShadeModel (GL_SMOOTH); //mengaktifkan shade model
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);// Fungsi yang mengimplementasikan dari object 3D
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);// fungsi yang mengimplementasikan sinar dari objek 3D
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);// fungsi untuk mengatur posisi cahaya
    //glEnable(GL_LIGHTING); //mengaktifkan pencahayaan
    //glEnable(GL_LIGHT0); //mengaktifkan sumber cahaya
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_SMOOTH);
    
    //penambahan posisi cahaya
    GLfloat lightColor0[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat lightPos0[] = {5.0f, 7.0f, 5.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    //Background
    Image *image1 = loadTexture();
    Image2 *image2 = loadTexture2();
    Image3 *image3 = loadTexture3();
    
    //Kepala Mio
    Kepala1 *kepala1 = loadTextureKepala1();
    Kepala2 *kepala2 = loadTextureKepala2();
    Kepala3 *kepala3 = loadTextureKepala3();
    Kepala4 *kepala4 = loadTextureKepala4();
    Kepala5 *kepala5 = loadTextureKepala5();
    Kepala6 *kepala6 = loadTextureKepala6();
    
    //Kepala Mugi
    KepalaMugi1 *kepalaMugi1 = loadTextureKepalaMugi1();
    KepalaMugi2 *kepalaMugi2 = loadTextureKepalaMugi2();
    KepalaMugi3 *kepalaMugi3 = loadTextureKepalaMugi3();
    KepalaMugi4 *kepalaMugi4 = loadTextureKepalaMugi4();
    KepalaMugi5 *kepalaMugi5 = loadTextureKepalaMugi5();
    
    //Kepala Yui
    KepalaYui1 *kepalaYui1 = loadTextureKepalaYui1();
    KepalaYui2 *kepalaYui2 = loadTextureKepalaYui2();
    KepalaYui3 *kepalaYui3 = loadTextureKepalaYui3();
    KepalaYui4 *kepalaYui4 = loadTextureKepalaYui4();
    KepalaYui5 *kepalaYui5 = loadTextureKepalaYui5();
    
    //Badan Mio
    Badan1 *badan1 = loadTextureBadan1();
    Badan2 *badan2 = loadTextureBadan2();
    Badan3 *badan3 = loadTextureBadan3();
    Badan4 *badan4 = loadTextureBadan4();
    Badan5 *badan5 = loadTextureBadan5();
    
    //Badan Mugi
    BadanMugi1 *badanMugi1 = loadTextureBadanMugi1();
    BadanMugi2 *badanMugi2 = loadTextureBadanMugi2();
    BadanMugi3 *badanMugi3 = loadTextureBadanMugi3();
    
    //Badan Yui
    BadanYui1 *badanYui1 = loadTextureBadanYui1();
    BadanYui2 *badanYui2 = loadTextureBadanYui2();
    BadanYui3 *badanYui3 = loadTextureBadanYui3();
    
    //Rok
    Rok *rok = loadTextureRok();
    
    //Kaki Mio
    Kaki1 * kaki1 = loadTextureKaki1();
    Kaki2 * kaki2 = loadTextureKaki2();
    Kaki3 * kaki3 = loadTextureKaki3();
    
    //Kaki Mugi
    KakiMugi1 * kakiMugi1 = loadTextureKakiMugi1();
    KakiMugi2 * kakiMugi2 = loadTextureKakiMugi2();
    KakiMugi3 * kakiMugi3 = loadTextureKakiMugi3();
    
    //Kaki Yui
    KakiYui1 * kakiYui1 = loadTextureKakiYui1();
    KakiYui2 * kakiYui2 = loadTextureKakiYui2();
    KakiYui3 * kakiYui3 = loadTextureKakiYui3();
    
    //Tangan Kanan
    Tangan1 * tangan1 = loadTextureTangan1();
    Tangan2 * tangan2 = loadTextureTangan2();
    Tangan3 * tangan3 = loadTextureTangan3();
    Tangan4 * tangan4 = loadTextureTangan4();
    Tangan5 * tangan5 = loadTextureTangan5();
    
    //Tangan Kiri
    Tangan7 * tangan7 = loadTextureTangan7();
    Tangan8 * tangan8 = loadTextureTangan8();
    Tangan9 * tangan9 = loadTextureTangan9();
    Tangan10 * tangan10 = loadTextureTangan10();
    Tangan11 * tangan11 = loadTextureTangan11();
    
    
    if(image1,image2,image3 == NULL) {
        printf("Image was not returned from loadTexture background\n");
        exit(0);
    }
    
    if(kepala1,kepala2,kepala3,kepala4,kepala5,kepala6 == NULL) {
        printf("Image was not returned from loadTexture kepala\n");
        exit(0);
    }
    
    if(kepalaMugi1,kepalaMugi2,kepalaMugi3,kepalaMugi4,kepalaMugi5 == NULL) {
        printf("Image was not returned from loadTexture kepala\n");
        exit(0);
    }
    
    if(kepalaYui1,kepalaYui2,kepalaYui3,kepalaYui4,kepalaYui5 == NULL) {
        printf("Image was not returned from loadTexture kepala\n");
        exit(0);
    }
    
    if(badan1,badan2,badan3,badan4,badan5 == NULL) {
        printf("Image was not returned from loadTexture badan\n");
        exit(0);
    }
    
    if(badanMugi1,badanMugi2,badanMugi3 == NULL) {
        printf("Image was not returned from loadTexture badan\n");
        exit(0);
    }
    
    if(badanYui1,badanYui2,badanYui3 == NULL) {
        printf("Image was not returned from loadTexture badan\n");
        exit(0);
    }
    
    if(rok == NULL) {
        printf("Image was not returned from loadTexture rok\n");
        exit(0);
    }
    
    if(kaki1,kaki2,kaki3 == NULL) {
        printf("Image was not returned from loadTexture kaki\n");
        exit(0);
    }
    
    if(kakiMugi1,kakiMugi2,kakiMugi3 == NULL) {
        printf("Image was not returned from loadTexture kaki\n");
        exit(0);
    }
    
    if(kakiYui1,kakiYui2,kakiYui3 == NULL) {
        printf("Image was not returned from loadTexture kaki\n");
        exit(0);
    }
    
    if(tangan1,tangan2,tangan3,tangan4, tangan5 == NULL) {
        printf("Image was not returned from loadTexture tangan\n");
        exit(0);
    }
    
    if(tangan7,tangan8, tangan9, tangan10, tangan11 == NULL) {
        printf("Image was not returned from loadTexture tangan\n");
        exit(0);
    }
    
    makeCheckImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);//Menetapkan mod penyimpanan pixel
    
    // Create Texture1
    glGenTextures(2, bg1);// digunakan untuk mengenerate tekstur
    glBindTexture(GL_TEXTURE_2D, bg1[0]);// untuk memasang tekstur pada objek 2d
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); //skala linear bila gambar lebih besar dari tekstur yg ingin ditempel
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); //skala linear bila gambar lebih kecil dari tekstur yg ingin ditempel
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image1->sizeX, image1->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, image1->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, bg1[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);// fungsi untuk mengatur parameter bungkus untuk tekstur koordinat s
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);// fungsi untuk mengatur parameter bungkus untuk tekstur koordinat t
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);// Fungsi ini digunakan untuk mencampurkan warna
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);// Tekstur RGBA: Membentuk tekstur 2-dimensi
                                 
    
    // Create Texture2
    glGenTextures(2, bg2);
    glBindTexture(GL_TEXTURE_2D, bg2[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image2->sizeX, image2->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, image2->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, bg2[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create Texture3
    glGenTextures(2, bg3);
    glBindTexture(GL_TEXTURE_2D, bg3[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, image3->sizeX, image3->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, image3->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, bg3[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create Kepala1 Muka
    glGenTextures(2, texturekepala1);
    glBindTexture(GL_TEXTURE_2D, texturekepala1[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, kepala1->sizeX, kepala1->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, kepala1->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturekepala1[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create Kepala2 Samping Kanan
    glGenTextures(2, texturekepala2);
    glBindTexture(GL_TEXTURE_2D, texturekepala2[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, kepala2->sizeX, kepala2->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, kepala2->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturekepala2[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create Kepala3 Belakang
    glGenTextures(2, texturekepala3);
    glBindTexture(GL_TEXTURE_2D, texturekepala3[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, kepala3->sizeX, kepala3->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, kepala3->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturekepala3[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create Kepala4 Samping Kiri
    glGenTextures(2, texturekepala4);
    glBindTexture(GL_TEXTURE_2D, texturekepala4[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, kepala4->sizeX, kepala4->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, kepala4->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturekepala4[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create Kepala5 Atas
    glGenTextures(2, texturekepala5);
    glBindTexture(GL_TEXTURE_2D, texturekepala5[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, kepala5->sizeX, kepala5->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, kepala5->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturekepala5[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create Kepala6 Bawah
    glGenTextures(2, texturekepala6);
    glBindTexture(GL_TEXTURE_2D, texturekepala6[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, kepala6->sizeX, kepala6->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, kepala6->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturekepala6[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create KepalaMugi1 Muka
    glGenTextures(2, texturekepalaMugi1);
    glBindTexture(GL_TEXTURE_2D, texturekepalaMugi1[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, kepalaMugi1->sizeX, kepalaMugi1->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, kepalaMugi1->data);
    
    if (pointerPath == 1) {
    glDeleteTextures(2, texturekepalaMugi1);
    glGenTextures(2, texturekepalaMugi1);
    glBindTexture(GL_TEXTURE_2D, texturekepalaMugi1[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    }
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturekepalaMugi1[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create KepalaMugi2 Samping Kanan
    glGenTextures(2, texturekepalaMugi2);
    glBindTexture(GL_TEXTURE_2D, texturekepalaMugi2[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, kepalaMugi2->sizeX, kepalaMugi2->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, kepalaMugi2->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturekepalaMugi2[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create KepalaMugi3 Belakang
    glGenTextures(2, texturekepalaMugi3);
    glBindTexture(GL_TEXTURE_2D, texturekepalaMugi3[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, kepalaMugi3->sizeX, kepalaMugi3->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, kepalaMugi3->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturekepalaMugi3[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create KepalaMugi4 Samping Kiri
    glGenTextures(2, texturekepalaMugi4);
    glBindTexture(GL_TEXTURE_2D, texturekepalaMugi4[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, kepalaMugi4->sizeX, kepalaMugi4->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, kepalaMugi4->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturekepalaMugi4[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create KepalaMugi5 Atas
    glGenTextures(2, texturekepalaMugi5);
    glBindTexture(GL_TEXTURE_2D, texturekepalaMugi5[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, kepalaMugi5->sizeX, kepalaMugi5->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, kepalaMugi5->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturekepalaMugi5[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create KepalaYui1 Muka
    glGenTextures(2, texturekepalaYui1);
    glBindTexture(GL_TEXTURE_2D, texturekepalaYui1[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, kepalaYui1->sizeX, kepalaYui1->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, kepalaYui1->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturekepalaYui1[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create KepalaYui2 Samping Kanan
    glGenTextures(2, texturekepalaYui2);
    glBindTexture(GL_TEXTURE_2D, texturekepalaYui2[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, kepalaYui2->sizeX, kepalaYui2->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, kepalaYui2->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturekepalaYui2[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create KepalaYui3 Belakang
    glGenTextures(2, texturekepalaYui3);
    glBindTexture(GL_TEXTURE_2D, texturekepalaYui3[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, kepalaYui3->sizeX, kepalaYui3->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, kepalaYui3->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturekepalaYui3[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create KepalaYui4 Samping Kiri
    glGenTextures(2, texturekepalaYui4);
    glBindTexture(GL_TEXTURE_2D, texturekepalaYui4[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, kepalaYui4->sizeX, kepalaYui4->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, kepalaYui4->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturekepalaYui4[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create KepalaYui5 Atas
    glGenTextures(2, texturekepalaYui5);
    glBindTexture(GL_TEXTURE_2D, texturekepalaYui5[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, kepalaYui5->sizeX, kepalaYui5->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, kepalaYui5->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturekepalaYui5[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create Badan1 Depan
    glGenTextures(2, texturebadan1);
    glBindTexture(GL_TEXTURE_2D, texturebadan1[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, badan1->sizeX, badan1->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, badan1->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturebadan1[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create Badan2 Samping Kanan
    glGenTextures(2, texturebadan2);
    glBindTexture(GL_TEXTURE_2D, texturebadan2[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, badan2->sizeX, badan2->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, badan2->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturebadan2[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create Badan3 Belakang
    glGenTextures(2, texturebadan3);
    glBindTexture(GL_TEXTURE_2D, texturebadan3[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, badan3->sizeX, badan3->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, badan3->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturebadan3[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create Badan4 Samping Kiri
    glGenTextures(2, texturebadan4);
    glBindTexture(GL_TEXTURE_2D, texturebadan4[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, badan4->sizeX, badan4->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, badan4->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturebadan4[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create Badan5 Bawah
    glGenTextures(2, texturebadan5);
    glBindTexture(GL_TEXTURE_2D, texturebadan5[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, badan5->sizeX, badan5->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, badan5->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturebadan5[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create BadanMugi1 Depan
    glGenTextures(2, texturebadanMugi1);
    glBindTexture(GL_TEXTURE_2D, texturebadanMugi1[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, badanMugi1->sizeX, badanMugi1->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, badanMugi1->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturebadanMugi1[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create BadanMugi2 Belakang
    glGenTextures(2, texturebadanMugi2);
    glBindTexture(GL_TEXTURE_2D, texturebadanMugi2[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, badanMugi2->sizeX, badanMugi2->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, badanMugi2->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturebadanMugi2[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create BadanMugi3 Bawah
    glGenTextures(2, texturebadanMugi3);
    glBindTexture(GL_TEXTURE_2D, texturebadanMugi3[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, badanMugi3->sizeX, badanMugi3->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, badanMugi3->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturebadanMugi3[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create BadanYui1 Depan
    glGenTextures(2, texturebadanYui1);
    glBindTexture(GL_TEXTURE_2D, texturebadanYui1[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, badanYui1->sizeX, badanYui1->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, badanYui1->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturebadanYui1[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create BadanYui2 Belakang
    glGenTextures(2, texturebadanYui2);
    glBindTexture(GL_TEXTURE_2D, texturebadanYui2[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, badanYui2->sizeX, badanYui2->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, badanYui2->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturebadanYui2[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create BadanYui3 Bawah
    glGenTextures(2, texturebadanYui3);
    glBindTexture(GL_TEXTURE_2D, texturebadanYui3[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, badanYui3->sizeX, badanYui3->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, badanYui3->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, texturebadanYui3[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create Rok
    glGenTextures(2, textureRok);
    glBindTexture(GL_TEXTURE_2D, textureRok[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, rok->sizeX, rok->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, rok->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, textureRok[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create Kaki1 Depan
    glGenTextures(2, textureKaki1);
    glBindTexture(GL_TEXTURE_2D, textureKaki1[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, kaki1->sizeX, kaki1->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, kaki1->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, textureKaki1[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    
    // Create Kaki2 Samping
    glGenTextures(2, textureKaki2);
    glBindTexture(GL_TEXTURE_2D, textureKaki2[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, kaki2->sizeX, kaki2->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, kaki2->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, textureKaki2[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create Kaki3 Belakang
    glGenTextures(2, textureKaki3);
    glBindTexture(GL_TEXTURE_2D, textureKaki3[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, kaki3->sizeX, kaki3->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, kaki3->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, textureKaki3[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create KakiMugi1 Depan
    glGenTextures(2, textureKakiMugi1);
    glBindTexture(GL_TEXTURE_2D, textureKakiMugi1[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, kakiMugi1->sizeX, kakiMugi1->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, kakiMugi1->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, textureKakiMugi1[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    
    // Create KakiMugi2 Samping
    glGenTextures(2, textureKakiMugi2);
    glBindTexture(GL_TEXTURE_2D, textureKakiMugi2[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, kakiMugi2->sizeX, kakiMugi2->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, kakiMugi2->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, textureKakiMugi2[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create KakiMugi3 Belakang
    glGenTextures(2, textureKakiMugi3);
    glBindTexture(GL_TEXTURE_2D, textureKakiMugi3[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, kakiMugi3->sizeX, kakiMugi3->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, kakiMugi3->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, textureKakiMugi3[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create KakiYui1 Depan
    glGenTextures(2, textureKakiYui1);
    glBindTexture(GL_TEXTURE_2D, textureKakiYui1[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, kakiYui1->sizeX, kakiYui1->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, kakiYui1->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, textureKakiYui1[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    
    // Create KakiYui2 Samping
    glGenTextures(2, textureKakiYui2);
    glBindTexture(GL_TEXTURE_2D, textureKakiYui2[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, kakiYui2->sizeX, kakiYui2->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, kakiYui2->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, textureKakiYui2[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create KakiYui3 Belakang
    glGenTextures(2, textureKakiYui3);
    glBindTexture(GL_TEXTURE_2D, textureKakiYui3[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, kakiYui3->sizeX, kakiYui3->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, kakiYui3->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, textureKakiYui3[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create Tangan1 Atas
    glGenTextures(2, textureTangan1);
    glBindTexture(GL_TEXTURE_2D, textureTangan1[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, tangan1->sizeX, tangan1->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, tangan1->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, textureTangan1[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create Tangan2 Kanan
    glGenTextures(2, textureTangan2);
    glBindTexture(GL_TEXTURE_2D, textureTangan2[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, tangan2->sizeX, tangan2->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, tangan2->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, textureTangan2[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create Tangan3 Bawah
    glGenTextures(2, textureTangan3);
    glBindTexture(GL_TEXTURE_2D, textureTangan3[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, tangan3->sizeX, tangan3->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, tangan3->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, textureTangan3[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create Tangan4 Bahu
    glGenTextures(2, textureTangan4);
    glBindTexture(GL_TEXTURE_2D, textureTangan4[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, tangan4->sizeX, tangan4->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, tangan4->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, textureTangan4[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create Tangan5 Jari
    glGenTextures(2, textureTangan5);
    glBindTexture(GL_TEXTURE_2D, textureTangan5[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, tangan5->sizeX, tangan5->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, tangan5->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, textureTangan5[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create Tangan7 Atas
    glGenTextures(2, textureTangan7);
    glBindTexture(GL_TEXTURE_2D, textureTangan7[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, tangan7->sizeX, tangan7->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, tangan7->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, textureTangan7[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create Tangan8 Kanan
    glGenTextures(2, textureTangan8);
    glBindTexture(GL_TEXTURE_2D, textureTangan8[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, tangan8->sizeX, tangan8->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, tangan8->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, textureTangan8[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create Tangan9 Bawah
    glGenTextures(2, textureTangan9);
    glBindTexture(GL_TEXTURE_2D, textureTangan9[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, tangan9->sizeX, tangan9->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, tangan9->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, textureTangan9[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    // Create Tangan10 Depan
    glGenTextures(2, textureTangan10);
    glBindTexture(GL_TEXTURE_2D, textureTangan10[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, tangan10->sizeX, tangan10->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, tangan10->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, textureTangan10[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    
    // Create Tangan11 Belakang
    glGenTextures(2, textureTangan11);
    glBindTexture(GL_TEXTURE_2D, textureTangan11[0]);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); 
    
    glTexImage2D(GL_TEXTURE_2D, 0, 3, tangan11->sizeX, tangan11->sizeY, 0,
    GL_RGB, GL_UNSIGNED_BYTE, tangan11->data);
    
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glBindTexture(GL_TEXTURE_2D, textureTangan11[1]);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, checkImageWidth,
    checkImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,&checkImage[0][0][0]);
    
    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_FLAT);
}

void badan(void) {
         
    glBindTexture(GL_TEXTURE_2D, texturebadan1[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS); //ABCD Depan
                        glTexCoord2f(0.0,0.0);
            glVertex3f (-0.33, -0.36, 0.33);
                       glTexCoord2f(1.0,0.0);
            glVertex3f (0.33, -0.36, 0.33);
                       glTexCoord2f(1.0,1.0);
            glVertex3f (0.33, 0.36, 0.33);
                       glTexCoord2f(0.0,1.0);
            glVertex3f (-0.33, 0.36, 0.33);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, texturebadan2[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//BFGC Samping Kanan
                    glTexCoord2f(0.0,0.0);
        glVertex3f (0.33, -0.36, 0.33);
                   glTexCoord2f(1.0,0.0);
        glVertex3f (0.33, -0.36, -0.33);
                   glTexCoord2f(1.0,1.0);
        glVertex3f (0.33, 0.36, -0.33);
                   glTexCoord2f(0.0,1.0);
        glVertex3f (0.33, 0.36, 0.33);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, texturebadan3[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//EFGH Belakang
                    glTexCoord2f(0.0,0.0);
        glVertex3f (0.33, -0.36, -0.33);
                   glTexCoord2f(1.0,0.0);
        glVertex3f (-0.33, -0.36, -0.33);
                   glTexCoord2f(1.0,1.0);
        glVertex3f (-0.33, 0.36, -0.33);
                   glTexCoord2f(0.0,1.0);
        glVertex3f (0.33, 0.36, -0.33);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, texturebadan4[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//AEHD Samping Kiri
                    glTexCoord2f(0.0,0.0);
        glVertex3f (-0.33, -0.36, -0.33);
                   glTexCoord2f(1.0,0.0);
        glVertex3f (-0.33, -0.36, 0.33);
                   glTexCoord2f(1.0,1.0);
        glVertex3f (-0.33, 0.36, 0.33);
                   glTexCoord2f(0.0,1.0);
        glVertex3f (-0.33, 0.36, -0.33);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBegin(GL_QUADS);//DCGH Atas
    glColor3f (0.0, 1.0, 0.0);
    glVertex3f (-0.33, 0.36, 0.33);
    glVertex3f (0.33, 0.36, 0.33);
    glVertex3f (0.33, 0.36, -0.33);
    glVertex3f (-0.33, 0.36, -0.33);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, texturebadan5[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//ABFE Bawah
                    glTexCoord2f(0.0,0.0);
        glVertex3f (-0.33, -0.36, 0.33);
                   glTexCoord2f(1.0,0.0);
        glVertex3f (0.33, -0.36, 0.33);
                   glTexCoord2f(1.0,1.0);
        glVertex3f (0.33, -0.36, -0.33);
                   glTexCoord2f(0.0,1.0);
        glVertex3f (-0.33, -0.36, -0.33);
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

void badanMugi(void) {
         
    glBindTexture(GL_TEXTURE_2D, texturebadanMugi1[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS); //ABCD Depan
                        glTexCoord2f(0.0,0.0);
            glVertex3f (-0.33, -0.36, 0.33);
                       glTexCoord2f(1.0,0.0);
            glVertex3f (0.33, -0.36, 0.33);
                       glTexCoord2f(1.0,1.0);
            glVertex3f (0.33, 0.36, 0.33);
                       glTexCoord2f(0.0,1.0);
            glVertex3f (-0.33, 0.36, 0.33);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, texturebadan2[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//BFGC Samping Kanan
                    glTexCoord2f(0.0,0.0);
        glVertex3f (0.33, -0.36, 0.33);
                   glTexCoord2f(1.0,0.0);
        glVertex3f (0.33, -0.36, -0.33);
                   glTexCoord2f(1.0,1.0);
        glVertex3f (0.33, 0.36, -0.33);
                   glTexCoord2f(0.0,1.0);
        glVertex3f (0.33, 0.36, 0.33);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, texturebadanMugi2[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//EFGH Belakang
                    glTexCoord2f(0.0,0.0);
        glVertex3f (0.33, -0.36, -0.33);
                   glTexCoord2f(1.0,0.0);
        glVertex3f (-0.33, -0.36, -0.33);
                   glTexCoord2f(1.0,1.0);
        glVertex3f (-0.33, 0.36, -0.33);
                   glTexCoord2f(0.0,1.0);
        glVertex3f (0.33, 0.36, -0.33);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, texturebadan4[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//AEHD Samping Kiri
                    glTexCoord2f(0.0,0.0);
        glVertex3f (-0.33, -0.36, -0.33);
                   glTexCoord2f(1.0,0.0);
        glVertex3f (-0.33, -0.36, 0.33);
                   glTexCoord2f(1.0,1.0);
        glVertex3f (-0.33, 0.36, 0.33);
                   glTexCoord2f(0.0,1.0);
        glVertex3f (-0.33, 0.36, -0.33);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBegin(GL_QUADS);//DCGH Atas
    glColor3f (0.0, 1.0, 0.0);
    glVertex3f (-0.33, 0.36, 0.33);
    glVertex3f (0.33, 0.36, 0.33);
    glVertex3f (0.33, 0.36, -0.33);
    glVertex3f (-0.33, 0.36, -0.33);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, texturebadanMugi3[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//ABFE Bawah
                    glTexCoord2f(0.0,0.0);
        glVertex3f (-0.33, -0.36, 0.33);
                   glTexCoord2f(1.0,0.0);
        glVertex3f (0.33, -0.36, 0.33);
                   glTexCoord2f(1.0,1.0);
        glVertex3f (0.33, -0.36, -0.33);
                   glTexCoord2f(0.0,1.0);
        glVertex3f (-0.33, -0.36, -0.33);
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

void badanYui (void) {
         
    glBindTexture(GL_TEXTURE_2D, texturebadanYui1[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS); //ABCD Depan
                        glTexCoord2f(0.0,0.0);
            glVertex3f (-0.33, -0.36, 0.33);
                       glTexCoord2f(1.0,0.0);
            glVertex3f (0.33, -0.36, 0.33);
                       glTexCoord2f(1.0,1.0);
            glVertex3f (0.33, 0.36, 0.33);
                       glTexCoord2f(0.0,1.0);
            glVertex3f (-0.33, 0.36, 0.33);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, texturebadan2[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//BFGC Samping Kanan
                    glTexCoord2f(0.0,0.0);
        glVertex3f (0.33, -0.36, 0.33);
                   glTexCoord2f(1.0,0.0);
        glVertex3f (0.33, -0.36, -0.33);
                   glTexCoord2f(1.0,1.0);
        glVertex3f (0.33, 0.36, -0.33);
                   glTexCoord2f(0.0,1.0);
        glVertex3f (0.33, 0.36, 0.33);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, texturebadanYui2[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//EFGH Belakang
                    glTexCoord2f(0.0,0.0);
        glVertex3f (0.33, -0.36, -0.33);
                   glTexCoord2f(1.0,0.0);
        glVertex3f (-0.33, -0.36, -0.33);
                   glTexCoord2f(1.0,1.0);
        glVertex3f (-0.33, 0.36, -0.33);
                   glTexCoord2f(0.0,1.0);
        glVertex3f (0.33, 0.36, -0.33);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, texturebadan4[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//AEHD Samping Kiri
                    glTexCoord2f(0.0,0.0);
        glVertex3f (-0.33, -0.36, -0.33);
                   glTexCoord2f(1.0,0.0);
        glVertex3f (-0.33, -0.36, 0.33);
                   glTexCoord2f(1.0,1.0);
        glVertex3f (-0.33, 0.36, 0.33);
                   glTexCoord2f(0.0,1.0);
        glVertex3f (-0.33, 0.36, -0.33);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBegin(GL_QUADS);//DCGH Atas
    glColor3f (0.0, 1.0, 0.0);
    glVertex3f (-0.33, 0.36, 0.33);
    glVertex3f (0.33, 0.36, 0.33);
    glVertex3f (0.33, 0.36, -0.33);
    glVertex3f (-0.33, 0.36, -0.33);
    glEnd();
    
    glBindTexture(GL_TEXTURE_2D, texturebadanYui3[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//ABFE Bawah
                    glTexCoord2f(0.0,0.0);
        glVertex3f (-0.33, -0.36, 0.33);
                   glTexCoord2f(1.0,0.0);
        glVertex3f (0.33, -0.36, 0.33);
                   glTexCoord2f(1.0,1.0);
        glVertex3f (0.33, -0.36, -0.33);
                   glTexCoord2f(0.0,1.0);
        glVertex3f (-0.33, -0.36, -0.33);
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

void kepala(void) {
         
    glBindTexture(GL_TEXTURE_2D, texturekepala1[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//IJKL Muka
                      glTexCoord2f(0.0,0.0);
            glVertex3f (-0.5, 0.36, 0.5); //I
                       glTexCoord2f(1.0,0.0);
            glVertex3f (0.5, 0.36, 0.5); //J
                       glTexCoord2f(1.0,1.0);
            glVertex3f (0.5, 1.08, 0.5); //K
                       glTexCoord2f(0.0,1.0);
            glVertex3f (-0.5, 1.08, 0.5); //L
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, texturekepala2[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//JNOK Samping Kanan
                        glTexCoord2f(0.0,0.0);
            glVertex3f (0.5, 0.36, 0.5); //J
                       glTexCoord2f(1.0,0.0);
            glVertex3f (0.5, 0.36, -0.5); //N
                       glTexCoord2f(1.0,1.0);
            glVertex3f (0.5, 1.08, -0.5); //O
                       glTexCoord2f(0.0,1.0);
            glVertex3f (0.5, 1.08, 0.5); //K
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, texturekepala3[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//NMPO Belakang
                    glTexCoord2f(0.0,0.0);
        glVertex3f (0.5, -0.36, -0.5); //N
                   glTexCoord2f(1.0,0.0);
        glVertex3f (-0.5, -0.36, -0.5); //M
                   glTexCoord2f(1.0,1.0);
        glVertex3f (-0.5, 1.08, -0.5); //P
                   glTexCoord2f(0.0,1.0);
        glVertex3f (0.5, 1.08, -0.5); //O
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, texturekepala4[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//IMPL Samping Kiri
                    glTexCoord2f(1.0,0.0);
        glVertex3f (-0.5, 0.36, 0.5); //I
                   glTexCoord2f(0.0,0.0);
        glVertex3f (-0.5, 0.36, -0.5); //M
                   glTexCoord2f(0.0,1.0);
        glVertex3f (-0.5, 1.08, -0.5); //P
                   glTexCoord2f(1.0,1.0);
        glVertex3f (-0.5, 1.08, 0.5); //L
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, texturekepala5[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//LKOP Atas
                    glTexCoord2f(0.0,0.0);
        glVertex3f (-0.5, 1.08, 0.5);
                   glTexCoord2f(1.0,0.0);
        glVertex3f (0.5, 1.08, 0.5);
                   glTexCoord2f(1.0,1.0);
        glVertex3f (0.5, 1.08, -0.5);
                   glTexCoord2f(0.0,1.0);
        glVertex3f (-0.5, 1.08, -0.5);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, texturekepala6[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//IJNM Bawah
                    glTexCoord2f(0.0,0.0);
        glVertex3f (-0.5, 0.36, 0.5);
                   glTexCoord2f(1.0,0.0);
        glVertex3f (0.5, 0.36, 0.5);
                   glTexCoord2f(1.0,1.0);
        glVertex3f (0.5, 0.36, -0.5);
                   glTexCoord2f(0.0,1.0);
        glVertex3f (-0.5, 0.36, -0.5);
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

void kepalaMugi(void) {
         
    glBindTexture(GL_TEXTURE_2D, texturekepalaMugi1[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//IJKL Muka
                      glTexCoord2f(0.0,0.0);
            glVertex3f (-0.5, 0.36, 0.5); //I
                       glTexCoord2f(1.0,0.0);
            glVertex3f (0.5, 0.36, 0.5); //J
                       glTexCoord2f(1.0,1.0);
            glVertex3f (0.5, 1.08, 0.5); //K
                       glTexCoord2f(0.0,1.0);
            glVertex3f (-0.5, 1.08, 0.5); //L
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, texturekepalaMugi2[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//JNOK Samping Kanan
                        glTexCoord2f(0.0,0.0);
            glVertex3f (0.5, 0.36, 0.5); //J
                       glTexCoord2f(1.0,0.0);
            glVertex3f (0.5, 0.36, -0.5); //N
                       glTexCoord2f(1.0,1.0);
            glVertex3f (0.5, 1.08, -0.5); //O
                       glTexCoord2f(0.0,1.0);
            glVertex3f (0.5, 1.08, 0.5); //K
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, texturekepalaMugi3[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//NMPO Belakang
                    glTexCoord2f(0.0,0.0);
        glVertex3f (0.5, -0.36, -0.5); //N
                   glTexCoord2f(1.0,0.0);
        glVertex3f (-0.5, -0.36, -0.5); //M
                   glTexCoord2f(1.0,1.0);
        glVertex3f (-0.5, 1.08, -0.5); //P
                   glTexCoord2f(0.0,1.0);
        glVertex3f (0.5, 1.08, -0.5); //O
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, texturekepalaMugi4[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//IMPL Samping Kiri
                    glTexCoord2f(1.0,0.0);
        glVertex3f (-0.5, 0.36, 0.5); //I
                   glTexCoord2f(0.0,0.0);
        glVertex3f (-0.5, 0.36, -0.5); //M
                   glTexCoord2f(0.0,1.0);
        glVertex3f (-0.5, 1.08, -0.5); //P
                   glTexCoord2f(1.0,1.0);
        glVertex3f (-0.5, 1.08, 0.5); //L
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, texturekepalaMugi5[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//LKOP Atas
                    glTexCoord2f(0.0,0.0);
        glVertex3f (-0.5, 1.08, 0.5);
                   glTexCoord2f(1.0,0.0);
        glVertex3f (0.5, 1.08, 0.5);
                   glTexCoord2f(1.0,1.0);
        glVertex3f (0.5, 1.08, -0.5);
                   glTexCoord2f(0.0,1.0);
        glVertex3f (-0.5, 1.08, -0.5);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, texturekepala6[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//IJNM Bawah
                    glTexCoord2f(0.0,0.0);
        glVertex3f (-0.5, 0.36, 0.5);
                   glTexCoord2f(1.0,0.0);
        glVertex3f (0.5, 0.36, 0.5);
                   glTexCoord2f(1.0,1.0);
        glVertex3f (0.5, 0.36, -0.5);
                   glTexCoord2f(0.0,1.0);
        glVertex3f (-0.5, 0.36, -0.5);
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

void kepalaYui (void) {
         
    glBindTexture(GL_TEXTURE_2D, texturekepalaYui1[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//IJKL Muka
                      glTexCoord2f(0.0,0.0);
            glVertex3f (-0.5, 0.36, 0.5); //I
                       glTexCoord2f(1.0,0.0);
            glVertex3f (0.5, 0.36, 0.5); //J
                       glTexCoord2f(1.0,1.0);
            glVertex3f (0.5, 1.08, 0.5); //K
                       glTexCoord2f(0.0,1.0);
            glVertex3f (-0.5, 1.08, 0.5); //L
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, texturekepalaYui2[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//JNOK Samping Kanan
                        glTexCoord2f(0.0,0.0);
            glVertex3f (0.5, 0.36, 0.5); //J
                       glTexCoord2f(1.0,0.0);
            glVertex3f (0.5, 0.36, -0.5); //N
                       glTexCoord2f(1.0,1.0);
            glVertex3f (0.5, 1.08, -0.5); //O
                       glTexCoord2f(0.0,1.0);
            glVertex3f (0.5, 1.08, 0.5); //K
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, texturekepalaYui3[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//NMPO Belakang
                    glTexCoord2f(0.0,0.0);
        glVertex3f (0.5, 0.36, -0.5); //N
                   glTexCoord2f(1.0,0.0);
        glVertex3f (-0.5, 0.36, -0.5); //M
                   glTexCoord2f(1.0,1.0);
        glVertex3f (-0.5, 1.08, -0.5); //P
                   glTexCoord2f(0.0,1.0);
        glVertex3f (0.5, 1.08, -0.5); //O
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, texturekepalaYui4[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//IMPL Samping Kiri
                    glTexCoord2f(1.0,0.0);
        glVertex3f (-0.5, 0.36, 0.5); //I
                   glTexCoord2f(0.0,0.0);
        glVertex3f (-0.5, 0.36, -0.5); //M
                   glTexCoord2f(0.0,1.0);
        glVertex3f (-0.5, 1.08, -0.5); //P
                   glTexCoord2f(1.0,1.0);
        glVertex3f (-0.5, 1.08, 0.5); //L
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, texturekepalaYui5[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//LKOP Atas
                    glTexCoord2f(0.0,0.0);
        glVertex3f (-0.5, 1.08, 0.5);
                   glTexCoord2f(1.0,0.0);
        glVertex3f (0.5, 1.08, 0.5);
                   glTexCoord2f(1.0,1.0);
        glVertex3f (0.5, 1.08, -0.5);
                   glTexCoord2f(0.0,1.0);
        glVertex3f (-0.5, 1.08, -0.5);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, texturekepala6[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//IJNM Bawah
                    glTexCoord2f(0.0,0.0);
        glVertex3f (-0.5, 0.36, 0.5);
                   glTexCoord2f(1.0,0.0);
        glVertex3f (0.5, 0.36, 0.5);
                   glTexCoord2f(1.0,1.0);
        glVertex3f (0.5, 0.36, -0.5);
                   glTexCoord2f(0.0,1.0);
        glVertex3f (-0.5, 0.36, -0.5);
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

void tangan_kiri(void) { //Tangan kiri
    
    //Tangan Jari
    glBindTexture(GL_TEXTURE_2D, textureTangan5[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//ABCD
            glTexCoord2f(0.0,0.0);glVertex3f (0.33, -0.14, 0.15);
            glTexCoord2f(1.0,0.0);glVertex3f (0.57, -0.14, 0.15);
            glTexCoord2f(1.0,1.0);glVertex3f (0.57, 0.04, 0.33);
            glTexCoord2f(0.0,1.0);glVertex3f (0.33, 0.04, 0.33);
        glEnd();
    glDisable(GL_TEXTURE_2D); 
    
    //Tangan Kiri Kanan
    glBindTexture(GL_TEXTURE_2D, textureTangan2[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//BFGC
            glTexCoord2f(0.0,0.0);glVertex3f (0.57, -0.14, 0.15);
            glTexCoord2f(1.0,0.0);glVertex3f (0.57, 0.18, -0.18);
            glTexCoord2f(1.0,1.0);glVertex3f (0.57, 0.36, 0.0);
            glTexCoord2f(0.0,1.0);glVertex3f (0.57, 0.04, 0.33);
        glEnd(); 
    glDisable(GL_TEXTURE_2D);
    
    //Tangan Bahu
    glBindTexture(GL_TEXTURE_2D, textureTangan4[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//FEHG
            glTexCoord2f(0.0,0.0);glVertex3f (0.57, 0.18, -0.18);
            glTexCoord2f(1.0,0.0);glVertex3f (0.33, 0.18, -0.18);
            glTexCoord2f(1.0,1.0);glVertex3f (0.33, 0.36, 0.0);
            glTexCoord2f(0.0,1.0);glVertex3f (0.57, 0.36, 0.0);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBegin(GL_QUADS);//EADH
        glColor3f (0.0, 1.0, 1.0);
        glVertex3f (0.33, 0.18, -0.18);
        glVertex3f (0.33, -0.14, 0.15);
        glVertex3f (0.33, 0.04, 0.33);
        glVertex3f (0.33, 0.36, 0.0);
    glEnd();
    
    //Tangan Kiri Atas
    glBindTexture(GL_TEXTURE_2D, textureTangan1[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//DCGH
            glTexCoord2f(0.0,0.0);glVertex3f (0.33, 0.04, 0.33);
            glTexCoord2f(1.0,0.0);glVertex3f (0.57, 0.04, 0.33);
            glTexCoord2f(1.0,1.0);glVertex3f (0.57, 0.36, 0.0);
            glTexCoord2f(0.0,1.0);glVertex3f (0.33, 0.36, 0.0);
        glEnd();
    glDisable(GL_TEXTURE_2D);  
    
    //Tangan Kiri Bawah
    glBindTexture(GL_TEXTURE_2D, textureTangan3[0]);
    glEnable(GL_TEXTURE_2D);     
        glBegin(GL_QUADS);//ABFE
            glTexCoord2f(0.0,0.0);glVertex3f (0.33, -0.14, 0.15);
            glTexCoord2f(1.0,0.0);glVertex3f (0.57, -0.14, 0.15);
            glTexCoord2f(1.0,1.0);glVertex3f (0.57, 0.18, -0.18);
            glTexCoord2f(0.0,1.0);glVertex3f (0.33, 0.18, -0.18);
        glEnd();
    glDisable(GL_TEXTURE_2D);     
}

void tangan_kanan(void) { //Tangan Kanan
    
    //tangan kanan depan
    glBindTexture(GL_TEXTURE_2D, textureTangan10[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//ABCD
            glTexCoord2f(0.0,0.0);glVertex3f (-0.33, -0.14, 0.15);
            glTexCoord2f(1.0,0.0);glVertex3f (-0.57, -0.14, 0.15);
            glTexCoord2f(1.0,1.0);glVertex3f (-0.57, 0.04, 0.33);
            glTexCoord2f(0.0,1.0);glVertex3f (-0.33, 0.04, 0.33);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    //Tangan kanan Kanan      
    glBindTexture(GL_TEXTURE_2D, textureTangan8[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//BFGC
            glTexCoord2f(1.0,0.0);glVertex3f (-0.57, -0.14, 0.15);
            glTexCoord2f(0.0,1.0);glVertex3f (-0.57, 0.18, -0.18);
            glTexCoord2f(0.0,0.0);glVertex3f (-0.57, 0.36, 0.0);
            glTexCoord2f(1.0,1.0);glVertex3f (-0.57, 0.04, 0.33);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    //tangan kanan belakang
    glBindTexture(GL_TEXTURE_2D, textureTangan8[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//FEHG
            glTexCoord2f(0.0,0.0);glVertex3f (-0.57, 0.18, -0.18);
            glTexCoord2f(1.0,0.0);glVertex3f (-0.33, 0.18, -0.18);
            glTexCoord2f(1.0,1.0);glVertex3f (-0.33, 0.36, 0.0);
            glTexCoord2f(0.0,1.0);glVertex3f (-0.57, 0.36, 0.0);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBegin(GL_QUADS);//EADH
        glColor3f (0.0, 1.0, 1.0);
        glVertex3f (-0.33, 0.18, -0.18);
        glVertex3f (-0.33, -0.14, 0.15);
        glVertex3f (-0.33, 0.04, 0.33);
        glVertex3f (-0.33, 0.36, 0.0);
    glEnd();
    
    //Tangan kanan Atas
    glBindTexture(GL_TEXTURE_2D, textureTangan7[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//DCGH
            glTexCoord2f(0.0,0.0);glVertex3f (-0.33, 0.04, 0.33);
            glTexCoord2f(1.0,0.0);glVertex3f (-0.57, 0.04, 0.33);
            glTexCoord2f(1.0,1.0);glVertex3f (-0.57, 0.36, 0.0);
            glTexCoord2f(0.0,1.0);glVertex3f (-0.33, 0.36, 0.0);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    //Tangan kanan Bawah
    glBindTexture(GL_TEXTURE_2D, textureTangan9[0]);
    glEnable(GL_TEXTURE_2D);     
        glBegin(GL_QUADS);//ABFE
            glTexCoord2f(0.0,0.0);glVertex3f (-0.33, -0.14, 0.15);
            glTexCoord2f(1.0,0.0);glVertex3f (-0.57, -0.14, 0.15);
            glTexCoord2f(1.0,1.0);glVertex3f (-0.57, 0.18, -0.18);
            glTexCoord2f(0.0,1.0);glVertex3f (-0.33, 0.18, -0.18);
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

void rok(void) {
     
    glBindTexture(GL_TEXTURE_2D, textureRok[0]);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);//ABCD [Rok Depan]
            glTexCoord2f(0.0,0.0);glVertex3f (-0.41, -0.36, 0.43);
            glTexCoord2f(1.0,0.2);glVertex3f (0.41, -0.36, 0.43);
            glTexCoord2f(1.0,1.0);glVertex3f (0.33, -0.18, 0.33);
            glTexCoord2f(0.2,1.0);glVertex3f (-0.33, -0.18, 0.33); 

//BFGC [Rok Kanan]
            glTexCoord2f(0.0,0.0);glVertex3f (0.41, -0.36, 0.43);
            glTexCoord2f(1.0,0.2);glVertex3f (0.41, -0.36, -0.43);
            glTexCoord2f(1.0,1.0);glVertex3f (0.33, -0.18, -0.33);
            glTexCoord2f(0.2,1.0);glVertex3f (0.33, -0.18, 0.33);

//FEHG [Rok Belakang]
            glTexCoord2f(0.0,0.0);glVertex3f (0.41, -0.36, -0.43);
            glTexCoord2f(1.0,0.2);glVertex3f (-0.41, -0.36, -0.43);
            glTexCoord2f(1.0,1.0);glVertex3f (-0.33, -0.18, -0.33);
            glTexCoord2f(0.2,1.0);glVertex3f (0.33, -0.18, -0.33);

//EADH [Rok Kanan]
            glTexCoord2f(0.0,0.0);glVertex3f (-0.41, -0.36, -0.43);
            glTexCoord2f(1.0,0.2);glVertex3f (-0.41, -0.36, 0.43);
            glTexCoord2f(1.0,1.0);glVertex3f (-0.33, -0.18, 0.33);
            glTexCoord2f(0.2,1.0);glVertex3f (-0.33, -0.18, -0.33);
     glEnd();
     glDisable(GL_TEXTURE_2D);
}

void kaki(void) {
    
    glBindTexture(GL_TEXTURE_2D, textureKaki1[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//ABCD [kaki depan]
            glTexCoord2f(0.0,0.0);glVertex3f (-0.25, -0.54, 0.25);
            glTexCoord2f(1.0,0.0);glVertex3f (0.25, -0.54, 0.25);
            glTexCoord2f(1.0,1.0);glVertex3f (0.25, -0.36, 0.25);
            glTexCoord2f(0.0,1.0);glVertex3f (-0.25, -0.36, 0.25);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, textureKaki2[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//BFGC [kaki samping kanan]
            glTexCoord2f(0.0,0.0);glVertex3f (0.25, -0.54, 0.25);
            glTexCoord2f(1.0,0.0);glVertex3f (0.25, -0.54, -0.25);
            glTexCoord2f(1.0,1.0);glVertex3f (0.25, -0.36, -0.25);
            glTexCoord2f(0.0,1.0);glVertex3f (0.25, -0.36, 0.25);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, textureKaki2[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS); //EADH [kaki samping kiri]
            glTexCoord2f(0.0,0.0);glVertex3f (-0.25, -0.54, -0.25);
            glTexCoord2f(1.0,0.0);glVertex3f (-0.25, -0.54, 0.25);
            glTexCoord2f(1.0,1.0);glVertex3f (-0.25, -0.36, 0.25);
            glTexCoord2f(0.0,1.0);glVertex3f (-0.25, -0.36, -0.25);
        glEnd();
    glDisable(GL_TEXTURE_2D);
         
    glBindTexture(GL_TEXTURE_2D, textureKaki3[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//FEHG [kaki belakang]
            glTexCoord2f(0.0,0.0);glVertex3f (0.25, -0.54, -0.25);
            glTexCoord2f(1.0,0.0);glVertex3f (-0.25, -0.54, -0.25);
            glTexCoord2f(1.0,1.0);glVertex3f (-0.25, -0.36, -0.25);
            glTexCoord2f(0.0,1.0);glVertex3f (0.25, -0.36, -0.25);
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

void kakiMugi(void) {
    
    glBindTexture(GL_TEXTURE_2D, textureKakiMugi1[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//ABCD [kaki depan]
            glTexCoord2f(0.0,0.0);glVertex3f (-0.25, -0.54, 0.25);
            glTexCoord2f(1.0,0.0);glVertex3f (0.25, -0.54, 0.25);
            glTexCoord2f(1.0,1.0);glVertex3f (0.25, -0.36, 0.25);
            glTexCoord2f(0.0,1.0);glVertex3f (-0.25, -0.36, 0.25);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, textureKakiMugi2[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//BFGC [kaki samping kanan]
            glTexCoord2f(0.0,0.0);glVertex3f (0.25, -0.54, 0.25);
            glTexCoord2f(1.0,0.0);glVertex3f (0.25, -0.54, -0.25);
            glTexCoord2f(1.0,1.0);glVertex3f (0.25, -0.36, -0.25);
            glTexCoord2f(0.0,1.0);glVertex3f (0.25, -0.36, 0.25);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, textureKakiMugi2[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS); //EADH [kaki samping kiri]
            glTexCoord2f(0.0,0.0);glVertex3f (-0.25, -0.54, -0.25);
            glTexCoord2f(1.0,0.0);glVertex3f (-0.25, -0.54, 0.25);
            glTexCoord2f(1.0,1.0);glVertex3f (-0.25, -0.36, 0.25);
            glTexCoord2f(0.0,1.0);glVertex3f (-0.25, -0.36, -0.25);
        glEnd();
    glDisable(GL_TEXTURE_2D);
         
    glBindTexture(GL_TEXTURE_2D, textureKakiMugi3[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//FEHG [kaki belakang]
            glTexCoord2f(0.0,0.0);glVertex3f (0.25, -0.54, -0.25);
            glTexCoord2f(1.0,0.0);glVertex3f (-0.25, -0.54, -0.25);
            glTexCoord2f(1.0,1.0);glVertex3f (-0.25, -0.36, -0.25);
            glTexCoord2f(0.0,1.0);glVertex3f (0.25, -0.36, -0.25);
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

void kakiYui(void) {
    
    glBindTexture(GL_TEXTURE_2D, textureKakiYui1[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//ABCD [kaki depan]
            glTexCoord2f(0.0,0.0);glVertex3f (-0.25, -0.54, 0.25);
            glTexCoord2f(1.0,0.0);glVertex3f (0.25, -0.54, 0.25);
            glTexCoord2f(1.0,1.0);glVertex3f (0.25, -0.36, 0.25);
            glTexCoord2f(0.0,1.0);glVertex3f (-0.25, -0.36, 0.25);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, textureKakiYui2[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//BFGC [kaki samping kanan]
            glTexCoord2f(0.0,0.0);glVertex3f (0.25, -0.54, 0.25);
            glTexCoord2f(1.0,0.0);glVertex3f (0.25, -0.54, -0.25);
            glTexCoord2f(1.0,1.0);glVertex3f (0.25, -0.36, -0.25);
            glTexCoord2f(0.0,1.0);glVertex3f (0.25, -0.36, 0.25);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, textureKakiYui2[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS); //EADH [kaki samping kiri]
            glTexCoord2f(0.0,0.0);glVertex3f (-0.25, -0.54, -0.25);
            glTexCoord2f(1.0,0.0);glVertex3f (-0.25, -0.54, 0.25);
            glTexCoord2f(1.0,1.0);glVertex3f (-0.25, -0.36, 0.25);
            glTexCoord2f(0.0,1.0);glVertex3f (-0.25, -0.36, -0.25);
        glEnd();
    glDisable(GL_TEXTURE_2D);
         
    glBindTexture(GL_TEXTURE_2D, textureKakiYui3[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//FEHG [kaki belakang]
            glTexCoord2f(0.0,0.0);glVertex3f (0.25, -0.54, -0.25);
            glTexCoord2f(1.0,0.0);glVertex3f (-0.25, -0.54, -0.25);
            glTexCoord2f(1.0,1.0);glVertex3f (-0.25, -0.36, -0.25);
            glTexCoord2f(0.0,1.0);glVertex3f (0.25, -0.36, -0.25);
        glEnd();
    glDisable(GL_TEXTURE_2D);
}

void background(void) {
    
    glBindTexture(GL_TEXTURE_2D, bg2[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);//BFGC Samping Kanan
                    glTexCoord2f(0.0,0.0);
        glVertex3f (3.0, -0.54, 5.0); //B
                   glTexCoord2f(1.0,0.0);
        glVertex3f (3.0, -0.54, -3.0); //F
                   glTexCoord2f(1.0,1.0);
        glVertex3f (3.0, 2.5, -3.0); //G
                   glTexCoord2f(0.0,1.0);
        glVertex3f (3.0, 2.3, 5.0); //C
        glEnd();
    glDisable(GL_TEXTURE_2D);  
    
    glBindTexture(GL_TEXTURE_2D, bg1[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS); //EFGH Belakang
                        glTexCoord2f(0.0,0.0);
            glVertex3f (-3.0, -0.54, -3.0); //E
                       glTexCoord2f(1.0,0.0);
            glVertex3f (3.0, -0.54, -3.0); //F
                       glTexCoord2f(1.0,1.0);
            glVertex3f (3.0, 2.5, -3.0); //G
                       glTexCoord2f(0.0,1.0);
            glVertex3f (-3.0, 2.5, -3.0); //H
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, bg2[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS); //AEHD Samping Kiri
                    glTexCoord2f(0.0,0.0);
        glVertex3f (-3.0, -0.54, 5.0); //A
                   glTexCoord2f(1.0,0.0);
        glVertex3f (-3.0, -0.54, -3.0); //E
                   glTexCoord2f(1.0,1.0);
        glVertex3f (-3.0, 2.5, -3.0); //H
                   glTexCoord2f(0.0,1.0);
        glVertex3f (-3.0, 2.3, 5.0); //D
        glEnd();
    glDisable(GL_TEXTURE_2D);
    
    glBindTexture(GL_TEXTURE_2D, bg3[0]);
    glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS); //ABFE Bawah
                    glTexCoord2f(0.0,0.0);
        glVertex3f (-3.0, -0.54, 5.0); //A
                   glTexCoord2f(1.0,0.0);
        glVertex3f (3.0, -0.54, 5.0); //B
                   glTexCoord2f(1.0,1.0);
        glVertex3f (3.0, -0.54, -3.0); //F
                   glTexCoord2f(0.0,1.0);
        glVertex3f (-3.0, -0.54, -3.0); //E
        glEnd();
    glDisable(GL_TEXTURE_2D);
          
}
void rotate (void) {
     
    glPushMatrix();// fungsinya untuk menyimpan koordinat yang ada
    glTranslatef(0.0f, 0.0f, -object01_size*2.0);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
        
    badan();
    kepala();
    tangan_kiri();
    tangan_kanan();
    rok();
    kaki();
        
    glPopMatrix();// fungsi nya untuk memanggil suatu fungsi yang telah disimpan pada glPushMatrix.
 
}

void rotateMugi (void) {
     
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -object01_size*2.0);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
        
    badan();
    kepalaMugi();
    tangan_kiri();
    tangan_kanan();
    rok();
    kaki();
        
    glPopMatrix();
 
}

void rotateYui (void) {
     
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, -object01_size*2.0);
    glRotatef(xRot, 1.0f, 0.0f, 0.0f);
    glRotatef(yRot, 0.0f, 1.0f, 0.0f);
        
    badan();
    kepalaYui();
    tangan_kiri();
    tangan_kanan();
    rok();
    kaki();
        
    glPopMatrix();
 
}

void reshape (int w, int h) {
     
    glViewport (0, 0, (GLsizei) w, (GLsizei) h); // Menjadikan viewport kepada segi empat tepat dengan lebar, w dan tinggi, h di mana penjuru kiri ialah (x,y) dalam window.
    glMatrixMode (GL_PROJECTION);// Memaparkan gambaran objek dalam 2-dimensi dalam OpenGL dan menetapkan parameter unjuran.
    glLoadIdentity ();// Menetapkan matrik kepada identiti
    gluPerspective(15, (GLfloat) w /(GLfloat) h , 0.15, 100.0);// Menentukan derajat sudut pandangan bagi unjuran perspektif simetrik.
    glMatrixMode(GL_MODELVIEW);// Untuk menetapkan mod untuk matrik transformasi geometrik
    gluLookAt (rotLx, 3, 10.0 + rotLz, 0.0, 0.3, 0.0, 0.0, 1.0, 0.0);// Menetapkan parameter pandangan 3-Dimensi
}

void display(void) {
             
    int i, n;
        
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);// Fungsinya untuk menghapus window dan memberi warna yang telah kita definisikan 
    if (Wireframe)
       glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    //isi objek disini mas broooo :D
    
    if (pointerPath == 0)
    {
        rotate();
        background();
    }
            
    if (pointerPath == 1)
    {
        rotateMugi();
        background();
    }
    
    if (pointerPath == 2)
    {
        rotateYui();
        background();
    }
            
    glPopMatrix();
    glFlush ();// untuk memastikan bahwa perintah gambar di eksekusi
    glutPostRedisplay();// adalah mengirimkan perintah untuk mengaktifkan display secara berkala atau looping
}

void SpecialKeys(int key, int x, int y) {
     
    float awalY;
    
    //zoom in
	if(key == GLUT_KEY_UP)
	if(rotLz + 1 >= 0)
    rotLz -= 0.2f;           
    glMatrixMode(GL_MODELVIEW);    
    glLoadIdentity();
    gluLookAt (rotLx, 3, 10.0 + rotLz, 0.0, 0.3, 0.0, 0.0, 1.0, 0.0);
	
    //zoom out    
    if(key == GLUT_KEY_DOWN)
    if(rotLz + 1 <= 6.7) 
    rotLz += 0.2f;
    glMatrixMode(GL_MODELVIEW);// Untuk dapat menampilkan objek 3D pada layar monitor
    glLoadIdentity();
    gluLookAt (rotLx, 3, 10.0 + rotLz, 0.0, 0.3, 0.0, 0.0, 1.0, 0.0);

	if(key == GLUT_KEY_LEFT)
		yRot -= 5.0f;

	if(key == GLUT_KEY_RIGHT)
		yRot += 5.0f;
                
        xRot = (GLfloat)((const int)xRot % 360);
        yRot = (GLfloat)((const int)yRot % 360);

	// Refresh the Window
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {  
        case 'w':
            Wireframe = !Wireframe;
            break;
        
        case 'q':
        case 27:
            exit(0);
            break;
        
        case 'r':
            rotLx = 0.0f;
            rotLy = 0.0f;
            rotLz = 0.0f;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt (rotLx, 3, 10.0 + rotLz, 0.0, 0.3, 0.0, 0.0, 1.0, 0.0);
            //rotateAwal ();
            break;
       
       case '1':
           pointerPath = 0;
           break;
       
       case '2':
           pointerPath = 1;
           break;
           
       case '3':
           pointerPath = 2;
           break;

    }
  glutPostRedisplay();
} // keyboard 

void idle(void)
{
    glutPostRedisplay();
} // idle

void menu(int item)
{
    keyboard((unsigned char) item, 0, 0);
} // menu

//program utama
int main(int argc, char** argv) {

    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);// fungsi yang sedikit lebih terlibat karena mendefinisikan jenis kontek openGL
    glutInitWindowSize (600, 400);// fungsi untuk Menetapkan ukuran windows
    glutInitWindowPosition (100, 70);// fungsi untuk menetapkan posisi windows
    glutCreateWindow ("TUGAS BESAR KOMPUTER GRAFIKA");// fungsi untuk membuat judul "TUGAS BESAR KOMPUTER GRAFIKA"
    
    glutCreateMenu(menu);// fungsi untuk menentukan menu
    glutAddMenuEntry("TUGAS BESAR KOMPUTER GRAFIKA", 0);// fungsi untuk memasukkan daftar menu
    glutAddMenuEntry("", 0);
    glutAddMenuEntry("[w] Kerangka", 'w');
    glutAddMenuEntry("[1] Mio", '1');
    glutAddMenuEntry("[2] Mugi", '2');
    glutAddMenuEntry("[3] Yui", '3');
    glutAddMenuEntry("", 0);
    glutAddMenuEntry("[q] Quit", 27);
    glutAttachMenu(GLUT_RIGHT_BUTTON);// fungsi rotasi 
    
    init ();
    glutDisplayFunc(display);//menampilkan callback
    glutReshapeFunc(reshape);// melakukan registrasi callback reshape
    glutKeyboardFunc(keyboard);//  fungsi untuk mendeteksi input dari keyboard.
    glutSpecialFunc(SpecialKeys);// fungsi callback pada opengl yang digunakan untuk mengaktifkan tombol-tombol khusus pada keyboard
    glutIdleFunc(idle);// Fungsi untuk waktu jeda
    glutMainLoop();//me-looping fungsi main untuk memantau aksi user
    return 0;

}
