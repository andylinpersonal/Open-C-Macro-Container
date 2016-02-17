#include <stdio.h>
#include <stdlib.h>

#define CCC_DLLST_BLOCK_SIZE 1000

#include "../src/ccc.h"


int main(void)
{
    /* Test 0 */
    /* For demonstration */

    printf("Test 0:\n\n");

    {
        cc_dllst(msg, char*);
        cc_dllst_iter(msg_iter, msg);

        cc_dllst_push_back(msg, "Hello everyone:\n");
        cc_dllst_push_back(msg, "Welcome to C Container Collection Project!\n");

        cc_dllst_trav(msg, msg_iter)
            printf("%s", cc_dllst_iter_dref(msg_iter));

        cc_dllst_free(msg);
    }


    /* Test 1 */
    /* Push back ten pointers to char */

    printf("\n\nTest 1: \n");

    {
        cc_dllst(test1, char*);

        char *num_str[10] = { "five" , "six", "four", "seven", "three",
                              "eight", "two", "nine", "one"  , "ten"    };

        int cnt = 0;

        while (puts("") && cnt < 10)
        {
            cc_dllst_iter(test1_iter, test1);

            cc_dllst_push_front(test1, num_str[cnt++]);
            cc_dllst_push_back (test1, num_str[cnt++]);

            cc_dllst_trav(test1, test1_iter)
                printf("%s ", cc_dllst_iter_dref(test1_iter));
        }

        cc_dllst_free(test1);
    }


    /* Test 2 */
    /* Deallocation */

    printf("\n\nTest 2: ");

    {
        cc_dllst(test2, int);

        int cnt = 0;

        while (cnt < 10000000)
            cc_dllst_push_back(test2, cnt++);

        cc_dllst_free(test2);

        puts("Test deallocation.");
    }


    /* Test 3 */
    /* Push back two structs */

    printf("\n\nTest 3: ");

    {
        typedef struct
        {
            char *msg[2];
        } test3_struct;

        cc_dllst(test3, test3_struct);
        cc_dllst_iter(test3_iter, test3);

        test3_struct test3_1, test3_2;

        test3_1.msg[0] = "Push";
        test3_1.msg[1] = "back";
        test3_2.msg[0] = "two";
        test3_2.msg[1] = "structs.\n";

        cc_dllst_push_back(test3, test3_1);
        cc_dllst_push_back(test3, test3_2);

        cc_dllst_trav(test3, test3_iter)
            printf("%s ", cc_dllst_iter_dref(test3_iter).msg[0]),
            printf("%s ", cc_dllst_iter_dref(test3_iter).msg[1]);

        cc_dllst_free(test3);
    }


    /* Test 4 */
    /* Empty container */

    printf("\n\nTest 4: ");

    {
        cc_dllst(test4, int);
        cc_dllst_iter(test4_iter, test4);

        cc_dllst_trav(test4, test4_iter)
            printf("%d", cc_dllst_iter_dref(test4_iter));

        if (cc_dllst_iter_incr(test4_iter) == NULL)
            puts("The iterator points to the tail.");

        (void)cc_dllst_iter_dref(test4_iter);

        cc_dllst_free(test4);
    }


    /* Test 5 */
    /* Element access */

    printf("\n\nTest 5: ");

    {
        cc_dllst(test5, char*);
        cc_dllst_iter(test5_iter, test5);

        (void)cc_dllst_front(test5);
        (void)cc_dllst_back(test5);
        cc_dllst_push_front(test5, "Failed ");
        cc_dllst_push_front(test5, "to access.\n");
        cc_dllst_back(test5)  = "Element access ";
        cc_dllst_front(test5) = "succeed.\n";

        cc_dllst_trav_backward(test5, test5_iter)
            printf("%s", cc_dllst_iter_dref(test5_iter));

        cc_dllst_free(test5);
    }


    /* Test 6 */
    /* Pop elements */

    printf("\n\nTest 6: ");

    {
        cc_dllst(test6, int);
        cc_dllst_iter(test6_iter, test6);

        cc_dllst_pop_front(test6);

        cc_dllst_push_front(test6, 1);
        cc_dllst_pop_front(test6);

        cc_dllst_push_back(test6, 1);
        cc_dllst_push_back(test6, 2);
        cc_dllst_pop_back(test6);
        cc_dllst_trav(test6, test6_iter)
            printf("Only '%d' remains in the container.\n",
                   cc_dllst_iter_dref(test6_iter));

        cc_dllst_free(test6);
    }


    /* Test 7 */
    /* Frequently push and pop elements */

    printf("\n\nTest 7: \n");

    {
        cc_dllst(test7, int);

        puts("\nPushing back 10^7 elements...");
        for (int cnt = 0; cnt < 10000000; cnt++)
            cc_dllst_push_back(test7, cnt);
        puts("Clearing the dllst container...");
        cc_dllst_clear(test7);

        puts("\nPushing back 10^7 elements...");
        for (int cnt = 0; cnt < 10000000; cnt++)
            cc_dllst_push_back(test7, cnt);
        puts("Deallocating the dllst container...");
        cc_dllst_free(test7);
    }


    /* Test 8 */
    /* Test packed structure */

    printf("\n\nTest 8: \n\n");

    {
        cc_dllst_packed(test8_char       , char);
        cc_dllst_packed(test8_short      , short);
        cc_dllst_packed(test8_int        , int);
        cc_dllst_packed(test8_long_int   , long int);
        cc_dllst_packed(test8_long_double, long double);

        for (int cnt = 0; cnt < 1000000; cnt++)
        {
            cc_dllst_push_back(test8_char, cnt);
            cc_dllst_push_back(test8_short, cnt);
            cc_dllst_push_back(test8_int, cnt);
            cc_dllst_push_back(test8_long_int, cnt);
            cc_dllst_push_back(test8_long_double, cnt);
        }

        cc_dllst_iter(iter, test8_char);

        cc_dllst_trav(test8_char, iter)
        {
            char var;

            if ((var = cc_dllst_iter_dref(iter)) > 0)
                printf("%d%c", var, (var != 127) ? ' ' : '\n');
            else if (var != 0)
                break;
        }

        cc_dllst_free(test8_char);
        cc_dllst_free(test8_short);
        cc_dllst_free(test8_int);
        cc_dllst_free(test8_long_int);
        cc_dllst_free(test8_long_double);
    }


    return 0;
}
