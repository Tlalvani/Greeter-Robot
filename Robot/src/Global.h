#define SERVOS 24

float clip(float n, float lower, float upper) //Clips value to lie between two other values
{
    return n <= lower ? lower : n >= upper ? upper
                                           : n;
}

float scale(float n, float min, float max, float scaleMin, float scaleMax) //Convert min to scaleMin and max to scaleMax
{
    return (((n - scaleMin) / (scaleMax - scaleMin)) * (max - min) + min);
}

//Used for basic control. Declared in global so that both arm and subscriber can use
float basicArray[SERVOS] = {1, .5, 0, 0, 0, 0, 0, 0, 0, 0, 1, .5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};