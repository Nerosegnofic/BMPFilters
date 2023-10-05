// Program: demo2.cpp
// Purpose: Demonstrate use of bmplip for handling
//          bmp colored and grayscale images
//          Program load a gray image and store in another file
// Author:  Mohammad El-Ramly
// Date:    30 March 2018
// Version: 1.0

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;
unsigned char image[SIZE][SIZE];
unsigned char image2[SIZE][SIZE];
unsigned char image3[SIZE][SIZE];


void loadImage ();
void saveImage ();
void menu();
void BW();
void invert();
void merge();
void flip();
void rotate();
void darken_and_lighten();


int main() {
  menu();
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
void BW() {
    int avg {0};
  for (int i {0}; i < SIZE; ++i) {
    for (int j {0}; j < SIZE; ++j) {
        avg += image[i][j];
    }
  }
  avg /= SIZE * SIZE;

  for (int i {0}; i < SIZE; ++i) {
      for (int j {0}; j < SIZE; ++j) {
          if (image[i][j] > avg) {
              image[i][j] = 255;
          } else {
              image[i][j] = 0;
          }
      }
  }
}

void invert() {
    for (int i {0}; i < SIZE; ++i) {
        for (int j {0}; j < SIZE; ++j) {
            image[i][j] = 255 - image[i][j];
        }
    }
}

void merge() {
    char imageFileName[100];

    cout << "Enter the second source image file name: ";
    cin >> imageFileName;

    strcat (imageFileName, ".bmp");
    readGSBMP(imageFileName, image2);

    for (int i {0}; i < SIZE; ++i) {
        for (int j {0}; j < SIZE; ++j) {
            image3[i][j] = (image[i][j] + image2[i][j]) / 2;
        }
    }

    char image3FileName[100];

    cout << "Enter the target image file name: ";
    cin >> image3FileName;

    // Add to it .bmp extension and load image
    strcat (image3FileName, ".bmp");
    writeGSBMP(image3FileName, image3);
}

void flip() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            // do something with the image
        }
    }
}

void rotate() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {
            // do something with the image
        }
    }
}

void darken_and_lighten() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j< SIZE; j++) {

        // do something with the image
        }
    }
}

void menu() {
    int choice;
    do {
        loadImage();
        cout << "What filter do you want to apply upon this image?\n";
        cout << "=================================================\n";
        cout << "1 - Black and White Image.\n"
             << "2 - Invert Image.\n"
             << "3 - Merge Two Images.\n"
             << "4 - Flip Image.\n"
             << "5 - Rotate Image.\n"
             << "6 - Darken and Lighten Image.\n"
             << "7 - Exit" << endl;
        cin >> choice;
        switch (choice) {
            case 1:
                BW();
                break;
            case 2:
                invert();
                break;
            case 3:
                merge();
                break;
            case 4:
                flip();
                break;
            case 5:
                rotate();
                break;
            case 6:
                darken_and_lighten();
                break;
            default:
                break;
        }
        if (choice != 7 && choice != 3) {
            saveImage();
        }
    } while (choice != 7);

}
