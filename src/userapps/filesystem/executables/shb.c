void shb_echo(char* arg) {
    if (arg) kprintf("%s\n", arg);
}

void shb_alert(char* arg) {
    // Hier käme dein !alert id = warnbox Logik rein
    kprintf("[SHB-SECURITY] ALERT TRIGGERED: %s\n", arg ? arg : "Generic Error");
}

void shb_exit(char* arg) {
    kprintf("Leaving SHB... bye loser.\n");
}
