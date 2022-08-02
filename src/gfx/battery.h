#ifndef battery_include_file
#define battery_include_file

#ifdef __cplusplus
extern "C" {
#endif

#define battery_width 22
#define battery_height 9
#define battery_size 200
#define battery ((gfx_sprite_t*)battery_data)
extern unsigned char battery_data[200];

#ifdef __cplusplus
}
#endif

#endif
