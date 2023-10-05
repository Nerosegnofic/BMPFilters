// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:			    demo2.cpp
// Last Modification Date:	    10/5/2023
// Author1 and ID and Group:	Nour-aldeen Alaa    20220360
// Author2 and ID and Group:	xxxxx xxxxx
// Author3 and ID and Group:	xxxxx xxxxx
// Teaching Assistant:		xxxxx xxxxx
// Purpose: Applying filters to images


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
    unsigned char imageCopy[SIZE][SIZE];
    unsigned char imageCopy2[SIZE][SIZE];
    unsigned char imageCopy3[SIZE][SIZE];

    int choice;
    cout << "How many degrees do you want the image to be rotated? (90, 180, 270) ";
    do {
        cin >> choice;
        if (choice != 90 && choice != 180 && choice != 270) {
            cout << "Invalid Input. Try again. ";
        }
    } while (choice != 90 && choice != 180 && choice != 270);

    switch (choice) {
        case 90:
            for (int i {0}; i < SIZE; ++i) {
                for (int j {0}; j < SIZE; ++j) {
                    imageCopy[j][SIZE - i - 1] = image[i][j];
                }
            }
            break;

        case 180:
            for (int i {0}; i < SIZE; ++i) {
                for (int j {0}; j < SIZE; ++j) {
                    imageCopy[j][SIZE - i - 1] = image[i][j];
                }
            }

            for (int i {0}; i < SIZE; ++i) {
                for (int j {0}; j < SIZE; ++j) {
                    imageCopy2[j][SIZE - i - 1] = imageCopy[i][j];
                }
            }
            break;

        case 270:
            for (int i {0}; i < SIZE; ++i) {
                for (int j {0}; j < SIZE; ++j) {
                    imageCopy[j][SIZE - i - 1] = image[i][j];
                }
            }

            for (int i {0}; i < SIZE; ++i) {
                for (int j {0}; j < SIZE; ++j) {
                    imageCopy2[j][SIZE - i - 1] = imageCopy[i][j];
                }
            }

            for (int i {0}; i < SIZE; ++i) {
                for (int j {0}; j < SIZE; ++j) {
                    imageCopy3[j][SIZE - i - 1] = imageCopy2[i][j];
                }
            }

            break;
        default:
            break;
    }

    char imageCopyFileName[100];

    cout << "Enter the target image file name: ";
    cin >> imageCopyFileName;

    strcat (imageCopyFileName, ".bmp");
    if (choice == 90) {
        writeGSBMP(imageCopyFileName, imageCopy);
    } else if (choice == 180) {
        writeGSBMP(imageCopyFileName, imageCopy2);
    } else if (choice == 270) {
        writeGSBMP(imageCopyFileName, imageCopy3);
    }
}

void darken_and_lighten() {
    cout << "Do you want to (d)arken or (l)ighten?\n";
    char choice;
    cin >> choice;

    if (choice == 'd') {
        //To make the image darker by 50%, you have to decrease the number of bits in the pixel by half
        //because as we know the pixel in gray-scale images are from zero(Black) to 255(White) bits
        //so decreasing the bits in the pixel make it more dark.

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                image[i][j] /= 2;
            }
        }
    } else if(choice == 'l'){
        //Same thing for making it more white, but this time you have to increase the number of bits in the pixel

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                double AmountOfIncrease = (255 - image[i][j])/2;
                image[i][j] = image[i][j] + AmountOfIncrease;
            }

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
             << "0 - Exit" << endl;
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
        if (choice != 0 && choice != 3) {
            saveImage();
        }
    } while (choice != 0);

}
