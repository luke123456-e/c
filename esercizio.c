#include <stdio.h>
#include <stdlib.h>

struct EthernetFrame {
    unsigned char dst[6];
    unsigned char src[6];
    unsigned short ethertype;
    unsigned char payload[1500];
    int payload_len;
};

int main() {
    unsigned char temp[1600];
    int len = 0;

    printf("Inserisci frame in esadecimale:\n");

    while (scanf("%2hhx", &temp[len]) == 1) {
        len++;
    }

    if (len < 14) {
        printf("Frame troppo corto!\n");
        return 1;
    }

    struct EthernetFrame f;

    for (int i = 0; i < 6; i++) {
        f.dst[i] = temp[i];
    }

    for (int i = 0; i < 6; i++) {
        f.src[i] = temp[6 + i];
    }

    f.ethertype = (temp[12] << 8) | temp[13];

    f.payload_len = len - 14;
    for (int i = 0; i < f.payload_len; i++) {
        f.payload[i] = temp[14 + i];
    }

    printf("\n=== FRAME ETHERNET ===\n");

    printf("MAC Dest: ");
    for (int i = 0; i < 6; i++) {
        printf("%02X", f.dst[i]);
        if (i < 5) printf(":");
    }

    printf("\nMAC Sorg: ");
    for (int i = 0; i < 6; i++) {
        printf("%02X", f.src[i]);
        if (i < 5) printf(":");
    }

    printf("\nEtherType: 0x%04X\n", f.ethertype);

    printf("Payload (%d byte):\n", f.payload_len);
    for (int i = 0; i < f.payload_len; i++) {
        printf("%02X ", f.payload[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }

    printf("\nTotale: %d byte\n", len);

    return 0;
}