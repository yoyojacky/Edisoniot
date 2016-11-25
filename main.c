#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include <mraa/gpio.h>

int sensor_state = 0;

void *take_photo_thread (void *args){
    for(;;){
        if(sensor_state >= 500 ){
            char str[25];
            sprintf(str,"%d.jpg",(int) time((time_t*)NULL));
            take_photo(str);
            sleep (1);
            char command[100];
            sprintf (command, "upload.sh %s", str);
            system (command);
        }
        sleep(1);
    }
}

int main(int argc, char** argv)
{
    mraa_gpio_context sensor_gpio = NULL;

    sensor_gpio = mraa_gpio_init(5);

    if (sensor_gpio == NULL) {
        fprintf(stdout, "Could not initilaize sensor_gpio\n");
        return 1;
    }

    mraa_gpio_dir(sensor_gpio, MRAA_GPIO_IN);

    pthread_t t;
    pthread_create(&t,NULL,take_photo_thread,NULL);

    for (;;) {
        if( sensor_state != mraa_gpio_read(sensor_gpio)) {
            sensor_state = !sensor_state;
            printf("%d\n",sensor_state);
            sleep(1);
        }
    }
    
    return 0;
}
