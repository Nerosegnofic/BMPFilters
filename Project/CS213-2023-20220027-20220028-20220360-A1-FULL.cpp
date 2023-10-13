// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:			    CS213-2023-20220027-20220028-20220360-A1-Part1.cpp
// Last Modification Date:	    10/6/2023
// Author1 and ID, Email, and Group:	Nour-aldeen Alaa            20220360 - nouralaa2279@gmail.com -  To Be Determined
// Author2 and ID, Email, and Group:	Ahmed Alaa Al-Din Mostafa   20220028 - alaa25086@gmail.com    -  To Be Determined
// Author3 and ID, Email, and Group:	Ahmed Abdelnabi Abdelrasol  20220027 - amedgamer36@gmail.com  -  To Be Determined
// Teaching Assistant:		To Be Determined
// Purpose: Applying Filters to 256x256 BMP Images

#include <iostream>
#include <vector>
#include <algorithm>
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
      /*
     * Detecting Edges has many algorithms, here we'll do the sobel operator algorithm
     * This algorithm uses a 3*3 matrix with negative and positive same values and zeroes in the middle
     * we multiply the adjacents of each index in the original image by these values to know if there is a change
     * in the intensity of the picture happening or not, we do it vertically and horizontally
     * then we calculate the gradient and if its bigger than the threshold value then it is an edge
     *
     * NOTE: the threshold value is a value that you decide depending on whether you want the edges to be clear and a lot
     * or you want a light simple edges.
     * Make sure you search more on the algorithm to understand it better if you found struggle with the code
     */
    unsigned char EdgedImage[SIZE][SIZE];
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if(i == 0 || j == 0 || i == SIZE - 1 || j == SIZE - 1){ //if it is a corner, make it the same as the original pixel
                EdgedImage[i][j] = image[i][j];
                continue;
            }
            //Vertical change is the change in intensity in the x-axis
            int VerticalChange = (image[i-1][j-1]*-1) + (image[i][j-1]*-2) + (image[i+1][j-1]*-1)
                    + (image[i-1][j+1]) + (image[i][j+1]*2) + (image[i+1][j+1]);
            
            //Horizontal change is the change in intensity in the y-axis
            int HorizontalChange = (image[i-1][j-1]*-1) + (image[i-1][j]*-2) + (image[i-1][j+1]*-1)
                                   + (image[i+1][j-1]) + (image[i+1][j]*2) + (image[i+1][j+1]);
            
            //The gradient of these two changes will give us a value to determine by it the centered pixel if it is an edge or not
            //We do that by comparing this gradient value by a threshold value
            int gradient = (int)(round(sqrt( (VerticalChange*VerticalChange) + (HorizontalChange*HorizontalChange))));
            if(gradient > 180){ //if its bigger we'll consider it an edge so we make the pixel black
                EdgedImage[i][j] = 0;
            }
            else
                EdgedImage[i][j] = 255;
        }
    }
    char imageFileName[100];
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeGSBMP(imageFileName, EdgedImage);

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
            cout << "Invalid Input. Try again." << endl;
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
    cout << "Shrink to: a) 1/2, b) 1/3 or c) 1/4 ?\n";
    char ans;
    cin >> ans;
    unsigned char Shrinked_image[SIZE][SIZE];
    if(ans == 'a'){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                Shrinked_image[i][j] = 255;
            }
        }
        //Shrinking by half means we want each pixel to have two pixels of the original image
        //and since the pixel is a row and a column, then we want two pixels from the rows, and two from the columns
        //Example to make it clear: suppose we have an 8*8 bitmap, and we want to shrink it by half (4*4)
        //then the first pixel will have these indices (row,col): { (0,0), (0,1), (1,0), (1,1) }, we'll take the average of these pixels
        //so in the end each pixel in the shrinked image will have that 2*2 square

        for (int i = 0, x = 0; i < SIZE; i+=2, x++){
            for (int j = 0, y = 0; j < SIZE; j+=2, y++) {
                Shrinked_image[x][y] = (double)(image[i][j] + image[i][j+1] + image[i+1][j] + image[i+1][j+1])/4.0;
            }
        }

        char imageFileName[100];
        cout << "Enter the target image file name: ";
        cin >> imageFileName;
        strcat (imageFileName, ".bmp");
        writeGSBMP(imageFileName, Shrinked_image);

    }
    else if(ans == 'b'){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                Shrinked_image[i][j] = 255;
            }
        }
        //shrinking by 1/3 means taking the average of the 9 adjacent pixels
        for (int i = 1, x = 0; i < SIZE; i+=3, x++){
            for (int j = 1, y = 0; j < SIZE; j+=3, y++) {
                Shrinked_image[x][y] = (image[i][j] + image[i][j+1] + image[i][j - 1] + image[i+1][j] + image[i+1][j+1] + image[i+1][j - 1] + image[i - 1][j] + image[i - 1][j+1] + image[i - 1][j - 1])/9;
            }
        }

        char imageFileName[100];
        cout << "Enter the target image file name: ";
        cin >> imageFileName;
        strcat (imageFileName, ".bmp");
        writeGSBMP(imageFileName, Shrinked_image);

    }
    else if(ans == 'c'){
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                Shrinked_image[i][j] = 255;
            }
        }
        //shrinking by 1/4 means taking the average of the 16 adjacent pixels
        for (int i = 0, x = 0; i < SIZE; i+=4, x++){
            for (int j = 0, y = 0; j < SIZE; j+=4, y++) {
                Shrinked_image[x][y] = (image[i][j] + image[i][j+1] + image[i][j+2] + image[i][j+3]
                        + image[i+1][j] + image[i+1][j+1] + image[i+1][j+2] + image[i+1][j+3]
                        + image[i+2][j] + image[i+2][j+1] + image[i+2][j+2] + image[i+2][j+3]
                        + image[i+3][j] + image[i+3][j+1] + image[i+3][j+2] + image[i+3][j+3])/16;
            }
        }

        char imageFileName[100];
        cout << "Enter the target image file name: ";
        cin >> imageFileName;
        strcat (imageFileName, ".bmp");
        writeGSBMP(imageFileName, Shrinked_image);

    }
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
                    image[i][SIZE - j - 1] = image[i][j];
                }
            }
            break;

        case 'r':
        case 'R':
            for (int i {0}; i < SIZE; ++i) {
                for (int j {255}; j >= SIZE / 2; --j) {
                    image[i][SIZE - j - 1] = image[i][j];
                }
            }
            break;

        case 'u':
        case 'U':
            for (int i {0}; i < SIZE / 2; ++i) {
                for (int j {0}; j < SIZE; ++j) {
                    image[SIZE - i - 1][j] = image[i][j];
                }
            }
            break;

        case 'd':
        case 'D':
            for (int i {255}; i >= SIZE / 2; --i) {
                for (int j {0}; j < SIZE; ++j) {
                    image[SIZE - i - 1][j] = image[i][j];
                }
            }

        default:
            break;
    }
}

//_________________________________________
void shuffle() {
    vector<vector<vector<int>>> quarters(4, vector<vector<int>> (128, vector<int>(128)));
    for (int i {0}; i < 128; ++i) {
        for (int j {0}; j < 128; ++j) {
            quarters[0][i][j] = image[i][j];
        }
    }

    for (int i {0}; i < 128; ++i) {
        for (int j {0}; j < 128; ++j) {
            quarters[1][i][j] = image[i][j + 128];
        }
    }

    for (int i {0}; i < 128; ++i) {
        for (int j {0}; j < 128; ++j) {
            quarters[2][i][j] = image[i + 128][j];
        }
    }

    for (int i {0}; i < 128; ++i) {
        for (int j {0}; j < 128; ++j) {
            quarters[3][i][j] = image[i + 128][j + 128];
        }
    }

    int first_quarter, second_quarter, third_quarter, fourth_quarter;
    cout << "Enter your input." << endl;
    cin >> first_quarter >> second_quarter >> third_quarter >> fourth_quarter;

    --first_quarter;
    --second_quarter;
    --third_quarter;
    --fourth_quarter;

    vector<int> check_valid {first_quarter, second_quarter, third_quarter, fourth_quarter};

    sort(check_valid.begin(), check_valid.end());
    for (int i {0}; i < 4; ++i) {
        if (check_valid[i] != i) {
            return void(cout << "Invalid input. Try again.\n");
        }
    }

    unsigned char shuffled_image[SIZE][SIZE];

    for (int i {0}; i < 128; ++i) {
        for (int j {0}; j < 128; ++j) {
            shuffled_image[i][j] = quarters[first_quarter][i][j];
        }
    }

    for(int i {0}; i < 128; ++i) {
        for (int j {128}; j < SIZE; ++j) {
            shuffled_image[i][j] = quarters[second_quarter][i][j - 128];
        }
    }

    for (int i {128}; i < SIZE; ++i) {
        for (int j {0}; j < 128; ++j) {
            shuffled_image[i][j] = quarters[third_quarter][i - 128][j];
        }
    }

    for (int i {128}; i < SIZE; ++i) {
        for (int j {128}; j < SIZE; ++j) {
            shuffled_image[i][j] = quarters[fourth_quarter][i - 128][j - 128];
        }
    }

    char imageCopyFileName[100];

    cout << "Enter the target image file name: ";
    cin >> imageCopyFileName;

    strcat(imageCopyFileName, ".bmp");
    writeGSBMP(imageCopyFileName, shuffled_image);
}

//_________________________________________
void blur() {
    unsigned char imageCopy[SIZE][SIZE];

    for (int i {0}; i < SIZE; ++i) {
        for (int j {0}; j < SIZE; ++j) {
            imageCopy[i][j] = image[i][j];
        }
    }

    // Get the average of all adjacent pixels of every pixel
    for (int i {0}; i < SIZE; ++i) {
        for (int j {0}; j < SIZE; ++j) {
            if (i == 0 && j == 0) {
                image[0][0] = (imageCopy[0][0] + imageCopy[0][1] + imageCopy[1][0] + imageCopy[1][1]) / 4;
            } else if (i == 0 && j == 255) {
                image[0][255] = (imageCopy[0][255] + imageCopy[1][255] + imageCopy[1][254] + imageCopy[1][254]) / 4;
            } else if (i == 255 && j == 0) {
                image[255][0] = (imageCopy[255][0] + imageCopy[255][1] + imageCopy[254][0] + imageCopy[254][1]) / 4;
            } else if (i == 255 && j == 255) {
                image[255][255] = (imageCopy[255][255] + imageCopy[255][254] + imageCopy[254][255] + imageCopy[254][254]) / 4;
            } else if (i == 0) {
                image[0][j] = (imageCopy[0][j] + imageCopy[0][j - 1] + imageCopy[0][j + 1] + imageCopy[1][j] + imageCopy[1][j - 1] + imageCopy[1][j + 1]) / 6;
            } else if (i == 255) {
                image[255][j] = (imageCopy[255][j] + imageCopy[255][j - 1] + imageCopy[255][j + 1] + imageCopy[254][j] + imageCopy[254][j - 1] + imageCopy[254][j + 1]) / 6;
            } else if (j == 0) {
                image[i][0] = (imageCopy[i][0] + imageCopy[i + 1][0] + imageCopy[i - 1][0] + imageCopy[i][1] + imageCopy[i + 1][1] + imageCopy[i - 1][1]) / 6;
            } else if (j == 255) {
                image[i][255] = (imageCopy[i][255] + imageCopy[i + 1][255] + imageCopy[i - 1][255] + imageCopy[i][254] + imageCopy[i + 1][254] + imageCopy[i - 1][254]) / 6;
            } else {
                image[i][j] = (image[i][j] + image[i][j + 1] + image[i][j - 1] + image[i - 1][j - 1] + image[i - 1][j] + image[i - 1][j + 1] + image[i + 1][j - 1] + image[i + 1][j] + image[i + 1][j + 1]) / 9;
            }
        }
    }
}

//_________________________________________
void crop() {
    int x, y, l, w;
    cout << "Enter x, y position." << endl;
    do {
        cin >> x >> y;
        if (x < 0 || x > 255 || y < 0 || y > 255) {
            cout << "Invalid Input. Try again." << endl;
        }
    } while (x < 0 || x > 255 || y < 0 || y > 255);

    cout << "Enter length and width." << endl;
    do {
        cin >> l >> w;
        if ((x + l - 1) > 255 || (x + l - 1) < 0 || (y + w - 1) > 255 || (y + w - 1) < 0) {
            cout << "Invalid Input. Try again." << endl;
        }
    } while ((x + l - 1) > 255 || (x + l - 1) < 0 || (y + w - 1) > 255 || (y + w - 1) < 0);

    unsigned char cropped_image[SIZE][SIZE];

    for (int i {0}; i < SIZE; ++i) {
        for (int j {0}; j < SIZE; ++j) {
            cropped_image[i][j] = 255;
        }
    }

    for (int i {x}; i < x + l; ++i) {
        for (int j {y}; j < y + w; ++j) {
            cropped_image[i][j] = image[i][j];
        }
    }

    char imageCopyFileName[100];

    cout << "Enter the target image file name: ";
    cin >> imageCopyFileName;

    strcat(imageCopyFileName, ".bmp");
    writeGSBMP(imageCopyFileName, cropped_image);
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
        if (choice != 0 && choice != 3 && choice != 5 && choice != 8 && choice != 13 && choice != 11) {
            saveImage();
        }
    } while (choice != 0);
}
