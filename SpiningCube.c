/* This is All Library in my Projects*/
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

float A,B,C; // The inisiation for the matriks

float cubeWidth = 10;
int width = 160, height = 44; // this is cube id for the result 
float zBuffer[160 * 44];
char buffer[160 * 44];
int backgroundASCIICode =' ';
int distanceFromCam = 50;
float X1 = 40; 


float incrementSpeed = 0.6;

float i,j,k;
float ook;
int ip, jp;
int xdi;

float calculateI(int x, int y, int z) {
    return y * sin(A) * sin(B) * cos(C) - z * cos(A) * sin(B) * cos(C) +
           y * cos(A) * sin(C) + z * sin(A) * sin(C) + x * cos(B) * cos(C);
}

float calculateJ(int x, int y, int z) {
    return y * cos(A) * cos(C) + z * sin(A) * cos(C) +
           y * sin(A) * sin(B) *  sin(C) + z * cos(A) * sin(B) * sin(C) -
           x * cos(B) * sin(C);  
}

float calculateK(int x, int y, int z) {
    return z * cos(A) * cos(B) - y * sin(A) * cos(B) + x * sin(B);
}

void calculateForSurface(float cubeI, float cubeJ, float cubeK, int ch) {
    i = calculateI(cubeI, cubeJ, cubeK);
    j = calculateJ(cubeI, cubeJ, cubeK);
    k = calculateK(cubeI, cubeJ, cubeK) +distanceFromCam;

    ook = 1/k;

    ip = (int)(width/2 + X1 * ook * i *2);
    jp = (int)(height/2 + X1 *ook * j);

    xdi = ip + jp * width;
    if (xdi>= 0 && xdi < width * height) {
        if(ook> zBuffer[xdi]) {
            zBuffer[xdi] = ook;
            buffer[xdi] = ch;
        }
    }
}

int main() {
    printf("\x1b[2]");
    while (1) {
      memset(buffer, backgroundASCIICode, width * height);
      memset(zBuffer, 0, width * height * 4);
      for (float cubeI = -cubeWidth; cubeI < cubeWidth; cubeI += incrementSpeed) {
        for(float cubeJ = -cubeWidth; cubeJ < cubeWidth; cubeJ += incrementSpeed) {
            calculateForSurface(cubeI, cubeJ, -cubeWidth, '.');
            calculateForSurface(cubeWidth, cubeJ, cubeI, '$');
            calculateForSurface(-cubeWidth, cubeJ, -cubeI, '~');
            calculateForSurface(-cubeI, cubeJ, cubeWidth, '~');
        }
      }
      printf("\x1b[H");
      for(int z = 0; z < width * height; z++){
        putchar(z % width ? buffer[z] : 10);
      }
      A += 0.005;
      B += 0.005;
      usleep(1000); // timelepse cube 
    }
    return 0; 
}
