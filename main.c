#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

#include <mraa/gpio.h>

int ir_state = 0;

void *take_photo_thread (void *args){
    for(;;){
        if(ir_state /* || 1 */){
            char str[25];
            sprintf(str,"%d.jpg",(int) time((time_t*)NULL));
            take_photo(str);
            sleep (1);
            char command[100];
            sprintf (command, "upload.sh %s", str);
            system (command);
            //sprintf(command,"curl --form \"fileupload=@%s\"  http://www.lisperli.org/upload/?upload=yes",str);
            //system  (command);
        }
        sleep(1);
    }
}

int main(int argc, char** argv)
{
    mraa_gpio_context ir_gpio = NULL;

    ir_gpio = mraa_gpio_init(7);

    if (ir_gpio == NULL) {
        fprintf(stdout, "Could not initilaize ir_gpio\n");
        return 1;
    }

    mraa_gpio_dir(ir_gpio, MRAA_GPIO_IN);

    pthread_t t;
    pthread_create(&t,NULL,take_photo_thread,NULL);

    for (;;) {
        if( ir_state != mraa_gpio_read(ir_gpio)) {
            ir_state = !ir_state;
            printf("%d\n",ir_state);
            sleep(1);
        }
    }

    return 0;
}
