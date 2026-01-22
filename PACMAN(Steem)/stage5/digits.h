#ifndef DIGITS_H
#define DIGITS_H

/* BITMAP LIBRARY FOR NUMBERS 0–9 (8×8) */
/* Uses your existing UINT16 from raster.h */

/* DIGIT 0 */
static const UINT16 DIGIT_0[8] = {
    0xFC00,
    0xCC00,
    0xCC00,
    0xCC00,
    0xCC00,
    0xCC00,
    0xFC00,
    0x0000
};

/* DIGIT 1 */
static const UINT16 DIGIT_1[8] = {
    0x3000,
    0x7000,
    0x3000,
    0x3000,
    0x3000,
    0x3000,
    0xFC00,
    0x0000
};

/* DIGIT 2 */
static const UINT16 DIGIT_2[8] = {
    0xFC00,
    0x0C00,
    0x0C00,
    0xFC00,
    0xC000,
    0xC000,
    0xFC00,
    0x0000
};

/* DIGIT 3 */
static const UINT16 DIGIT_3[8] = {
    0xFC00,
    0x0C00,
    0x0C00,
    0xFC00,
    0x0C00,
    0x0C00,
    0xFC00,
    0x0000
};

/* DIGIT 4 */
static const UINT16 DIGIT_4[8] = {
    0xCC00,
    0xCC00,
    0xCC00,
    0xFC00,
    0x0C00,
    0x0C00,
    0x0C00,
    0x0000
};

/* DIGIT 5 */
static const UINT16 DIGIT_5[8] = {
    0xFC00,
    0xC000,
    0xC000,
    0xFC00,
    0x0C00,
    0x0C00,
    0xFC00,
    0x0000
};

/* DIGIT 6 */
static const UINT16 DIGIT_6[8] = {
    0xFC00,
    0xC000,
    0xC000,
    0xFC00,
    0xCC00,
    0xCC00,
    0xFC00,
    0x0000
};

/* DIGIT 7 */
static const UINT16 DIGIT_7[8] = {
    0xFC00,
    0x0C00,
    0x0C00,
    0x0C00,
    0x0C00,
    0x0C00,
    0x0C00,
    0x0000
};

/* DIGIT 8 */
static const UINT16 DIGIT_8[8] = {
    0xFC00,
    0xCC00,
    0xCC00,
    0xFC00,
    0xCC00,
    0xCC00,
    0xFC00,
    0x0000
};

/* DIGIT 9 */
static const UINT16 DIGIT_9[8] = {
    0xFC00,
    0xCC00,
    0xCC00,
    0xFC00,
    0x0C00,
    0x0C00,
    0xFC00,
    0x0000
};

#endif
