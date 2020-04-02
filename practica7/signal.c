#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void processSignal(int s) {
    if(s == 15) {
        printf("No me puedes matar %d\n", s);
    } else {
        printf("Recibí señal %d\n", s);
    }
}

int main() {
    signal(10, processSignal);
    signal(15, processSignal);
    while(1) {
        sleep(3);
        printf("Trabajando\n");
    }
    return 1;
}
