float clip(float n, float lower, float upper)
{
    return n <= lower ? lower : n >= upper ? upper
                                           : n;
}

float scale(float n, float min, float max) //Scale 0-1
{
    return (n * (max - min) + min);
}