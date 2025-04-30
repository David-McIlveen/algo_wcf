#ifndef IMG_DATA_IO
#define IMG_DATA_IO

#include <iostream>
#include <filesystem>
#include <string>

using namespace std;
namespace fs = std::filesystem;

enum image_type{
    PNG,
    JPEG
};

class Image{
    public:
        //Creates a blank image with a width x, height y and channel count c
        Image(int x, int y, int c);
        //Loads an image from a given path
        Image(fs::path);

        // Sets the path to save / load data from.
        void set_file(fs::path);
        // Gets the number of channels in the image
        int get_channels();
        // Gets the image height or y
        int get_height();
        // Gets the image width or x
        int get_width();
        // Saves the image to the set file path
        void save_image();
        // Loads a given image
        void load_image();
        // Gets the pixel value at a set x, y and c (channel)
        double at(int x, int y, int c);
        // Sets the double value of a given pixel at x and y
        void set(double value, int x, int y, int c);
        // Gets a relatively unique value for the summation of all the colors in the image
        double get_color_sum();
        // Determines if the image is saved as a JPEG or PNG
        void set_save_mode(image_type save);
        // double at_grey(int x, int y);
        ~Image();
    private:
        double* u_eight_to_double(unsigned char*, int);
        unsigned char* double_to_u_eight(double*, int);
        fs::path _file_path;
        double* _colors_d;
        int _total_elements;
        int _width;
        int _height;
        int _channels;
        image_type _save_mode;
};

inline double ut8_to_double(unsigned char);
inline unsigned char double_to_ut8(double);

#endif