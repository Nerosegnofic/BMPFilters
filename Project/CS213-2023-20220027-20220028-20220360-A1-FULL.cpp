// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:			    CS213-2023-20220027-20220028-20220360-A1-Part1.cpp
// Last Modification Date:	    10/6/2023
// Author1 and ID, Email, and Group:	Nour-aldeen Alaa            20220360 - nouralaa2279@gmail.com -  To Be Determined
// Author2 and ID, Email, and Group:	Ahmed Alaa Al-Din Mostafa   20220028 - alaa25086@gmail.com    -  To Be Determined
// Author3 and ID, Email, and Group:	Ahmed Abdelnabi Abdelrasol  20220027 - amedgamer36@gmail.com  -  To Be Determined
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

//_________________________________________
void invert() {
    for (int i {0}; i < SIZE; ++i) {
        for (int j {0}; j < SIZE; ++j) {
            image[i][j] = 255 - image[i][j];
        }
    }
}

//_________________________________________
void merge() {
    char imageFileName[100];
    unsigned char image2[SIZE][SIZE];
    unsigned char image3[SIZE][SIZE];

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

//_________________________________________
void flip() {
    // ask the user about the way to flip the image (vertically or horizontally)
    cout << "Enter 'H' if you want to flip the image horizontally, otherwise enter 'V'" << endl;
    char choice;
    // check receiving a valid option
    do {
        cin >> choice;
        if (choice != 'H' && choice != 'h' && choice != 'V' && choice != 'v') {
            cout << "Invalid input. Try again." << endl;
        }
    } while (choice != 'H' && choice != 'h' && choice != 'V' && choice != 'v');
    switch (choice) {
        // if horizontally go through each row and swap each column from the left with its counterpart from the right
        case 'H':
        case 'h':
            for (int i {0}; i < SIZE; ++i) {
                for (int j{0}; j < SIZE / 2; ++j) {
                    swap(image[i][j], image[i][SIZE - j - 1]);
                }
            }
            break;
            // if vertically go through each column and swap each row from the left with it counterpart from the right
        case 'V':
        case 'v':
            for (int i {0}; i < SIZE / 2; ++i) {
                for (int j {0}; j < SIZE; ++j) {
                    swap(image[i][j], image[SIZE - i - 1][j]);
                }
            }
            break;

        default:
            break;
    }
}

//_________________________________________
void rotate() {
    unsigned char imageCopy[SIZE][SIZE];
    unsigned char imageCopy2[SIZE][SIZE];
    unsigned char imageCopy3[SIZE][SIZE];

    int choice;
    cout << "How many degrees do you want the image to be rotated? (90, 180, 270)" << endl;
    do {
        cin >> choice;
        if (choice != 90 && choice != 180 && choice != 270) {
            cout << "Invalid Input. Try again." << endl;
        }
    } while (choice != 90 && choice != 180 && choice != 270);

    switch (choice) {
        /*First pixels row of original image is the last pixels column of resulting image,
         * and second pixels row of original image is the second last pixels column of resulting image,
         * and so on until the last pixels row of original image is the first pixels column of resulting image.*/
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

//_________________________________________
void darken_and_lighten() {
    cout << "Do you want to (d)arken or (l)ighten?" << endl;
    char choice;
    do {
        cin >> choice;
        if (choice != 'd' && choice != 'D' && choice != 'l' && choice != 'L') {
            cout << "Invalid Input. Try again. ";
        }
    } while (choice != 'd' && choice != 'D' && choice != 'l' && choice != 'L');

    if (choice == 'd' || choice == 'D') {
        //To make the image darker by 50%, you have to decrease the number of bits in the pixel by half
        //because as we know the pixel in gray-scale images are from zero(Black) to 255(White) bits
        //so decreasing the bits in the pixel make it more dark.

        for (int i {0}; i < SIZE; ++i) {
            for (int j {0}; j < SIZE; ++j) {
                image[i][j] /= 2;
            }
        }
    } else if (choice == 'l' || choice == 'L') {
        //Same thing for making it more white, but this time you have to increase the number of bits in the pixel

        for (int i {0}; i < SIZE; ++i) {
            for (int j {0}; j < SIZE; ++j) {
                double AmountOfIncrease = (255.0 - image[i][j]) / 2;
                image[i][j] += AmountOfIncrease;
            }

        }
    }
}

//_________________________________________
void detect_edges() {

}

//_________________________________________
void enlarge() {
    unsigned char quarter_image[128][128];
    unsigned char enlarged_image[SIZE][SIZE];

    // ask the user which quarter they want to enlarge
    cout << "Which quarter do you want to enlarge?" << endl;
    int choice;
    do {
        cin >> choice;
        if (choice != 1 && choice != 2 && choice != 3 && choice != 4) {
            cout << "Invalid Input. Try again. ";
        }
    } while (choice != 1 && choice != 2 && choice != 3 && choice != 4);

    switch (choice) {
        case 1:
            for (int i {0}; i < 128 ; ++i) {
                for (int j{0}; j < 128; ++j) {
                    quarter_image[i][j] = image[i][j];
                }
            }
            break;

        case 2:
            for (int i {0}; i < 128; ++i) {
                for (int j {0}; j < 128; ++j) {
                    quarter_image[i][j] = image[i][j + 128];
                }
            }
            break;

        case 3:
            for (int i {0}; i < 128; ++i) {
                for (int j {0}; j < 128; ++j) {
                    quarter_image[i][j] = image[i + 128][j];
                }
            }
            break;

        case 4:
            for (int i {}; i < 128; ++i) {
                for (int j {0}; j < 128; ++j) {
                    quarter_image[i][j] = image[i + 128][j + 128];
                }
            }
            break;

        default:
            break;
    }

    for(int i {0}, x {0}; i < SIZE; ++++i, ++x) {
        for (int j {0}, y {0}; j < SIZE; ++ ++j, ++y) {
            enlarged_image[i][j]
                    = enlarged_image[i + 1][j]
                    = enlarged_image[i][j + 1]
                    = enlarged_image[i + 1][j + 1]
                    = quarter_image[x][y];
        }
    }

    char imageCopyFileName[100];

    cout << "Enter the target image file name: ";
    cin >> imageCopyFileName;

    strcat(imageCopyFileName, ".bmp");
    writeGSBMP(imageCopyFileName, enlarged_image);

}

//_________________________________________
void shrink() {

}

//_________________________________________
void mirror() {
    unsigned char half_image[256][128];
    char choice;

    cout << "Which part do you want to mirror? (L)eft, (R)ight, (U)p, or (D)own?";
    do {
        cin >> choice;
        if (choice != 'd' && choice != 'l') {
            cout << "Invalid Input. Try again. ";
        }
    } while (choice != 'd' && choice != 'l');


}

//_________________________________________
void shuffle() {

}

//_________________________________________
void blur() {

}

//_________________________________________
void crop() {

}

//_________________________________________
void skew() {

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
             << "7  - Detect Image Edges."
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
                flip();
                break;
            case 5:
                rotate();
                break;
            case 6:
                darken_and_lighten();
                break;
            case 7:
                detect_edges();
                break;
            case 8:
                enlarge();
                break;
            case 9:
                shrink();
                break;
            case 10:
                mirror();
                break;
            case 11:
                shuffle();
                break;
            case 12:
                blur();
                break;
            case 13:
                crop();
                break;
            case 14:
                skew();
                break;
            default:
                break;
        }
        if (choice != 0 && choice != 3 && choice != 5 && choice != 8) {
            saveImage();
        }
    } while (choice != 0);
}
