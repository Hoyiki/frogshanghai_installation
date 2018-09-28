#include <Wire.h>
#include <avr/pgmspace.h>

//rs485
int txden = 8;

byte a_stripes[] = {0x80, 0x83, 0x00, 0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F};
byte b_stripes[] = {0x80, 0x83, 0x01, 0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F};

byte c_stripes[] = {0x80, 0x83, 0x02, 
0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f
,0x8F};

byte d_stripes[] = {0x80, 0x83, 0x03, 
0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f
,0x8F};

int eye_delay_list[15] = {111, 94, 81, 69, 61, 54, 51, 50, 51, 54, 61, 69, 81, 94, 111};


const byte all_frames[15][4][32] PROGMEM =
{{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x5f,0x6f,0x77,0x7b,0x7d,0x7d,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x7f,0x7f,0x1f,0xe,0x6,0x2,0x1,0x1,0x3,0x7,0xf,0x1f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7d,0x7b,0x77,0x6f,0x5f,0x5f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7c,0x38,0x30,0x20,0x40,0x40,0x60,0x70,0x78,0x7c,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}},{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x5f,0x6f,0x77,0x7b,0x7d,0x7d,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x7f,0x1f,0xf,0x6,0x2,0x2,0x1,0x1,0x3,0x7,0xf,0x5f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7d,0x7b,0x77,0x6f,0x5f,0x5f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0x7f,0x7c,0x78,0x30,0x20,0x20,0x40,0x40,0x60,0x70,0x78,0x7d,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}},{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x5f,0x6f,0x77,0x7b,0x7d,0x7d,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x1f,0xf,0x7,0x2,0x2,0x2,0x1,0x5,0xb,0x17,0x6f,0x5f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7d,0x7b,0x77,0x6f,0x5f,0x5f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0x7c,0x78,0x70,0x20,0x20,0x20,0x40,0x50,0x68,0x74,0x7b,0x7d,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}},{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x5f,0x6f,0x77,0x7b,0x7d,0x7d,0x7e,0x7e,0x7e,0x7f,0x7f,0x1f,0xf,0x7,0x3,0x2,0x2,0x2,0x5,0xd,0x1b,0x77,0x6f,0x5f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7d,0x7b,0x77,0x6f,0x5f,0x5f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7c,0x78,0x70,0x60,0x20,0x20,0x20,0x50,0x58,0x6c,0x77,0x7b,0x7d,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}},{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x5f,0x6f,0x77,0x7b,0x7d,0x7d,0x7e,0x7e,0x7e,0x7f,0x1f,0xf,0x7,0x3,0x3,0x2,0x2,0x6,0xd,0x1d,0x7b,0x77,0x6f,0x5f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7d,0x7b,0x77,0x6f,0x5f,0x5f,0x3f,0x3f,0x3f,0x7f,0x7c,0x78,0x70,0x60,0x60,0x20,0x20,0x30,0x58,0x5c,0x6f,0x77,0x7b,0x7d,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}},{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x5f,0x6f,0x77,0x7b,0x7d,0x7d,0x7e,0x7e,0x7e,0x1f,0xf,0x7,0x3,0x3,0x3,0x2,0x6,0xe,0x1d,0x7d,0x7b,0x77,0x6f,0x5f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7d,0x7b,0x77,0x6f,0x5f,0x5f,0x3f,0x3f,0x3f,0x7c,0x78,0x70,0x60,0x60,0x60,0x20,0x30,0x38,0x5c,0x5f,0x6f,0x77,0x7b,0x7d,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}},{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x5f,0x6f,0x77,0x7b,0x7d,0x7d,0x7e,0x7e,0x1e,0xf,0x7,0x3,0x3,0x3,0x3,0x6,0xe,0x1e,0x7d,0x7d,0x7b,0x77,0x6f,0x5f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7d,0x7b,0x77,0x6f,0x5f,0x5f,0x3f,0x3f,0x3c,0x78,0x70,0x60,0x60,0x60,0x60,0x30,0x38,0x3c,0x5f,0x5f,0x6f,0x77,0x7b,0x7d,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}},{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x5f,0x6f,0x77,0x7b,0x7d,0x7d,0x7e,0x1e,0xe,0x7,0x3,0x3,0x3,0x3,0x7,0xe,0x1e,0x7e,0x7d,0x7d,0x7b,0x77,0x6f,0x5f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7d,0x7b,0x77,0x6f,0x5f,0x5f,0x3f,0x3c,0x38,0x70,0x60,0x60,0x60,0x60,0x70,0x38,0x3c,0x3f,0x5f,0x5f,0x6f,0x77,0x7b,0x7d,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}},{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x5f,0x6f,0x77,0x7b,0x7d,0x7d,0x1e,0xe,0x6,0x3,0x3,0x3,0x3,0x7,0xf,0x1e,0x7e,0x7e,0x7d,0x7d,0x7b,0x77,0x6f,0x5f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7d,0x7b,0x77,0x6f,0x5f,0x5f,0x3c,0x38,0x30,0x60,0x60,0x60,0x60,0x70,0x78,0x3c,0x3f,0x3f,0x5f,0x5f,0x6f,0x77,0x7b,0x7d,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}},{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x5f,0x6f,0x77,0x7b,0x7d,0x1d,0xe,0x6,0x2,0x3,0x3,0x3,0x7,0xf,0x1f,0x7e,0x7e,0x7e,0x7d,0x7d,0x7b,0x77,0x6f,0x5f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7d,0x7b,0x77,0x6f,0x5f,0x5c,0x38,0x30,0x20,0x60,0x60,0x60,0x70,0x78,0x7c,0x3f,0x3f,0x3f,0x5f,0x5f,0x6f,0x77,0x7b,0x7d,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}},{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x5f,0x6f,0x77,0x7b,0x1d,0xd,0x6,0x2,0x2,0x3,0x3,0x7,0xf,0x1f,0x7f,0x7e,0x7e,0x7e,0x7d,0x7d,0x7b,0x77,0x6f,0x5f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7d,0x7b,0x77,0x6f,0x5c,0x58,0x30,0x20,0x20,0x60,0x60,0x70,0x78,0x7c,0x7f,0x3f,0x3f,0x3f,0x5f,0x5f,0x6f,0x77,0x7b,0x7d,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}},{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x5f,0x6f,0x77,0x1b,0xd,0x5,0x2,0x2,0x2,0x3,0x7,0xf,0x1f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7d,0x7d,0x7b,0x77,0x6f,0x5f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7d,0x7b,0x77,0x6c,0x58,0x50,0x20,0x20,0x20,0x60,0x70,0x78,0x7c,0x7f,0x7f,0x3f,0x3f,0x3f,0x5f,0x5f,0x6f,0x77,0x7b,0x7d,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}},{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x5f,0x6f,0x17,0xb,0x5,0x1,0x2,0x2,0x2,0x7,0xf,0x1f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7d,0x7d,0x7b,0x77,0x6f,0x5f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7d,0x7b,0x74,0x68,0x50,0x40,0x20,0x20,0x20,0x70,0x78,0x7c,0x7f,0x7f,0x7f,0x3f,0x3f,0x3f,0x5f,0x5f,0x6f,0x77,0x7b,0x7d,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}},{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x5f,0xf,0x7,0x3,0x1,0x1,0x2,0x2,0x6,0xf,0x1f,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7d,0x7d,0x7b,0x77,0x6f,0x5f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7d,0x78,0x70,0x60,0x40,0x40,0x20,0x20,0x30,0x78,0x7c,0x7f,0x7f,0x7f,0x7f,0x3f,0x3f,0x3f,0x5f,0x5f,0x6f,0x77,0x7b,0x7d,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}},{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x1f,0xf,0x7,0x3,0x1,0x1,0x2,0x6,0xe,0x1f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7d,0x7d,0x7b,0x77,0x6f,0x5f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7c,0x78,0x70,0x60,0x40,0x40,0x20,0x30,0x38,0x7c,0x7f,0x7f,0x7f,0x7f,0x7f,0x3f,0x3f,0x3f,0x5f,0x5f,0x6f,0x77,0x7b,0x7d,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}}}
;

const byte all_frames_blink[7][4][32] PROGMEM =
{{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x5f,0x6f,0x77,0x7b,0x7d,0x7d,0x7e,0x1e,0xe,0x7,0x3,0x3,0x3,0x3,0x7,0xe,0x1e,0x7e,0x7d,0x7d,0x7b,0x77,0x6f,0x5f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7d,0x7b,0x77,0x6f,0x5f,0x5f,0x3f,0x3c,0x38,0x70,0x60,0x60,0x60,0x60,0x70,0x38,0x3c,0x3f,0x5f,0x5f,0x6f,0x77,0x7b,0x7d,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}},{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x3f,0x5f,0x6f,0x77,0x7b,0x7b,0x7d,0x1d,0xd,0x6,0x2,0x2,0x2,0x2,0x6,0xd,0x1d,0x7d,0x7b,0x7b,0x77,0x6f,0x5f,0x3f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7e,0x7d,0x7b,0x77,0x6f,0x6f,0x5f,0x5c,0x58,0x30,0x20,0x20,0x20,0x20,0x30,0x58,0x5c,0x5f,0x6f,0x6f,0x77,0x7b,0x7d,0x7e,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}},{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x3f,0x3f,0x5f,0x6f,0x77,0x77,0x7b,0x1b,0xb,0x5,0x1,0x1,0x1,0x1,0x5,0xb,0x1b,0x7b,0x77,0x77,0x6f,0x5f,0x3f,0x3f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7e,0x7e,0x7d,0x7b,0x77,0x77,0x6f,0x6c,0x68,0x50,0x40,0x40,0x40,0x40,0x50,0x68,0x6c,0x6f,0x77,0x77,0x7b,0x7d,0x7e,0x7e,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}},{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x3f,0x3f,0x3f,0x5f,0x6f,0x6f,0x77,0x17,0x7,0x3,0x3,0x3,0x3,0x3,0x3,0x7,0x17,0x77,0x6f,0x6f,0x5f,0x3f,0x3f,0x3f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7e,0x7e,0x7e,0x7d,0x7b,0x7b,0x77,0x74,0x70,0x60,0x60,0x60,0x60,0x60,0x60,0x70,0x74,0x77,0x7b,0x7b,0x7d,0x7e,0x7e,0x7e,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}},{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x3f,0x3f,0x3f,0x3f,0x5f,0x5f,0x6f,0xf,0xf,0x7,0x7,0x7,0x7,0x7,0x7,0xf,0xf,0x6f,0x5f,0x5f,0x3f,0x3f,0x3f,0x3f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7d,0x7d,0x7b,0x78,0x78,0x70,0x70,0x70,0x70,0x70,0x70,0x78,0x78,0x7b,0x7d,0x7d,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}},{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x5f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x5f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7d,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7c,0x7d,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}},{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}}}
;

const byte all_frames_blink_new[5][4][32] PROGMEM =
{{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x5f,0x6f,0x77,0x7b,0x7d,0x7d,0x7e,0x1e,0xe,0x7,0x3,0x3,0x3,0x3,0x7,0xe,0x1e,0x7e,0x7d,0x7d,0x7b,0x77,0x6f,0x5f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7d,0x7b,0x77,0x6f,0x5f,0x5f,0x3f,0x3c,0x38,0x70,0x60,0x60,0x60,0x60,0x70,0x38,0x3c,0x3f,0x5f,0x5f,0x6f,0x77,0x7b,0x7d,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}},{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x1f,0x2f,0x37,0x5b,0x5d,0x6d,0x6e,0xe,0x6,0x7,0x7,0x7,0x7,0x7,0x7,0x6,0xe,0x6e,0x6d,0x5d,0x5b,0x37,0x2f,0x1f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7d,0x7b,0x77,0x6f,0x5f,0x5f,0x3f,0x3c,0x38,0x70,0x60,0x60,0x60,0x60,0x70,0x38,0x3c,0x3f,0x5f,0x5f,0x6f,0x77,0x7b,0x7d,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}},{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x1f,0x2f,0x37,0x3b,0x3d,0x3d,0x3e,0x3e,0x3e,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3e,0x3e,0x3e,0x3d,0x3d,0x3b,0x37,0x2f,0x1f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7d,0x7b,0x77,0x6f,0x5f,0x5f,0x3f,0x3c,0x38,0x70,0x60,0x60,0x60,0x60,0x70,0x38,0x3c,0x3f,0x5f,0x5f,0x6f,0x77,0x7b,0x7d,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}},{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x5f,0x6f,0x77,0x7b,0x7d,0x7d,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7d,0x7d,0x7b,0x77,0x6f,0x5f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7c,0x7a,0x76,0x6e,0x5d,0x5d,0x3d,0x3b,0x3b,0x73,0x63,0x63,0x63,0x63,0x73,0x3b,0x3b,0x3d,0x5d,0x5d,0x6e,0x76,0x7a,0x7c,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}},{{0x80,0x83,0x00,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F},{0x80,0x83,0x01,0x7f,0x3f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x3f,0x7f,0x8F},{0x80,0x83,0x02,0x7f,0x7e,0x7c,0x79,0x73,0x67,0x4f,0x4f,0x1f,0x1f,0x1f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x1f,0x1f,0x1f,0x4f,0x4f,0x67,0x73,0x79,0x7c,0x7e,0x7f,0x8F},{0x80,0x83,0x03,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e,0x7e,0x7e,0x7e,0x7e,0x7e,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x8F}}}
;


void write_frame(int i)
{
  byte one_frame[4][32] = {{}};
  for (int r = 0; r < 4; r ++){
    for (int l = 0; l < 32; l ++){
      one_frame[r][l] = pgm_read_byte(&all_frames[i][r][l]);
    }
  }
  Serial.write(one_frame[0], 32);
  Serial.write(one_frame[1], 32);
  Serial.write(one_frame[2], 32);
  Serial.write(one_frame[3], 32);
}

void write_frame_blink(int i)
{
  byte one_frame[4][32] = {{}};
  for (int r = 0; r < 4; r ++){
    for (int l = 0; l < 32; l ++){
      one_frame[r][l] = pgm_read_byte(&all_frames_blink[i][r][l]);
    }
  }
  Serial.write(one_frame[0], 32);
  Serial.write(one_frame[1], 32);
  Serial.write(one_frame[2], 32);
  Serial.write(one_frame[3], 32);
}

void write_frame_blink_new(int i)
{
  byte one_frame[4][32] = {{}};
  for (int r = 0; r < 4; r ++){
    for (int l = 0; l < 32; l ++){
      one_frame[r][l] = pgm_read_byte(&all_frames_blink_new[i][r][l]);
    }
  }
  Serial.write(one_frame[0], 32);
  Serial.write(one_frame[1], 32);
  Serial.write(one_frame[2], 32);
  Serial.write(one_frame[3], 32);
}

void write_white(){
  Serial.write(a_stripes, 32);
  Serial.write(b_stripes, 32);
  Serial.write(c_stripes, 32);
  Serial.write(d_stripes, 32);
}

void setup() 
{
 Serial.begin(9600);
 pinMode(txden, OUTPUT);
 digitalWrite(txden, HIGH); // master 
}

void loop() { 

//  write_white();
//  delay(5000);

  for (int i = 0; i < 15; i++){
    write_frame(i);
    delay(eye_delay_list[i]);
  }
  for (int i = 13; i > 0; i--){
    write_frame(i);
    delay(eye_delay_list[i]);
  }

//  write_frame(7);
//  delay(1000);
//  for (int i = 1; i < 7; i++){
//    write_frame_blink(i);
//    delay(30);
//  }
//  for (int i = 5; i >= 1; i--){
//    write_frame_blink(i);
//    delay(30 + (5-i)*6);
//  }

//  write_frame(7);
//  delay(1000);
//  for (int i = 1; i < 5; i++){
//    write_frame_blink_new(i);
//    delay(30);
//  }
//  delay(1000);
//  for (int i = 3; i >= 1; i--){
//    write_frame_blink_new(i);
//    delay(30 + (5-i)*6);
//  }
}