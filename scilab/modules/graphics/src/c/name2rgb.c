/* C code produced by gperf version 3.0.4 */
/* Command-line: gperf -m 50 name2rgb.gperf  */
/* Computed positions: -k'1,3,5-9,12-15,$' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 21 "name2rgb.gperf"

#include <name2rgb.h>
#include "strlen.h"

struct color {char* name; int red; int green; int blue;};
#line 36 "name2rgb.gperf"
struct color;

#define TOTAL_KEYWORDS 796
#define MIN_WORD_LENGTH 3
#define MAX_WORD_LENGTH 22
#define MIN_HASH_VALUE 57
#define MAX_HASH_VALUE 3612
/* maximum key range = 3556, duplicates = 0 */

#ifndef GPERF_DOWNCASE
#define GPERF_DOWNCASE 1
static unsigned char gperf_downcase[256] =
  {
      0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  10,  11,  12,  13,  14,
     15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,
     30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,
     45,  46,  47,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,
     60,  61,  62,  63,  64,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106,
    107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121,
    122,  91,  92,  93,  94,  95,  96,  97,  98,  99, 100, 101, 102, 103, 104,
    105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
    120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134,
    135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149,
    150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164,
    165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179,
    180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194,
    195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209,
    210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224,
    225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
    240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254,
    255
  };
#endif

#ifndef GPERF_CASE_STRCMP
#define GPERF_CASE_STRCMP 1
static int
gperf_case_strcmp (s1, s2)
     register const char *s1;
     register const char *s2;
{
  for (;;)
    {
      unsigned char c1 = gperf_downcase[(unsigned char)*s1++];
      unsigned char c2 = gperf_downcase[(unsigned char)*s2++];
      if (c1 != 0 && c1 == c2)
        continue;
      return (int)c1 - (int)c2;
    }
}
#endif

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash (str, len)
     register const char *str;
     register unsigned int len;
{
  static const unsigned short asso_values[] =
    {
      3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613,
      3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613,
      3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613,
      3613, 3613,  480, 3613, 3613, 3613, 3613, 3613, 3613, 3613,
      3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613,  805,   18,
        17,   14,   13, 1148,  990,  936,  436,  188, 3613, 3613,
      3613, 3613, 3613, 3613, 3613,   43,   44,  711,   86,   13,
        36,   13,  207,  587,   13,  400,   81,  157,   30,   85,
       416,   85,   15,   13,  155,  279, 1100, 1179, 3613,  295,
      3613, 3613, 3613, 3613, 3613, 3613, 3613,   43,   44,  711,
        86,   13,   36,   13,  207,  587,   13,  400,   81,  157,
        30,   85,  416,   85,   15,   13,  155,  279, 1100, 1179,
      3613,  295, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613,
      3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613,
      3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613,
      3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613,
      3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613,
      3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613,
      3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613,
      3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613,
      3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613,
      3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613,
      3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613,
      3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613,
      3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613, 3613,
      3613, 3613, 3613, 3613, 3613, 3613
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[14]];
      /*FALLTHROUGH*/
      case 14:
        hval += asso_values[(unsigned char)str[13]];
      /*FALLTHROUGH*/
      case 13:
        hval += asso_values[(unsigned char)str[12]];
      /*FALLTHROUGH*/
      case 12:
        hval += asso_values[(unsigned char)str[11]];
      /*FALLTHROUGH*/
      case 11:
      case 10:
      case 9:
        hval += asso_values[(unsigned char)str[8]];
      /*FALLTHROUGH*/
      case 8:
        hval += asso_values[(unsigned char)str[7]];
      /*FALLTHROUGH*/
      case 7:
        hval += asso_values[(unsigned char)str[6]];
      /*FALLTHROUGH*/
      case 6:
        hval += asso_values[(unsigned char)str[5]];
      /*FALLTHROUGH*/
      case 5:
        hval += asso_values[(unsigned char)str[4]];
      /*FALLTHROUGH*/
      case 4:
      case 3:
        hval += asso_values[(unsigned char)str[2]];
      /*FALLTHROUGH*/
      case 2:
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval + asso_values[(unsigned char)str[len - 1]];
}

static const struct color colorlist[] =
  {
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""},
#line 627 "name2rgb.gperf"
    {"grey4", 10, 10, 10},
    {""},
#line 625 "name2rgb.gperf"
    {"grey3", 8, 8, 8},
    {""}, {""}, {""}, {""}, {""},
#line 623 "name2rgb.gperf"
    {"grey2", 5, 5, 5},
    {""},
#line 621 "name2rgb.gperf"
    {"grey1", 3, 3, 3},
    {""}, {""}, {""},
#line 707 "name2rgb.gperf"
    {"grey44", 112, 112, 112},
#line 687 "name2rgb.gperf"
    {"grey34", 87, 87, 87},
#line 705 "name2rgb.gperf"
    {"grey43", 110, 110, 110},
#line 685 "name2rgb.gperf"
    {"grey33", 84, 84, 84},
#line 667 "name2rgb.gperf"
    {"grey24", 61, 61, 61},
#line 647 "name2rgb.gperf"
    {"grey14", 36, 36, 36},
#line 665 "name2rgb.gperf"
    {"grey23", 59, 59, 59},
#line 645 "name2rgb.gperf"
    {"grey13", 33, 33, 33},
#line 703 "name2rgb.gperf"
    {"grey42", 107, 107, 107},
#line 683 "name2rgb.gperf"
    {"grey32", 82, 82, 82},
#line 701 "name2rgb.gperf"
    {"grey41", 105, 105, 105},
#line 681 "name2rgb.gperf"
    {"grey31", 79, 79, 79},
#line 663 "name2rgb.gperf"
    {"grey22", 56, 56, 56},
#line 643 "name2rgb.gperf"
    {"grey12", 31, 31, 31},
#line 661 "name2rgb.gperf"
    {"grey21", 54, 54, 54},
#line 641 "name2rgb.gperf"
    {"grey11", 28, 28, 28},
#line 626 "name2rgb.gperf"
    {"gray4", 10, 10, 10},
#line 449 "name2rgb.gperf"
    {"green4", 0, 139, 0},
#line 624 "name2rgb.gperf"
    {"gray3", 8, 8, 8},
#line 448 "name2rgb.gperf"
    {"green3", 0, 205, 0},
#line 214 "name2rgb.gperf"
    {"green", 0, 255, 0},
    {""}, {""}, {""},
#line 622 "name2rgb.gperf"
    {"gray2", 5, 5, 5},
#line 447 "name2rgb.gperf"
    {"green2", 0, 238, 0},
#line 620 "name2rgb.gperf"
    {"gray1", 3, 3, 3},
#line 446 "name2rgb.gperf"
    {"green1", 0, 255, 0},
    {""}, {""},
#line 706 "name2rgb.gperf"
    {"gray44", 112, 112, 112},
#line 686 "name2rgb.gperf"
    {"gray34", 87, 87, 87},
#line 704 "name2rgb.gperf"
    {"gray43", 110, 110, 110},
#line 684 "name2rgb.gperf"
    {"gray33", 84, 84, 84},
#line 666 "name2rgb.gperf"
    {"gray24", 61, 61, 61},
#line 646 "name2rgb.gperf"
    {"gray14", 36, 36, 36},
#line 664 "name2rgb.gperf"
    {"gray23", 59, 59, 59},
#line 644 "name2rgb.gperf"
    {"gray13", 33, 33, 33},
#line 702 "name2rgb.gperf"
    {"gray42", 107, 107, 107},
#line 682 "name2rgb.gperf"
    {"gray32", 82, 82, 82},
#line 700 "name2rgb.gperf"
    {"gray41", 105, 105, 105},
#line 680 "name2rgb.gperf"
    {"gray31", 79, 79, 79},
#line 662 "name2rgb.gperf"
    {"gray22", 56, 56, 56},
#line 642 "name2rgb.gperf"
    {"gray12", 31, 31, 31},
#line 660 "name2rgb.gperf"
    {"gray21", 54, 54, 54},
#line 640 "name2rgb.gperf"
    {"gray11", 28, 28, 28},
    {""},
#line 557 "name2rgb.gperf"
    {"red4", 139, 0, 0},
#line 556 "name2rgb.gperf"
    {"red3", 205, 0, 0},
    {""}, {""},
#line 555 "name2rgb.gperf"
    {"red2", 238, 0, 0},
#line 554 "name2rgb.gperf"
    {"red1", 255, 0, 0},
    {""},
#line 481 "name2rgb.gperf"
    {"gold4", 139, 117, 0},
    {""},
#line 480 "name2rgb.gperf"
    {"gold3", 205, 173, 0},
    {""},
#line 309 "name2rgb.gperf"
    {"snow4", 139, 137, 137},
    {""},
#line 308 "name2rgb.gperf"
    {"snow3", 205, 201, 201},
#line 501 "name2rgb.gperf"
    {"sienna4", 139, 71, 38},
#line 479 "name2rgb.gperf"
    {"gold2", 238, 201, 0},
#line 500 "name2rgb.gperf"
    {"sienna3", 205, 104, 57},
#line 478 "name2rgb.gperf"
    {"gold1", 255, 215, 0},
    {""},
#line 307 "name2rgb.gperf"
    {"snow2", 238, 233, 233},
    {""},
#line 306 "name2rgb.gperf"
    {"snow1", 255, 250, 250},
#line 499 "name2rgb.gperf"
    {"sienna2", 238, 121, 66},
    {""},
#line 498 "name2rgb.gperf"
    {"sienna1", 255, 130, 71},
    {""}, {""}, {""}, {""}, {""},
#line 250 "name2rgb.gperf"
    {"sienna", 160, 82, 45},
    {""},
#line 445 "name2rgb.gperf"
    {"springgreen4", 0, 139, 69},
    {""},
#line 444 "name2rgb.gperf"
    {"springgreen3", 0, 205, 102},
#line 211 "name2rgb.gperf"
    {"springgreen", 0, 255, 127},
    {""}, {""}, {""}, {""},
#line 443 "name2rgb.gperf"
    {"springgreen2", 0, 238, 118},
    {""},
#line 442 "name2rgb.gperf"
    {"springgreen1", 0, 255, 127},
    {""},
#line 437 "name2rgb.gperf"
    {"seagreen4", 46, 139, 87},
    {""},
#line 436 "name2rgb.gperf"
    {"seagreen3", 67, 205, 128},
#line 203 "name2rgb.gperf"
    {"seagreen", 46, 139, 87},
    {""}, {""}, {""}, {""},
#line 435 "name2rgb.gperf"
    {"seagreen2", 78, 238, 148},
    {""},
#line 434 "name2rgb.gperf"
    {"seagreen1", 84, 255, 159},
#line 266 "name2rgb.gperf"
    {"orange", 255, 165, 0},
    {""}, {""},
#line 92 "name2rgb.gperf"
    {"linen", 250, 240, 230},
    {""}, {""},
#line 202 "name2rgb.gperf"
    {"sea green", 46, 139, 87},
    {""}, {""}, {""}, {""},
#line 238 "name2rgb.gperf"
    {"gold", 255, 215, 0},
    {""}, {""},
#line 537 "name2rgb.gperf"
    {"orange4", 139, 90, 0},
    {""},
#line 536 "name2rgb.gperf"
    {"orange3", 205, 133, 0},
#line 275 "name2rgb.gperf"
    {"red", 255, 0, 0},
#line 525 "name2rgb.gperf"
    {"brown4", 139, 35, 35},
    {""},
#line 524 "name2rgb.gperf"
    {"brown3", 205, 51, 51},
#line 260 "name2rgb.gperf"
    {"brown", 165, 42, 42},
#line 535 "name2rgb.gperf"
    {"orange2", 238, 154, 0},
    {""},
#line 534 "name2rgb.gperf"
    {"orange1", 255, 165, 0},
    {""},
#line 523 "name2rgb.gperf"
    {"brown2", 238, 59, 59},
    {""},
#line 522 "name2rgb.gperf"
    {"brown1", 255, 64, 64},
#line 513 "name2rgb.gperf"
    {"tan4", 139, 90, 43},
#line 512 "name2rgb.gperf"
    {"tan3", 205, 133, 63},
    {""}, {""},
#line 511 "name2rgb.gperf"
    {"tan2", 238, 154, 73},
#line 510 "name2rgb.gperf"
    {"tan1", 255, 165, 79},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""},
#line 257 "name2rgb.gperf"
    {"tan", 210, 180, 140},
    {""}, {""}, {""}, {""}, {""},
#line 197 "name2rgb.gperf"
    {"darkgreen", 0, 100, 0},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 529 "name2rgb.gperf"
    {"salmon4", 139, 76, 57},
    {""},
#line 528 "name2rgb.gperf"
    {"salmon3", 205, 112, 84},
#line 263 "name2rgb.gperf"
    {"salmon", 250, 128, 114},
#line 807 "name2rgb.gperf"
    {"grey94", 240, 240, 240},
    {""},
#line 805 "name2rgb.gperf"
    {"grey93", 237, 237, 237},
    {""},
#line 527 "name2rgb.gperf"
    {"salmon2", 238, 130, 98},
    {""},
#line 526 "name2rgb.gperf"
    {"salmon1", 255, 140, 105},
    {""},
#line 803 "name2rgb.gperf"
    {"grey92", 235, 235, 235},
    {""},
#line 801 "name2rgb.gperf"
    {"grey91", 232, 232, 232},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""},
#line 433 "name2rgb.gperf"
    {"darkseagreen4", 105, 139, 105},
    {""},
#line 432 "name2rgb.gperf"
    {"darkseagreen3", 155, 205, 155},
#line 201 "name2rgb.gperf"
    {"darkseagreen", 143, 188, 143},
    {""}, {""}, {""}, {""},
#line 431 "name2rgb.gperf"
    {"darkseagreen2", 180, 238, 180},
#line 806 "name2rgb.gperf"
    {"gray94", 240, 240, 240},
#line 430 "name2rgb.gperf"
    {"darkseagreen1", 193, 255, 193},
#line 804 "name2rgb.gperf"
    {"gray93", 237, 237, 237},
    {""}, {""}, {""}, {""}, {""},
#line 802 "name2rgb.gperf"
    {"gray92", 235, 235, 235},
    {""},
#line 800 "name2rgb.gperf"
    {"gray91", 232, 232, 232},
    {""}, {""}, {""}, {""},
#line 553 "name2rgb.gperf"
    {"orangered4", 139, 37, 0},
#line 552 "name2rgb.gperf"
    {"orangered3", 205, 55, 0},
    {""}, {""},
#line 551 "name2rgb.gperf"
    {"orangered2", 238, 64, 0},
#line 550 "name2rgb.gperf"
    {"orangered1", 255, 69, 0},
    {""}, {""}, {""}, {""},
#line 225 "name2rgb.gperf"
    {"forestgreen", 34, 139, 34},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 831 "name2rgb.gperf"
    {"darkred", 139, 0, 0},
    {""},
#line 268 "name2rgb.gperf"
    {"darkorange", 255, 140, 0},
#line 541 "name2rgb.gperf"
    {"darkorange4", 139, 69, 0},
#line 540 "name2rgb.gperf"
    {"darkorange3", 205, 102, 0},
    {""}, {""},
#line 539 "name2rgb.gperf"
    {"darkorange2", 238, 118, 0},
#line 538 "name2rgb.gperf"
    {"darkorange1", 255, 127, 0},
    {""}, {""}, {""},
#line 581 "name2rgb.gperf"
    {"maroon4", 139, 28, 98},
    {""},
#line 580 "name2rgb.gperf"
    {"maroon3", 205, 41, 144},
#line 285 "name2rgb.gperf"
    {"maroon", 176, 48, 96},
    {""},
#line 140 "name2rgb.gperf"
    {"grey", 190, 190, 190},
    {""}, {""},
#line 579 "name2rgb.gperf"
    {"maroon2", 238, 48, 167},
    {""},
#line 578 "name2rgb.gperf"
    {"maroon1", 255, 52, 179},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 164 "name2rgb.gperf"
    {"blue", 0, 0, 255},
    {""}, {""},
#line 833 "name2rgb.gperf"
    {"lightgreen", 144, 238, 144},
    {""}, {""},
#line 485 "name2rgb.gperf"
    {"goldenrod4", 139, 105, 20},
#line 484 "name2rgb.gperf"
    {"goldenrod3", 205, 155, 29},
    {""}, {""},
#line 483 "name2rgb.gperf"
    {"goldenrod2", 238, 180, 34},
#line 482 "name2rgb.gperf"
    {"goldenrod1", 255, 193, 37},
    {""},
#line 113 "name2rgb.gperf"
    {"azure", 240, 255, 255},
#line 369 "name2rgb.gperf"
    {"blue4", 0, 0, 139},
#line 139 "name2rgb.gperf"
    {"gray", 190, 190, 190},
#line 368 "name2rgb.gperf"
    {"blue3", 0, 0, 205},
    {""}, {""}, {""}, {""},
#line 221 "name2rgb.gperf"
    {"limegreen", 50, 205, 50},
#line 367 "name2rgb.gperf"
    {"blue2", 0, 0, 238},
#line 274 "name2rgb.gperf"
    {"orangered", 255, 69, 0},
#line 366 "name2rgb.gperf"
    {"blue1", 0, 0, 255},
    {""}, {""},
#line 357 "name2rgb.gperf"
    {"azure4", 131, 139, 139},
#line 99 "name2rgb.gperf"
    {"bisque", 255, 228, 196},
#line 356 "name2rgb.gperf"
    {"azure3", 193, 205, 205},
    {""}, {""}, {""}, {""}, {""},
#line 355 "name2rgb.gperf"
    {"azure2", 224, 238, 238},
    {""},
#line 354 "name2rgb.gperf"
    {"azure1", 240, 255, 255},
#line 249 "name2rgb.gperf"
    {"saddlebrown", 139, 69, 19},
    {""}, {""}, {""},
#line 321 "name2rgb.gperf"
    {"bisque4", 139, 125, 107},
    {""},
#line 320 "name2rgb.gperf"
    {"bisque3", 205, 183, 158},
    {""}, {""}, {""}, {""}, {""},
#line 319 "name2rgb.gperf"
    {"bisque2", 238, 213, 183},
    {""},
#line 318 "name2rgb.gperf"
    {"bisque1", 255, 228, 196},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""},
#line 637 "name2rgb.gperf"
    {"grey9", 23, 23, 23},
    {""}, {""}, {""},
#line 829 "name2rgb.gperf"
    {"darkmagenta", 139, 0, 139},
    {""}, {""}, {""}, {""}, {""},
#line 207 "name2rgb.gperf"
    {"lightseagreen", 32, 178, 170},
#line 241 "name2rgb.gperf"
    {"goldenrod", 218, 165, 32},
    {""}, {""},
#line 717 "name2rgb.gperf"
    {"grey49", 125, 125, 125},
#line 697 "name2rgb.gperf"
    {"grey39", 99, 99, 99},
    {""}, {""},
#line 677 "name2rgb.gperf"
    {"grey29", 74, 74, 74},
#line 657 "name2rgb.gperf"
    {"grey19", 48, 48, 48},
    {""}, {""}, {""}, {""}, {""},
#line 589 "name2rgb.gperf"
    {"magenta4", 139, 0, 139},
    {""},
#line 588 "name2rgb.gperf"
    {"magenta3", 205, 0, 205},
    {""}, {""},
#line 636 "name2rgb.gperf"
    {"gray9", 23, 23, 23},
    {""}, {""},
#line 587 "name2rgb.gperf"
    {"magenta2", 238, 0, 238},
    {""},
#line 586 "name2rgb.gperf"
    {"magenta1", 255, 0, 255},
    {""}, {""}, {""}, {""}, {""},
#line 290 "name2rgb.gperf"
    {"magenta", 255, 0, 255},
    {""}, {""},
#line 716 "name2rgb.gperf"
    {"gray49", 125, 125, 125},
#line 696 "name2rgb.gperf"
    {"gray39", 99, 99, 99},
    {""}, {""},
#line 676 "name2rgb.gperf"
    {"gray29", 74, 74, 74},
#line 656 "name2rgb.gperf"
    {"gray19", 48, 48, 48},
    {""},
#line 393 "name2rgb.gperf"
    {"slategray4", 108, 123, 139},
#line 392 "name2rgb.gperf"
    {"slategray3", 159, 182, 205},
    {""}, {""},
#line 391 "name2rgb.gperf"
    {"slategray2", 185, 211, 238},
#line 390 "name2rgb.gperf"
    {"slategray1", 198, 226, 255},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 313 "name2rgb.gperf"
    {"seashell4", 139, 134, 130},
    {""},
#line 312 "name2rgb.gperf"
    {"seashell3", 205, 197, 191},
    {""},
#line 569 "name2rgb.gperf"
    {"pink4", 139, 99, 108},
    {""},
#line 568 "name2rgb.gperf"
    {"pink3", 205, 145, 158},
    {""},
#line 311 "name2rgb.gperf"
    {"seashell2", 238, 229, 222},
    {""},
#line 310 "name2rgb.gperf"
    {"seashell1", 255, 245, 238},
    {""},
#line 567 "name2rgb.gperf"
    {"pink2", 238, 169, 184},
    {""},
#line 566 "name2rgb.gperf"
    {"pink1", 255, 181, 197},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 787 "name2rgb.gperf"
    {"grey84", 214, 214, 214},
    {""},
#line 785 "name2rgb.gperf"
    {"grey83", 212, 212, 212},
    {""}, {""}, {""}, {""}, {""},
#line 783 "name2rgb.gperf"
    {"grey82", 209, 209, 209},
    {""},
#line 781 "name2rgb.gperf"
    {"grey81", 207, 207, 207},
    {""}, {""}, {""},
#line 155 "name2rgb.gperf"
    {"slateblue", 106, 90, 205},
#line 361 "name2rgb.gperf"
    {"slateblue4", 71, 60, 139},
#line 360 "name2rgb.gperf"
    {"slateblue3", 105, 89, 205},
    {""}, {""},
#line 359 "name2rgb.gperf"
    {"slateblue2", 122, 103, 238},
#line 358 "name2rgb.gperf"
    {"slateblue1", 131, 111, 255},
    {""}, {""}, {""}, {""}, {""},
#line 262 "name2rgb.gperf"
    {"darksalmon", 233, 150, 122},
    {""}, {""}, {""},
#line 786 "name2rgb.gperf"
    {"gray84", 214, 214, 214},
    {""},
#line 784 "name2rgb.gperf"
    {"gray83", 212, 212, 212},
#line 109 "name2rgb.gperf"
    {"seashell", 255, 245, 238},
    {""}, {""}, {""}, {""},
#line 782 "name2rgb.gperf"
    {"gray82", 209, 209, 209},
    {""},
#line 780 "name2rgb.gperf"
    {"gray81", 207, 207, 207},
    {""}, {""}, {""}, {""},
#line 825 "name2rgb.gperf"
    {"darkblue", 0, 0, 139},
    {""}, {""}, {""}, {""},
#line 302 "name2rgb.gperf"
    {"purple", 160, 32, 240},
    {""},
#line 174 "name2rgb.gperf"
    {"steelblue", 70, 130, 180},
#line 377 "name2rgb.gperf"
    {"steelblue4", 54, 100, 139},
#line 376 "name2rgb.gperf"
    {"steelblue3", 79, 148, 205},
    {""}, {""},
#line 375 "name2rgb.gperf"
    {"steelblue2", 92, 172, 238},
#line 374 "name2rgb.gperf"
    {"steelblue1", 99, 184, 255},
    {""}, {""}, {""}, {""}, {""},
#line 609 "name2rgb.gperf"
    {"purple4", 85, 26, 139},
    {""},
#line 608 "name2rgb.gperf"
    {"purple3", 125, 38, 205},
    {""}, {""}, {""}, {""}, {""},
#line 607 "name2rgb.gperf"
    {"purple2", 145, 44, 238},
    {""},
#line 606 "name2rgb.gperf"
    {"purple1", 155, 48, 255},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""},
#line 533 "name2rgb.gperf"
    {"lightsalmon4", 139, 87, 66},
    {""},
#line 532 "name2rgb.gperf"
    {"lightsalmon3", 205, 129, 98},
#line 265 "name2rgb.gperf"
    {"lightsalmon", 255, 160, 122},
#line 549 "name2rgb.gperf"
    {"tomato4", 139, 54, 38},
    {""},
#line 548 "name2rgb.gperf"
    {"tomato3", 205, 79, 57},
    {""},
#line 531 "name2rgb.gperf"
    {"lightsalmon2", 238, 149, 114},
#line 489 "name2rgb.gperf"
    {"darkgoldenrod4", 139, 101, 8},
#line 530 "name2rgb.gperf"
    {"lightsalmon1", 255, 160, 122},
#line 488 "name2rgb.gperf"
    {"darkgoldenrod3", 205, 149, 12},
#line 547 "name2rgb.gperf"
    {"tomato2", 238, 92, 66},
    {""},
#line 546 "name2rgb.gperf"
    {"tomato1", 255, 99, 71},
#line 817 "name2rgb.gperf"
    {"grey99", 252, 252, 252},
    {""},
#line 487 "name2rgb.gperf"
    {"darkgoldenrod2", 238, 173, 14},
    {""},
#line 486 "name2rgb.gperf"
    {"darkgoldenrod1", 255, 185, 15},
    {""}, {""}, {""},
#line 441 "name2rgb.gperf"
    {"palegreen4", 84, 139, 84},
#line 440 "name2rgb.gperf"
    {"palegreen3", 124, 205, 124},
    {""}, {""},
#line 439 "name2rgb.gperf"
    {"palegreen2", 144, 238, 144},
#line 438 "name2rgb.gperf"
    {"palegreen1", 154, 255, 154},
    {""}, {""}, {""},
#line 120 "name2rgb.gperf"
    {"mistyrose", 255, 228, 225},
#line 353 "name2rgb.gperf"
    {"mistyrose4", 139, 125, 123},
#line 352 "name2rgb.gperf"
    {"mistyrose3", 205, 183, 181},
    {""}, {""},
#line 351 "name2rgb.gperf"
    {"mistyrose2", 238, 213, 210},
#line 350 "name2rgb.gperf"
    {"mistyrose1", 255, 228, 225},
#line 209 "name2rgb.gperf"
    {"palegreen", 152, 251, 152},
    {""}, {""}, {""}, {""}, {""},
#line 816 "name2rgb.gperf"
    {"gray99", 252, 252, 252},
#line 166 "name2rgb.gperf"
    {"dodgerblue", 30, 144, 255},
#line 373 "name2rgb.gperf"
    {"dodgerblue4", 16, 78, 139},
#line 372 "name2rgb.gperf"
    {"dodgerblue3", 24, 116, 205},
    {""}, {""},
#line 371 "name2rgb.gperf"
    {"dodgerblue2", 28, 134, 238},
#line 370 "name2rgb.gperf"
    {"dodgerblue1", 30, 144, 255},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 272 "name2rgb.gperf"
    {"tomato", 255, 99, 71},
    {""}, {""}, {""}, {""}, {""},
#line 243 "name2rgb.gperf"
    {"darkgoldenrod", 184, 134, 11},
    {""},
#line 210 "name2rgb.gperf"
    {"spring green", 0, 255, 127},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""},
#line 253 "name2rgb.gperf"
    {"beige", 245, 245, 220},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""},
#line 196 "name2rgb.gperf"
    {"dark green", 0, 100, 0},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""},
#line 178 "name2rgb.gperf"
    {"lightblue", 173, 216, 230},
#line 401 "name2rgb.gperf"
    {"lightblue4", 104, 131, 139},
#line 400 "name2rgb.gperf"
    {"lightblue3", 154, 192, 205},
    {""}, {""},
#line 399 "name2rgb.gperf"
    {"lightblue2", 178, 223, 238},
#line 398 "name2rgb.gperf"
    {"lightblue1", 191, 239, 255},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 170 "name2rgb.gperf"
    {"skyblue", 135, 206, 235},
    {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 134 "name2rgb.gperf"
    {"slategrey", 112, 128, 144},
    {""}, {""}, {""}, {""},
#line 251 "name2rgb.gperf"
    {"peru", 205, 133, 63},
#line 385 "name2rgb.gperf"
    {"skyblue4", 74, 112, 139},
    {""},
#line 384 "name2rgb.gperf"
    {"skyblue3", 108, 166, 205},
    {""}, {""}, {""}, {""}, {""},
#line 383 "name2rgb.gperf"
    {"skyblue2", 126, 192, 238},
#line 153 "name2rgb.gperf"
    {"darkslateblue", 72, 61, 139},
#line 382 "name2rgb.gperf"
    {"skyblue1", 135, 206, 255},
#line 597 "name2rgb.gperf"
    {"plum4", 139, 102, 139},
    {""},
#line 596 "name2rgb.gperf"
    {"plum3", 205, 150, 205},
    {""}, {""}, {""}, {""}, {""},
#line 595 "name2rgb.gperf"
    {"plum2", 238, 174, 238},
    {""},
#line 594 "name2rgb.gperf"
    {"plum1", 255, 187, 255},
    {""}, {""},
#line 132 "name2rgb.gperf"
    {"slategray", 112, 128, 144},
#line 821 "name2rgb.gperf"
    {"darkgrey", 169, 169, 169},
#line 469 "name2rgb.gperf"
    {"lightgoldenrod4", 139, 129, 76},
    {""},
#line 468 "name2rgb.gperf"
    {"lightgoldenrod3", 205, 190, 112},
    {""}, {""},
#line 169 "name2rgb.gperf"
    {"sky blue", 135, 206, 235},
    {""}, {""},
#line 467 "name2rgb.gperf"
    {"lightgoldenrod2", 238, 220, 130},
    {""},
#line 466 "name2rgb.gperf"
    {"lightgoldenrod1", 255, 236, 139},
    {""}, {""}, {""}, {""}, {""},
#line 473 "name2rgb.gperf"
    {"lightyellow4", 139, 139, 122},
#line 273 "name2rgb.gperf"
    {"orange red", 255, 69, 0},
#line 472 "name2rgb.gperf"
    {"lightyellow3", 205, 205, 180},
    {""}, {""}, {""}, {""}, {""},
#line 471 "name2rgb.gperf"
    {"lightyellow2", 238, 238, 209},
#line 45 "name2rgb.gperf"
    {"scilabgreen4", 0, 144, 0},
#line 470 "name2rgb.gperf"
    {"lightyellow1", 255, 255, 224},
#line 47 "name2rgb.gperf"
    {"scilabgreen3", 0, 176, 0},
    {""},
#line 823 "name2rgb.gperf"
    {"darkgray", 169, 169, 169},
    {""}, {""}, {""},
#line 49 "name2rgb.gperf"
    {"scilabgreen2", 0, 208, 0},
    {""}, {""}, {""},
#line 267 "name2rgb.gperf"
    {"dark orange", 255, 140, 0},
    {""}, {""}, {""}, {""}, {""},
#line 425 "name2rgb.gperf"
    {"darkslategray4", 82, 139, 139},
#line 421 "name2rgb.gperf"
    {"cyan4", 0, 139, 139},
#line 424 "name2rgb.gperf"
    {"darkslategray3", 121, 205, 205},
#line 420 "name2rgb.gperf"
    {"cyan3", 0, 205, 205},
#line 188 "name2rgb.gperf"
    {"cyan", 0, 255, 255},
#line 830 "name2rgb.gperf"
    {"dark red", 139, 0, 0},
    {""}, {""},
#line 423 "name2rgb.gperf"
    {"darkslategray2", 141, 238, 238},
#line 419 "name2rgb.gperf"
    {"cyan2", 0, 238, 238},
#line 422 "name2rgb.gperf"
    {"darkslategray1", 151, 255, 255},
#line 418 "name2rgb.gperf"
    {"cyan1", 0, 255, 255},
    {""}, {""}, {""},
#line 224 "name2rgb.gperf"
    {"forest green", 34, 139, 34},
#line 240 "name2rgb.gperf"
    {"lightgoldenrod", 238, 221, 130},
    {""}, {""}, {""},
#line 248 "name2rgb.gperf"
    {"saddle brown", 139, 69, 19},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 832 "name2rgb.gperf"
    {"light green", 144, 238, 144},
#line 220 "name2rgb.gperf"
    {"lime green", 50, 205, 50},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""},
#line 57 "name2rgb.gperf"
    {"scilabred4", 144, 0, 0},
#line 59 "name2rgb.gperf"
    {"scilabred3", 176, 0, 0},
    {""}, {""},
#line 61 "name2rgb.gperf"
    {"scilabred2", 208, 0, 0},
#line 165 "name2rgb.gperf"
    {"dodger blue", 30, 144, 255},
#line 163 "name2rgb.gperf"
    {"royalblue", 65, 105, 225},
#line 365 "name2rgb.gperf"
    {"royalblue4", 39, 64, 139},
#line 364 "name2rgb.gperf"
    {"royalblue3", 58, 95, 205},
    {""}, {""},
#line 363 "name2rgb.gperf"
    {"royalblue2", 67, 110, 238},
#line 362 "name2rgb.gperf"
    {"royalblue1", 72, 118, 255},
    {""}, {""},
#line 545 "name2rgb.gperf"
    {"coral4", 139, 62, 47},
    {""},
#line 544 "name2rgb.gperf"
    {"coral3", 205, 91, 69},
    {""},
#line 176 "name2rgb.gperf"
    {"lightsteelblue", 176, 196, 222},
#line 797 "name2rgb.gperf"
    {"grey89", 227, 227, 227},
    {""}, {""},
#line 543 "name2rgb.gperf"
    {"coral2", 238, 106, 80},
#line 205 "name2rgb.gperf"
    {"mediumseagreen", 60, 179, 113},
#line 542 "name2rgb.gperf"
    {"coral1", 255, 114, 86},
#line 280 "name2rgb.gperf"
    {"pink", 255, 192, 203},
    {""}, {""}, {""}, {""}, {""},
#line 292 "name2rgb.gperf"
    {"plum", 221, 160, 221},
#line 397 "name2rgb.gperf"
    {"lightsteelblue4", 110, 123, 139},
    {""},
#line 396 "name2rgb.gperf"
    {"lightsteelblue3", 162, 181, 205},
    {""}, {""}, {""}, {""}, {""},
#line 395 "name2rgb.gperf"
    {"lightsteelblue2", 188, 210, 238},
    {""},
#line 394 "name2rgb.gperf"
    {"lightsteelblue1", 202, 225, 255},
#line 130 "name2rgb.gperf"
    {"dimgrey", 105, 105, 105},
#line 69 "name2rgb.gperf"
    {"scilabbrown4", 128, 48, 0},
    {""},
#line 71 "name2rgb.gperf"
    {"scilabbrown3", 160, 64, 0},
    {""}, {""},
#line 796 "name2rgb.gperf"
    {"gray89", 227, 227, 227},
    {""}, {""},
#line 73 "name2rgb.gperf"
    {"scilabbrown2", 192, 96, 0},
    {""}, {""}, {""}, {""},
#line 129 "name2rgb.gperf"
    {"dim grey", 105, 105, 105},
#line 497 "name2rgb.gperf"
    {"indianred4", 139, 58, 58},
#line 496 "name2rgb.gperf"
    {"indianred3", 205, 85, 85},
    {""}, {""},
#line 495 "name2rgb.gperf"
    {"indianred2", 238, 99, 99},
#line 494 "name2rgb.gperf"
    {"indianred1", 255, 106, 106},
#line 142 "name2rgb.gperf"
    {"lightgrey", 211, 211, 211},
    {""}, {""},
#line 122 "name2rgb.gperf"
    {"black", 0, 0, 0},
#line 269 "name2rgb.gperf"
    {"coral", 255, 127, 80},
    {""},
#line 133 "name2rgb.gperf"
    {"slate grey", 112, 128, 144},
#line 457 "name2rgb.gperf"
    {"olivedrab4", 105, 139, 34},
#line 456 "name2rgb.gperf"
    {"olivedrab3", 154, 205, 50},
#line 128 "name2rgb.gperf"
    {"dimgray", 105, 105, 105},
    {""},
#line 455 "name2rgb.gperf"
    {"olivedrab2", 179, 238, 58},
#line 454 "name2rgb.gperf"
    {"olivedrab1", 192, 255, 62},
    {""},
#line 635 "name2rgb.gperf"
    {"grey8", 20, 20, 20},
    {""},
#line 828 "name2rgb.gperf"
    {"dark magenta", 139, 0, 139},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 127 "name2rgb.gperf"
    {"dim gray", 105, 105, 105},
    {""},
#line 206 "name2rgb.gperf"
    {"light sea green", 32, 178, 170},
    {""},
#line 261 "name2rgb.gperf"
    {"dark salmon", 233, 150, 122},
#line 715 "name2rgb.gperf"
    {"grey48", 122, 122, 122},
#line 695 "name2rgb.gperf"
    {"grey38", 97, 97, 97},
#line 144 "name2rgb.gperf"
    {"lightgray", 211, 211, 211},
    {""},
#line 675 "name2rgb.gperf"
    {"grey28", 71, 71, 71},
#line 655 "name2rgb.gperf"
    {"grey18", 46, 46, 46},
    {""}, {""},
#line 131 "name2rgb.gperf"
    {"slate gray", 112, 128, 144},
#line 227 "name2rgb.gperf"
    {"olivedrab", 107, 142, 35},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 634 "name2rgb.gperf"
    {"gray8", 20, 20, 20},
    {""}, {""},
#line 87 "name2rgb.gperf"
    {"gainsboro", 220, 220, 220},
    {""},
#line 264 "name2rgb.gperf"
    {"light salmon", 255, 160, 122},
    {""}, {""},
#line 159 "name2rgb.gperf"
    {"lightslateblue", 132, 112, 255},
    {""}, {""}, {""}, {""}, {""},
#line 714 "name2rgb.gperf"
    {"gray48", 122, 122, 122},
#line 694 "name2rgb.gperf"
    {"gray38", 97, 97, 97},
    {""}, {""},
#line 674 "name2rgb.gperf"
    {"gray28", 71, 71, 71},
#line 654 "name2rgb.gperf"
    {"gray18", 46, 46, 46},
    {""}, {""},
#line 247 "name2rgb.gperf"
    {"indianred", 205, 92, 92},
#line 168 "name2rgb.gperf"
    {"deepskyblue", 0, 191, 255},
    {""},
#line 91 "name2rgb.gperf"
    {"oldlace", 253, 245, 230},
    {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 184 "name2rgb.gperf"
    {"darkturquoise", 0, 206, 209},
    {""}, {""}, {""},
#line 381 "name2rgb.gperf"
    {"deepskyblue4", 0, 104, 139},
    {""},
#line 380 "name2rgb.gperf"
    {"deepskyblue3", 0, 154, 205},
    {""}, {""}, {""},
#line 154 "name2rgb.gperf"
    {"slate blue", 106, 90, 205},
    {""},
#line 379 "name2rgb.gperf"
    {"deepskyblue2", 0, 178, 238},
    {""},
#line 378 "name2rgb.gperf"
    {"deepskyblue1", 0, 191, 255},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""},
#line 767 "name2rgb.gperf"
    {"grey74", 189, 189, 189},
    {""},
#line 765 "name2rgb.gperf"
    {"grey73", 186, 186, 186},
    {""}, {""},
#line 341 "name2rgb.gperf"
    {"ivory4", 139, 139, 131},
    {""},
#line 340 "name2rgb.gperf"
    {"ivory3", 205, 205, 193},
#line 763 "name2rgb.gperf"
    {"grey72", 184, 184, 184},
#line 255 "name2rgb.gperf"
    {"sandy brown", 244, 164, 96},
#line 761 "name2rgb.gperf"
    {"grey71", 181, 181, 181},
    {""}, {""},
#line 339 "name2rgb.gperf"
    {"ivory2", 238, 238, 224},
    {""},
#line 338 "name2rgb.gperf"
    {"ivory1", 255, 255, 240},
    {""},
#line 305 "name2rgb.gperf"
    {"thistle", 216, 191, 216},
    {""}, {""},
#line 173 "name2rgb.gperf"
    {"steel blue", 70, 130, 180},
    {""}, {""}, {""}, {""}, {""},
#line 824 "name2rgb.gperf"
    {"dark blue", 0, 0, 139},
    {""},
#line 126 "name2rgb.gperf"
    {"darkslategrey", 47, 79, 79},
    {""},
#line 766 "name2rgb.gperf"
    {"gray74", 189, 189, 189},
#line 617 "name2rgb.gperf"
    {"thistle4", 139, 123, 139},
#line 764 "name2rgb.gperf"
    {"gray73", 186, 186, 186},
#line 616 "name2rgb.gperf"
    {"thistle3", 205, 181, 205},
    {""}, {""}, {""}, {""},
#line 762 "name2rgb.gperf"
    {"gray72", 184, 184, 184},
#line 615 "name2rgb.gperf"
    {"thistle2", 238, 210, 238},
#line 760 "name2rgb.gperf"
    {"gray71", 181, 181, 181},
#line 614 "name2rgb.gperf"
    {"thistle1", 255, 225, 255},
    {""}, {""}, {""},
#line 172 "name2rgb.gperf"
    {"lightskyblue", 135, 206, 250},
#line 90 "name2rgb.gperf"
    {"old lace", 253, 245, 230},
    {""}, {""}, {""}, {""},
#line 232 "name2rgb.gperf"
    {"palegoldenrod", 238, 232, 170},
    {""}, {""},
#line 747 "name2rgb.gperf"
    {"grey64", 163, 163, 163},
    {""},
#line 745 "name2rgb.gperf"
    {"grey63", 161, 161, 161},
    {""},
#line 124 "name2rgb.gperf"
    {"darkslategray", 47, 79, 79},
#line 389 "name2rgb.gperf"
    {"lightskyblue4", 96, 123, 139},
    {""},
#line 388 "name2rgb.gperf"
    {"lightskyblue3", 141, 182, 205},
#line 743 "name2rgb.gperf"
    {"grey62", 158, 158, 158},
    {""},
#line 741 "name2rgb.gperf"
    {"grey61", 156, 156, 156},
    {""}, {""},
#line 387 "name2rgb.gperf"
    {"lightskyblue2", 164, 211, 238},
#line 465 "name2rgb.gperf"
    {"khaki4", 139, 134, 78},
#line 386 "name2rgb.gperf"
    {"lightskyblue1", 176, 226, 255},
#line 464 "name2rgb.gperf"
    {"khaki3", 205, 198, 115},
    {""}, {""}, {""}, {""}, {""},
#line 463 "name2rgb.gperf"
    {"khaki2", 238, 230, 133},
#line 208 "name2rgb.gperf"
    {"pale green", 152, 251, 152},
#line 462 "name2rgb.gperf"
    {"khaki1", 255, 246, 143},
    {""}, {""},
#line 141 "name2rgb.gperf"
    {"light grey", 211, 211, 211},
    {""}, {""},
#line 746 "name2rgb.gperf"
    {"gray64", 163, 163, 163},
    {""},
#line 744 "name2rgb.gperf"
    {"gray63", 161, 161, 161},
#line 119 "name2rgb.gperf"
    {"misty rose", 255, 228, 225},
#line 115 "name2rgb.gperf"
    {"aliceblue", 240, 248, 255},
    {""}, {""}, {""},
#line 742 "name2rgb.gperf"
    {"gray62", 158, 158, 158},
    {""},
#line 740 "name2rgb.gperf"
    {"gray61", 156, 156, 156},
    {""}, {""}, {""},
#line 815 "name2rgb.gperf"
    {"grey98", 250, 250, 250},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""},
#line 143 "name2rgb.gperf"
    {"light gray", 211, 211, 211},
#line 161 "name2rgb.gperf"
    {"mediumblue", 0, 0, 205},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 39 "name2rgb.gperf"
    {"scilabblue4", 0, 0, 144},
#line 41 "name2rgb.gperf"
    {"scilabblue3", 0, 0, 176},
    {""}, {""},
#line 43 "name2rgb.gperf"
    {"scilabblue2", 0, 0, 208},
    {""}, {""},
#line 814 "name2rgb.gperf"
    {"gray98", 250, 250, 250},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 242 "name2rgb.gperf"
    {"dark goldenrod", 184, 134, 11},
    {""}, {""}, {""}, {""}, {""},
#line 63 "name2rgb.gperf"
    {"scilabmagenta4", 144, 0, 144},
    {""},
#line 65 "name2rgb.gperf"
    {"scilabmagenta3", 176, 0, 176},
    {""}, {""}, {""}, {""}, {""},
#line 67 "name2rgb.gperf"
    {"scilabmagenta2", 208, 0, 208},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 177 "name2rgb.gperf"
    {"light blue", 173, 216, 230},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""},
#line 187 "name2rgb.gperf"
    {"turquoise", 64, 224, 208},
#line 417 "name2rgb.gperf"
    {"turquoise4", 0, 134, 139},
#line 416 "name2rgb.gperf"
    {"turquoise3", 0, 197, 205},
    {""},
#line 138 "name2rgb.gperf"
    {"lightslategrey", 119, 136, 153},
#line 415 "name2rgb.gperf"
    {"turquoise2", 0, 229, 238},
#line 414 "name2rgb.gperf"
    {"turquoise1", 0, 245, 255},
    {""},
#line 195 "name2rgb.gperf"
    {"aquamarine", 127, 255, 212},
#line 429 "name2rgb.gperf"
    {"aquamarine4", 69, 139, 116},
#line 428 "name2rgb.gperf"
    {"aquamarine3", 102, 205, 170},
    {""}, {""},
#line 427 "name2rgb.gperf"
    {"aquamarine2", 118, 238, 198},
#line 426 "name2rgb.gperf"
    {"aquamarine1", 127, 255, 212},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""},
#line 271 "name2rgb.gperf"
    {"lightcoral", 240, 128, 128},
#line 258 "name2rgb.gperf"
    {"chocolate", 210, 105, 30},
#line 517 "name2rgb.gperf"
    {"chocolate4", 139, 69, 19},
#line 516 "name2rgb.gperf"
    {"chocolate3", 205, 102, 29},
    {""}, {""},
#line 515 "name2rgb.gperf"
    {"chocolate2", 238, 118, 33},
#line 514 "name2rgb.gperf"
    {"chocolate1", 255, 127, 36},
    {""},
#line 136 "name2rgb.gperf"
    {"lightslategray", 119, 136, 153},
    {""}, {""},
#line 727 "name2rgb.gperf"
    {"grey54", 138, 138, 138},
    {""},
#line 725 "name2rgb.gperf"
    {"grey53", 135, 135, 135},
    {""}, {""}, {""}, {""}, {""},
#line 723 "name2rgb.gperf"
    {"grey52", 133, 133, 133},
    {""},
#line 721 "name2rgb.gperf"
    {"grey51", 130, 130, 130},
    {""},
#line 827 "name2rgb.gperf"
    {"darkcyan", 0, 139, 139},
#line 56 "name2rgb.gperf"
    {"scilab red4", 144, 0, 0},
#line 58 "name2rgb.gperf"
    {"scilab red3", 176, 0, 0},
#line 820 "name2rgb.gperf"
    {"dark grey", 169, 169, 169},
    {""},
#line 60 "name2rgb.gperf"
    {"scilab red2", 208, 0, 0},
#line 217 "name2rgb.gperf"
    {"mediumspringgreen", 0, 250, 154},
#line 239 "name2rgb.gperf"
    {"light goldenrod", 238, 221, 130},
    {""}, {""}, {""}, {""},
#line 200 "name2rgb.gperf"
    {"dark sea green", 143, 188, 143},
    {""}, {""}, {""}, {""}, {""},
#line 726 "name2rgb.gperf"
    {"gray54", 138, 138, 138},
    {""},
#line 724 "name2rgb.gperf"
    {"gray53", 135, 135, 135},
    {""}, {""}, {""}, {""}, {""},
#line 722 "name2rgb.gperf"
    {"gray52", 133, 133, 133},
    {""},
#line 720 "name2rgb.gperf"
    {"gray51", 130, 130, 130},
    {""}, {""}, {""}, {""},
#line 822 "name2rgb.gperf"
    {"dark gray", 169, 169, 169},
#line 215 "name2rgb.gperf"
    {"chartreuse", 127, 255, 0},
#line 453 "name2rgb.gperf"
    {"chartreuse4", 69, 139, 0},
#line 452 "name2rgb.gperf"
    {"chartreuse3", 102, 205, 0},
    {""}, {""},
#line 451 "name2rgb.gperf"
    {"chartreuse2", 118, 238, 0},
#line 450 "name2rgb.gperf"
    {"chartreuse1", 127, 255, 0},
    {""}, {""},
#line 157 "name2rgb.gperf"
    {"mediumslateblue", 123, 104, 238},
    {""}, {""},
#line 44 "name2rgb.gperf"
    {"scilab green4", 0, 144, 0},
    {""},
#line 46 "name2rgb.gperf"
    {"scilab green3", 0, 176, 0},
#line 106 "name2rgb.gperf"
    {"ivory", 255, 255, 240},
    {""}, {""}, {""}, {""},
#line 48 "name2rgb.gperf"
    {"scilab green2", 0, 208, 0},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 82 "name2rgb.gperf"
    {"snow", 255, 250, 250},
    {""}, {""}, {""},
#line 204 "name2rgb.gperf"
    {"medium sea green", 60, 179, 113},
    {""},
#line 146 "name2rgb.gperf"
    {"midnightblue", 25, 25, 112},
    {""}, {""}, {""}, {""},
#line 112 "name2rgb.gperf"
    {"mintcream", 245, 255, 250},
    {""}, {""},
#line 68 "name2rgb.gperf"
    {"scilab brown4", 128, 48, 0},
    {""},
#line 70 "name2rgb.gperf"
    {"scilab brown3", 160, 64, 0},
#line 162 "name2rgb.gperf"
    {"royal blue", 65, 105, 225},
    {""}, {""}, {""}, {""},
#line 72 "name2rgb.gperf"
    {"scilab brown2", 192, 96, 0},
    {""}, {""}, {""}, {""},
#line 160 "name2rgb.gperf"
    {"medium blue", 0, 0, 205},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 152 "name2rgb.gperf"
    {"dark slate blue", 72, 61, 139},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""},
#line 38 "name2rgb.gperf"
    {"scilab blue4", 0, 0, 144},
    {""},
#line 40 "name2rgb.gperf"
    {"scilab blue3", 0, 0, 176},
    {""}, {""}, {""}, {""}, {""},
#line 42 "name2rgb.gperf"
    {"scilab blue2", 0, 0, 208},
    {""},
#line 795 "name2rgb.gperf"
    {"grey88", 224, 224, 224},
    {""}, {""}, {""},
#line 777 "name2rgb.gperf"
    {"grey79", 201, 201, 201},
    {""}, {""}, {""},
#line 116 "name2rgb.gperf"
    {"lavender", 230, 230, 250},
    {""},
#line 246 "name2rgb.gperf"
    {"indian red", 205, 92, 92},
#line 405 "name2rgb.gperf"
    {"lightcyan4", 122, 139, 139},
#line 404 "name2rgb.gperf"
    {"lightcyan3", 180, 205, 205},
    {""}, {""},
#line 403 "name2rgb.gperf"
    {"lightcyan2", 209, 238, 238},
#line 402 "name2rgb.gperf"
    {"lightcyan1", 224, 255, 255},
    {""}, {""}, {""}, {""}, {""},
#line 182 "name2rgb.gperf"
    {"paleturquoise", 175, 238, 238},
#line 226 "name2rgb.gperf"
    {"olive drab", 107, 142, 35},
    {""}, {""}, {""},
#line 190 "name2rgb.gperf"
    {"lightcyan", 224, 255, 255},
    {""}, {""},
#line 794 "name2rgb.gperf"
    {"gray88", 224, 224, 224},
    {""}, {""}, {""},
#line 776 "name2rgb.gperf"
    {"gray79", 201, 201, 201},
    {""},
#line 409 "name2rgb.gperf"
    {"paleturquoise4", 102, 139, 139},
    {""},
#line 408 "name2rgb.gperf"
    {"paleturquoise3", 150, 205, 205},
#line 509 "name2rgb.gperf"
    {"wheat4", 139, 126, 102},
    {""},
#line 508 "name2rgb.gperf"
    {"wheat3", 205, 186, 150},
    {""},
#line 213 "name2rgb.gperf"
    {"lawngreen", 124, 252, 0},
#line 407 "name2rgb.gperf"
    {"paleturquoise2", 174, 238, 238},
    {""},
#line 406 "name2rgb.gperf"
    {"paleturquoise1", 187, 255, 255},
#line 507 "name2rgb.gperf"
    {"wheat2", 238, 216, 174},
    {""},
#line 506 "name2rgb.gperf"
    {"wheat1", 255, 231, 186},
    {""},
#line 192 "name2rgb.gperf"
    {"cadetblue", 95, 158, 160},
#line 413 "name2rgb.gperf"
    {"cadetblue4", 83, 134, 139},
#line 412 "name2rgb.gperf"
    {"cadetblue3", 122, 197, 205},
    {""}, {""},
#line 411 "name2rgb.gperf"
    {"cadetblue2", 142, 229, 238},
#line 410 "name2rgb.gperf"
    {"cadetblue1", 152, 245, 255},
#line 757 "name2rgb.gperf"
    {"grey69", 176, 176, 176},
    {""}, {""}, {""}, {""}, {""},
#line 493 "name2rgb.gperf"
    {"rosybrown4", 139, 105, 105},
#line 492 "name2rgb.gperf"
    {"rosybrown3", 205, 155, 155},
    {""}, {""},
#line 491 "name2rgb.gperf"
    {"rosybrown2", 238, 180, 180},
#line 490 "name2rgb.gperf"
    {"rosybrown1", 255, 193, 193},
    {""}, {""}, {""},
#line 565 "name2rgb.gperf"
    {"hotpink4", 139, 58, 98},
    {""},
#line 564 "name2rgb.gperf"
    {"hotpink3", 205, 96, 144},
    {""}, {""}, {""}, {""},
#line 245 "name2rgb.gperf"
    {"rosybrown", 188, 143, 143},
#line 563 "name2rgb.gperf"
    {"hotpink2", 238, 106, 167},
    {""},
#line 562 "name2rgb.gperf"
    {"hotpink1", 255, 110, 180},
    {""}, {""}, {""},
#line 304 "name2rgb.gperf"
    {"mediumpurple", 147, 112, 219},
#line 756 "name2rgb.gperf"
    {"gray69", 176, 176, 176},
#line 147 "name2rgb.gperf"
    {"navy", 0, 0, 128},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""},
#line 613 "name2rgb.gperf"
    {"mediumpurple4", 93, 71, 139},
    {""},
#line 612 "name2rgb.gperf"
    {"mediumpurple3", 137, 104, 205},
    {""}, {""}, {""}, {""},
#line 98 "name2rgb.gperf"
    {"blanchedalmond", 255, 235, 205},
#line 611 "name2rgb.gperf"
    {"mediumpurple2", 159, 121, 238},
    {""},
#line 610 "name2rgb.gperf"
    {"mediumpurple1", 171, 130, 255},
    {""}, {""}, {""}, {""},
#line 325 "name2rgb.gperf"
    {"peachpuff4", 139, 119, 101},
#line 324 "name2rgb.gperf"
    {"peachpuff3", 205, 175, 149},
    {""}, {""},
#line 323 "name2rgb.gperf"
    {"peachpuff2", 238, 203, 173},
#line 322 "name2rgb.gperf"
    {"peachpuff1", 255, 218, 185},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 101 "name2rgb.gperf"
    {"peachpuff", 255, 218, 185},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""},
#line 585 "name2rgb.gperf"
    {"violetred4", 139, 34, 82},
#line 584 "name2rgb.gperf"
    {"violetred3", 205, 50, 120},
    {""}, {""},
#line 583 "name2rgb.gperf"
    {"violetred2", 238, 58, 140},
#line 582 "name2rgb.gperf"
    {"violetred1", 255, 62, 150},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 593 "name2rgb.gperf"
    {"orchid4", 139, 71, 137},
    {""},
#line 592 "name2rgb.gperf"
    {"orchid3", 205, 105, 201},
    {""}, {""},
#line 254 "name2rgb.gperf"
    {"wheat", 245, 222, 179},
    {""}, {""},
#line 591 "name2rgb.gperf"
    {"orchid2", 238, 122, 233},
    {""},
#line 590 "name2rgb.gperf"
    {"orchid1", 255, 131, 250},
    {""},
#line 291 "name2rgb.gperf"
    {"violet", 238, 130, 238},
    {""}, {""}, {""}, {""},
#line 125 "name2rgb.gperf"
    {"dark slate grey", 47, 79, 79},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 231 "name2rgb.gperf"
    {"pale goldenrod", 238, 232, 170},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""},
#line 123 "name2rgb.gperf"
    {"dark slate gray", 47, 79, 79},
#line 114 "name2rgb.gperf"
    {"alice blue", 240, 248, 255},
    {""}, {""}, {""}, {""}, {""},
#line 737 "name2rgb.gperf"
    {"grey59", 150, 150, 150},
    {""}, {""}, {""}, {""},
#line 293 "name2rgb.gperf"
    {"orchid", 218, 112, 214},
#line 289 "name2rgb.gperf"
    {"violetred", 208, 32, 144},
    {""}, {""}, {""}, {""},
#line 561 "name2rgb.gperf"
    {"deeppink4", 139, 10, 80},
#line 149 "name2rgb.gperf"
    {"navyblue", 0, 0, 128},
#line 560 "name2rgb.gperf"
    {"deeppink3", 205, 16, 118},
    {""}, {""}, {""}, {""}, {""},
#line 559 "name2rgb.gperf"
    {"deeppink2", 238, 18, 137},
    {""},
#line 558 "name2rgb.gperf"
    {"deeppink1", 255, 20, 147},
    {""},
#line 104 "name2rgb.gperf"
    {"moccasin", 255, 228, 181},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 736 "name2rgb.gperf"
    {"gray59", 150, 150, 150},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""},
#line 601 "name2rgb.gperf"
    {"mediumorchid4", 122, 55, 139},
#line 111 "name2rgb.gperf"
    {"mint cream", 245, 255, 250},
#line 600 "name2rgb.gperf"
    {"mediumorchid3", 180, 82, 205},
    {""}, {""}, {""}, {""},
#line 230 "name2rgb.gperf"
    {"khaki", 240, 230, 140},
#line 599 "name2rgb.gperf"
    {"mediumorchid2", 209, 95, 238},
    {""},
#line 598 "name2rgb.gperf"
    {"mediumorchid1", 224, 102, 255},
    {""}, {""}, {""},
#line 349 "name2rgb.gperf"
    {"lavenderblush4", 139, 131, 134},
    {""},
#line 348 "name2rgb.gperf"
    {"lavenderblush3", 205, 193, 197},
#line 270 "name2rgb.gperf"
    {"light coral", 240, 128, 128},
    {""}, {""}, {""},
#line 62 "name2rgb.gperf"
    {"scilab magenta4", 144, 0, 144},
#line 347 "name2rgb.gperf"
    {"lavenderblush2", 238, 224, 229},
#line 64 "name2rgb.gperf"
    {"scilab magenta3", 176, 0, 176},
#line 346 "name2rgb.gperf"
    {"lavenderblush1", 255, 240, 245},
    {""},
#line 619 "name2rgb.gperf"
    {"grey0", 0, 0, 0},
    {""}, {""},
#line 66 "name2rgb.gperf"
    {"scilab magenta2", 208, 0, 208},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""},
#line 699 "name2rgb.gperf"
    {"grey40", 102, 102, 102},
#line 679 "name2rgb.gperf"
    {"grey30", 77, 77, 77},
    {""}, {""},
#line 659 "name2rgb.gperf"
    {"grey20", 51, 51, 51},
#line 639 "name2rgb.gperf"
    {"grey10", 26, 26, 26},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""},
#line 618 "name2rgb.gperf"
    {"gray0", 0, 0, 0},
    {""},
#line 477 "name2rgb.gperf"
    {"yellow4", 139, 139, 0},
#line 295 "name2rgb.gperf"
    {"mediumorchid", 186, 85, 211},
#line 476 "name2rgb.gperf"
    {"yellow3", 205, 205, 0},
    {""}, {""}, {""}, {""}, {""},
#line 475 "name2rgb.gperf"
    {"yellow2", 238, 238, 0},
    {""},
#line 474 "name2rgb.gperf"
    {"yellow1", 255, 255, 0},
    {""},
#line 698 "name2rgb.gperf"
    {"gray40", 102, 102, 102},
#line 678 "name2rgb.gperf"
    {"gray30", 77, 77, 77},
    {""}, {""},
#line 658 "name2rgb.gperf"
    {"gray20", 51, 51, 51},
#line 638 "name2rgb.gperf"
    {"gray10", 26, 26, 26},
    {""}, {""}, {""}, {""}, {""},
#line 296 "name2rgb.gperf"
    {"dark orchid", 153, 50, 204},
    {""},
#line 137 "name2rgb.gperf"
    {"light slate grey", 119, 136, 153},
#line 826 "name2rgb.gperf"
    {"dark cyan", 0, 139, 139},
    {""},
#line 256 "name2rgb.gperf"
    {"sandybrown", 244, 164, 96},
    {""}, {""}, {""},
#line 573 "name2rgb.gperf"
    {"lightpink4", 139, 95, 101},
#line 572 "name2rgb.gperf"
    {"lightpink3", 205, 140, 149},
    {""}, {""},
#line 571 "name2rgb.gperf"
    {"lightpink2", 238, 162, 173},
#line 570 "name2rgb.gperf"
    {"lightpink1", 255, 174, 185},
    {""}, {""}, {""}, {""}, {""},
#line 219 "name2rgb.gperf"
    {"greenyellow", 173, 255, 47},
    {""}, {""}, {""}, {""}, {""},
#line 223 "name2rgb.gperf"
    {"yellowgreen", 154, 205, 50},
    {""}, {""}, {""}, {""}, {""},
#line 135 "name2rgb.gperf"
    {"light slate gray", 119, 136, 153},
    {""},
#line 605 "name2rgb.gperf"
    {"darkorchid4", 104, 34, 139},
#line 604 "name2rgb.gperf"
    {"darkorchid3", 154, 50, 205},
    {""}, {""},
#line 603 "name2rgb.gperf"
    {"darkorchid2", 178, 58, 238},
#line 602 "name2rgb.gperf"
    {"darkorchid1", 191, 62, 255},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 75 "name2rgb.gperf"
    {"scilabpink4", 255, 128, 128},
#line 77 "name2rgb.gperf"
    {"scilabpink3", 255, 160, 160},
    {""}, {""},
#line 79 "name2rgb.gperf"
    {"scilabpink2", 255, 192, 192},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 183 "name2rgb.gperf"
    {"dark turquoise", 0, 206, 209},
    {""}, {""}, {""}, {""},
#line 51 "name2rgb.gperf"
    {"scilabcyan4", 0, 144, 144},
#line 53 "name2rgb.gperf"
    {"scilabcyan3", 0, 176, 176},
    {""}, {""},
#line 55 "name2rgb.gperf"
    {"scilabcyan2", 0, 208, 208},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""},
#line 158 "name2rgb.gperf"
    {"light slate blue", 132, 112, 255},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 277 "name2rgb.gperf"
    {"hotpink", 255, 105, 180},
    {""}, {""}, {""},
#line 194 "name2rgb.gperf"
    {"mediumaquamarine", 102, 205, 170},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 121 "name2rgb.gperf"
    {"white", 255, 255, 255},
    {""}, {""}, {""}, {""},
#line 297 "name2rgb.gperf"
    {"darkorchid", 153, 50, 204},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 118 "name2rgb.gperf"
    {"lavenderblush", 255, 240, 245},
    {""}, {""},
#line 505 "name2rgb.gperf"
    {"burlywood4", 139, 115, 85},
#line 504 "name2rgb.gperf"
    {"burlywood3", 205, 170, 125},
    {""}, {""},
#line 503 "name2rgb.gperf"
    {"burlywood2", 238, 197, 145},
#line 502 "name2rgb.gperf"
    {"burlywood1", 255, 211, 155},
#line 189 "name2rgb.gperf"
    {"light cyan", 224, 255, 255},
    {""}, {""}, {""}, {""},
#line 175 "name2rgb.gperf"
    {"light steel blue", 176, 196, 222},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 799 "name2rgb.gperf"
    {"grey90", 229, 229, 229},
#line 521 "name2rgb.gperf"
    {"firebrick4", 139, 26, 26},
#line 520 "name2rgb.gperf"
    {"firebrick3", 205, 38, 38},
    {""},
#line 212 "name2rgb.gperf"
    {"lawn green", 124, 252, 0},
#line 519 "name2rgb.gperf"
    {"firebrick2", 238, 44, 44},
#line 518 "name2rgb.gperf"
    {"firebrick1", 255, 48, 48},
#line 171 "name2rgb.gperf"
    {"light sky blue", 135, 206, 250},
    {""}, {""},
#line 775 "name2rgb.gperf"
    {"grey78", 199, 199, 199},
    {""},
#line 337 "name2rgb.gperf"
    {"cornsilk4", 139, 136, 120},
    {""},
#line 336 "name2rgb.gperf"
    {"cornsilk3", 205, 200, 177},
#line 345 "name2rgb.gperf"
    {"honeydew4", 131, 139, 131},
    {""},
#line 344 "name2rgb.gperf"
    {"honeydew3", 193, 205, 193},
    {""}, {""},
#line 335 "name2rgb.gperf"
    {"cornsilk2", 238, 232, 205},
    {""},
#line 334 "name2rgb.gperf"
    {"cornsilk1", 255, 248, 220},
#line 343 "name2rgb.gperf"
    {"honeydew2", 224, 238, 224},
#line 186 "name2rgb.gperf"
    {"mediumturquoise", 72, 209, 204},
#line 342 "name2rgb.gperf"
    {"honeydew1", 240, 255, 240},
    {""}, {""}, {""},
#line 191 "name2rgb.gperf"
    {"cadet blue", 95, 158, 160},
#line 798 "name2rgb.gperf"
    {"gray90", 229, 229, 229},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 774 "name2rgb.gperf"
    {"gray78", 199, 199, 199},
#line 244 "name2rgb.gperf"
    {"rosy brown", 188, 143, 143},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 333 "name2rgb.gperf"
    {"lemonchiffon4", 139, 137, 112},
    {""},
#line 332 "name2rgb.gperf"
    {"lemonchiffon3", 205, 201, 165},
#line 108 "name2rgb.gperf"
    {"lemonchiffon", 255, 250, 205},
    {""}, {""},
#line 252 "name2rgb.gperf"
    {"burlywood", 222, 184, 135},
    {""},
#line 331 "name2rgb.gperf"
    {"lemonchiffon2", 238, 233, 191},
    {""},
#line 330 "name2rgb.gperf"
    {"lemonchiffon1", 255, 250, 205},
    {""}, {""}, {""}, {""}, {""},
#line 755 "name2rgb.gperf"
    {"grey68", 173, 173, 173},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 156 "name2rgb.gperf"
    {"medium slate blue", 123, 104, 238},
    {""},
#line 633 "name2rgb.gperf"
    {"grey7", 18, 18, 18},
    {""}, {""}, {""}, {""}, {""},
#line 236 "name2rgb.gperf"
    {"lightyellow", 255, 255, 224},
    {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 713 "name2rgb.gperf"
    {"grey47", 120, 120, 120},
#line 693 "name2rgb.gperf"
    {"grey37", 94, 94, 94},
    {""}, {""},
#line 673 "name2rgb.gperf"
    {"grey27", 69, 69, 69},
#line 653 "name2rgb.gperf"
    {"grey17", 43, 43, 43},
#line 100 "name2rgb.gperf"
    {"peach puff", 255, 218, 185},
#line 754 "name2rgb.gperf"
    {"gray68", 173, 173, 173},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 632 "name2rgb.gperf"
    {"gray7", 18, 18, 18},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 279 "name2rgb.gperf"
    {"deeppink", 255, 20, 147},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 712 "name2rgb.gperf"
    {"gray47", 120, 120, 120},
#line 692 "name2rgb.gperf"
    {"gray37", 94, 94, 94},
    {""}, {""},
#line 672 "name2rgb.gperf"
    {"gray27", 69, 69, 69},
#line 652 "name2rgb.gperf"
    {"gray17", 43, 43, 43},
    {""}, {""}, {""}, {""},
#line 288 "name2rgb.gperf"
    {"violet red", 208, 32, 144},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 303 "name2rgb.gperf"
    {"medium purple", 147, 112, 219},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 94 "name2rgb.gperf"
    {"antiquewhite", 250, 235, 215},
    {""}, {""}, {""},
#line 145 "name2rgb.gperf"
    {"midnight blue", 25, 25, 112},
    {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 631 "name2rgb.gperf"
    {"grey6", 15, 15, 15},
    {""},
#line 317 "name2rgb.gperf"
    {"antiquewhite4", 139, 131, 120},
    {""},
#line 316 "name2rgb.gperf"
    {"antiquewhite3", 205, 192, 176},
    {""}, {""}, {""}, {""}, {""},
#line 315 "name2rgb.gperf"
    {"antiquewhite2", 238, 223, 204},
    {""},
#line 314 "name2rgb.gperf"
    {"antiquewhite1", 255, 239, 219},
    {""},
#line 711 "name2rgb.gperf"
    {"grey46", 117, 117, 117},
#line 691 "name2rgb.gperf"
    {"grey36", 92, 92, 92},
    {""}, {""},
#line 671 "name2rgb.gperf"
    {"grey26", 66, 66, 66},
#line 651 "name2rgb.gperf"
    {"grey16", 41, 41, 41},
#line 294 "name2rgb.gperf"
    {"medium orchid", 186, 85, 211},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 630 "name2rgb.gperf"
    {"gray6", 15, 15, 15},
    {""},
#line 97 "name2rgb.gperf"
    {"blanched almond", 255, 235, 205},
    {""}, {""}, {""}, {""}, {""},
#line 148 "name2rgb.gperf"
    {"navy blue", 0, 0, 128},
#line 180 "name2rgb.gperf"
    {"powderblue", 176, 224, 230},
    {""},
#line 735 "name2rgb.gperf"
    {"grey58", 148, 148, 148},
    {""}, {""},
#line 710 "name2rgb.gperf"
    {"gray46", 117, 117, 117},
#line 690 "name2rgb.gperf"
    {"gray36", 92, 92, 92},
    {""}, {""},
#line 670 "name2rgb.gperf"
    {"gray26", 66, 66, 66},
#line 650 "name2rgb.gperf"
    {"gray16", 41, 41, 41},
    {""}, {""}, {""},
#line 461 "name2rgb.gperf"
    {"darkolivegreen4", 110, 139, 61},
    {""},
#line 460 "name2rgb.gperf"
    {"darkolivegreen3", 162, 205, 90},
#line 199 "name2rgb.gperf"
    {"darkolivegreen", 85, 107, 47},
    {""}, {""}, {""}, {""},
#line 459 "name2rgb.gperf"
    {"darkolivegreen2", 188, 238, 104},
    {""},
#line 458 "name2rgb.gperf"
    {"darkolivegreen1", 202, 255, 112},
    {""}, {""}, {""},
#line 779 "name2rgb.gperf"
    {"grey80", 204, 204, 204},
    {""}, {""}, {""},
#line 734 "name2rgb.gperf"
    {"gray58", 148, 148, 148},
    {""}, {""},
#line 167 "name2rgb.gperf"
    {"deep sky blue", 0, 191, 255},
    {""}, {""}, {""}, {""}, {""},
#line 282 "name2rgb.gperf"
    {"lightpink", 255, 182, 193},
#line 813 "name2rgb.gperf"
    {"grey97", 247, 247, 247},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 778 "name2rgb.gperf"
    {"gray80", 204, 204, 204},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""},
#line 193 "name2rgb.gperf"
    {"medium aquamarine", 102, 205, 170},
    {""}, {""},
#line 812 "name2rgb.gperf"
    {"gray97", 247, 247, 247},
    {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 81 "name2rgb.gperf"
    {"scilabpink", 255, 224, 224},
    {""},
#line 299 "name2rgb.gperf"
    {"darkviolet", 148, 0, 211},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 88 "name2rgb.gperf"
    {"floral white", 255, 250, 240},
    {""},
#line 181 "name2rgb.gperf"
    {"pale turquoise", 175, 238, 238},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""},
#line 281 "name2rgb.gperf"
    {"light pink", 255, 182, 193},
#line 216 "name2rgb.gperf"
    {"medium spring green", 0, 250, 154},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""},
#line 234 "name2rgb.gperf"
    {"lightgoldenrodyellow", 250, 250, 210},
    {""}, {""}, {""}, {""}, {""},
#line 811 "name2rgb.gperf"
    {"grey96", 245, 245, 245},
    {""}, {""},
#line 276 "name2rgb.gperf"
    {"hot pink", 255, 105, 180},
    {""}, {""}, {""}, {""},
#line 74 "name2rgb.gperf"
    {"scilab pink4", 255, 128, 128},
    {""},
#line 76 "name2rgb.gperf"
    {"scilab pink3", 255, 160, 160},
#line 50 "name2rgb.gperf"
    {"scilab cyan4", 0, 144, 144},
    {""},
#line 52 "name2rgb.gperf"
    {"scilab cyan3", 0, 176, 176},
    {""},
#line 105 "name2rgb.gperf"
    {"cornsilk", 255, 248, 220},
#line 78 "name2rgb.gperf"
    {"scilab pink2", 255, 192, 192},
#line 259 "name2rgb.gperf"
    {"firebrick", 178, 34, 34},
    {""},
#line 54 "name2rgb.gperf"
    {"scilab cyan2", 0, 208, 208},
#line 222 "name2rgb.gperf"
    {"yellow green", 154, 205, 50},
    {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 228 "name2rgb.gperf"
    {"dark khaki", 189, 183, 107},
    {""},
#line 810 "name2rgb.gperf"
    {"gray96", 245, 245, 245},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""},
#line 89 "name2rgb.gperf"
    {"floralwhite", 255, 250, 240},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 179 "name2rgb.gperf"
    {"powder blue", 176, 224, 230},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 233 "name2rgb.gperf"
    {"light goldenrod yellow", 250, 250, 210},
    {""},
#line 629 "name2rgb.gperf"
    {"grey5", 13, 13, 13},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 229 "name2rgb.gperf"
    {"darkkhaki", 189, 183, 107},
    {""}, {""}, {""}, {""}, {""},
#line 793 "name2rgb.gperf"
    {"grey87", 222, 222, 222},
#line 709 "name2rgb.gperf"
    {"grey45", 115, 115, 115},
#line 689 "name2rgb.gperf"
    {"grey35", 89, 89, 89},
    {""}, {""},
#line 669 "name2rgb.gperf"
    {"grey25", 64, 64, 64},
#line 649 "name2rgb.gperf"
    {"grey15", 38, 38, 38},
    {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 301 "name2rgb.gperf"
    {"blueviolet", 138, 43, 226},
    {""}, {""},
#line 628 "name2rgb.gperf"
    {"gray5", 13, 13, 13},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""},
#line 792 "name2rgb.gperf"
    {"gray87", 222, 222, 222},
#line 708 "name2rgb.gperf"
    {"gray45", 115, 115, 115},
#line 688 "name2rgb.gperf"
    {"gray35", 89, 89, 89},
    {""}, {""},
#line 668 "name2rgb.gperf"
    {"gray25", 64, 64, 64},
#line 648 "name2rgb.gperf"
    {"gray15", 38, 38, 38},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 84 "name2rgb.gperf"
    {"ghostwhite", 248, 248, 255},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 107 "name2rgb.gperf"
    {"lemon chiffon", 255, 250, 205},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 278 "name2rgb.gperf"
    {"deep pink", 255, 20, 147},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 93 "name2rgb.gperf"
    {"antique white", 250, 235, 215},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""},
#line 791 "name2rgb.gperf"
    {"grey86", 219, 219, 219},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 86 "name2rgb.gperf"
    {"whitesmoke", 245, 245, 245},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 819 "name2rgb.gperf"
    {"grey100", 255, 255, 255},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""},
#line 790 "name2rgb.gperf"
    {"gray86", 219, 219, 219},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 818 "name2rgb.gperf"
    {"gray100", 255, 255, 255},
    {""}, {""}, {""}, {""}, {""},
#line 577 "name2rgb.gperf"
    {"palevioletred4", 139, 71, 93},
    {""},
#line 576 "name2rgb.gperf"
    {"palevioletred3", 205, 104, 137},
    {""}, {""}, {""}, {""}, {""},
#line 575 "name2rgb.gperf"
    {"palevioletred2", 238, 121, 159},
    {""},
#line 574 "name2rgb.gperf"
    {"palevioletred1", 255, 130, 171},
    {""}, {""}, {""},
#line 809 "name2rgb.gperf"
    {"grey95", 242, 242, 242},
    {""}, {""}, {""},
#line 151 "name2rgb.gperf"
    {"cornflowerblue", 100, 149, 237},
    {""}, {""}, {""}, {""},
#line 117 "name2rgb.gperf"
    {"lavender blush", 255, 240, 245},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 198 "name2rgb.gperf"
    {"dark olive green", 85, 107, 47},
    {""}, {""}, {""},
#line 85 "name2rgb.gperf"
    {"white smoke", 245, 245, 245},
    {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 808 "name2rgb.gperf"
    {"gray95", 242, 242, 242},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""},
#line 284 "name2rgb.gperf"
    {"palevioletred", 219, 112, 147},
    {""}, {""}, {""},
#line 150 "name2rgb.gperf"
    {"cornflower blue", 100, 149, 237},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""},
#line 759 "name2rgb.gperf"
    {"grey70", 179, 179, 179},
    {""}, {""},
#line 80 "name2rgb.gperf"
    {"scilab pink", 255, 224, 224},
    {""}, {""}, {""}, {""},
#line 185 "name2rgb.gperf"
    {"medium turquoise", 72, 209, 204},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""},
#line 298 "name2rgb.gperf"
    {"dark violet", 148, 0, 211},
    {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 758 "name2rgb.gperf"
    {"gray70", 179, 179, 179},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""},
#line 739 "name2rgb.gperf"
    {"grey60", 153, 153, 153},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""},
#line 738 "name2rgb.gperf"
    {"gray60", 153, 153, 153},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""},
#line 83 "name2rgb.gperf"
    {"ghost white", 248, 248, 255},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 789 "name2rgb.gperf"
    {"grey85", 217, 217, 217},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 719 "name2rgb.gperf"
    {"grey50", 127, 127, 127},
    {""}, {""}, {""},
#line 788 "name2rgb.gperf"
    {"gray85", 217, 217, 217},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 718 "name2rgb.gperf"
    {"gray50", 127, 127, 127},
#line 287 "name2rgb.gperf"
    {"mediumvioletred", 199, 21, 133},
#line 300 "name2rgb.gperf"
    {"blue violet", 138, 43, 226},
    {""}, {""},
#line 237 "name2rgb.gperf"
    {"yellow", 255, 255, 0},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""},
#line 773 "name2rgb.gperf"
    {"grey77", 196, 196, 196},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""},
#line 772 "name2rgb.gperf"
    {"gray77", 196, 196, 196},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""},
#line 753 "name2rgb.gperf"
    {"grey67", 171, 171, 171},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""},
#line 752 "name2rgb.gperf"
    {"gray67", 171, 171, 171},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""},
#line 771 "name2rgb.gperf"
    {"grey76", 194, 194, 194},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""},
#line 770 "name2rgb.gperf"
    {"gray76", 194, 194, 194},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 110 "name2rgb.gperf"
    {"honeydew", 240, 255, 240},
    {""}, {""}, {""}, {""},
#line 751 "name2rgb.gperf"
    {"grey66", 168, 168, 168},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""},
#line 750 "name2rgb.gperf"
    {"gray66", 168, 168, 168},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""},
#line 733 "name2rgb.gperf"
    {"grey57", 145, 145, 145},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""},
#line 732 "name2rgb.gperf"
    {"gray57", 145, 145, 145},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""},
#line 102 "name2rgb.gperf"
    {"navajo white", 255, 222, 173},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 731 "name2rgb.gperf"
    {"grey56", 143, 143, 143},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""},
#line 730 "name2rgb.gperf"
    {"gray56", 143, 143, 143},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 103 "name2rgb.gperf"
    {"navajowhite", 255, 222, 173},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""},
#line 329 "name2rgb.gperf"
    {"navajowhite4", 139, 121, 94},
    {""},
#line 328 "name2rgb.gperf"
    {"navajowhite3", 205, 179, 139},
    {""}, {""}, {""}, {""}, {""},
#line 327 "name2rgb.gperf"
    {"navajowhite2", 238, 207, 161},
    {""},
#line 326 "name2rgb.gperf"
    {"navajowhite1", 255, 222, 173},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""},
#line 769 "name2rgb.gperf"
    {"grey75", 191, 191, 191},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""},
#line 768 "name2rgb.gperf"
    {"gray75", 191, 191, 191},
#line 218 "name2rgb.gperf"
    {"green yellow", 173, 255, 47},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""},
#line 749 "name2rgb.gperf"
    {"grey65", 166, 166, 166},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""},
#line 748 "name2rgb.gperf"
    {"gray65", 166, 166, 166},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 95 "name2rgb.gperf"
    {"papaya whip", 255, 239, 213},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""},
#line 729 "name2rgb.gperf"
    {"grey55", 140, 140, 140},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""},
#line 235 "name2rgb.gperf"
    {"light yellow", 255, 255, 224},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 728 "name2rgb.gperf"
    {"gray55", 140, 140, 140},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 283 "name2rgb.gperf"
    {"pale violet red", 219, 112, 147},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""},
#line 96 "name2rgb.gperf"
    {"papayawhip", 255, 239, 213},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
    {""}, {""}, {""}, {""}, {""}, {""},
#line 286 "name2rgb.gperf"
    {"medium violet red", 199, 21, 133}
  };

#ifdef __GNUC__
__inline
#if defined __GNUC_STDC_INLINE__ || defined __GNUC_GNU_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
const struct color *
lookup_color (str, len)
     register const char *str;
     register unsigned int len;
{
  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = colorlist[key].name;

          if ((((unsigned char)*str ^ (unsigned char)*s) & ~32) == 0 && !gperf_case_strcmp (str, s))
            return &colorlist[key];
        }
    }
  return 0;
}
#line 834 "name2rgb.gperf"

void name2rgb(char* name, double* rgb)
{
    const struct color* c = lookup_color(name, balisc_strlen(name));

    if (c)
    {
        rgb[0] = (double)(c->red);
        rgb[1] = (double)(c->green);
        rgb[2] = (double)(c->blue);
    }
    else
    {
        rgb[0] = -1.0;
        rgb[1] = -1.0;
        rgb[2] = -1.0;
    }
}
