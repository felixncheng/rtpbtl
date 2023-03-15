#include <time.h>
#include <stdio.h>
#include "utils.h"

void byte_size_format(long long bytes, char fmt[])
{
    if (bytes / GByte > 0)
    {
        double size = (double)bytes / GByte;
        sprintf(fmt, "%.2f GByte", size);
    }
    else if (bytes / MByte > 0)
    {
        double size = (double)bytes / MByte;
        sprintf(fmt, "%.2f MByte", size);
    }
    else if (bytes / KByte > 0)
    {
        double size = (double)bytes / KByte;
        sprintf(fmt, "%.2f KByte", size);
    }
}

void bit_size_format(long long bits, char fmt[])
{
    if (bits / Gbit > 0)
    {
        double size = (double)bits / Gbit;
        sprintf(fmt, "%.2f Gbit", size);
    }
    else if (bits / Mbit > 0)
    {
        double size = (double)bits / Mbit;
        sprintf(fmt, "%.2f Mbit", size);
    }
    else if (bits / Kbit > 0)
    {
        double size = (double)bits / Kbit;
        sprintf(fmt, "%.2f Kbit", size);
    }
}

long long timeInMilliseconds()
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return (((long long)ts.tv_sec) * 1000) + (((long long)ts.tv_nsec) / 1000000);
}

void throughput(long long bytes, double begin, double end, char str[])
{
    char fmt_str[20], bit_fmt_str[20], iv[10];
    double interval = end - begin;
    byte_size_format(bytes, fmt_str);
    bit_size_format(bytes * 8 / interval, bit_fmt_str);
    sprintf(iv, "%.1f-%.1f sec", begin, end);
    sprintf(str, "%-10s\t%-10s\t%-10s/s", iv, fmt_str, bit_fmt_str);
}