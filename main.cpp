#include "mbed.h"
#include "platform/mbed_thread.h"


//Définition de la partie Bluetooth
UnbufferedSerial bt(A0, A1); //TX, RX
UnbufferedSerial pc(USBTX, USBRX);

//Définition de la partie
PwmOut moteur1a_cc(PA_15);
PwmOut moteur1b_cc(PA_10);
PwmOut moteur2a_cc(PB_14);
PwmOut moteur2b_cc(PB_13);
PwmOut moteur3a_cc(PB_8);
PwmOut moteur3b_cc(PC_9);

int main() {
    //Partie Bluetooth
    char ch;
    char data[8];
    char str[64];

    bt.baud(9600);
    pc.baud(115200);

    // Test de la liaison, envoit OK sur TeraTerm
    sprintf(str, "TEST");
    pc.write(str, sizeof(str));

    //Définition de la partie mécanique
    moteur1a_cc.period_ms(10);
    moteur1a_cc.write(0);
    moteur1b_cc.period_ms(10);
    moteur1b_cc.write(0);

    moteur2a_cc.period_ms(10);
    moteur2a_cc.write(0);
    moteur2b_cc.period_ms(10);
    moteur2b_cc.write(0);

    moteur3a_cc.period_ms(10);
    moteur3a_cc.write(0);
    moteur3b_cc.period_ms(10);
    moteur3b_cc.write(0);

    double rc = 0.9;

    while(1)
    {
        if (bt.readable())
        {
            bt.read(&data, 1);
            pc.write(data, 1);
        }


        if (data[0] == 'B') {
            moteur1a_cc.write(0);
            moteur1b_cc.write(rc);

            moteur2a_cc.write(0);
            moteur2b_cc.write(rc);

            moteur3a_cc.write(0);
            moteur3b_cc.write(0);
        } else if (data[0] == 'F') {
            moteur1a_cc.write(rc);
            moteur1b_cc.write(0);

            moteur2a_cc.write(rc);
            moteur2b_cc.write(0);

            moteur3a_cc.write(0);
            moteur3b_cc.write(0);
        } else if (data[0] == 'R') {
            moteur1a_cc.write(0);
            moteur1b_cc.write(0);

            moteur2a_cc.write(rc);
            moteur2b_cc.write(0);

            moteur3a_cc.write(0);
            moteur3b_cc.write(rc);
        } else if (data[0] == 'L') {
            moteur1a_cc.write(0);
            moteur1b_cc.write(0);

            moteur2a_cc.write(0);
            moteur2b_cc.write(rc);

            moteur3a_cc.write(rc);
            moteur3b_cc.write(0);
        } else if (data[0] == 'S') {
            rc = 0.2;
            moteur1a_cc.write(rc);
            moteur1b_cc.write(0);

            moteur2a_cc.write(0);
            moteur2b_cc.write(rc);

            moteur3a_cc.write(0);
            moteur3b_cc.write(rc);
        }
        else if (data[0] == 'C') {
            rc = 0.2;
            moteur1a_cc.write(0);
            moteur1b_cc.write(rc);

            moteur2a_cc.write(rc);
            moteur2b_cc.write(0);

            moteur3a_cc.write(rc);
            moteur3b_cc.write(0);
        }else if (data[0] == 'T') {
            rc = 0.9;
        } else if (data[0] == 'X') {
            rc = 0.2;
        } else if (data[0] == 'P') {
            moteur1a_cc.write(0);
            moteur1b_cc.write(0);

            moteur2a_cc.write(0);
            moteur2b_cc.write(0);

            moteur3a_cc.write(0);
            moteur3b_cc.write(0);
        }
    }
}
