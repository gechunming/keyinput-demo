#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>

#define INPUT_DEVICE "/dev/input/event3"

#define SLEEP_FILE_CONTROL "/sys/power/state"
void set_system_to_sleep()
{
	int fd; 
	fd = open(SLEEP_FILE_CONTROL, O_RDWR);
	if (fd < 0) {
		printf("open %s error\n", SLEEP_FILE_CONTROL);
		return ;
	}
	write(fd, "on\n", 3);
	close(fd);
	return ;
}
int main(int argc, char *argv[])
{
    struct input_event event;
    int i;
    int fd;
    int len;
    int count = 0;

	if (argc < 2) {
		printf("give a device name\n");
		return 0;
	}
    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        printf("open %s\n", INPUT_DEVICE);
        return -1;
    }

    for (i = 0; ; i++) {
        len = read(fd, (void *)&event, sizeof(event));
        if (len != sizeof(event)) {
            printf("error on read not len\n");
        }
        printf("%2d:type=0x%04x, code=0x%04x, value=0x%08x\n",
                count, event.type, event.code, event.value);
		if ((event.code == 0x74) && (event.value == 0)) {
			set_system_to_sleep();
		}
    }
    close(fd);

    return 0;
}
        


    


