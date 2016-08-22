#include <stdio.h>
#include <string.h>
#include "base64.h"

#define UNIT 3

/* The set of base64-encoded characters. You may use this table if you want.
 * (The last character is not part of the actual base64 set, but used for
 * padding). 
 */
const char *encoding = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";

void encode(char* dst, unsigned char* src, int src_len);
int decode(char* dst, unsigned char* src);
char decoding(char c);

/* Open file named <src_file> for reading, and convert it to Base64 format,
 * which is written to file named <dst_file>.
 * 
 * Returns: number of bytes in <src_file>, or -1 if there was an error,
 * for example if opening of <src_file> did not succeed.
 */
int to_base64(const char *dst_file, const char *src_file)
{
    FILE* f_dst = fopen(dst_file, "w");
    FILE* f_src = fopen(src_file, "r");
    if (!f_dst || !f_src)
        return -1;
    unsigned char buf[UNIT];
    char base64[5];
    base64[4] = '\0';
    int line = 64;
    int read = fread(buf, 1, UNIT, f_src);
    while (read == UNIT) {
        encode(base64, buf, UNIT);
        
        if (fputs(base64, f_dst) < 0) {
            return -1;
        }
        line -= 4;
        if (!line) {
            fputc('\n', f_dst);
            line = 64;
        }
        
        read = fread(buf, 1, UNIT, f_src);
    }
    if (read == 1 || read == 2) {
        buf[2] = '\0';
        if (read == 1) {
            buf[1] = '\0';
        }
        encode(base64, buf, read);
        if (fputs(base64, f_dst) < 0) {
            return -1;
        }
    }
    
    int src_len = ftell(f_src);
    if (fclose(f_dst) < 0 || fclose(f_src) < 0)
        return -1;
    return src_len;
}

/* Open Base64-encoded file named <src_file> for reading, and convert it
 * to regular binary format, which is written to file named <dst_file>.
 * 
 * Returns: number of bytes in <src_file>, or -1 if there was an error,
 * for example if opening of <src_file> did not succeed.
 */
int from_base64(const char *dst_file, const char *src_file)
{
    FILE* f_dst = fopen(dst_file, "w");
    FILE* f_src = fopen(src_file, "r");
    if (!f_dst || !f_src)
        return -1;
    char buf[UNIT], base64[5];
    int line = 64, src_len = 0;
    char* read = fgets(base64, 5, f_src);
    while (read) {
        line -= 4;
        src_len += 4;
        int write = decode(buf, (unsigned char*)base64);
        
        fwrite(buf, sizeof(*buf), write, f_dst);
        
        if (!line) {
            fseek(f_src, 1, SEEK_CUR);
            src_len++;
            line = 64;
        }
        read = fgets(base64, 5, f_src);
    }

    if (fclose(f_dst) < 0 || fclose(f_src) < 0)
        return -1;
    return src_len;
}

void encode(char* dst, unsigned char* src, int src_len)
{
    dst[0] = encoding[src[0] >> 2];
    dst[1] = encoding[63 & (src[0] << 4 | (63 & src[1] >> 4))];
    dst[2] = src_len >= 2 ? encoding[63 & (src[1] << 2 | (63 & src[2] >> 6))] : encoding[64];
    dst[3] = src_len == 3 ? encoding[63 & src[2]] : encoding[64];
}

int decode(char* dst, unsigned char* src)
{
    dst[0] = decoding(src[0]) << 2 | decoding(src[1]) >> 4;
    if (src[2] == encoding[64])
        return 1;
    dst[1] = decoding(src[1]) << 4 | decoding(src[2]) >> 2;
    if (src[3] == encoding[64])
        return 2;
    dst[2] = decoding(src[2]) << 6 | decoding(src[3]);
    return 3;
}

char decoding(char c) {
    return (char)(strchr(encoding, c) - encoding);
}