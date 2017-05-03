/**
 * @file lab9.c
 *
 * @author Jade Baca
 *
 * @date 4/21/17
 *
 * Assignment: Lab 9
 *
 * @brief A binary calculator
 *
 * @bugs Seg faults at zero padding error
 *
 **/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "function.h"


int main()
{
        char buf[BUF];
        char *string1 = NULL;
        char *op;
        char *string2 = NULL;
        char *string3 = NULL;
        struct cpu_t *cpu = NULL;
        cpu = malloc(sizeof(struct cpu_t ));

        start:

                printf("Enter word size: \n");
                fgets(buf, BUF, stdin);
                sscanf(buf,"%d", &cpu->word_size);

                if((cpu->word_size < 1) || (cpu->word_size > 64)){
                        // Error checking for word size
                        printf("Error: word size must be between 1 and 64\n");
                        memset(buf, 0, sizeof(buf)); //reset the memory for word size
                        goto start;
                        }
                // for zero padding -- calloc
                string1 = calloc(cpu->word_size + 1, 1);
                string2 = calloc(cpu->word_size + 1, 1);
                string3 = calloc(cpu->word_size + 1, 1);
                memset(buf, 0, sizeof(buf));

                printf("Press 0 for signed number, 1 for unsigned: \n");
                fgets(buf, BUF, stdin);
                sscanf(buf, "%d", &cpu->unsign);

                printf("Enter binary expression (Example: 101 + 111):\n");
                fgets(buf, BUF, stdin);
                // we split up the string into individual strings
                string1 = strtok(buf, " ");
                op = strtok(NULL, " ");
                string2 = strtok(NULL,"\n");


                // allocating memory and inserting at the tail for each string -- now a linked list
                //More error checking for word size
                if(strlen(string1) > cpu->word_size){
                        printf("Error:First number is greater than word size\n");
                        goto start;
                }

                if(strlen(string2) > cpu->word_size){
                        printf("Error: Second number is greater than word size\n");
                        goto start;
                }
                //creates doubly linked list
                create_list(&(cpu->r1_head), &(cpu->r1_tail), string1);
                create_list(&(cpu->r2_head), &(cpu->r2_tail), string2);
                create_list(&(cpu->r3_head), &(cpu->r3_tail), string3);


                if(*op == '+'){
                        //we're gonna run the adder
                        print_list(cpu->r1_head);
                        printf("%c\n", *op);
                        print_list(cpu->r2_head);
                        full_add(cpu);
                        printf("\n");
                        print_list(cpu->r3_head);
                        printf("flags\n");
                        over_flow(cpu);
                        printf("over: %d\n",cpu->overflow);
                        printf("carry: %d\n",cpu->carry);
                        sign(cpu);
                        printf("sign: %d\n",cpu->sign);
                        parity(cpu);
                        printf("parity: %d\n",cpu->parity);
                        zero(cpu);
                        printf("zero: %d\n", cpu->zero);
                        decimal(cpu);
                        memset(buf, 0, sizeof(buf));
                        printf("Do you want to continue [Y/n] ?");
                        fgets(buf,1024,stdin);
                        switch(*buf){
                                case 'Y':
                                case 'y':
                                {
                                        goto start;
                                        break;
                                }
                                case 'N':
                                case 'n':{
                                        break;
                                }
                        }
                if(*op == '-'){
                        // We gotta subtract by flipping the bit
                        print_list(cpu->r1_head);
                        printf("%c\n", *op);
                        print_list(cpu->r2_head);
                        bit_flip(cpu);
                        printf("\n");
                        print_list(cpu->r3_head);
                        printf("flags\n");
                        over_flow(cpu);
                        printf("over: %d\n",cpu->overflow);
                        printf("carry: %d\n",cpu->carry);
                        sign(cpu);
                        printf("sign: %d\n",cpu->sign);
                        parity(cpu);
                        printf("parity: %d\n",cpu->parity);
                        zero(cpu);
                        printf("zero: %d\n", cpu->zero);
                        decimal(cpu);
                        memset(buf, 0, sizeof(buf));
                        printf("Do you want to continue [Y/n] ?");
                        fgets(buf,1024,stdin);
                        switch(*buf){
                                case 'Y':
                                case 'y':
                                {
                                        goto start;
                                        break;
                                }
                                case 'N':
                                case 'n':{
                                        break;
                                }
                        }
                }
                if(*op == '&'){
                        print_list(cpu->r1_head);
                        printf("&\n");
                        print_list(cpu->r2_head);
                        and_gate(cpu);
                        printf("\n");
                        print_list(cpu->r3_head);
                        printf("flags\n");
                        over_flow(cpu);
                        printf("over: %d\n",cpu->overflow);
                        printf("carry: %d\n",cpu->carry);
                        sign(cpu);
                        printf("sign: %d\n",cpu->sign);
                        parity(cpu);
                        printf("parity: %d\n",cpu->parity);
                        zero(cpu);
                        printf("zero: %d\n", cpu->zero);
                        decimal(cpu);
                        memset(buf, 0, sizeof(buf));
                        printf("Do you want to continue [Y/n] ?");
                        fgets(buf,1024,stdin);
                        switch(*buf){
                                case 'Y':
                                case 'y':
                                {
                                        goto start;
                                        break;
                                }
                                case 'N':
                                case 'n':{
                                        break;
                                }
                        }
                }
                if(*op == '|'){
                        print_list(cpu->r1_head);
                        printf("|\n");
                        print_list(cpu->r2_head);
                        or_gate(cpu);
                        printf("\n");
                        print_list(cpu->r3_head);
                        printf("flags\n");
                        over_flow(cpu);
                        printf("over: %d\n",cpu->overflow);
                        printf("carry: %d\n",cpu->carry);
                        sign(cpu);
                        printf("sign: %d\n",cpu->sign);
                        parity(cpu);
                        printf("parity: %d\n",cpu->parity);
                        zero(cpu);
                        printf("zero: %d\n", cpu->zero);
                        decimal(cpu);
                        memset(buf, 0, sizeof(buf));
                        printf("Do you want to continue [Y/n] ?");
                        fgets(buf,1024,stdin);
                        switch(*buf){
                                case 'Y':
                                case 'y':
                                {
                                        goto start;
                                        break;
                                }
                                case 'N':
                                case 'n':{
                                        break;
                                }
                        }
                }
                if(*op == '^'){
                        print_list(cpu->r1_head);
                        printf("^\n");
                        print_list(cpu->r2_head);
                        xor_gate(cpu);
                        printf("\n");
                        print_list(cpu->r3_head);
                        printf("flags\n");
                        over_flow(cpu);
                        printf("over: %d\n",cpu->overflow);
                        printf("carry: %d\n",cpu->carry);
                        sign(cpu);
                        printf("sign: %d\n",cpu->sign);
                        parity(cpu);
                        printf("parity: %d\n",cpu->parity);
                        zero(cpu);
                        printf("zero: %d\n", cpu->zero);
                        decimal(cpu);
                        memset(buf, 0, sizeof(buf));
                        printf("Do you want to continue [Y/n] ?");
                        fgets(buf,1024,stdin);
                        switch(*buf){
                                case 'Y':
                                case 'y':
                                {
                                        goto start;
                                        break;
                                }
                                case 'N':
                                case 'n':{
                                        break;
                                }
                        }
                } else {
                        printf("Invalid operator\n");
                        goto start;
                }

        delete_list(cpu->r1_head);
        delete_list(cpu->r2_head);
        delete_list(cpu->r3_head);
        free(cpu);

        return 0;
}
}
