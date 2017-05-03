/**
 * @file function.h
 *
 * @author Jade Baca
 *
 * @date 4/21/17
 *
 * Assignment: Lab 9
 *
 * @brief Declares the structure and the cpu
 *
 * @bugs
 *
 **/
#ifndef BUF
#define BUF 1024
struct bit_t {
        unsigned char data; /* store either 0 or 1 not ’0’ or ’1’ */

        struct bit_t *prev;
        struct bit_t *next;
};

struct cpu_t {
        int word_size;
        int unsign; //0 -- signed, 1 for unsigned
        //flags
        int overflow;
        int carry;
        int sign;
        int parity;
        int zero;
        struct bit_t *r1_head;
        struct bit_t *r1_tail;
        struct bit_t *r2_head;
        struct bit_t *r2_tail;
        struct bit_t *r3_head;
        struct bit_t *r3_tail;
};


struct bit_t *create_bit(unsigned char x);
void print_list(struct bit_t *node);
void create_list(struct bit_t **r_head, struct bit_t **r_tail, char *string1);
struct bit_t *insert_tail(struct bit_t *tail, struct bit_t *node);
void and_gate(struct cpu_t *cpu);
void or_gate(struct cpu_t *cpu);
void xor_gate(struct cpu_t *cpu);
void full_add(struct cpu_t *cpu);
void bit_flip(struct cpu_t *cpu);
void delete_list(struct bit_t *head);
void decimal(struct cpu_t *cpu);
void sign(struct cpu_t *cpu);
void over_flow(struct cpu_t *cpu);
void zero(struct cpu_t *cpu);
void parity(struct cpu_t *cpu);
#endif
