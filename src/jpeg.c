#include "jpeg.h"

/**
 * @name       jpegShow
 * @brief      jpeg Show jpeg显示
 * @param      
 *             @lcd_mp  Mapping space 映射空间
 *             @x  start x
 *             @y  start y 
 * @retval     none
 * @date       2026/04/19
 * @version    1.0
 * @note       
 */
void jpegShow(int *lcd_mp, int x, int y)
{
    //参数有效性分析,判断LCD内存映射的地址是否有效
	if(NULL == lcd_mp)
	{
		errorPrint("lcd mp is invaild\n");
		return;
	}

    char gif_path[128] = {0};

    for (int i = 1; i < jpegcount; i++)
    {
        sprintf(gif_path,"./gif/7_%d.jpeg",i);
        jpeg_to_lcd(lcd_mp, gif_path, x, y);
        usleep(1000 * 20);
    }
    
}


/**
 * @name       jpeg_to_lcd
 * @brief      jpeg show lcd LCD显示图片
 * @param      
 *             @lcd_mp  Mapping space 映射空间
 *             @jpegpath jieg path 
 *             @start_x  start x
 *             @start_y  start y 
 * @retval     none
 * @date       2026/04/19
 * @version    1.0
 * @note       
 */
bool jpeg_to_lcd(int *lcd_mp, const char* jpegpath, int start_x, int start_y)
{
  struct jpeg_decompress_struct cinfo;

  struct jpeg_error_mgr jerr;
  /* More stuff */
  FILE * infile;		/* source file */
  unsigned char *buffer;		/* Output row buffer */
  int row_stride;		/* physical row width in output buffer */

  if ((infile = fopen(jpegpath, "rb")) == NULL) {
    return false;
  }

  cinfo.err = jpeg_std_error(&jerr);

  jpeg_create_decompress(&cinfo);

  jpeg_stdio_src(&cinfo, infile);


  (void) jpeg_read_header(&cinfo, TRUE);

  (void) jpeg_start_decompress(&cinfo);

  row_stride = cinfo.output_width * cinfo.output_components;
  buffer = calloc(1, row_stride);

  int data = 0;
  while (cinfo.output_scanline < cinfo.output_height) 
  {
    (void) jpeg_read_scanlines(&cinfo, &buffer, 1);  //读数据
    int row = cinfo.output_scanline - 1;   // 当前行索引（0 起始）
    for (int i = 0; i < cinfo.output_width; i++)
    {
        data |= buffer[3*i] << 16;
        data |= buffer[3*i+1] << 8;
        data |= buffer[3*i+2];

        // 有问题
        // lcd_mp[800*start_y + start_x + 800*(cinfo.output_scanline-1) + i] = data;
        int x = start_x + i;
        int y = start_y + row;
        if (x >= 0 && x < 800 && y >= 0 && y < 480)
        {
            lcd_mp[y * 800 + x] = data;
        }
        
        data = 0;
    } 
  }

  (void) jpeg_finish_decompress(&cinfo);

  jpeg_destroy_decompress(&cinfo);

  fclose(infile);

  return true;
}