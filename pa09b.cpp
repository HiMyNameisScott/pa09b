#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct pixel_t {
    short red = 0;                    //  Used to store 3 digit number for red
    short green = 0;                  //  Used to store 3 digit number for green
    short blue = 0;                   //  Used to store 3 digit number for blue
};

struct image_t {
    short width;                    //  Used to store width of image
    short height;                   //  Used to store height of image
    short max_colors;               //  Describes maximum color intensity
    pixel_t data[1024][1024];       //  Array stores single pixels as pixel_t
};

//Function Prototypes
void read_pixel(std::ifstream& infile, pixel_t& pixel);
void write_pixel(std::ofstream& outfile, const pixel_t& pixel);
bool read_image(std::ifstream& infile, image_t& image);
void write_image(std::ofstream& outfile, const image_t& image);
void flop_image(image_t& image);
void flip_image(image_t& image);
void sepia(image_t& image);

int main(int argc, const char** argv){

    ifstream infile;                //  init infile
    ofstream outfile;               //  init outfile


    infile.open(argv[1]);           //  opens infile from main argv[1]
    outfile.open(argv[2]);          //  saves outfile from main argv[2]

    image_t image;                  //  image_t to save image data

    read_image(infile, image);      //  Funciton call to read in image

    flop_image(image);              //  Flips image horizontally

    flip_image(image);              //  Flips image vertically

    sepia(image);                   //  Makes everything cowboy styled

    write_image(outfile, image);    //  Function to write image to file argv[2]

    infile.close();                 //  closes infile
    outfile.close();                //  closes outfile

    return 0;

}

////////////////////////////////////////////////////////////////////////////////
//  Functions!
////////////////////////////////////////////////////////////////////////////////

/// Reads an RGB color triplet into a pixel_t from an input file.
void read_pixel(std::ifstream& infile, pixel_t& pixel){
            infile >> pixel.red;
            infile >> pixel.blue;
            infile >> pixel.green;
}

//Writes a pixel_t RGB components to an output file stream. Each value is
//followed by a whitespace.
void write_pixel(std::ofstream& outfile, const pixel_t& pixel){
            outfile << pixel.red << " ";
            outfile << pixel.blue << " ";
            outfile << pixel.green << " ";
}

//Reads a P3 image from if stream.
//@returns true if image is read successfully and is of the correct size.
bool read_image(std::ifstream& infile, image_t& image){
    bool failure = false;           //  used to track file load/read failure
    string magicNumber;             //  stores header as magic number
    if(!infile.fail()){
        infile >> magicNumber;

        if(magicNumber == "P3"){
            failure = false;
            while(infile.peek() == '#'){
            infile.ignore(1000, '\n');
            }
            infile >> image.width >> image.height;
            infile >> image.max_colors;
            for (int h = 0 ; h < image.height ; h++){
                for (int w = 0 ; w < image.width ; w++) {
                    read_pixel(infile, image.data[h][w]);
                }
            }

        } else{
            std::cout << "Wrong File Type," << '\n';
            failure = true;
        }
    } else {
        std::cout << "Failure to load file." << '\n';
        failure = true;
    }

    return failure;
}

//writes a p3 ppm image to the output file stream.
//the header is formatted as specified, and the author's name is
//inserted as a comment after the magic number.
void write_image(std::ofstream& outfile, const image_t& image){
    outfile << "P3" << endl;
    outfile << "#Scott Koss Scott.Koss@student.csn.edu" << endl;
    outfile << image.width << endl;
    outfile << image.height << endl;
    outfile << image.max_colors << endl;

    for (int r = 0 ; r < image.height ; r++){
        for(int c = 0 ; c < image.width ; c++){
           write_pixel(outfile, image.data[r][c]);
        }
        outfile << endl;
    }
}


//Takes in pixels from data, and swaps them to flip image across Y axis.
void flop_image(image_t& image){

    pixel_t temp;   //  Used to store temporary data for swap

    for (int r = 0 ; r < image.height ; r++){

    for(int c = 0 ; c < (image.width / 2) ; c++){
        temp = image.data[r][c];

        image.data[r][c] = image.data[r][image.width - c];
        image.data[r][image.width - c] = temp;

        }
    }

};

//Takes in pixels from data, and swaps them to flip image axross X axis
void flip_image(image_t& image){

    pixel_t temp;   //  Used to store temporary data for swap

    for (int w = 0 ; w < image.width ; w++){

        for(int h = 0; h < image.height / 2 ; h++){
            temp = image.data[h][w];

            image.data[h][w] = image.data[image.height - h][w];
            image.data[image.height-h][w] = temp;
        }

    }

};

//Takes in the pixel data, and uses predetermined percentages in order to
//manipulate the color intensities and changes the tone and color of the image
//to a sepia toned color. Uses for loops to iterate through entire image data.
void sepia(image_t& image){

    short red;          //  Stores pixel red for manipulation
    short blue;         //  Stores pixel blue for manipulation
    short green;        //  Stores pixel green for manipulation
    short newRed;       //  Stores post manipulated red.
    short newGreen;     //  Stores post manipulated green.
    short newBlue;      //  Stores post manipulated blue.

    for (int w = 0 ; w < image.height ; w++){

    for (int h = 0; h < image.width ; h++){
        red = image.data[w][h].red;
        green = image.data[w][h].green;
        blue = image.data[w][h].blue;

    newRed = static_cast<short>((red * 0.393)+(green * 0.769)+(blue * 0.189));
    newGreen = static_cast<short>((red * 0.349)+(green * 0.686)+(blue * 0.168));
    newBlue = static_cast<short>((red * 0.272)+(green * 0.534)+(blue * 0.131));

    if (newRed > image.max_colors){
        newRed = 255;
        }
    if (newGreen > image.max_colors){
        newGreen = 255;
        }
    if (newBlue > image.max_colors){
        newBlue = 255;
        }

     image.data[w][h].red = newRed;
     image.data[w][h].green = newGreen;
     image.data[w][h].blue = newBlue;

    }

    }

};