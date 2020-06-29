//SHNMBA004
//Mbaliyethemba Shangase
//CSC3022H
//1 May 2019

#include <iostream>
#include <sstream>
#include "image.h"

using namespace std;

//Check if right amount of arguments
int main(int argc, char * argv[]){
    if (argc > 5 ||argc < 3){
        cout << "Incorrect arguments passed" <<endl;
    }
    else{
        cout<<"Image manipulation program"<<endl;
        //Get file names
        string operation = string(argv[1]);
        if (operation == "-a" || operation == "-s" ||operation == "-l" ){ 
			//Binary operations
            if (argc !=5){
                cout<<"Not enough parameters"<<endl;
                exit(0);
            }
            string inputImage1 = string(argv[2]);
            string inputImage2 = string(argv[3]);
            string outputFileName = string(argv[4]);
            SHNMBA004::Image img1(inputImage1);
            SHNMBA004::Image img2(inputImage2);
            SHNMBA004::Image imageResult; //Empty constructor
            if (operation == "-a" ){
                cout<<"Addition chosen"<<endl;
                 imageResult = img1 + img2; //add
            }
            else if (operation == "-s" ){
                cout<<"Subtract chosen"<<endl;
                imageResult = img1 - img2;//subtract
            }
            else{
                cout<<"Mask chosen"<<endl;
                imageResult = img1 / img2; //mask
            }

            imageResult >> outputFileName; //print to file
        }
        else if (operation == "-i"){ 
			//inverse
            if (argc !=4){
                cout<<"Not enough parameters"<<endl;
                exit(0);
            }
            cout<<"Inverse chosen"<<endl;
            string inputImage1 = string(argv[2]);
            string outputFileName = string(argv[3]);
            SHNMBA004::Image img1(inputImage1);
            SHNMBA004::Image inverse = !img1;
            inverse >>outputFileName;
        }
        else if (operation == "-t"){ 
			//threshold
            if (argc !=5){
                cout<<"Not enough parameters"<<endl;
                exit(0);
            }
            cout<<"Threshold chosen"<<endl;
            string inputImage1 = string(argv[2]);
            stringstream threshString(argv[3]);
            int threshold;
            threshString >>threshold;
            string outputFileName = string(argv[4]);
            SHNMBA004::Image img1(inputImage1);
            SHNMBA004::Image thresheldImg = img1*threshold;
            thresheldImg >>outputFileName;
        }
        else{
            cout<<"Invalid";
        }
        cout<<"complete."<<endl;

    }
    return 0;
}

