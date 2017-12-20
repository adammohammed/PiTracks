/* Serial Interface between PI and Arduino
   This Library opens and configures port
   OpenArduinoSerial will return a file descriptor to device
   Reading and Writing can be done on that FD

   Make sure to close the FD when done
*/
#ifndef SERIAL_INTERFACE_H
#define SERIAL_INTERFACE_H

#include <stdio.h>
/* Opens and sets default Serial Interface parameters for Arduino */
// Use must try and close the device
#ifdef __cplusplus
extern "C" {
#endif
int OpenArduinoSerial(char const * const device);

/* Helper Functions */
int set_interface_attribs (int fd, int speed, int parity);
void set_blocking (int fd, int should_block);

void CloseArduinoSerial(int fd);
#ifdef __cplusplus
}
#endif

#endif /* SERIAL_INTERFACE_H */
