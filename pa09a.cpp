/// @file pa09a
/// @author Scott T. Koss <Scott.Koss@student.csn.edu>
/// @date 04/29/2022
/// @note I pledge my word of honor that I have complied with the
/// CSN Academic Integrity Policy while completing this assignment.
/// @brief Copies .ppm data to a new file, and adds comment
/// @note 4-5 hours spent on assignment.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct pixel_t
{
    short red;
    short green;
    short blue;
};

struct image_t
{
    short width;
    short height;
    short max_colors;
    pixel_t data[1024][1024];
};

// Function Prototypes
void read_pixel(std::ifstream &infile, pixel_t &pixel);
void write_pixel(std::ofstream &outfile, const pixel_t &pixel);
bool read_image(std::ifstream &infile, image_t &image);
void write_image(std::ofstream &outfile, const image_t &image);

int main(int argc, const char **argv)
{

    ifstream infile;
    ofstream outfile;

    infile.open(argv[1]);
    outfile.open(argv[2]);

    image_t image;

    read_image(infile, image);

    write_image(outfile, image);

    infile.close();
    outfile.close();

    return 0;
}

////////////////////////////////////////////////////////////////////////////////
//  Functions!
////////////////////////////////////////////////////////////////////////////////

/// Reads an RGB color triplet into a pixel_t from an input file.
void read_pixel(std::ifstream &infile, pixel_t &pixel)
{
    infile >> pixel.red;
    infile >> pixel.blue;
    infile >> pixel.green;
}

// Writes a pixel_t RGB components to an output file stream. Each value is
// followed by a whitespace.
void write_pixel(std::ofstream &outfile, const pixel_t &pixel)
{
    outfile << pixel.red << " ";
    outfile << pixel.blue << " ";
    outfile << pixel.green << " ";
}

// Reads a P3 image from if stream.
//@returns true if image is read successfully and is of the correct size.
bool read_image(std::ifstream &infile, image_t &image)
{
    bool failure = false;
    string magicNumber;
    if (!infile.fail())
    {
        infile >> magicNumber;

        if (magicNumber == "P3")
        {
            failure = false;
            while (infile.peek() == '#')
            {
                infile.ignore(1000, '\n');
            }
            infile >> image.width >> image.height;
            infile >> image.max_colors;
            for (int h = 0; h < image.height; h++)
            {
                for (int w = 0; w < image.width; w++)
                {
                    read_pixel(infile, image.data[h][w]);
                }
            }
        }
        else
        {
            std::cout << "Wrong File Type," << '\n';
            failure = true;
        }
    }
    else
    {
        std::cout << "Failure to load file." << '\n';
        failure = true;
    }

    return failure;
}

// writes a p3 ppm image to the output file stream.
// the header is formatted as specified, and the author's name is
// inserted as a comment after the magic number.
void write_image(std::ofstream &outfile, const image_t &image)
{
    outfile << "P3" << endl;
    outfile << "#Scott Koss Scott.Koss@student.csn.edu" << endl;
    outfile << image.width << endl;
    outfile << image.height << endl;
    outfile << image.max_colors << endl;

    for (int r = 0; r < image.height; r++)
    {
        for (int c = 0; c < image.width; c++)
        {
            write_pixel(outfile, image.data[r][c]);
        }
        outfile << endl;
    }
}
