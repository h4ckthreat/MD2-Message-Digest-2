#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MD2_BLOCK_SIZE 16
#define MD2_DIGEST_SIZE 16

typedef struct {
    unsigned char state[48];
    unsigned char checksum[16];
    unsigned char buffer[16];
    unsigned char digest[16];
} MD2_CTX;

static const unsigned char sbox[256] = {
    /* S-Box */
    41, 46, 67, 201, 162, 216, 124, 1, 61, 54, 84, 161, 236, 240, 6, 19,
    98, 167, 5, 243, 192, 199, 115, 140, 152, 147, 43, 217, 188, 76, 130,
    202, 30, 155, 87, 60, 253, 212, 224, 22, 103, 66, 111, 24, 138, 23, 229,
    18, 190, 78, 196, 214, 218, 158, 222, 73, 160, 251, 245, 142, 187, 47,
    238, 122, 169, 104, 121, 145, 21, 178, 7, 63, 148, 194, 16, 137, 11, 34,
    95, 33, 128, 127, 93, 154, 90, 144, 50, 39, 53, 62, 204, 231, 191, 247,
    151, 3, 255, 25, 48, 179, 72, 165, 181, 209, 215, 94, 146, 42, 172, 86,
    170, 198, 79, 184, 56, 210, 150, 164, 125, 182, 118, 252, 107, 226, 156,
    116, 4, 241, 69, 157, 112, 89, 100, 113, 135, 32, 134, 91, 207, 101, 230,
    45, 168, 2, 27, 96, 37, 173, 174, 176, 185, 246, 28, 70, 97, 105, 52, 64,
    126, 15, 85, 71, 163, 35, 221, 81, 175, 58, 195, 92, 249, 206, 186, 197,
    234, 38, 44, 83, 13, 110, 133, 40, 132, 9, 211, 223, 205, 244, 65, 129,
    77, 82, 106, 220, 55, 200, 108, 193, 171, 250, 36, 225, 123, 8, 12, 189,
    177, 74, 120, 136, 149, 139, 227, 99, 232, 109, 233, 203, 213, 254, 59,
    0, 29, 57, 242, 239, 183, 14, 102, 88, 208, 228, 166, 119, 114, 248, 235,
    117, 75, 10, 49, 68, 80, 180, 143, 237, 31, 26, 219, 153, 141, 51, 159,
    17, 131, 20
};

void md2_transform(MD2_CTX *ctx) {
    unsigned char t;
    unsigned char x;
    unsigned char y;
    unsigned char z;
    unsigned char *state = ctx->state;
    unsigned char *checksum = ctx->checksum;
    unsigned char *buffer = ctx->buffer;

    for (int i = 0; i < 16; i++) {
        state[16 + i] = buffer[i];
        state[32 + i] = state[16 + i] ^ state[i];
    }

    t = 0;
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 48; j++) {
            state[j] ^= sbox[t];
            t = state[j];
        }
        t += i;
    }

    x = 0;
    y = 0;
    for (int i = 0; i < 18; i++) {
        for (int j = 0; j < 48; j++) {
            x = state[j] = checksum[j] ^= sbox[x];
        }
        y += x;
        x += i;
    }

    memset(buffer, 0, sizeof(ctx->buffer));
}

void md2_init(MD2_CTX *ctx) {
    memset(ctx->state, 0, sizeof(ctx->state));
    memset(ctx->checksum, 0, sizeof(ctx->checksum));
    memset(ctx->buffer, 0, sizeof(ctx->buffer));
    memset(ctx->digest, 0, sizeof(ctx->digest));
}

void md2_update(MD2_CTX *ctx, const unsigned char *data, size_t length) {
    unsigned char *buffer = ctx->buffer;
    size_t buffer_size = sizeof(ctx->buffer);
    size_t index = 0;

    while (length--) {
        buffer[index++] = *data++;

        if (index == buffer_size) {
            md2_transform(ctx);
            index = 0;
        }
    }
}

void md2_final(MD2_CTX *ctx) {
    unsigned char *buffer = ctx->buffer;
    size_t buffer_size = sizeof(ctx->buffer);
    size_t pad_size = buffer_size - sizeof(ctx->checksum);
    unsigned char pad_value = (unsigned char)pad_size;

    for (size_t i = 0; i < pad_size; i++) {
        buffer[i] = pad_value;
    }

    md2_transform(ctx);
    md2_transform(ctx);

    memcpy(ctx->digest, ctx->state, sizeof(ctx->digest));
}

void md2(const unsigned char *message, size_t length, unsigned char *digest) {
    MD2_CTX ctx;

    md2_init(&ctx);
    md2_update(&ctx, message, length);
    md2_final(&ctx);

    memcpy(digest, ctx.digest, MD2_DIGEST_SIZE);
}

int main() {
    char message[256];
    unsigned char digest[MD2_DIGEST_SIZE];

    printf("Digite a mensagem: ");
    fgets(message, sizeof(message), stdin);

    size_t length = strlen(message);
    if (length > 0 && message[length - 1] == '\n') {
        message[length - 1] = '\0';
        length--;
    }

    md2((unsigned char *)message, length, digest);

    printf("Hash MD2: ");
    for (int i = 0; i < MD2_DIGEST_SIZE; i++) {
        printf("%02x", digest[i]);
    }
    printf("\n");

    return 0;
}
