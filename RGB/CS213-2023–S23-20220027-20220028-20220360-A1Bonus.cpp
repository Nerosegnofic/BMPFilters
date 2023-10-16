// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:			    CS213-2023–S23-20220027-20220028-20220360-A1Bonus
// Last Modification Date:	    14/6/2023
// Author1 and ID, Email, and Group:	Nour-aldeen Alaa            20220360 - nouralaa2279@gmail.com -  S24
// Author2 and ID, Email, and Group:	Ahmed Alaa Al-Din Mostafa   20220028 - alaa25086@gmail.com    -  S23
// Author3 and ID, Email, and Group:	Ahmed Abdelnabi Abdelrasol  20220027 - amedgamer36@gmail.com  -  S23
// Teaching Assistant:		To Be Determined
// Purpose: Applying Filters to 256x256 BMP RGB Images

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;

unsigned char image[SIZE][SIZE][RGB];
unsigned char result_image[SIZE][SIZE][RGB];

void loadImage ();
void saveImage ();
void menu();
void BW();
void invert();
void merge();
void flip();
void rotate();
void darken_and_lighten();
void detect_edges();
void enlarge();
void shrink();
void mirror();
void shuffle();
void blur();
void crop();
void skew();
void skew_vertically();

int main() {
    menu();
    return 0;
}

//_________________________________________
void loadImage() {
   char imageFileName[100];

   // Get gray scale image file name
   cout << "Enter the source image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat(imageFileName, ".bmp");
   readRGBBMP(imageFileName, image);
}

//_________________________________________
void saveImage() {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Enter the target image file name: ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat(imageFileName, ".bmp");
   writeRGBBMP(imageFileName, result_image);
}

//_________________________________________
void BW() {
    int avg {0};
    for (int i {0}; i < SIZE; ++i) {
        for (int j {0}; j < SIZE; ++j) {
            avg += image[i][j][0] + image[i][j][1] + image[i][j][2];
        }
    }
    avg /= SIZE * SIZE * RGB;

    for (int i {0}; i < SIZE; ++i) {
        for (int j {0}; j < SIZE; ++j) {
            if (image[i][j][0] + image[i][j][1] + image[i][j][2] > avg) {
                image[i][j][0] = image[i][j][1] = image[i][j][2] = 255;
            } else {
                image[i][j][0] = image[i][j][1] = image[i][j][2] = 0;
            }
        }
    }

    for (int i {0}; i < SIZE; ++i) {
        for (int j {0}; j < SIZE; ++j) {
            result_image[i][j][0] = image[i][j][0];
            result_image[i][j][1] = image[i][j][1];
            result_image[i][j][2] = image[i][j][2];
        }
    }
}

//_________________________________________
void invert() {
    for (int i {0}; i < SIZE; ++i) {
        for (int j {0}; j < SIZE; ++j) {
            result_image[i][j][0] = 255 - image[i][j][0];
            result_image[i][j][1] = 255 - image[i][j][1];
            result_image[i][j][2] = 255 - image[i][j][2];
        }
    }
}

//_________________________________________
void merge() {
    char imageFileName[100];
    unsigned char image2[SIZE][SIZE][RGB];
    unsigned char image3[SIZE][SIZE][RGB];

    cout << "Enter the second source image file name: ";
    cin >> imageFileName;

    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, image2);

    for (int i {0}; i < SIZE; ++i) {
        for (int j {0}; j < SIZE; ++j) {
            image3[i][j][0] = (image[i][j][0] + image2[i][j][0]) / 2;
            image3[i][j][1] = (image[i][j][1] + image2[i][j][1]) / 2;
            image3[i][j][2] = (image[i][j][2] + image2[i][j][2]) / 2;
        }
    }

    for (int i {0}; i < SIZE; ++i) {
        for (int j {0}; j < SIZE; ++j) {
            result_image[i][j][0] = image3[i][j][0];
            result_image[i][j][1] = image3[i][j][1];
            result_image[i][j][2] = image3[i][j][2];
        }
    }
}

//_________________________________________
void flip() {

}

//_________________________________________
void rotate() {

}

//_________________________________________
void darken_and_lighten() {

}

//_________________________________________
void detect_edges() {

}

//_________________________________________
void enlarge() {

}

//_________________________________________
void shrink() {

}

//_________________________________________
void mirror() {

}

//_________________________________________
void shuffle() {

}

//_________________________________________
void crop() {

}

//_________________________________________
void skew() {

}

//_________________________________________
void skew_vertically() {

}

//_________________________________________
void menu() {
    int choice;
    do {
        loadImage();
        cout << "What filter do you want to apply upon this image?\n";
        cout << "=================================================\n";
        cout << "1  - Black and White Image.\n"
             << "2  - Invert Image.\n"
             << "3  - Merge Two Images.\n"
             << "4  - Flip Image.\n"
             << "5  - Rotate Image.\n"
             << "6  - Darken and Lighten Image.\n"
             << "7  - Detect Image Edges.\n"
             << "8  - Enlarge Image.\n"
             << "9  - Shrink Image.\n"
             << "10 - Mirror Image.\n"
             << "11 - Shuffle Image.\n"
             << "12 - Blur Image.\n"
             << "13 - Crop Image.\n"
             << "14 - Skew Image.\n"
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
//                flip();
                break;
            case 5:
//                rotate();
                break;
            case 6:
//                darken_and_lighten();
                break;
            case 7:
//                detect_edges();
                break;
            case 8:
//                enlarge();
                break;
            case 9:
//                shrink();
                break;
            case 10:
//                mirror();
                break;
            case 11:
//                shuffle();
                break;
            case 12:
//                blur();
                break;
            case 13:
//                crop();
                break;
            case 14:
//                skew();
                break;
            default:
                break;
        }

        if (choice != 0) {
            cout << "Do you want to save this filter?" << endl;
            cout << "(Y): yes or (N): no" << endl;

            char choice2;
            cin >> choice2;
            choice2 = tolower(choice2);

            if (choice2 == 'y') {
                saveImage();
                cout << "Do you want to exit? (y) yes or (n) no" << endl;
                cin >> choice2;
                if (choice2 == 'y')
                    return;
            }
        }
    } while (choice != 0);
}
