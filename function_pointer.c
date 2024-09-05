#include <stdio.h>

struct user
{
    int id;
    int (*operation)(int *, int, int);
};

void add(int *ret, int a, int b)
{
    *ret = a + b;
}

void subtract(int *ret, int a, int b)
{
    *ret = a - b;
}

int main()
{
    int a = 5;
    int b = 3;
    int ret;

    int (*fp)(int *, int, int);

    // No problem that ADD and SUBTRACT is defined at the same time

#ifdef ADD
    fp = add;
#endif
#ifdef SUBTRACT
    fp = subtract;
#endif

    (*fp)(&ret, a, b);
    printf("Ret value is %d\n", ret);

    /* Lets try to create some polymorphism */
    struct user user_1, user_2;
    struct user users[2];

    user_1.id = 0;
    user_1.operation = add;
    users[0] = user_1;

    user_2.id = 1;
    user_2.operation = subtract;
    users[1] = user_2;

    for (int i = 0; i < 2; i++)
    {
        users[i].operation(&ret, a, b);
        printf("Return value for user %d is %d\n", users[i].id, ret);
    }

    return 0;
}
