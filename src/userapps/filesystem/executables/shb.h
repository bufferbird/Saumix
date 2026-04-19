#ifndef SHB_H
#define SHB_H

void shb_exit(char* arg);
void shb_alert(char* arg);
void shb_echo(char* arg);

typedef struct{
    char* name;
    void (*func)(char* arg);
} SHB_Command;

SHB_Command cmd_table[] = {
    {"echo",   shb_echo},
    {"!alert", shb_alert},
    {"exit",   shb_exit},
    {NULL,     NULL} // Ende der Liste
};

#endif
