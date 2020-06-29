//SHNMBA004
//Mbaliyethemba Shangase
//CSC3022H
//1 May 2019

#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include "image.h"
using namespace std;

namespace SHNMBA004{
	//copy
	Image::iterator::iterator(const Image::iterator &rhs):ptr(rhs.ptr),index(rhs.index){}
	//constructor
	Image::iterator::iterator(unsigned char *p): ptr(p), index(0){ }
	//copy assignment
    Image::iterator& Image::iterator::operator=(const Image::iterator &rhs) {
		index = rhs.index;
        ptr = (rhs.ptr);
        return *this;
    }
    //move assignment
    Image::iterator& Image::iterator::operator=(Image::iterator &&rhs) { 
        index = rhs.index;
        ptr = (move(rhs.ptr));
        rhs.ptr = nullptr;
    }
    
    Image::iterator::iterator(unsigned char *ptrToData, int givenIndex):ptr(ptrToData),index(givenIndex){}
    
    //default constructor
    Image::Image() { 
        height =0;
        width =0;
    }
    
    //Constructor with filename
    Image::Image(std::string &filename){
		this->width = 0;
		this->height = 0;
		load(filename);
	}
	
	Image::Image(unsigned char *dataInput,int width, int height) {
        this->width = width;
        this->height = height;
        data.reset(dataInput);
    }
    
    //destructor
    Image::~Image(){
		width = 0;
		height = 0;
		data.release();
	}
	
	//Copy constructor
    Image::Image(const Image &rhs) : width(rhs.width),height(rhs.height) {
        unsigned char copyData[width*height];
        strcpy((char *) copyData, (const char *) rhs.data.get());
        data.reset(copyData);
    }
    
    //Move constructor
    Image::Image(Image &&rhs):width(move(rhs.width)),height(move(rhs.height)){
		data.swap(rhs.data);
	}
	
	//Copy assignment
    Image &Image::operator=(const Image &rhs) {
        width = rhs.width;
        height = rhs.height;
        unsigned char copyData[width*height];
        strcpy((char *) copyData, (const char *) rhs.data.get());
        data.reset(copyData);
        return *this;
    }
    
    //Move Assignment
    Image &Image::operator=(const Image &&rhs){
		width = move(rhs.width);
		height = move(rhs.height);
		data.reset(move(rhs.data).get());
		return *this;
	}
	
	int Image::getWidth() const {
        return this->width;
    }
    
    int Image::getHeight() const{
		return this->height;
	}
	
	bool Image::dataNotEmpty() const{
        if (data){
            return true;
        }else{
            return false;
        }
    }
    
    //Load function
    bool Image::load(string infile){
		ifstream input(infile,ios::binary | ios::in);
		string line;
		int width;
		int height;
		int counter = 0;
		if(input.is_open()){
			while(getline(input,line)){
				if(line.at(0) != '#'){
					counter++;
					if(counter == 2){
						stringstream ss;
						ss << line;
						ss >> width;
						ss >> height;
					}
				}
				if(counter == 3){
					break;
				}
			}
		}
		else{
			cout<<"Unable to open file"<<endl;
			return false;
		}
		this->height = height;
		this->width = width;
		unsigned char *mainData = new unsigned char[width * height];
		input.read((char *) mainData, width * height);
		this->data = unique_ptr<unsigned char[]>(mainData);
		input.close();
		return true;
	}
	
	//Save function to store pgm file
    bool Image::save(std::string outFileName) {
		 //Open file
        ofstream output(outFileName, ios::out | ios::binary);
        if (output.is_open()){
			//Header information
            string header = "P5\n" + to_string(width) + " " + to_string(height) +"\n255\n"; 
            const char* bytesInHeader = header.c_str();
            //Write header information as chars
            output.write(bytesInHeader,header.length()); 
            //Write all the unsigned char data to file
            output.write((const char *) data.get(), width * height); 
            output.close();
            return true;
        }
        else{
            return false;
        }
    }
    
    //Binary I/O operators
    void Image::operator>>(const string file){
		this->save(file);
	}
	
	void Image::operator<<(const string file){
        this->load(file);
    }
    
    unsigned char *Image::getData() const{
		return data.get();
	}
	
	Image::iterator Image::begin(void)const {
        return Image::iterator(data.get());
    }
    
    Image::iterator Image::end(void) const{
		return Image::iterator((data.get()),width*height);
	}
	
	unsigned char &Image::iterator::operator*() { //return pointer to wherever it is currently pointing too
            return ptr[index];
    }
    
    //increment operator
    Image::iterator & Image::iterator::operator++(){
		++index;
		return *this;
	}
	
	//Decrement operator
    Image::iterator & Image::iterator::operator--() {
        --index;
        return *this;
    }
    
    //add images
    Image Image::operator+(const Image & rhs) const{
		Image addedImage(*this);
		addedImage += rhs;
		return addedImage;
	}
	
	//Add and increments an image
    Image &Image::operator+=(const Image &rhs) {
        if (this->getWidth() != rhs.getWidth() || this->getHeight() != rhs.getHeight()){
            cout<<"Image parameters not equal."<<endl;
            exit(0);
        }
        int counter = 0;
        Image::iterator image1 = this->begin();
        for (Image::iterator image2 = rhs.begin(); image2 != rhs.end(); ++image2) { //Iterator for 1st image
            unsigned char image1Pixel = *image1;
            unsigned char image2Pixel = (*image2);
            if ( (image1Pixel + image2Pixel) >255){ //cap pixels at 255
                (*image1) = 255;
            }
            else{
                (*image1) = (image1Pixel + image2Pixel); //add pixels
            }
            ++counter;
            ++image1;
        }
        return *this;
    }
    
    //Not equal to  operator for iterator
    bool Image::iterator::operator!=(const Image::iterator &rhs){
		return (this->index != rhs.index);
	}
	
	//Subtract operation for images
    Image Image::operator-(const Image & rhs) const {
        Image subtractedImage(*this);
        subtractedImage -= rhs;
        return subtractedImage;
    }
    
    //Subtract pixels from one image by another
    Image &Image::operator-=(const Image &rhs){
		if(this->getWidth() != rhs.getWidth() || this->getHeight() != rhs.getHeight()){
			cout<<"Image parameters not equal."<<endl;
			exit(0);
		}
		int counter = 0;
		Image::iterator image1 = this->begin();
		for(Image::iterator image2 = rhs.begin(); image2 != rhs.end(); ++image2){
			unsigned char image1pixel = (*image1);
			unsigned char image2pixel = (*image2);
			if((image1pixel - image2pixel)<0){
				(*image1) = 0;
			}
			else{
				(*image1) = (image1pixel - image2pixel);
			}
			++counter;
			++image1;
		}
		return *this;
	}
	
	//Inverse operator
    Image Image::operator!() {
        Image inverse(*this);
        unsigned char * j = this->getData();
        unsigned char * x = inverse.getData();
        int counter = 0;
        for (Image::iterator i = inverse.begin(); i != inverse.end(); ++i) {
            (*i) = (unsigned char) (255 - (*i)); //inverse pixel
            counter++;
        }
        return inverse;
    }
    
    //masking operation
    Image Image::operator/(const Image &rhs) const{
		if(this->getWidth() == rhs.width && this->getHeight() == rhs.height){
			Image mask(*this);
			Image::iterator iteratorMask = mask.begin();
			for(Image::iterator iteratorImage2 = rhs.begin(); iteratorImage2 != rhs.end(); ++iteratorImage2){
				if((*iteratorImage2) == 0){
					(*iteratorMask) = 0;
				}
				++iteratorMask;
			}
			return mask;
		}
		else{
			cout<<"Mask images not the same size."<<endl;
			exit(0);
		}
	}
	
	//Threshold operation
    Image Image::operator*(const int threshold) {
        Image thresheldImage(*this);
        for (Image::iterator i = thresheldImage.begin(); i != thresheldImage.end(); ++i) {
            if ( (*i) > threshold){
                (*i) = 255;
            }
            else{
                (*i) = 0;
            }
        }
        return thresheldImage;
    }
}
