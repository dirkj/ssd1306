#ifndef SSD1306_H
#define SSD1306_H

#include "mgos_features.h"

#include <stdbool.h>

#include "mgos_init.h"
#include "mgos_sys_config.h"
#include "mgos_i2c.h"

#include "fonts.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */


  typedef enum
  {
    SSD1306_COLOR_TRANSPARENT = -1,     //< Transparent (not drawing)
    SSD1306_COLOR_BLACK = 0,    //< Black (pixel off)
    SSD1306_COLOR_WHITE = 1,    //< White (or blue, yellow, pixel on)
    SSD1306_COLOR_INVERT = 2,   //< Invert pixel (XOR)
  } mgos_ssd1306_color_t;

  typedef struct mgos_ssd1306
  {
    uint8_t address;              // I2C address
    uint8_t width;                // panel width
    uint8_t height;               // panel height
    uint8_t *buffer;              // display buffer
    uint8_t refresh_top;          // 'Dirty' window corners
    uint8_t refresh_left;
    uint8_t refresh_right;
    uint8_t refresh_bottom;
    const font_info_t *font;      // current font
    struct mgos_i2c *i2c;         // i2c connection
  } mgos_ssd1306;

  /**
   * @brief Standard Mongoose-OS init hook.
   *
   * @return True if module was enabled and successfully initialized.
   */
  bool mgos_ssd1306_init(void);

  /**
   * @brief Access the SSD1306 driver handle that is set up via sysconfig.
   *
   * @return Preconfigured SSD1306 driver handle.
   */
  struct mgos_ssd1306 *mgos_ssd1306_get_global(void);

  /**
   * @brief Initialize the SSD1306 driver with the given params. Typically clients
   * don't need to do that manually; mgos has a global SSD1306 instance that is created
   * with the params given in system config; use `mgos_ssd1306_get_global() to get the
   * global instance
   *
   * @param cfg SSD1306 configuration.
   *
   * @return SSD1306 driver handle, or NULL if setup failed.
   */
  struct mgos_ssd1306 *mgos_ssd1306_create(const struct mgos_config_ssd1306 *cfg);

  /**
   * @brief Power down the display, close I2C connection, and free memory.
   *
   * @param oled SSD1306 driver handle.
   */
  void mgos_ssd1306_close(struct mgos_ssd1306 *oled);

  /**
   * @brief Get screen width.
   *
   * @param oled SSD1306 driver handle
   *
   * @return Screen width, in pixels.
   */
  uint8_t mgos_ssd1306_get_width(struct mgos_ssd1306 *oled);

  /**
   * @brief Get screen height
   *
   * @param oled SSD1306 driver handle
   *
   * @return Screen height, in pixels.
   */
  uint8_t mgos_ssd1306_get_height(struct mgos_ssd1306 *oled);

  /**
   * @brief Clear the screen bitmap.
   *
   * @param oled SSD1306 driver handle.
   */
  void mgos_ssd1306_clear(struct mgos_ssd1306 *oled);

  /**
   * @brief Refresh the display, sending any dirty regions to the OLED controller for display.
   * Call this after you are finished calling any drawing primitives.
   *
   * @param oled SSD1306 driver handle.
   * @param force Redraw the entire bitmap, not just dirty regions.
   */
  void mgos_ssd1306_refresh(struct mgos_ssd1306 *oled, bool force);

  /**
   * @brief Draw a single pixel.
   *
   * @param oled SSD1306 driver handle.
   * @param x X coordinate.
   * @param y Y coordinate.
   * @param color Pixel color.
   */
  void mgos_ssd1306_draw_pixel(struct mgos_ssd1306 *oled, int8_t x, int8_t y,
                                mgos_ssd1306_color_t color);

  /**
   * @brief Draw a horizontal line.
   *
   * @param oled SSD1306 driver handle.
   * @param x X coordinate.
   * @param y Y coordinate.
   * @param w Line length.
   * @param color Line color.
   */
  void mgos_ssd1306_draw_hline(struct mgos_ssd1306 *oled, int8_t x, int8_t y, uint8_t w,
                                mgos_ssd1306_color_t color);

  /**
   * @brief Draw a vertical line.
   *
   * @param oled SSD1306 driver handle.
   * @param x X coordinate.
   * @param y Y coordinate.
   * @param h Line length.
   * @param color Line color.
   */
  void mgos_ssd1306_draw_vline(struct mgos_ssd1306 *oled, int8_t x, int8_t y, uint8_t h,
                                mgos_ssd1306_color_t color);


  /**
   * @brief Draw a line.
   *
   * @param oled SSD1306 driver handle.
   * @param x0 X coordinate.
   * @param y0 Y coordinate.
   * @param x1 X coordinate.
   * @param y1 Y coordinate.
   * @param color Line color.
   */
  void mgos_ssd1306_draw_line(struct mgos_ssd1306 *oled, int8_t x0, int8_t y0, int8_t x1,
                                int8_t y1, mgos_ssd1306_color_t color);

  /**
   * @brief Draw an unfilled rectangle.
   *
   * @param oled SSD1306 driver handle.
   * @param x X coordinate.
   * @param y Y coordinate.
   * @param w Rectangle width.
   * @param h Rectangle height.
   * @param color Line color.
   */
  void mgos_ssd1306_draw_rectangle(struct mgos_ssd1306 *oled, int8_t x, int8_t y, uint8_t w, uint8_t h,
                                    mgos_ssd1306_color_t color);

  /**
   * @brief Draw a filled rectangle.
   *
   * @param oled SSD1306 driver handle.
   * @param x X coordinate.
   * @param y Y coordinate.
   * @param w Rectangle width.
   * @param h Rectangle height.
   * @param color Line and fill color.
   */
  void mgos_ssd1306_fill_rectangle(struct mgos_ssd1306 *oled, int8_t x, int8_t y, uint8_t w, uint8_t h,
                                    mgos_ssd1306_color_t color);

  /**
   * @brief Draw an unfilled circle.
   *
   * @param oled SSD1306 driver handle.
   * @param x0 Center X coordinate .
   * @param y0 Center Y coordinate.
   * @param r Radius.
   * @param color Line color.
   */
  void mgos_ssd1306_draw_circle(struct mgos_ssd1306 *oled, int8_t x0, int8_t y0, uint8_t r, mgos_ssd1306_color_t color);

  /**
   * @brief Draw a filled circle.
   *
   * @param oled SSD1306 driver handle.
   * @param x0 Center X coordinate.
   * @param y0 Center Y coordinate.
   * @param r Radius.
   * @param color Line and fill color.
   */
  void mgos_ssd1306_fill_circle(struct mgos_ssd1306 *oled, int8_t x0, int8_t y0, uint8_t r, mgos_ssd1306_color_t color);

  /**
   * @brief Select active font ID.
   *
   * @param oled SSD1306 driver handle.
   * @param font Font index; see `fonts.h`.
   */
  void mgos_ssd1306_select_font(struct mgos_ssd1306 *oled, uint8_t font);

  /**
   * @brief Draw a single character using the active font and selected colors.
   *
   * @param oled SSD1306 driver handle.
   * @param x X coordinate.
   * @param y Y coordinate.
   * @param c Character to draw.
   * @param foreground Foreground color.
   * @param background Background color.
   *
   * @return Character width in pixels
   */
  uint8_t mgos_ssd1306_draw_char(struct mgos_ssd1306 *oled, uint8_t x, uint8_t y, unsigned char c,
                                  mgos_ssd1306_color_t foreground, mgos_ssd1306_color_t background);

  /**
   * @brief Draw a string using the active font and selected colors.
   *
   * @param oled SSD1306 driver handle.
   * @param x X coordinate.
   * @param y Y coordinate.
   * @param str String to draw.
   * @param foreground Foreground color.
   * @param background Background color.
   *
   * @return String witdth in pixels.
   */
  uint8_t mgos_ssd1306_draw_string_color(struct mgos_ssd1306 *oled, uint8_t x, uint8_t y, const char *str,
                                          mgos_ssd1306_color_t foreground, mgos_ssd1306_color_t background);

  /**
   * @brief Draw a string using the active font and default colors (white on transparent)
   *
   * @param oled SSD1306 driver handle.
   * @param x X coordinate.
   * @param y Y coordinate.
   * @param str String to draw.
   *
   * @return String width in pixels.
   */
  uint8_t mgos_ssd1306_draw_string(struct mgos_ssd1306 *oled, uint8_t x, uint8_t y, const char *str);

  /**
   * @brief Draw a string right aligned to the given position, using the active font and default colors (white on transparent)
   *
   * @param oled SSD1306 driver handle.
   * @param x X coordinate, if negative, then it is the distance from right side of the display.
   * @param y Y coordinate, if negative, then it is the distance from the bottom of the display.
   * @param str String to draw.
   *
   * @return String width in pixels.
   */
  uint8_t mgos_ssd1306_draw_string_right_aligned(struct mgos_ssd1306 * oled, int x, int y, const char *str);

  /**
   * @brief Measure on-screen width of string if drawn using active font.
   *
   * @param oled SSD1306 driver handle.
   * @param str String to measure.
   *
   * @return String width in pixels.
   */
  uint8_t mgos_ssd1306_measure_string(struct mgos_ssd1306 *oled, const char *str);

  /**
   * @brief Get the height of the active font.
   *
   * @param oled SSD1306 driver handle.
   *
   * @return Font height in pixels.
   */
  uint8_t mgos_ssd1306_get_font_height(struct mgos_ssd1306 *oled);

  /**
   * @brief Get the inter-character font spacing.
   *
   * @param oled SSD1306 driver handle.
   *
   * @return Font inter-character spacing in pixels.
   */
  uint8_t mgos_ssd1306_get_font_c(struct mgos_ssd1306 *oled);

  /**
   * @brief Turns display off (entirely dark)
   *
   * @param oled SSD1306 driver handle.
   */
  void mgos_ssd1306_display_off(struct mgos_ssd1306 *oled);

  /**
   * @brief Turns display on
   *
   * @param oled SSD1306 driver handle.
   */
  void mgos_ssd1306_display_on(struct mgos_ssd1306 *oled);

  /**
   * @brief Invert or restore the display. Inverting the display flips the bitmask -
   * 1 is black (off) and 0 is white (on).
   *
   * @param oled SSD1306 driver handle.
   * @param invert Enable inversion.
   */
  void mgos_ssd1306_invert_display(struct mgos_ssd1306 *oled, bool invert);

  /**
   * @brief Flip the display render order. May not do exactly what you expect, depending on
   * the display's segment remap configuration.
   *
   * @param oled SSD1306 driver handle.
   * @param horizontal Enable horizontal flipping.
   * @param vertical Enable vertical flipping
   */
  void mgos_ssd1306_flip_display(struct mgos_ssd1306 *oled, bool horizontal, bool vertical);

  /**
   * @brief Copy pre-rendered bytes directly into the bitmap.
   *
   * @param oled SSD1306 driver handle.
   * @param data Array containing bytes to copy into buffer.
   * @param length Length to copy (unchecked) from source buffer.
   */
  void mgos_ssd1306_update_buffer(struct mgos_ssd1306 *oled, uint8_t * data, uint16_t length);

  /**
   * @brief Draw RAM-resident BitMap Files (*.bpm), exported from GIMP,
   * Usage: Export from GIMP to *.xbm, rename *.xbm to *.c and open in editor.
   * C Array can be directly used with this function.
   *
   * @param oled SSD1306 driver handle.
   * @param x X position of upper left corner
   * @paran y Y position of upper left corner
   * @param bitmap Array with bitmap data
   * @param w Width of image
   * @param h Height of image
   * @param color For pixels to be drawn (bit value 1)
   * @param bg For pixels not to be drawn (bit value 0)
   */
  void mgos_ssd1306_drawBitmap(struct mgos_ssd1306 *oled, int16_t x, int16_t y,
  const uint8_t bitmap[], int16_t w, int16_t h, mgos_ssd1306_color_t color, mgos_ssd1306_color_t bg);

  /**
   * @brief Draw RAM-resident XBitMap Files (*.xbm), exported from GIMP,
   * Usage: Export from GIMP to *.xbm, rename *.xbm to *.c and open in editor.
   * C Array can be directly used with this function.
   *
   * @param oled SSD1306 driver handle.
   * @param x X position of upper left corner
   * @paran y Y position of upper left corner
   * @param bitmap Array with bitmap data
   * @param w Width of image
   * @param h Height of image
   * @param color For pixels to be drawn (bit value 1)
   * @param bg For pixels not to be drawn (bit value 0)
   */
  void mgos_ssd1306_drawXBitmap(struct mgos_ssd1306 *oled, int16_t x, int16_t y,
  const uint8_t bitmap[], int16_t w, int16_t h, mgos_ssd1306_color_t color, mgos_ssd1306_color_t bg);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* SSD1306_H */
