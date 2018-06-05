/*
 * oled_fonts.c
 *
 */
#include "fonts.h"

extern const font_info_t glcd_5x7_font_info;
extern const font_info_t tahoma_8pt_font_info;
extern const font_info_t _fonts_bitocra_4x7_ascii_info;
extern const font_info_t _fonts_terminus_8x14_iso8859_1_info;
extern const font_info_t _fonts_terminus_bold_8x14_iso8859_1_info;
extern const font_info_t _fonts_terminus_bold_12x24_iso8859_1_info;

const font_info_t * fonts[NUM_FONTS] =
{
    &glcd_5x7_font_info,
    &tahoma_8pt_font_info,
    &_fonts_bitocra_4x7_ascii_info,
    &_fonts_terminus_8x14_iso8859_1_info,
    &_fonts_terminus_bold_8x14_iso8859_1_info,
    &_fonts_terminus_bold_12x24_iso8859_1_info
};
