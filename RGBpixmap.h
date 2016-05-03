//----------------------------------------------------------------------
// File:           RGBpixmap.h
// Description:    Pixmap storage object
// Programmer:     Dave Mount
// Date:           Fall 2013
// Source:         Adapted from the code from F. S. Hill's book,
//                 "Computer Graphics Using OpenGL", Prentice Hall,
//                 2000.
//
// Provides a number of utilities for reading, writing, and modifying
// bmp files. It provides a few hooks for interfacing with OpenGL. To
// use this with OpenGL, set the compiler variable "OGL".
//
// See the file ReadMe.txt for further information.
//----------------------------------------------------------------------

#ifndef RGB_PIXMAP
#define RGB_PIXMAP

#define OGL                             // comment out if not using OpenGL

#include <cstdlib>                      // standard includes
#include <fstream>                      // C++ file I/O
#include <iostream>                     // C++ I/O
#include <string>                       // STL strings
#ifdef OGL                              // for OpenGL use only
 #include <GLUT/glut.h>                   // glut/OpenGL includes
#endif

//----------------------------------------------------------------------
//  Types and constants
//----------------------------------------------------------------------
typedef unsigned char   RGB_uchar;      // unsigned type aliases
typedef unsigned short  RGB_ushort;
typedef unsigned long   RGB_ulong;

const int RGB_MAX = 255;                // maximum RGB value

using namespace std;                    // make std:: accessible

//----------------------------------------------------------------------
//  RGBpixel
//
//  Stores a single RGB value
//----------------------------------------------------------------------

struct RGBpixel {
public:
    RGB_uchar r, g, b;
//
    RGBpixel() { r = g = b = 0;  }      // default constructor

    RGBpixel(const RGBpixel& p)         // copy constructor
    { r = p.r; g = p.g; b = p.b;  }
                                        // construct from components
    RGBpixel(RGB_uchar rr, RGB_uchar gg, RGB_uchar bb)
    { r = rr; g = gg; b = bb; }
                                        // set values
    void set(RGB_uchar rr, RGB_uchar gg, RGB_uchar bb)
    { r = rr; g = gg; b = bb; }
};

//----------------------------------------------------------------------
//  RGBpixmap
//      RGB pixel array
//----------------------------------------------------------------------

class RGBpixmap {
public:
    RGBpixmap(int rows = 0, int cols = 0); // constructor from dimensions
    ~RGBpixmap();                       // destructor

    int getNRows() const;               // getters
    int getNCols() const;
    RGBpixel* getImageArray();
    const RGBpixel* getImageArray() const;
    RGBpixel getPixel(int col, int row) const;
                                        // set pixel color
    void setPixel(int col, int row, const RGBpixel& color);

    bool readBMPFile(                   // read from file
        const string& fname, 
        bool glPad=false,
        bool verbose=false);
                                        // write to file
    bool writeBMPFile(const string& fname);
#ifdef OGL                              // for OpenGL only
    void draw() const;                  // draw pixmap to raster pos
#endif

protected:                              // protected utilities
    void freeAll();                     // deallocate everything
private:
    int nRows, nCols;                   // dimensions
    RGBpixel* pixel;                    // array of pixels
    ifstream* bmpIn;                    // input file stream
    ofstream* bmpOut;                   // output file stream (if needed)
};

#endif
