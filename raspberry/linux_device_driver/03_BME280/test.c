#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int dev = open("/dev/bme280", O_RDONLY);
    if (dev == -1)
    {
        printf("Opening was not possible!\n");
        return -1;
    }
    printf("Opening was successfull!\n");
    char buf[31];
    read(dev, buf, 31);
    printf("buf: %s", buf);
    close(dev);
    return 0;
}