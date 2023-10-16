// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:			    CS213-2023–S23-20220027-20220028-20220360-A1Bonus
// Last Modification Date:	    14/6/2023
// Author1 and ID, Email, and Group:	Nour-aldeen Alaa            20220360 - nouralaa2279@gmail.com -  S24
// Author2 and ID, Email, and Group:	Ahmed Alaa Al-Din Mostafa   20220028 - alaa25086@gmail.com    -  To Be Determined
// Author3 and ID, Email, and Group:	Ahmed Abdelnabi Abdelrasol  20220027 - amedgamer36@gmail.com  -  S23
// Teaching Assistant:		To Be Determined
// Purpose: Applying Filters to 256x256 BMP Images

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];

void loadImage ();
void saveImage ();
void doSomethingForImage ();

int main()
{
  loadImage();
  doSomethingForImage();
  saveImage();
  return 0;
}

//_________________________________________
void loadImage () {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readGSBMP(imageFileName, image);
}

//_________________________________________
void saveImage () {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, image);
}

//_________________________________________
void doSomethingForImage() {
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j< SIZE; j++) {

/* Example code to convert to BW the image
   A better version should NOt use 127 but the
   average of the pixels

        if (image[i][j] > 127)
            image[i][j] = 255;
        else
            image[i][j] = 0;
*/
// do something with the image
    }
  }
}
