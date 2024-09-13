#include <emscripten.h>
#include <emscripten/bind.h>
#include <png.h>
#include <sstream> // Include the necessary header for std::stringstream
#include <boost/filesystem/fstream.hpp>
namespace fsm = boost::filesystem;

png_structp png_ptr_write;
png_infop info_ptr_write;

struct PngData {
png_bytep* rows;
png_uint_32 width;
png_uint_32 height;
};

PngData decoded_png_data;

png_bytep* frame_data = nullptr;
png_bytepp row_pointers = nullptr;
int height=1024;
int CframeCount=10;
int num_frames = 10;

void read_png(FILE *fp, int sig_read) {
png_structp png_ptr;
png_infop info_ptr;
// Create read struct and check for errors
png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
info_ptr = png_create_info_struct(png_ptr);
// Set up error handling (you'll need to implement png_error and png_warning)
png_init_io(png_ptr, fp);
    png_set_read_fn(png_ptr, (void*)&fp, [](png_structp png_ptr, png_bytep data, png_size_t length) {
        fsm::ifstream* stream = (fsm::ifstream*)png_get_io_ptr(png_ptr);
        stream->read((char*)data, length);
        return (png_uint_32)stream->gcount(); // Return the number of bytes actually read
    });
png_set_sig_bytes(png_ptr, sig_read);
// Read the image information
png_read_info(png_ptr, info_ptr);
png_uint_32 width, height;
int bit_depth, color_type, interlace_type;
png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, NULL,  NULL);
decoded_png_data.width = width;
decoded_png_data.height = height;
// Allocate memory for row pointers and read the image data
decoded_png_data.rows = (png_bytep*) malloc(sizeof(png_bytep) * height);
for (int y = 0; y < height; y++) {
decoded_png_data.rows[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr, info_ptr));
}
png_read_image(png_ptr, decoded_png_data.rows);
// Clean up
    png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
}

extern "C" {
int runApng(int* delays, int num_frames, int width, int height) {
// ... (Create APNG write and info structs, set up error handling) ... 
// Create the APNG write struct
png_ptr_write = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
if (!png_ptr_write) {
fprintf(stderr, "Error: could not create PNG write struct\n");
return 1; // Indicate an error
}
// Create the APNG info struct
info_ptr_write = png_create_info_struct(png_ptr_write);
if (!info_ptr_write) {
png_destroy_write_struct(&png_ptr_write, nullptr);
fprintf(stderr, "Error: could not create PNG info struct\n");
return 1; // Indicate an error
}
png_set_IHDR(png_ptr_write, info_ptr_write, width, height, 8, PNG_COLOR_TYPE_RGBA,
 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
// Write animation control chunk (acTL) using png_set_acTL
png_set_acTL(png_ptr_write, info_ptr_write, num_frames, 0); 
// Read and write each frame
for (int i = 0; i < num_frames; ++i) {
// Open the PNG file from Emscripten FS
std::stringstream ss;
ss << "/frames/frame" << (i + 1) << ".png";
std::string fileName = ss.str();
 fsm::ifstream fp(fileName.c_str(),std::ios::binary);
// FILE* fp = fopen(fileName.c_str(), "r");
// Read the PNG file
read_png(fp, 0); 
// Write frame control chunk (fcTL)
png_set_next_frame_fcTL(png_ptr_write, info_ptr_write, decoded_png_data.width, decoded_png_data.height, 0, 0, 
static_cast<png_uint_16>(delays[i]), 1000, 
PNG_DISPOSE_OP_BACKGROUND, PNG_BLEND_OP_SOURCE); 
// Write the image data for the frame
png_write_image(png_ptr_write, decoded_png_data.rows);
// Close the file and free memory allocated by read_png
fclose(fp);
for (int y = 0; y < decoded_png_data.height; y++) {
free(decoded_png_data.rows[y]);
}
free(decoded_png_data.rows);
}

// End the write operation
png_write_end(png_ptr_write, info_ptr_write);

// Clean up
png_destroy_write_struct(&png_ptr_write, &info_ptr_write);

return 0; 
}
}

int main(){

EM_ASM({
FS.mkdir('/frames');
document.getElementById("apngBtn").addEventListener('click',function(){
const acanvas = document.querySelector("#scanvas");
const siz = parseInt(acanvas.height);
let ii = 0;
let totalFrames = 0;
const delays = [500]; 

function render() {
totalFrames++;
if (totalFrames%30==0) {
if (ii > 10) {
// Animation complete, assemble APNG
Module.ccall('runApng', 'number', ['array', 'number', 'number', 'number'],  [delays, ii, siz, siz]);
return;
}
ii++;
console.log('Frame: ', ii);
const dataURL = acanvas.toDataURL('image/png', 1.0);
const fileStream = FS.open('/frames/frame' + ii + '.png', 'w+', { encoding: 'binary' });
 console.log('/frames/frame' + ii + '.png');
const encoder = new TextEncoder(); // To convert the string to Uint8Array
const uint8Array = encoder.encode(dataURL);
FS.write(fileStream, uint8Array, 0, uint8Array.length, 0); 
FS.close(fileStream);
}
setTimeout(function(){
render();
}, 16);
}

setTimeout(function() {
render(); 
}, 100); 
});

});


return 0;
}
