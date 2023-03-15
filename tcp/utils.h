#ifndef UTILS_FILE_TRANSFER_H
#define UTILS_FILE_TRANSFER_H

// Kbit大小
#define Kbit 1000
// Mbit大小
#define Mbit 1000000
// Gbit大小
#define Gbit 1000000000

#define KByte 1024

#define MByte (1024 * KByte)

#define GByte (1024 * MByte)

void byte_size_format(long long bytes, char fmt[]);
void bit_size_format(long long bits, char fmt[]);
long long timeInMilliseconds();
void throughput(long long bytes, double begin, double end, char str[]);

#endif // UTILS_FILE_TRANSFER_H
