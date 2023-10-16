// FCAI – OOP Programming – 2023 - Assignment 1
// Program Name:			    CS213-2023–S23-20220027-20220028-20220360-A1Bonus
// Last Modification Date:	    14/6/2023
// Author1 and ID, Email, and Group:	Nour-aldeen Alaa            20220360 - nouralaa2279@gmail.com -  S24
// Author2 and ID, Email, and Group:	Ahmed Alaa Al-Din Mostafa   20220028 - alaa25086@gmail.com    -  S23
// Author3 and ID, Email, and Group:	Ahmed Abdelnabi Abdelrasol  20220027 - amedgamer36@gmail.com  -  S23
// Teaching Assistant:		To Be Determined
// Purpose: Applying Filters to 256x256 BMP RGB Images

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;

unsigned char image[SIZE][SIZE][RGB];
unsigned char result_image[SIZE][SIZE][RGB];
unsigned char grayImage[SIZE][SIZE];
unsigned char edgedImage[SIZE][SIZE];
bool GS = false;

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
void gray_Scaling();

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
   if(GS){
       writeGSBMP(imageFileName, edgedImage);
       GS = false;
       return;
   }
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
                    swap(image[i][j][0], image[i][SIZE - j - 1][0]);
                    swap(image[i][j][1], image[i][SIZE - j - 1][1]);
                    swap(image[i][j][2], image[i][SIZE - j - 1][2]);

                }
            }
            break;
            // if vertically go through each column and swap each row from the left with it counterpart from the right
        case 'V':
        case 'v':
            for (int i {0}; i < SIZE / 2; ++i) {
                for (int j {0}; j < SIZE; ++j) {
                    swap(image[i][j][0], image[SIZE - i - 1][j][0]);
                    swap(image[i][j][1], image[SIZE - i - 1][j][1]);
                    swap(image[i][j][2], image[SIZE - i - 1][j][2]);

                }
            }
            break;

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

void gray_Scaling(){
    GS = true;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            grayImage[i][j] = (image[i][j][0] + image[i][j][1] + image[i][j][2]) / 3.0;
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

    //make the image gray-scale first
    gray_Scaling();

    for (int i {0}; i < SIZE; ++i) {
        for (int j{0}; j < SIZE; ++j) {
            if (i == 0 || j == 0 || i == SIZE - 1 ||
                j == SIZE - 1) { //if it is a corner, make it the same as the original pixel
                edgedImage[i][j] = grayImage[i][j];
                continue;
            }
            //Vertical change is the change in intensity in the x-axis
            //Horizontal change is the change in intensity in the y-axis

            int VerticalChange =
                    (grayImage[i - 1][j - 1] * -1) + (grayImage[i][j - 1] * -2) + (grayImage[i + 1][j - 1] * -1)
                    + (grayImage[i - 1][j + 1]) + (grayImage[i][j + 1] * 2) + (grayImage[i + 1][j + 1]);

            int HorizontalChange =
                    (grayImage[i - 1][j - 1] * -1) + (grayImage[i - 1][j] * -2) + (grayImage[i - 1][j + 1] * -1)
                    + (grayImage[i + 1][j - 1]) + (grayImage[i + 1][j] * 2) + (grayImage[i + 1][j + 1]);

            int gradient = (int) (round(
                    sqrt((VerticalChange * VerticalChange) + (HorizontalChange * HorizontalChange))));
            if (gradient > 180) { //if its bigger we'll consider it an edge so we make the pixel black
                edgedImage[i][j] = 0;
            } else {
                edgedImage[i][j] = 255;
            }

        }
    }

}

//_________________________________________
void enlarge() {

    unsigned char quarter_image[128][128][RGB];
    unsigned char enlarged_image[SIZE][SIZE][RGB];

    // ask the user which quarter they want to enlarge
    cout << "Which quarter do you want to enlarge?" << endl;
    int choice;
    // check if the choice is valid
    do {
        cin >> choice;
        if (choice != 1 && choice != 2 && choice != 3 && choice != 4) {
            cout << "Invalid input. Try again." << endl;
        }
    } while (choice != 1 && choice != 2 && choice != 3 && choice != 4);
    // store the required quarter
    switch (choice) {
        case 1:
            for (int i {0}; i < 128 ; ++i) {
                for (int j {0}; j < 128; ++j) {
                    quarter_image[i][j][0] = image[i][j][0];
                    quarter_image[i][j][1] = image[i][j][1];
                    quarter_image[i][j][2] = image[i][j][2];


                }
            }
            break;

        case 2:
            for (int i {0}; i < 128; ++i) {
                for (int j {0}; j < 128; ++j) {
                    quarter_image[i][j][0] = image[i][j + 128][0];
                    quarter_image[i][j][1] = image[i][j + 128][1];
                    quarter_image[i][j][2] = image[i][j + 128][2];

                }
            }
            break;

        case 3:
            for (int i {0}; i < 128; ++i) {
                for (int j {0}; j < 128; ++j) {
                    quarter_image[i][j][0] = image[i + 128][j][0];
                    quarter_image[i][j][1] = image[i + 128][j][1];
                    quarter_image[i][j][2] = image[i + 128][j][2];

                }
            }
            break;

        case 4:
            for (int i {0}; i < 128; ++i) {
                for (int j {0}; j < 128; ++j) {
                    quarter_image[i][j][0] = image[i + 128][j + 128][0];
                    quarter_image[i][j][1] = image[i + 128][j + 128][1];
                    quarter_image[i][j][2] = image[i + 128][j + 128][2];

                }
            }
            break;

        default:
            break;
    }
// enlarge that quarter by putting each pixel in four bits
    for(int i {0}, x {0}; i < SIZE; ++++i, ++x) {
        for (int j {0}, y {0}; j < SIZE; ++ ++j, ++y) {
            for(int k{} ; k < RGB ; k++){
                enlarged_image[i][j][k]
                        = enlarged_image[i + 1][j][k]
                        = enlarged_image[i][j + 1][k]
                        = enlarged_image[i + 1][j + 1][k]
                        = quarter_image[x][y][k];
            }
        }
    }

    for (int i {0}; i < SIZE; ++i) {
        for (int j {0}; j < SIZE; ++j) {
            for(int k{} ; k < RGB ; k++){
                result_image[i][j][k] = enlarged_image[i][j][k];
            }
        }
    }
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

// store each quarter in a single vector and store the vectors in another vector to reach them by index easily
    vector< vector< vector< vector<int> > > > quarters(4, vector<vector<vector<int>>> (128, vector<vector<int>>(128 , vector<int>(3))));
    // store first quarter
    for (int i {0}; i < 128; ++i) {
        for (int j {0}; j < 128; ++j) {
            quarters[0][i][j][0] = image[i][j][0];
            quarters[0][i][j][1] = image[i][j][1];
            quarters[0][i][j][2] = image[i][j][2];
        }
    }
    // store second quarter
    for (int i {0}; i < 128; ++i) {
        for (int j {0}; j < 128; ++j) {
            quarters[1][i][j][0] = image[i][j + 128][0];
            quarters[1][i][j][1] = image[i][j + 128][1];
            quarters[1][i][j][2] = image[i][j + 128][2];

        }
    }
    // store third quarter
    for (int i {0}; i < 128; ++i) {
        for (int j {0}; j < 128; ++j) {
            quarters[2][i][j][0] = image[i + 128][j][0];
            quarters[2][i][j][1] = image[i + 128][j][1];
            quarters[2][i][j][2] = image[i + 128][j][2];

        }
    }
    // store the fourth quarter
    for (int i {0}; i < 128; ++i) {
        for (int j {0}; j < 128; ++j) {
            quarters[3][i][j][0] = image[i + 128][j + 128][0];
            quarters[3][i][j][1] = image[i + 128][j + 128][1];
            quarters[3][i][j][2] = image[i + 128][j + 128][2];

        }
    }
// take the order from the user
    int first_quarter, second_quarter, third_quarter, fourth_quarter;
    cout << "Enter your input." << endl;
    cin >> first_quarter >> second_quarter >> third_quarter >> fourth_quarter;

    --first_quarter;
    --second_quarter;
    --third_quarter;
    --fourth_quarter;
// check if it's valid (all quarters exist)
    vector<int> check_valid {first_quarter, second_quarter, third_quarter, fourth_quarter};

    sort(check_valid.begin(), check_valid.end());
    for (int i {0}; i < 4; ++i) {
        if (check_valid[i] != i) {
            return void(cout << "Invalid input. Try again.\n");
        }
    }

    unsigned char shuffled_image[SIZE][SIZE][RGB];
    // put the quarters in order of the new array
    for (int i {0}; i < 128; ++i) {
        for (int j {0}; j < 128; ++j) {
            shuffled_image[i][j][0] = quarters[first_quarter][i][j][0];
            shuffled_image[i][j][2] = quarters[first_quarter][i][j][2];
            shuffled_image[i][j][1] = quarters[first_quarter][i][j][1];

        }
    }

    for(int i {0}; i < 128; ++i) {
        for (int j {128}; j < SIZE; ++j) {
            shuffled_image[i][j][0] = quarters[second_quarter][i][j - 128][0];
            shuffled_image[i][j][1] = quarters[second_quarter][i][j - 128][1];
            shuffled_image[i][j][2] = quarters[second_quarter][i][j - 128][2];

        }
    }

    for (int i {128}; i < SIZE; ++i) {
        for (int j {0}; j < 128; ++j) {
            shuffled_image[i][j][0] = quarters[third_quarter][i - 128][j][0];
            shuffled_image[i][j][1] = quarters[third_quarter][i - 128][j][1];
            shuffled_image[i][j][2] = quarters[third_quarter][i - 128][j][2];

        }
    }

    for (int i {128}; i < SIZE; ++i) {
        for (int j {128}; j < SIZE; ++j) {
            shuffled_image[i][j][0] = quarters[fourth_quarter][i - 128][j - 128][0];
            shuffled_image[i][j][1] = quarters[fourth_quarter][i - 128][j - 128][1];
            shuffled_image[i][j][2] = quarters[fourth_quarter][i - 128][j - 128][2];

        }
    }

    for (int i {0}; i < SIZE; ++i) {
        for (int j {0}; j < SIZE; ++j) {
            for(int k{} ; k < RGB ; k++)
            {
                result_image[i][j][k] = shuffled_image[i][j][k];
            }
        }
    }
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

    unsigned char cropped_image[SIZE][SIZE][RGB];

    for (int i {0}; i < SIZE; ++i) {
        for (int j {0}; j < SIZE; ++j) {
            cropped_image[i][j][0] = 255;
            cropped_image[i][j][1] = 255;
            cropped_image[i][j][2] = 255;
        }
    }

    for (int i {x}; i < x + l; ++i) {
        for (int j {y}; j < y + w; ++j) {
            cropped_image[i][j][0] = image[i][j][0];
            cropped_image[i][j][1] = image[i][j][1];
            cropped_image[i][j][2] = image[i][j][2];
        }
    }

    for (int i {0}; i < SIZE; ++i) {
        for (int j {0}; j < SIZE; ++j) {
            result_image[i][j][0] = cropped_image[i][j][0];
            result_image[i][j][1] = cropped_image[i][j][1];
            result_image[i][j][2] = cropped_image[i][j][2];
        }
    }
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
        GS = false;
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
//                shrink();
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
