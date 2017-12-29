#include <sys/types.h>
#include <sys/stat.h>  // mkfifo, mode_t 
#include <errno.h>     // errno
#include <stdlib.h>    // EXIT_SUCESS
#include <fcntl.h>     // O_RDONLY

#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"
