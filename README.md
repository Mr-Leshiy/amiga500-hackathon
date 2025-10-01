Compile client

```shell
vc +kick13 src/client.c src/parg.c src/lib.c src/hashing/sha256.c src/encoding.c -o amiga_build/client 
```

Compile server
```shell
vc +kick13 src/server.c src/parg.c src/lib.c src/hashing/sha256.c src/encoding.c src/serial13.c -o amiga_build/server -lamiga
```


```
    struct SerialHandle *sh = serial_open(9600);
    if (!sh) {
        printf("Could not open serial.device\n");
        return 1;
    }

    serial_write(sh, "HELLO FROM AMIGA\r");

    char* msg = serial_read(sh, 16);
    if (msg) {
        printf("Received: %s\n", msg);
    } else {
        printf("No data.\n");
    }

    serial_close(sh);
```