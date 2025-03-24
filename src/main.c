#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 40

#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_RESET    "\x1b[0m"

unsigned int frame = 0;

char sineChar = '#';
char cosChar = '@';

float scale = 19.0f;
float cycle = 40.0f;

// quick helper function to get sine value to draw to screen.
float getSin(float nVal) {
    // float scale = 19;
    // float cycle = 20.0f; // not how this works, but needed a variable name :P
    return (sin(nVal/cycle)+1)*scale;
}

// quick helper function to get cosine value to draw to screen.
float getCos(float nVal) {
    // float scale = 19;
    // float cycle = 20.0f; // not how this works, but needed a variable name :P
    return (cos(nVal/cycle)+1)*scale;
}

// Clears terminal screen we're drawing to
void clearScreen() {
    printf("\033[?25l\033[H");
    // fflush(stdout);
}

// Clears screen buffer and sets all values to ' '
void clearBuffer(char screen[], int sSize) {
    memset(screen, ' ', sSize);
    screen[sSize - 1] = '\0';
}

// Draws the screen buffer to the terminal window.
void renderScreen(char screen[], int sWidth, int sHeight) {
    for(int i = 0; i < sWidth*sHeight; i++){
        char c;
        if(i % sWidth == 0 && i != 0)
            printf("\n");

        if(screen[i] == sineChar) {
            printf(ANSI_COLOR_RED"%c"ANSI_COLOR_RESET, screen[i]);
        }
        else if(screen[i] == cosChar) {
            printf(ANSI_COLOR_BLUE"%c"ANSI_COLOR_RESET, screen[i]);
        }
        else {
            printf(" ");
        }
    }
}

// Calculate the line to draw for sine and cos values.
// Then inserts a character into its position on the screen buffer.
void calcBuffer(char screen[], int sWidth, int sHeight) {

    for(int x = 0; x < sWidth; x++) {
        int resultSin = getSin(x+frame);
        int resultCos = getCos(x+frame);
        
        int sY = sHeight - resultSin - 1;
        int cY = sHeight - resultCos - 1;

        int resultIndexSin = sY*sWidth+x;
        int resultIndexCos = cY*sWidth+x;

        if(resultSin >= 0 && resultSin < sHeight)       screen[resultIndexSin] = sineChar;
        if(resultCos >= 0 && resultCos < sHeight)       screen[resultIndexCos] = cosChar;
    }

    // update frame if value gets too high, otherwise if program left on too long, will cause it to crash.
    if(frame % 1000 == 0 && frame != 0)
        frame=0;
    else
        frame++;
}

int main(int argc, char** argv) {


    unsigned int SCREEN_SIZE = SCREEN_WIDTH*SCREEN_HEIGHT;

    // create a buffer thats just a sine function, render that to screen
    char screen[SCREEN_SIZE]={};

    clearBuffer(screen, SCREEN_SIZE);

    // render screen
    while(1){
        clearBuffer(screen, SCREEN_SIZE);
        clearScreen();
        calcBuffer(screen, SCREEN_WIDTH, SCREEN_HEIGHT);
        renderScreen(screen, SCREEN_WIDTH, SCREEN_HEIGHT);
        fflush(stdout);
        usleep(10000);
    }

    return 0;
}
