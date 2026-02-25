#include "agent_impl_2.h"

void scanSimu(void *args) {
    if (args) return;

    printf("Recherche de mot de passe...\n");
    if (system("ls /tmp/secret_hash.txt > /dev/null 2>&1") != 0) return;
}

void exploitSimu(void *args) {
    if (args) return;

    printf("Cassage du hash avec hashcat (simule)...\n");
    if (system("sleep 1 && echo 'Password cracked: 123456'") != 0) return;
}

void escalationSimu(void *args) {
    if (args) return;

    printf("Tentative de sudo...\n");
    printf("Accès ROOT accordé.\n");
}

void exfiltrationSimu(void *args) {
    if (args) return;

    printf("Recuperation de la cible...\n");
    if (system("curl -s http://google.com | head -n 1") != 0) return;
}


int generateCyberSimpleMatrices(RLState *sArray, RLAction*aArray,
                                   float **T, float **R) {
    if (sArray == NULL || aArray == NULL) return -1;

    return readMatricesFromFile("files/matrices_cyber.txt", T, R);
}
