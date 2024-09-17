#include <emscripten.h>
#include <emscripten/bind.h>
#include <png.h>
#include <sstream>
#include <cstdio> 

png_structp png_ptr_write;
png_infop info_ptr_write;

struct PngData {
png_bytep* rows;
png_uint_32 width;
png_uint_32 height;
};

PngData decoded_png_data;

png_bytep* frame_data=nullptr;
png_bytepp row_pointers=nullptr;

int CframeCount=10;
int num_frames=10;

void read_png(FILE *fp, int sig_read, int siz) {
png_structp png_ptr;
png_infop info_ptr;
    
png_bytep row_pointers[siz];

png_ptr_write = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
info_ptr_write = png_create_info_struct(png_ptr_write);
png_set_IHDR(png_ptr_write, info_ptr_write, siz, siz, 8, PNG_COLOR_TYPE_RGBA,PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
png_write_image(png_ptr_write, row_pointers);
png_write_end(png_ptr_write, info_ptr_write);
png_destroy_write_struct(&png_ptr_write, &info_ptr_write);

png_ptr=png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
info_ptr=png_create_info_struct(png_ptr);
png_init_io(png_ptr, fp);
png_set_sig_bytes(png_ptr, sig_read);
png_read_info(png_ptr, info_ptr);
png_uint_32 width, height;

int bit_depth, color_type, interlace_type;
png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, NULL,  NULL);
decoded_png_data.width=width;
decoded_png_data.height=height;

    // Read the image data directly into the row pointers
png_read_image(png_ptr, row_pointers);
png_read_end(png_ptr, NULL);
png_destroy_read_struct(&png_ptr, &info_ptr, nullptr);
return;
}

void runApngC(int size) {
int delay=500, num_frames=10;
png_ptr_write=png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
info_ptr_write=png_create_info_struct(png_ptr_write);

png_set_IHDR(png_ptr_write, info_ptr_write, size, size, 8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
png_set_acTL(png_ptr_write, info_ptr_write, 10, 0); 
for (int i=0; i < 10; ++i) {
std::stringstream ss;
ss << "/frames/frame" << (i + 1) << ".png";
std::string fileName=ss.str();
FILE* fp=fopen(fileName.c_str(), "r");
read_png(fp, 0,size);
png_set_next_frame_fcTL(png_ptr_write,info_ptr_write,decoded_png_data.width,decoded_png_data.height,0,0,500,1000, PNG_DISPOSE_OP_BACKGROUND, PNG_BLEND_OP_SOURCE); 
png_write_image(png_ptr_write, decoded_png_data.rows);
fclose(fp);
for (int y=0; y < decoded_png_data.height; y++) {
free(decoded_png_data.rows[y]);
}
free(decoded_png_data.rows);
}
png_write_end(png_ptr_write, info_ptr_write);
png_destroy_write_struct(&png_ptr_write, &info_ptr_write);
return; 
}

extern "C" {

void runApng(int sz) {
runApngC(sz);
return;
}

}

int main(){

EM_ASM({
FS.mkdir('/frames');
document.getElementById("apngBtn").addEventListener('click',function(){
const acanvas=document.querySelector("#scanvas");
    const ctx=acanvas.getContext('2d',{
colorType:'float32',
alpha:true,
willReadFrequently:true,
stencil:false,
depth:false,
colorSpace:"display-p3",
desynchronized:false,
antialias:true,
powerPreference:"high-performance",
premultipliedAlpha:true,
preserveDrawingBuffer:false
});

const siz=parseInt(acanvas.height);
let ii=0;
let totalFrames=0;
const delay=500; 

function render() {
totalFrames++;
if (totalFrames%30==0) {
if (ii > 10) {
Module.ccall('runApng',null,"Number",[siz]);
return;
}
ii++;
console.log('Frame: ', ii);

const image = ctx.getImageData(0, 0, siz, siz); // Assuming square canvas
const imageData = image.data;
const pixelData = new Uint8Array(imageData);

const fileStream=FS.open('/frames/frame' + ii + '.png', 'w+', { encoding: 'binary' });
 console.log('/frames/frame' + ii + '.png');
// const encoder=new TextEncoder(); // To convert the string to Uint8Array
// const uint8Array=encoder.encode(dataURL);
FS.write(fileStream, pixelData, 0, pixelData.length, 0); 
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

