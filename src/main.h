#ifndef MAIN_H
#define MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

void startup(void);
void setdesktop(void);
void cursordetect();
void dock_draw(void);
void decode_Enter(unsigned int returned);
void cursor(unsigned int x, unsigned int y);
int second_main();
int all_callbacks(void *data, int retval);
int cas_callbacks(void *data, int retval);
void settings_gui(void);
unsigned int get_current_settings(char sector, char type);
unsigned int settings_general(unsigned int color, unsigned int type);
void monterey_appvar(void);
#ifdef __cplusplus
}
#endif
#endif