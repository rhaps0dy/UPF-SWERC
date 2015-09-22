#include <stdio.h>
#include <string.h>

#define MAX_LINE 82

int
main() {
    char line[MAX_LINE], quine[MAX_LINE];
    int i;
    for(;;) {
	gets(line);
	if(!strcmp(line, "END"))
	    return 0;
	if(line[0] != '"')
	    goto noquine;
	for(i=1; (quine[i-1]=line[i]) && line[i] != '"'; i++);
	quine[i-1] = '\0';
	if(line[i] != '"' || line[i+1] != ' ')
	    goto noquine;
	if(strcmp(quine, line+i+2))
	    goto noquine;
	printf("Quine(%s)\n", quine);
	continue;
    noquine:
	puts("not a quine");
    }
    return 0;
}
