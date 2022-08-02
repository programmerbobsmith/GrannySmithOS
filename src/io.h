#ifndef IO_H
#define IO_H

#ifdef _cplusplus
extern "C"{
#endif

void print_Double(double value, unsigned int num_of_decimal_places);
int get_Integer(unsigned int x, unsigned int y);
double get_Double(unsigned int x, unsigned int y);
int get_Slider(unsigned int start_x, unsigned int start_y, unsigned int max_entries);
int get_LaunchSlider(unsigned int x, unsigned int y);
int get_ProgSlider(unsigned int start_x, unsigned int start_y, unsigned int max_entries);

#ifdef _cplusplus
}
#endif
#endif