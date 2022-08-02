#ifndef LAUNCHPAD_H
#define LAUNCHPAD_H

#ifdef _cplusplus
extern "C"{
#endif

void launchpad_gui(void);
void launchpad_prog_basic(void);
void launchpad_prog_c(void);
int launch_callbacks(void *data, int retval);

#ifdef _cplusplus
}
#endif
#endif