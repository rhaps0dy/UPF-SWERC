#include <stdio.h>

static int
perform(char *number, int i) {
    int next = 1;
    while(i--)
	next *= number[i] - '0';
    i = sprintf(number, "%d", next);
    fputs(number, stdout);
    return i;
}


int
main() {
    int length;
    char number[7];

    for(;;) {
	scanf("%s", number);
	if(number[0] == '0' && number[1] == '\0')
	    break;
	fputs(number, stdout);
	/* if len of number is 1 */
	if(number[1] == '\0') {
	    putchar('\n');
	    continue;
	}

	/* set length */
	for(length=0; number[length]; length++);

	/* print the steps */
	while(length > 1) {
	    putchar(' ');
	    length = perform(number, length);
	}
	putchar('\n');
    }
    return 0;
}
