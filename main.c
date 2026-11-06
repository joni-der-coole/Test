#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PAYLOAD_PATH "/data/payloads/linux.bin"

// Funktion zum Laden und Vorbereiten des Payloads
void execute_payload(const char *filepath) {
    FILE *f = fopen(filepath, "rb");
    if (!f) {
        printf("Fehler: Konnte '%s' nicht öffnen.\n", filepath);
        return;
    }

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *buffer = malloc(fsize);
    if (!buffer) {
        printf("Fehler: Konnte keinen Speicher für den Payload zuweisen.\n");
        fclose(f);
        return;
    }

    fread(buffer, 1, fsize, f);
    fclose(f);

    printf("Payload erfolgreich geladen: %s (%ld Bytes)\n", filepath, fsize);

    // Hier wird der Payload in den Speicher übergeben und ausgeführt 
    // (z.B. per Kernel-Exec oder Socket-Weiterleitung, je nach deinem Setup)

    free(buffer);
}

int main(int argc, char *argv[]) {
    // Prüfen, ob die Datei 'linux.bin' im Pfad existiert und lesbar ist
    if (access(PAYLOAD_PATH, F_OK) != 0) {
        printf("Fehler: Die Datei '%s' wurde nicht gefunden. Beende App.\n", PAYLOAD_PATH);
        return 1; // Beendet die App sauber, kein Crash
    }

    printf("Datei gefunden. Starte Ladevorgang...\n");
    execute_payload(PAYLOAD_PATH);

    return 0;
}
