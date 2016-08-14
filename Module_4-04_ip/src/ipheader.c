#include <stdio.h>
#include <arpa/inet.h>
#include "ipheader.h"


/* Parses the given buffer into an IP header structure.
 * 
 * Parameters:
 * ip: pointer to the IP header structure that will be filled based
 *      on the data in the buffer
 * buffer: buffer of 20 bytes that contain the IP header. */
void parseIp(struct ipHeader *ip, const void *buffer)
{
    const char* uint8View = buffer;
    const unsigned short* uint16View = buffer;
    
    ip->version = (uint8View[0] & 0xF0) >> 4;
    ip->ihl = (uint8View[0] & 0x0F) * 4;
    ip->dscp = (uint8View[1] & 0xFC) >> 2;
    ip->ecn = uint8View[1] & 0x03;
    ip->length = ntohs(uint16View[1]);
    
    ip->identification = ntohs(uint16View[2]);
    ip->flags = (uint8View[6] & 0xE0) >> 5;
    ip->fragment_offset = ntohs(uint16View[3]) & 0x1FFF;
    
    ip->time_to_live = uint8View[8];
    ip->protocol = uint8View[9];
    ip->header_checksum = ntohs(uint16View[5]);
    
    for (int i = 0; i < 4; i++) {
        ip->source_ip[i] = uint8View[12 + i];
        ip->destination_ip[i] = uint8View[16 + i];
    }
}


/* Builds a 20-byte byte stream based on the given IP header structure
 * 
 * Parameters:
 * buffer: pointer to the 20-byte buffer to which the header is constructed
 * ip: IP header structure that will be packed to the buffer */
void sendIp(void *buffer, const struct ipHeader *ip)
{
    char* uint8View = buffer;
    unsigned short* uint16View = buffer;
    
    uint8View[0] = 0 | (ip->version << 4);
    uint8View[0] |= ip->ihl / 4;
    uint8View[1] = 0 | (ip->dscp << 2);
    uint8View[1] |= ip->ecn;
    uint16View[1] = htons(ip->length);
    
    uint16View[2] = htons(ip->identification);
    uint8View[6] = 0 | (ip->flags << 5);
    uint16View[3] |= htons(ip->fragment_offset);
    
    uint8View[8] = ip->time_to_live;
    uint8View[9] = ip->protocol;
    uint16View[5] = htons(ip->header_checksum);
    
    for (int i = 0; i < 4; i++) {
        uint8View[12 + i] = ip->source_ip[i];
        uint8View[16 + i] = ip->destination_ip[i];
    }
}


/* Prints the given IP header structure */
void printIp(const struct ipHeader *ip)
{
    /* Note: ntohs below is for converting numbers from network byte order
     to host byte order. You can ignore them for now
     To be discussed further in Network Programming course... */
    printf("version: %d   ihl: %d   dscp: %d   ecn: %d\n",
            ip->version, ip->ihl, ip->dscp, ip->ecn);
    printf("length: %d   id: %d   flags: %d   offset: %d\n",
            ntohs(ip->length), ntohs(ip->identification), ip->flags, ip->fragment_offset);
    printf("time to live: %d   protocol: %d   checksum: 0x%04x\n",
            ip->time_to_live, ip->protocol, ntohs(ip->header_checksum));
    printf("source ip: %d.%d.%d.%d\n", ip->source_ip[0], ip->source_ip[1],
            ip->source_ip[2], ip->source_ip[3]);
    printf("destination ip: %d.%d.%d.%d\n", ip->destination_ip[0],
            ip->destination_ip[1],
            ip->destination_ip[2], ip->destination_ip[3]);    
}

/* Shows hexdump of given data buffer */
void hexdump(const void *buffer, unsigned int length)
{
    const unsigned char *cbuf = buffer;
    unsigned int i;
    for (i = 0; i < length; ) {
        printf("%02x ", cbuf[i]);
        i++;
        if (!(i % 8))
            printf("\n");
    }
}
