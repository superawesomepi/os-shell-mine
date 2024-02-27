#define MAXBUF 256  // max number of characters allowed on command line
#define CAPACITY 128 // max numbers of characters allowed in an argument

// TODO: Any global variables go below
//int thisIsGlobal = 10;  // delete before submission

// TODO: Function declarations go below
char** split(char *str, char *delim);
void modeOne(char **filepath);
void modeTwo(char **filepath, char **paths);
char* removeSpaces(char *cmdlineInput, char* output);

