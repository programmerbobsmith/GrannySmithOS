#ifndef ERROR_H
#define ERROR_H

#ifdef _cplusplus
extern "C"{
#endif

void error_banner(const char *header, const char *text, unsigned int x, unsigned int y);
void error_notification(unsigned int x, unsigned int y, unsigned int width, unsigned int height, unsigned int color);

#ifdef _cplusplus
}
#endif
#endif