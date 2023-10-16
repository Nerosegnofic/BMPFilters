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
    unsigned char imageCopy[SIZE][SIZE][RGB];
    unsigned char imageCopy2[SIZE][SIZE][RGB];
    unsigned char imageCopy3[SIZE][SIZE][RGB];

    int choice;
    cout << "How many degrees do you want the image to be rotated? (90, 180, 270)" << endl;
    do {
        cin >> choice;
        if (choice != 90 && choice != 180 && choice != 270) {
            cout << "Invalid input. Try again." << endl;
        }
    } while (choice != 90 && choice != 180 && choice != 270);

    switch (choice) {
        /*First pixels row of original image is the last pixels column of resulting image,
         * and second pixels row of original image is the second last pixels column of resulting image,
         * and so on until the last pixels row of original image is the first pixels column of resulting image.*/
        case 90:
            for (int i {0}; i < SIZE; ++i) {
                for (int j {0}; j < SIZE; ++j) {
                    imageCopy[j][SIZE - i - 1][0] = image[i][j][0];
                    imageCopy[j][SIZE - i - 1][1] = image[i][j][1];
                    imageCopy[j][SIZE - i - 1][2] = image[i][j][2];
                }
            }
            break;

        case 180:
            for (int i {0}; i < SIZE; ++i) {
                for (int j {0}; j < SIZE; ++j) {
                    imageCopy[j][SIZE - i - 1][0] = image[i][j][0];
                    imageCopy[j][SIZE - i - 1][1] = image[i][j][1];
                    imageCopy[j][SIZE - i - 1][2] = image[i][j][2];
                }
            }

            for (int i {0}; i < SIZE; ++i) {
                for (int j {0}; j < SIZE; ++j) {
                    imageCopy2[j][SIZE - i - 1][0] = imageCopy[i][j][0];
                    imageCopy2[j][SIZE - i - 1][1] = imageCopy[i][j][1];
                    imageCopy2[j][SIZE - i - 1][2] = imageCopy[i][j][2];
                }
            }
            break;

        case 270:
            for (int i {0}; i < SIZE; ++i) {
                for (int j {0}; j < SIZE; ++j) {
                    imageCopy[j][SIZE - i - 1][0] = image[i][j][0];
                    imageCopy[j][SIZE - i - 1][1] = image[i][j][1];
                    imageCopy[j][SIZE - i - 1][2] = image[i][j][2];
                }
            }

            for (int i {0}; i < SIZE; ++i) {
                for (int j {0}; j < SIZE; ++j) {
                    imageCopy2[j][SIZE - i - 1][0] = imageCopy[i][j][0];
                    imageCopy2[j][SIZE - i - 1][1] = imageCopy[i][j][1];
                    imageCopy2[j][SIZE - i - 1][2] = imageCopy[i][j][2];
                }
            }

            for (int i {0}; i < SIZE; ++i) {
                for (int j {0}; j < SIZE; ++j) {
                    imageCopy3[j][SIZE - i - 1][0] = imageCopy2[i][j][0];
                    imageCopy3[j][SIZE - i - 1][1] = imageCopy2[i][j][1];
                    imageCopy3[j][SIZE - i - 1][2] = imageCopy2[i][j][2];
                }
            }

            break;
        default:
            break;
    }

    if (choice == 90) {
        for (int i {0}; i < SIZE; ++i) {
            for (int j {0}; j < SIZE; ++j) {
                result_image[i][j][0] = imageCopy[i][j][0];
                result_image[i][j][1] = imageCopy[i][j][1];
                result_image[i][j][2] = imageCopy[i][j][2];
            }
        }
    } else if (choice == 180) {
        for (int i {0}; i < SIZE; ++i) {
            for (int j {0}; j < SIZE; ++j) {
                result_image[i][j][0] = imageCopy2[i][j][0];
                result_image[i][j][1] = imageCopy2[i][j][1];
                result_image[i][j][2] = imageCopy2[i][j][2];
            }
        }
    } else if (choice == 270) {
        for (int i {0}; i < SIZE; ++i) {
            for (int j {0}; j < SIZE; ++j) {
                result_image[i][j][0] = imageCopy3[i][j][0];
                result_image[i][j][1] = imageCopy3[i][j][1];
                result_image[i][j][2] = imageCopy3[i][j][2];
            }
        }
    }
}

//_________________________________________
void darken_and_lighten() {
    cout << "Do you want to (d)arken or (l)ighten?" << endl;
    char choice;
    do {
        cin >> choice;
        if (choice != 'd' && choice != 'D' && choice != 'l' && choice != 'L') {
            cout << "Invalid input. Try again." << endl;
        }
    } while (choice != 'd' && choice != 'D' && choice != 'l' && choice != 'L');

    if (choice == 'd' || choice == 'D') {
        //To make the image darker by 50%, you have to decrease the number of bits in the pixel by half
        //we'll do that for each RGB channel: Red, Green and Blue

        for (int i {0}; i < SIZE; ++i) {
            for (int j {0}; j < SIZE; ++j) {
                image[i][j][0] /= 2, image[i][j][1] /= 2, image[i][j][2] /= 2;
            }
        }
    } else if (choice == 'l' || choice == 'L') {
        //Same thing for making it more white, but this time you have to increase the number of bits in the pixel

        for (int i {0}; i < SIZE; ++i) {
            for (int j {0}; j < SIZE; ++j) {
                double AmountOfIncrease = (255.0 - image[i][j][0]) / 2;
                image[i][j][0] += AmountOfIncrease;

                AmountOfIncrease = (255.0 - image[i][j][1]) / 2;
                image[i][j][1] += AmountOfIncrease;

                AmountOfIncrease = (255.0 - image[i][j][2]) / 2;
                image[i][j][2] += AmountOfIncrease;
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
    char choice;

    cout << "Which part do you want to mirror? (L)eft, (R)ight, (U)p, or (D)own?" << endl;
    do {
        cin >> choice;
        if (choice != 'l' && choice != 'L' && choice != 'r' && choice != 'R' && choice != 'u' && choice != 'U' && choice != 'd' && choice != 'D') {
            cout << "Invalid Input. Try again." << endl;
        }
    } while (choice != 'l' && choice != 'L' && choice != 'r' && choice != 'R' && choice != 'u' && choice != 'U' && choice != 'd' && choice != 'D');

    // Put every pixel on its opposite side of the image depending on user choice
    switch (choice) {
        case 'l':
        case 'L':
            for (int i {0}; i < SIZE; ++i) {
                for (int j {0}; j < SIZE / 2; ++j) {
                    image[i][SIZE - j - 1][0] = image[i][j][0];
                    image[i][SIZE - j - 1][1] = image[i][j][1];
                    image[i][SIZE - j - 1][2] = image[i][j][2];
                }
            }
            break;

        case 'r':
        case 'R':
            for (int i {0}; i < SIZE; ++i) {
                for (int j {255}; j >= SIZE / 2; --j) {
                    image[i][SIZE - j - 1][0] = image[i][j][0];
                    image[i][SIZE - j - 1][1] = image[i][j][1];
                    image[i][SIZE - j - 1][2] = image[i][j][2];
                }
            }
            break;

        case 'u':
        case 'U':
            for (int i {0}; i < SIZE / 2; ++i) {
                for (int j {0}; j < SIZE; ++j) {
                    image[SIZE - i - 1][j][0] = image[i][j][0];
                    image[SIZE - i - 1][j][1] = image[i][j][1];
                    image[SIZE - i - 1][j][2] = image[i][j][2];
                }
            }
            break;

        case 'd':
        case 'D':
            for (int i {255}; i >= SIZE / 2; --i) {
                for (int j {0}; j < SIZE; ++j) {
                    image[SIZE - i - 1][j][0] = image[i][j][0];
                    image[SIZE - i - 1][j][1] = image[i][j][1];
                    image[SIZE - i - 1][j][2] = image[i][j][2];
                }
            }

        default:
            break;
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
void shuffle() {

}

//_________________________________________
void blur() {
    unsigned char imageCopy[SIZE][SIZE][RGB];

    for (int i {0}; i < SIZE; ++i) {
        for (int j {0}; j < SIZE; ++j) {
            imageCopy[i][j][0] = image[i][j][0];
            imageCopy[i][j][1] = image[i][j][1];
            imageCopy[i][j][2] = image[i][j][2];
        }
    }

    // Get the average of all adjacent pixels of every pixel
    for (int i {0}; i < SIZE; ++i) {
        for (int j {0}; j < SIZE; ++j) {
            if (i == 0 && j == 0) {
                image[0][0][0] = (imageCopy[0][0][0] + imageCopy[0][1][0] + imageCopy[1][0][0] + imageCopy[1][1][0]) / 4;
                image[0][0][1] = (imageCopy[0][0][1] + imageCopy[0][1][1] + imageCopy[1][0][1] + imageCopy[1][1][1]) / 4;
                image[0][0][2] = (imageCopy[0][0][2] + imageCopy[0][1][2] + imageCopy[1][0][2] + imageCopy[1][1][2]) / 4;
            } else if (i == 0 && j == 255) {
                image[0][255][0] = (imageCopy[0][255][0] + imageCopy[1][255][0] + imageCopy[1][254][0] + imageCopy[1][254][0]) / 4;
                image[0][255][1] = (imageCopy[0][255][1] + imageCopy[1][255][1] + imageCopy[1][254][1] + imageCopy[1][254][1]) / 4;
                image[0][255][2] = (imageCopy[0][255][2] + imageCopy[1][255][2] + imageCopy[1][254][2] + imageCopy[1][254][2]) / 4;
            } else if (i == 255 && j == 0) {
                image[255][0][0] = (imageCopy[255][0][0] + imageCopy[255][1][0] + imageCopy[254][0][0] + imageCopy[254][1][0]) / 4;
                image[255][0][1] = (imageCopy[255][0][1] + imageCopy[255][1][1] + imageCopy[254][0][1] + imageCopy[254][1][1]) / 4;
                image[255][0][2] = (imageCopy[255][0][2] + imageCopy[255][1][2] + imageCopy[254][0][2] + imageCopy[254][1][2]) / 4;
            } else if (i == 255 && j == 255) {
                image[255][255][0] = (imageCopy[255][255][0] + imageCopy[255][254][0] + imageCopy[254][255][0] + imageCopy[254][254][0]) / 4;
                image[255][255][1] = (imageCopy[255][255][1] + imageCopy[255][254][1] + imageCopy[254][255][1] + imageCopy[254][254][1]) / 4;
                image[255][255][2] = (imageCopy[255][255][2] + imageCopy[255][254][2] + imageCopy[254][255][2] + imageCopy[254][254][2]) / 4;
            } else if (i == 0) {
                image[0][j][0] = (imageCopy[0][j][0] + imageCopy[0][j - 1][0] + imageCopy[0][j + 1][0] + imageCopy[1][j][0] + imageCopy[1][j - 1][0] + imageCopy[1][j + 1][0]) / 6;
                image[0][j][1] = (imageCopy[0][j][1] + imageCopy[0][j - 1][1] + imageCopy[0][j + 1][1] + imageCopy[1][j][1] + imageCopy[1][j - 1][1] + imageCopy[1][j + 1][1]) / 6;
                image[0][j][2] = (imageCopy[0][j][2] + imageCopy[0][j - 1][2] + imageCopy[0][j + 1][2] + imageCopy[1][j][2] + imageCopy[1][j - 1][2] + imageCopy[1][j + 1][2]) / 6;
            } else if (i == 255) {
                image[255][j][0] = (imageCopy[255][j][0] + imageCopy[255][j - 1][0] + imageCopy[255][j + 1][0] + imageCopy[254][j][0] + imageCopy[254][j - 1][0] + imageCopy[254][j + 1][0]) / 6;
                image[255][j][1] = (imageCopy[255][j][1] + imageCopy[255][j - 1][1] + imageCopy[255][j + 1][1] + imageCopy[254][j][1] + imageCopy[254][j - 1][1] + imageCopy[254][j + 1][1]) / 6;
                image[255][j][2] = (imageCopy[255][j][2] + imageCopy[255][j - 1][2] + imageCopy[255][j + 1][2] + imageCopy[254][j][2] + imageCopy[254][j - 1][2] + imageCopy[254][j + 1][2]) / 6;
            } else if (j == 0) {
                image[i][0][0] = (imageCopy[i][0][0] + imageCopy[i + 1][0][0] + imageCopy[i - 1][0][0] + imageCopy[i][1][0] + imageCopy[i + 1][1][0] + imageCopy[i - 1][1][0]) / 6;
                image[i][0][1] = (imageCopy[i][0][1] + imageCopy[i + 1][0][1] + imageCopy[i - 1][0][1] + imageCopy[i][1][1] + imageCopy[i + 1][1][1] + imageCopy[i - 1][1][1]) / 6;
                image[i][0][2] = (imageCopy[i][0][2] + imageCopy[i + 1][0][2] + imageCopy[i - 1][0][2] + imageCopy[i][1][2] + imageCopy[i + 1][1][2] + imageCopy[i - 1][1][2]) / 6;
            } else if (j == 255) {
                image[i][255][0] = (imageCopy[i][255][0] + imageCopy[i + 1][255][0] + imageCopy[i - 1][255][0] + imageCopy[i][254][0] + imageCopy[i + 1][254][0] + imageCopy[i - 1][254][0]) / 6;
                image[i][255][1] = (imageCopy[i][255][1] + imageCopy[i + 1][255][1] + imageCopy[i - 1][255][1] + imageCopy[i][254][1] + imageCopy[i + 1][254][1] + imageCopy[i - 1][254][1]) / 6;
                image[i][255][2] = (imageCopy[i][255][2] + imageCopy[i + 1][255][2] + imageCopy[i - 1][255][2] + imageCopy[i][254][2] + imageCopy[i + 1][254][2] + imageCopy[i - 1][254][2]) / 6;
            } else {
                image[i][j][0] = (image[i][j][0] + image[i][j + 1][0] + image[i][j - 1][0] + image[i - 1][j - 1][0] + image[i - 1][j][0] + image[i - 1][j + 1][0] + image[i + 1][j - 1][0] + image[i + 1][j][0] + image[i + 1][j + 1][0]) / 9;
                image[i][j][1] = (image[i][j][1] + image[i][j + 1][1] + image[i][j - 1][1] + image[i - 1][j - 1][1] + image[i - 1][j][1] + image[i - 1][j + 1][1] + image[i + 1][j - 1][1] + image[i + 1][j][1] + image[i + 1][j + 1][1]) / 9;
                image[i][j][2] = (image[i][j][2] + image[i][j + 1][2] + image[i][j - 1][2] + image[i - 1][j - 1][2] + image[i - 1][j][2] + image[i - 1][j + 1][2] + image[i + 1][j - 1][2] + image[i + 1][j][2] + image[i + 1][j + 1][2]) / 9;
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
                rotate();
                break;
            case 6:
                darken_and_lighten();
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
                mirror();
                break;
            case 11:
//                shuffle();
                break;
            case 12:
                blur();
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
