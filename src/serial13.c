#include "serial13.h"
#include <exec/memory.h>
#include <exec/io.h>
#include <proto/exec.h>
#include <proto/dos.h>
#include <string.h>
#include <stdio.h>

struct MsgPort *CreatePort(UBYTE *name, LONG pri);
VOID DeletePort(struct MsgPort *port);

static char readbuf[256];

struct SerialHandle *serial_open(ULONG baud) {
    struct SerialHandle *sh = AllocMem(sizeof(struct SerialHandle), MEMF_PUBLIC|MEMF_CLEAR);
    if (!sh) return NULL;

    sh->port = CreatePort(NULL, 0);
    if (!sh->port) {
        FreeMem(sh, sizeof(struct SerialHandle));
        return NULL;
    }

    sh->io = (struct IOExtSer *)AllocMem(sizeof(struct IOExtSer), MEMF_PUBLIC|MEMF_CLEAR);
    if (!sh->io) {
        DeletePort(sh->port);
        FreeMem(sh, sizeof(struct SerialHandle));
        return NULL;
    }

    sh->io->IOSer.io_Message.mn_ReplyPort = sh->port;
    sh->io->IOSer.io_Message.mn_Length    = sizeof(struct IOExtSer);

    if (OpenDevice("serial.device", 0, (struct IORequest *)sh->io, 0)) {
        FreeMem(sh->io, sizeof(struct IOExtSer));
        DeletePort(sh->port);
        FreeMem(sh, sizeof(struct SerialHandle));
        return NULL;
    }

    sh->io->io_Baud     = baud;
    sh->io->io_ReadLen  = 8;
    sh->io->io_WriteLen = 8;
    sh->io->io_StopBits = 1;
    sh->io->io_SerFlags = 0;

    sh->io->IOSer.io_Command = SDCMD_SETPARAMS;
    DoIO((struct IORequest *)sh->io);

    return sh;
}

void serial_close(struct SerialHandle *sh) {
    if (!sh) return;
    if (sh->io) {
        CloseDevice((struct IORequest *)sh->io);
        FreeMem(sh->io, sizeof(struct IOExtSer));
    }
    if (sh->port) DeletePort(sh->port);
    FreeMem(sh, sizeof(struct SerialHandle));
}

LONG serial_write(struct SerialHandle *sh, const char *msg) {
    if (!sh) return -1;
    sh->io->IOSer.io_Command = CMD_WRITE;
    sh->io->IOSer.io_Data    = (APTR)msg;
    sh->io->IOSer.io_Length  = strlen(msg);
    if (DoIO((struct IORequest *)sh->io) == 0)
        return sh->io->IOSer.io_Actual;
    return -1;
}

char *serial_read(struct SerialHandle *sh, LONG len) {
    if (!sh) return NULL;
    if (len > sizeof(readbuf)-1) len = sizeof(readbuf)-1;

    sh->io->IOSer.io_Command = CMD_READ;
    sh->io->IOSer.io_Data    = readbuf;
    sh->io->IOSer.io_Length  = len;

    if (DoIO((struct IORequest *)sh->io) == 0) {
        LONG n = sh->io->IOSer.io_Actual;
        readbuf[n] = '\0';
        return (n > 0) ? readbuf : NULL;
    }
    return NULL;
}