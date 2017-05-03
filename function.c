/**
 * @file function.c
 *
 * @author Jade Baca
 *
 * @date 4/21/17
 *
 * Assignment: Lab 9
 *
 * @brief Operators and other functions for binary calculator
 *
 * @bugs Seg faults at zero padding error.
 *
 **/
 #include <stdio.h>
 #include <stdlib.h>
 #include <math.h>
 #include <string.h>
 #include "function.h"

/** Creates list and calls create_bit function
 * @param *string1 this is the string we want to make into a linked list
 * @param *cpu we are going to edit the cpu so we have to access it
 * @param x this determines whether it's string 1, 2 or 3 (the output)
 */
void create_list(struct bit_t **r_head, struct bit_t **r_tail, char *string1)
{
        int i = 0;
        int n;
        struct bit_t *head = NULL;
        struct bit_t *tail = NULL;
        struct bit_t *node = NULL;

        while(*(string1 + i) != '\0'){

                if (*(string1 + i) == '1'){
                        n = 1;
                } else {
                        n = 0;
                }
                node = create_bit(n);
                if(i == 0){
                        head = node;
                        tail = node;
                } else {

                        tail = insert_tail(tail, node);
                }

                i = i + 1;
        };
        *r_head = head;
        *r_tail = tail;
}

 /** the bit (node and allocates memory for it
 * @param x this is the character we pass into the new node
 * @return bit we return the bit to create_list since we changed it
 */
struct bit_t *create_bit(unsigned char x)
{
        // malloc node
        struct bit_t *bit = malloc(sizeof(struct bit_t));
        // bit now points to x, which will equal data
        bit ->data = x;
        // Created bit
        bit ->next = NULL;
        bit ->prev = NULL;
        return bit;

}
/** This puts each node into the doubly linked list at the tail
 * @param *cpu we are going to edit the cpu so we have to access it
 * @param *node this is the node we are putting into the list
 * @param x this determines whether it's string 1, 2 or 3 (the output)
 * @return cpu ->(head) this returns what we edit depending on which string we edit
 */
struct bit_t *insert_tail(struct bit_t *tail, struct bit_t *node)
{
        //we created a tmp to run through the function bc we have to hold onto it, keep track of it
        if (tail == NULL){
                tail = node;
                return tail;
        }
        tail->next = node;
        node->prev = tail;
        node->next = NULL;
        tail = node;
        return tail;
}
/** This prints the binary cpus
 * @param the node from the linked list-- we print each one
 */
void print_list(struct bit_t *node)
{
        struct bit_t  *tmp = NULL;
        tmp = node;
        while(tmp != NULL){
                printf("%d", tmp->data); //print the data and increment
                tmp = tmp->next;
        }
        printf("\n");
}
/** this is supposed to be the and gate
 * @param *cpu we need to change the cpu so we have to have access to it
 */
void and_gate(struct cpu_t *cpu)
{
        struct bit_t *a = NULL;
        struct bit_t *b = NULL;
        struct bit_t *out = NULL;
        // a and b will have an out to put in r3
        a = cpu ->r1_head;
        b = cpu ->r2_head;
        out = cpu ->r3_head;
        while( a != NULL){ //truth table data
                if(a ->data == 1 || b ->data == 1){
                        out ->data = 1;
                } else {
                        out ->data = 0;
                }
                printf("-");
                a = a ->next;
                b = b ->next;
                out = out ->next;
                // goes to next node to preform the same steps
        }
}
/** this is supposed to be the or gate
 * @param *cpu we need to change the cpu so we have to have access to it
 */
void or_gate(struct cpu_t *cpu)
{
        struct bit_t *a = NULL;
        struct bit_t *b = NULL;
        struct bit_t *out = NULL;
        // a and b will have an out to put in r3
        a = cpu ->r1_head;
        b = cpu ->r2_head;
        out = cpu ->r3_head;
        while(a != NULL){ //truth table data for or
                if(a ->data == 0 && b ->data == 0){
                        out ->data = 0;
                } else {
                        out ->data = 1;
                }
                a = a ->next;
                b = b ->next;
                out = out ->next;
                // goes to next node to preform the same steps
        }
}
/** this is supposed to be the or gate
 * @param *cpu we need to change the cpu so we have to have access to it
 * Note: xor is fixed, should work 100%, the tutor garanteed
 */
void xor_gate(struct cpu_t *cpu)
{
        struct bit_t *a = NULL;
        struct bit_t *b = NULL;
        struct bit_t *out = NULL;
        // a and b will have an out to put in r3
        a = cpu ->r1_head;
        b = cpu ->r2_head;
        out = cpu ->r3_head;
        int i;
        for(i = 1; i < cpu->word_size; i++){
                if(a ->data == b ->data){
                        out ->data = 0;
                } else {
                        out ->data = 1;
                }
                a = a ->next;
                printf("-");
                b = b ->next;
                out = out ->next;
        }
}
/** simulates a full adder
 * @param *cpu we need to change the cpu so we have to have access to it
 */
void full_add(struct cpu_t *cpu)
{
        int i;
        struct bit_t *tmp1 = NULL;
        struct bit_t*tmp2 = NULL;
        struct bit_t *tmp3 = NULL;
        //we set each tmp to the tail so we can edit
        tmp1 = cpu->r1_tail;
        tmp2 = cpu->r2_tail;
        tmp3 = cpu->r3_tail;

        for(i = 0 ; i < cpu->word_size ; i++){
                printf("-");

                // adds the first 2 numbers and puts them in the output
                tmp3->data = tmp1->data + tmp2->data;
                if (tmp3->data >= 2)
                {
                        // carry flag is set
                        cpu->carry = 1;
                        tmp3->data = (tmp3->data) % 2;
                } else  {
                        cpu->carry = 0;
                }
                // decrements tmp
                tmp1 = tmp1->prev;
                tmp2 = tmp2->prev;
                tmp3 = tmp3->prev;
        }

}
/** does the subtraction by flipping the bit
 * @param *cpu we need to change the cpu so we have to have access to it
 */
void bit_flip(struct cpu_t *cpu)
{
        int i = 0;
        int first_one = 0;
        struct bit_t *tmp2 =  NULL;
        //
        tmp2 = cpu->r2_tail;
        for (i = 1 ; i < cpu->word_size ; i++){
                if (tmp2->data == 1){
                        first_one = 1;
                }
                if (first_one == 1)
                tmp2->prev->data =  (tmp2->prev->data + 1) % 2;
                tmp2 = tmp2->prev;

        }
        print_list(cpu->r2_head);
        full_add(cpu);

}

/** this frees up the memory at the end of the function
 * @param *head this is where we start at the linked list to delete
 */
 void delete_list(struct bit_t *head)
{
        struct bit_t *tmp = NULL;
        struct bit_t *current = NULL;
        current = head;

        while (current != NULL) {
                tmp = current ->next;
                free(current); //we're freeing the memory we made once the program terminates
                current = tmp;
        }
        head = NULL;
}

/** this is the decimal flag: converts binary to decimal
 * @param *cpu we need to change the cpu so we have to have access to it
 */
 void decimal(struct cpu_t *cpu)
 {
         int i = 0;
         int j = 0;
         int k;

         struct bit_t *tmp = NULL;
         tmp = cpu->r3_tail;
         //this interprets the number unsigned
         if(cpu->unsign == 1){
                 for( i = 0; i < cpu->word_size; i++){
                                j = j +(tmp->data) * pow(2,i);
                                tmp = tmp->prev;
                 }
                 printf("Decimal: %d\n", j);
         }
         //this one interprets the number as signed
         if(cpu->unsign == 0){
                 k = -(cpu->r3_head->data) * pow(2, cpu->word_size);
                 for(i = 0; i < cpu->word_size - 1; i++){
                         k = k +(tmp -> data) * pow(2,i);
                         tmp = tmp->prev;
                 }
                  printf("Decimal: %d\n", j);
         }

 }
 /** this is the sign flag: determines whether number is signed
  * @param *cpu we need to change the cpu so we have to have access to it
  */
 void sign(struct cpu_t *cpu)
 {
         if(cpu->r3_head->data == 1){
                 cpu->sign = 1;
         } else {
                 cpu->sign = 0;
         }
 }
 /** this is the overflow flag
  * @param *cpu we need to change the cpu so we have to have access to it
  */
 void over_flow(struct cpu_t *cpu)
 {
         if ((cpu->r3_head->data == 1 && cpu->r1_head->data ==0 && cpu->r2_head->data ==0) || (cpu->r1_head->data == 1 && cpu->r2_head->data == 1 && cpu->r3_head->data == 0)){
                 cpu->overflow = 1;
         } else{
                 cpu->overflow = 0;
         }
 }
 /** this is the zero flag
  * @param *cpu we need to change the cpu so we have to have access to it
  */
 void zero(struct cpu_t *cpu)
 {
         int count = 0;
         struct bit_t *tmp = NULL;
         tmp = cpu->r3_head;
         while(tmp != NULL){
                 if (tmp->data == 1)
                 count = count + 1;
                 tmp = tmp->next;
         }
         if ( count == 0){
                 cpu->zero = 1;
         }
         else
         cpu->zero = 1;
 }
 /** this is the parity flag
  * @param *cpu we need to change the cpu so we have to have access to it
  */
 void parity(struct cpu_t *cpu)
 {
         int count = 0;
         struct bit_t *tmp = NULL;
         tmp = cpu->r3_head;
         while(tmp != NULL){
                 if (tmp->data == 1)
                         count = count + 1;
                         tmp = tmp->next;
         }
         if (count % 2 ==0)
                cpu->parity = 1;
         else
                cpu->parity = 0;
 }
