#ifndef SERIAL13_H
#define SERIAL13_H

#include <exec/types.h>
#include <exec/ports.h>
#include <devices/serial.h>

struct SerialHandle {
    struct MsgPort   *port;
    struct IOExtSer  *io;
};

struct SerialHandle *serial_open(ULONG baud);

void serial_close(struct SerialHandle *sh);

LONG serial_write(struct SerialHandle *sh, const char *msg);

char *serial_read(struct SerialHandle *sh, LONG len);

#endif
