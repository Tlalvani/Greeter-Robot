#define SERVOS 20

float clip(float n, float lower, float upper)
{
    return n <= lower ? lower : n >= upper ? upper
                                           : n;
}

float scale(float n, float min, float max) //Scale 0-1
{
    return (n * (max - min) + min);
}

float basicArray[SERVOS]  = {1, .5, 0, 0, 0, 0, 0, 0, 0, 0, 1, .5, 0, 0, 0, 0, 0, 0, 0, 0};