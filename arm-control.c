#include <ncurses.h>
#include <stdio.h>
#include <pigpio.h>
#include <unistd.h>

// Pins for servos
#define SERVOPAN 17
#define SERVOTILT 4

// PWM increment per loop
#define INCREMENT 25


// Function to display everything to ncurses
int display_refresh(char *welcome, int pan, int tilt)
{
    erase();
    printw("%s",welcome);
    printw("\
#  Current pan value:  %d      #\n\
#  Current tilt value: %d      #\n\
##################################\n", pan, tilt);

    refresh();
    return 0;
}


int pwm_to_neutral(pan, tilt, display)
{
}

int main()
{
    // Start ncurses
    initscr();
    cbreak();

    // Start pigpio
    gpioInitialise();

    char *welcome_string = "\
##################################\n\
#      Pan and tilt control      #\n\
#                                #\n\
#  ----------------------------  #\n\
#  w = Tilt up    a = Pan left   #\n\
#  s = Tilt down  d = Pan right  #\n\
#  n = Go to neutral position    #\n\
#  ----------------------------  #\n\
#                                #\n\
#               Press q to quit  #\n\
##################################\n";

    // Declare pwm variables at neutral
    int pwm_pan = 1500, pwm_tilt = 1500, display_tilt = 1500; // display_tilt used to display pwm value for tilt

    // Move servo to neutral
    gpioServo(SERVOPAN, pwm_pan);
    gpioServo(SERVOTILT, pwm_tilt);

    display_refresh(welcome_string, pwm_pan, display_tilt);

    // Get a character from the user
    char usrinput = getchar();

    // Repeat until told to quit (q key pressed)
    while(usrinput != 'q')
    {
        // Pan right
        if(usrinput == 'd')
        {
            pwm_pan += INCREMENT;
        }
        // Pan left
        else if(usrinput == 'a')
        {
            pwm_pan -= INCREMENT;
        }
        // Tilt down
        else if(usrinput == 's')
        {
            pwm_tilt += INCREMENT;
            display_tilt -= INCREMENT;
        }
        // Tilt up
        else if(usrinput == 'w')
        {
            pwm_tilt -= INCREMENT;
            display_tilt += INCREMENT;
        }
        // Go to neutral
        else if(usrinput == 'n')
        {
            pwm_pan = 1500;
            pwm_tilt = 1500;
            display_tilt = 1500;
        }

        // Limit the pwm values to within range - avoid damage to servo 
        if (pwm_pan > 2000)
        {
            pwm_pan = 2000;
        }
        if (pwm_pan < 1000)
        {
            pwm_pan = 1000;
        }
        if (pwm_tilt > 2000)
        {
            pwm_tilt = 2000;
        }
        if (pwm_tilt < 1000)
        {
            pwm_tilt = 1000;
        }
        if (display_tilt > 2000)
        {
            display_tilt = 2000;
        }
        if (display_tilt < 1000)
        {
            display_tilt = 1000;
        }
 
        // Update servo
        gpioServo(SERVOPAN, pwm_pan);
        gpioServo(SERVOTILT, pwm_tilt);

        display_refresh(welcome_string, pwm_pan, display_tilt);

        // Get another character
        usrinput = getchar();
    }

    // Clear up screen & inform user of exit
    erase();
    printw("%s",welcome_string);
    printw("\
#         Cleaning up...         #\n\
#                                #\n\
##################################\n");
    refresh();

    // Turn off servos
    gpioServo(SERVOPAN, 1500);
    gpioServo(SERVOTILT, 1500);
    sleep(1);
    gpioServo(SERVOPAN, 00);
    gpioServo(SERVOTILT, 00);

    // Stop pigpio    
    gpioTerminate();
    // Stop ncurses
    endwin();
    return 0;
}
