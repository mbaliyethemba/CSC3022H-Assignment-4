//SHNMBA004
//Mbaliyethemba Shangase
//CSC3022H
//1 May 2019

#ifndef IMAGE_H
#define IMAGE_H
#include <memory>

namespace SHNMBA004{
	class Image{
		private:
			friend class iterator;
			int width;
			int height;
			std::unique_ptr<unsigned char[]> data;
		
		public:
			Image();
			Image(std::string &filename);
			Image(unsigned char * data, int width, int height);
			Image(const Image & rhs); //copy constructor
			Image(Image &&rhs); //move constructor
			Image & operator = (const Image &rhs); //copy assignment
			Image & operator = (const Image && rhs); //move assignment
			Image operator + (const Image & rhs) const; //addition operator
			Image & operator += (const Image & rhs);
			Image operator - (const Image & rhs) const; //subtraction
			Image & operator -= (const Image & rhs);
			Image operator ! ();//inverse
			Image operator / (const Image & rhs) const; //mask operator
			Image operator * (const int threshold); //Threshold operator
			
			virtual ~Image();
			bool load(std::string inFileName);
			void operator>>(const std::string file);
			void operator<<(const std::string file);
			int getWidth() const;
			int getHeight() const;
			bool save(std::string outFileName);
			unsigned char* getData() const;

        class iterator {
			private:
				friend class Image;
				unsigned char *ptr;
				int index;
				// construct only via Image class (begin/end)
				iterator(unsigned char *p);
			public:
				//copy construct
				iterator(const iterator &rhs);
				
				// define overloaded ops: *, ++, --, =
				iterator &operator=(const iterator &rhs);
				iterator& operator=(iterator &&rhs);
				unsigned char & operator * ();
				iterator & operator++();
				iterator & operator--();
				bool operator!=(const iterator &rhs);
				iterator(unsigned char *ptrToData, int givenIndex);
			};
			iterator begin(void)const;
			iterator end(void)const;
			bool dataNotEmpty() const;
		};
}

#endif
