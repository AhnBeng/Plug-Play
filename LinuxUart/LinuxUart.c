#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#define BAUDRATE B9600
#define MODEMDEVICE "/dev/ttyUSB0" // or "/dev/ttyUSB0" for USB to serial adapter
#define _POSIX_SOURCE 1

int main()
{
  int fd, c, res;
  struct termios oldtio, newtio;
  char buf[255];

  // Open the serial port for read/write access
  fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY);
  if (fd < 0) {
    perror(MODEMDEVICE);
    exit(1);
  }

  // Save current serial port settings
  tcgetattr(fd, &oldtio);

  // Configure new serial port settings
  memset(&newtio, 0, sizeof(newtio));
  newtio.c_cflag = BAUDRATE | CS8 | CLOCAL | CREAD;
  newtio.c_iflag = IGNPAR;
  newtio.c_oflag = 0;
  newtio.c_lflag = 0;
  newtio.c_cc[VTIME] = 0;
  newtio.c_cc[VMIN] = 1;
  tcflush(fd, TCIFLUSH);
  tcsetattr(fd, TCSANOW, &newtio);

  // Write to serial port
  strcpy(buf, "Hello Atmega32a!");
  res = write(fd, buf, strlen(buf));
  if (res < 0) {
    perror("write error");
  } else {
    printf("Sent %d bytes: %s\n", res, buf);
  }

  // Read from serial port
  res = read(fd, buf, sizeof(buf));
  if (res < 0) {
    perror("read error");
  } else {
    buf[res] = '\0';
    printf("Received %d bytes: %s\n", res, buf);
  }

  // Restore original serial port settings
  tcsetattr(fd, TCSANOW, &oldtio);

  // Close the serial port
  close(fd);

  return 0;
}


