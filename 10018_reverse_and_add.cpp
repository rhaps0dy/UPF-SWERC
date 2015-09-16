#include <iostream>

#define num unsigned long

int
length(num n)
{
    int ten = 10, i = 1;
    for(; n >= ten; i++)
        ten *= ten;
    return i;
}

bool
is_palindrome(num n)
{
    int l = length(n);
}

int
main()
{
    return 0;
}
