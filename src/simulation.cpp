#include <simulation.h>
#include <basics.h>
#include <km271.h>

#ifdef SIM_MODE
/* D E C L A R A T I O N S ****************************************************/  
uint8_t simData[144][11] = {
    {0x00, 0x00, 0x65, 0x0d, 0x22, 0x28, 0x02, 0x22, 0xff, 0x00, 0x00},
    {0x00, 0x07, 0x65, 0x00, 0x05, 0x05, 0x2d, 0x01, 0xff, 0x00, 0x00},
    {0x00, 0x0e, 0x01, 0x04, 0x5a, 0x05, 0x37, 0x65, 0xff, 0x00, 0x00},
    {0x00, 0x15, 0x03, 0x01, 0xfe, 0x65, 0x00, 0x05, 0xff, 0x00, 0x00},
    {0x00, 0x1c, 0x0c, 0x03, 0x01, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x00, 0x23, 0x65, 0x65, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x00, 0x2a, 0x28, 0x0a, 0x0a, 0x11, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x00, 0x31, 0x65, 0x65, 0x65, 0x00, 0x00, 0xfd, 0xff, 0x00, 0x00},
    {0x00, 0x38, 0x65, 0x12, 0x26, 0x26, 0x02, 0x21, 0xff, 0x00, 0x00},
    {0x00, 0x3f, 0x65, 0x00, 0x05, 0x05, 0x2d, 0x01, 0xff, 0x00, 0x00},
    {0x00, 0x46, 0x01, 0x04, 0x5a, 0x05, 0x4b, 0x65, 0xff, 0x00, 0x00},
    {0x00, 0x4d, 0x03, 0x01, 0x03, 0x65, 0x01, 0x05, 0xff, 0x00, 0x00},
    {0x00, 0x54, 0x0c, 0x03, 0x01, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x00, 0x5b, 0x65, 0x65, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x00, 0x62, 0x28, 0x0a, 0x0a, 0x11, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x00, 0x69, 0x65, 0x65, 0x65, 0x00, 0x00, 0x01, 0xff, 0x00, 0x00},
    {0x00, 0x70, 0xf6, 0x65, 0x01, 0x06, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x00, 0x77, 0x65, 0x65, 0x65, 0x65, 0x65, 0x01, 0xff, 0x00, 0x00},
    {0x00, 0x7e, 0x65, 0xfb, 0x28, 0x37, 0x3c, 0x65, 0xff, 0x00, 0x00},
    {0x00, 0x85, 0x02, 0x65, 0x65, 0x01, 0x65, 0x00, 0xff, 0x00, 0x00},
    {0x00, 0x8c, 0x65, 0x65, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x00, 0x93, 0x00, 0x01, 0x00, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x00, 0x9a, 0x65, 0x01, 0x65, 0x50, 0x05, 0x0c, 0xff, 0x00, 0x00},
    {0x00, 0xa1, 0x2d, 0x05, 0x65, 0x65, 0x65, 0x09, 0xff, 0x00, 0x00},
    {0x00, 0xa8, 0x1e, 0x0c, 0x19, 0x32, 0x28, 0x65, 0xff, 0x00, 0x00},
    {0x00, 0xaf, 0x0f, 0x0f, 0x08, 0x07, 0x07, 0x08, 0xff, 0x00, 0x00},
    {0x00, 0xb6, 0x0f, 0x0f, 0x64, 0x05, 0x01, 0x04, 0xff, 0x00, 0x00},
    {0x01, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00},
    {0x01, 0x07, 0x01, 0x22, 0x00, 0x85, 0x21, 0x21, 0xff, 0x00, 0x00},
    {0x01, 0x0e, 0x20, 0x84, 0x41, 0x22, 0x40, 0x85, 0xff, 0x00, 0x00},
    {0x01, 0x15, 0x61, 0x21, 0x60, 0x84, 0x81, 0x22, 0xff, 0x00, 0x00},
    {0x01, 0x1c, 0x80, 0x85, 0xa1, 0x21, 0xa0, 0x84, 0xff, 0x00, 0x00},
    {0x01, 0x23, 0xc1, 0x22, 0xc0, 0x85, 0xc2, 0x90, 0xff, 0x00, 0x00},
    {0x01, 0x2a, 0xc2, 0x90, 0xc2, 0x90, 0xc2, 0x90, 0xff, 0x00, 0x00},
    {0x01, 0x31, 0xc2, 0x90, 0xc2, 0x90, 0xc2, 0x90, 0xff, 0x00, 0x00},
    {0x01, 0x38, 0xc2, 0x90, 0xc2, 0x90, 0xc2, 0x90, 0xff, 0x00, 0x00},
    {0x01, 0x3f, 0xc2, 0x90, 0xc2, 0x90, 0xc2, 0x90, 0xff, 0x00, 0x00},
    {0x01, 0x46, 0xc2, 0x90, 0xc2, 0x90, 0xc2, 0x90, 0xff, 0x00, 0x00},
    {0x01, 0x4d, 0xc2, 0x90, 0xc2, 0x90, 0xc2, 0x90, 0xff, 0x00, 0x00},
    {0x01, 0x54, 0xc2, 0x90, 0xc2, 0x90, 0xc2, 0x90, 0xff, 0x00, 0x00},
    {0x01, 0x5b, 0xc2, 0x90, 0xc2, 0x90, 0xc2, 0x90, 0xff, 0x00, 0x00},
    {0x01, 0x62, 0xc2, 0x90, 0xc2, 0x90, 0xc2, 0x90, 0xff, 0x00, 0x00},
    {0x01, 0x69, 0x01, 0xff, 0xff, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00},
    {0x01, 0x70, 0x01, 0x21, 0x00, 0x84, 0x21, 0x21, 0xff, 0x00, 0x00},
    {0x01, 0x77, 0x20, 0x84, 0x41, 0x21, 0x40, 0x84, 0xff, 0x00, 0x00},
    {0x01, 0x7e, 0x61, 0x21, 0x60, 0x84, 0x81, 0x21, 0xff, 0x00, 0x00},
    {0x01, 0x85, 0x80, 0x8a, 0xa1, 0x27, 0xa0, 0x8d, 0xff, 0x00, 0x00},
    {0x01, 0x8c, 0xc1, 0x2a, 0xc0, 0x84, 0xc2, 0x90, 0xff, 0x00, 0x00},
    {0x01, 0x93, 0xc2, 0x90, 0xc2, 0x90, 0xc2, 0x90, 0xff, 0x00, 0x00},
    {0x01, 0x9a, 0xc2, 0x90, 0xc2, 0x90, 0xc2, 0x90, 0xff, 0x00, 0x00},
    {0x01, 0xa1, 0xc2, 0x90, 0xc2, 0x90, 0xc2, 0x90, 0xff, 0x00, 0x00},
    {0x01, 0xa8, 0xc2, 0x90, 0xc2, 0x90, 0xc2, 0x90, 0xff, 0x00, 0x00},
    {0x01, 0xaf, 0xc2, 0x90, 0xc2, 0x90, 0xc2, 0x90, 0xff, 0x00, 0x00},
    {0x01, 0xb6, 0xc2, 0x90, 0xc2, 0x90, 0xc2, 0x90, 0xff, 0x00, 0x00},
    {0x01, 0xbd, 0xc2, 0x90, 0xc2, 0x90, 0xc2, 0x90, 0xff, 0x00, 0x00},
    {0x01, 0xc4, 0xc2, 0x90, 0xc2, 0x90, 0xc2, 0x90, 0xff, 0x00, 0x00},
    {0x01, 0xcb, 0xc2, 0x90, 0xc2, 0x90, 0xc2, 0x90, 0xff, 0x00, 0x00},
    {0x01, 0xd2, 0x78, 0x0a, 0x05, 0x37, 0x4b, 0x00, 0xff, 0x00, 0x00},
    {0x01, 0xd9, 0x28, 0x0a, 0x02, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00},
    {0x01, 0xe0, 0xfb, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x80, 0x00, 0x0c, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x80, 0x01, 0x02, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x80, 0x02, 0x05, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x80, 0x03, 0x46, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x80, 0x04, 0x28, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x80, 0x05, 0x6e, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x80, 0x06, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x80, 0x07, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x80, 0x08, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x80, 0x09, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x80, 0x0a, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x80, 0x0b, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x80, 0x0c, 0x22, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x80, 0x0d, 0x2d, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x80, 0x0e, 0x37, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x80, 0x0f, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x80, 0x10, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x80, 0x11, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x81, 0x12, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x81, 0x13, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x81, 0x14, 0x1c, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x81, 0x15, 0x6e, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x81, 0x16, 0x26, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x81, 0x17, 0x6e, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x81, 0x18, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x81, 0x19, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x81, 0x1a, 0x64, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x81, 0x1b, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x81, 0x1c, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x81, 0x1d, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x81, 0x1e, 0x2b, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x81, 0x1f, 0x3b, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x81, 0x20, 0x4b, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x81, 0x21, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x81, 0x22, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x81, 0x23, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x84, 0x24, 0x01, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x84, 0x25, 0xe4, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x84, 0x26, 0x37, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x84, 0x27, 0x35, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x84, 0x28, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x84, 0x29, 0x01, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x88, 0x2a, 0x0c, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x88, 0x2b, 0x47, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x88, 0x2c, 0x05, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x88, 0x2d, 0x13, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x88, 0x30, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x88, 0x31, 0x20, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x88, 0x32, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x88, 0x33, 0xff, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x88, 0x34, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x88, 0x35, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x88, 0x36, 0x14, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x88, 0x37, 0x26, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x88, 0x38, 0x41, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x88, 0x39, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x88, 0x3a, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x88, 0x3b, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x89, 0x3c, 0x0a, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x89, 0x3d, 0x0b, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x89, 0x3e, 0x03, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x89, 0x3f, 0x12, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x89, 0x40, 0x02, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x89, 0x41, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x91, 0x42, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x91, 0x43, 0x20, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x91, 0x44, 0x6e, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x91, 0x45, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x91, 0x46, 0xff, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x91, 0x47, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x91, 0x48, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x91, 0x49, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x91, 0x4a, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x91, 0x4b, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x91, 0x4c, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x91, 0x4d, 0x00, 0x00, 0x65, 0x65, 0x65, 0x65, 0xff, 0x00, 0x00},
    {0x03, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00},
    {0x03, 0x07, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00},
    {0x03, 0x0e, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00},
    {0x03, 0x15, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00},
    {0x84, 0x27, 0x36, 0x01, 0x81, 0x8e, 0x00, 0xc1, 0xff, 0x00, 0x00},
    {0x88, 0x2b, 0x46, 0x01, 0x81, 0x8e, 0x00, 0xc1, 0xff, 0x00, 0x00},
    {0x88, 0x33, 0x01, 0x01, 0x81, 0x8e, 0x00, 0xc1, 0xff, 0x00, 0x00},
    {0x88, 0x33, 0xff, 0x01, 0x81, 0x8e, 0x00, 0xc1, 0xff, 0x00, 0x00}
};
uint8_t MAX_MSG_CNT = (sizeof(simData)/sizeof(simData[0]));
#endif

muTimer simTimer = muTimer();           // timer for sending simulation data
uint8_t msgCnt = 0;
bool simDataEnable = false;


void startSimData(){
   simDataEnable = true;
    msgCnt=0;
    Serial.println("start sim data === >>>");
}

void simDataCyclic(){
#ifdef SIM_MODE
    if (simTimer.cycleTrigger(100) && simDataEnable){
        if (msgCnt < MAX_MSG_CNT){
            parseInfo(simData[msgCnt], sizeof(simData[0]));
            Serial.print(msgCnt+1);
            Serial.print("/");
            Serial.println(MAX_MSG_CNT);
            msgCnt++;
        }
        else {
            simDataEnable = false;
            Serial.println("=== >>> finished sim data");
        }
    }
#endif
}