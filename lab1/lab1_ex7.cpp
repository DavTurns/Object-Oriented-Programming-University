#include <iostream>

using namespace std;

bool istprimzahl(int zahl) {
    //Hilfsfunktion von teilaufgabe_a

    int i = 2;
    while (i < zahl / 2) {
        if (zahl % i == 0) return false;
        i++;
    }
    return true;
}

void teilaufgabe_a() {
    /*
    Zerlege eine gegebene gerade natürliche Zahl, größer als 2, 
    als Summe zweier Primzahlen (Goldbachs Vermutung)
    */
    int input1;

    cout << "Geben Sie eine Zahl ein ,die gerade und größer als 2 ist (Floats verlieren Dezimalteil): ";
    while (true) {
        cin >> input1;
        if (input1 > 2 and input1 % 2 == 0) break;
        cout << "Eingabe undgültig, versuchen Sie es erneut";
    }

    for (int erstersummand = 2; erstersummand < input1; erstersummand++) {

        if (istprimzahl(erstersummand) == true) {

            for (int zweitersummand = 2; zweitersummand < input1; zweitersummand++) {

                if (istprimzahl(zweitersummand) == true and zweitersummand + erstersummand == input1) {
                    cout << "Erste Primzahl:" << erstersummand << "Zweite Primzahl" << zweitersummand << "\n\n";
                    return;
                }
            }
        }
    }
}


bool verschiedene_ziffern_gemeinsam(int zahl1_input, int zahl2_input) {
    /*
    Hilfsfunktion für teilaufgabe_b

    in: Zwei zahlen, deren ziffern verglichen werden
    out: true - wenn mindestens zwei verschiedene Ziffern gemeinsam
         false - sonst
    
    */

    //zahl1 in Bestandteile aufteilen
    int zahl2_tmp;
    int ziffer1;
    int ziffer2;

    do {
        ziffer1 = zahl1_input % 10;
        zahl2_tmp = zahl2_input;
        do {
            ziffer2 = zahl2_tmp % 10;

            //cout << "ziffer1: " << ziffer1 << ", ziffer2: " << ziffer2 << "\n"; 
            if (ziffer1 == ziffer2) return true;

            zahl2_tmp = zahl2_tmp / 10;
        } while (zahl2_tmp != 0);

        zahl1_input = zahl1_input / 10;
    } while (zahl1_input != 0);
    return false;
}

void teilaufgabe_b() {
    /*
    Bei einem Vektor aus Zahlen finden Sie die längste zusammenhängende Teilfolge, 
    so dass alle aufeinanderfolgenden Elemente mindestens zwei verschiedene Ziffern gemeinsam haben
    */
    int len_zahlenfolge = 20;
    int zahlenfolge[len_zahlenfolge];

    //wir setzen das letzte Element in der zahlenfolge 0 damit wir sicher am Ende Reihe eine 0 haben
    zahlenfolge[len_zahlenfolge - 1] = 0;


    //Zahlenfolge eingeben
    cout << "Geben Sie die Zahlenreihe ein, beenden Sie die Eingabe mit 0: ";
    for (int i = 0; i < len_zahlenfolge - 1; i++) {
        cin >> zahlenfolge[i];
        if (zahlenfolge[i] == 0) break;
    }

    //folgende Variablen sind wichtige für das ermitteln, ob noch zwei Ziffern der aktuellen Zahl gemeinsam sind mit 
    int liste_mit_gemeinsamen_ziffern[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int zahl_tmp;
    int ziffer;
    int zähler_für_jede_ziffer;
    int ziffer_gefunden;

    int counter_für_gemeinsame_ziffern;


    //folgende Variablen sind wichtig für das Herausfinden der längsten Sequenz

    int start_index = 0;
    int end_index = 0;

    int start_index_max_seq = 0;
    int end_index_max_seq = 0;
    int max_len = 0;

    //berechne Ergebnis
    for (int i = 0; zahlenfolge[i] != 0; i++) {
        //liste_mit_gemeinsamen_ziffern aktualisieren
        /*
        wir gehen die große zahlenfolge durch
        für jede gemeinsame ziffer
            nehmen wir von der zahl jede ziffer
            und schauen ob sie identisch sind, 
            wenn nichts gefunden, wird die aktuelle gemeinsame ziffer als -1 markiert
        */

        for (int j = 0; j < 10; j++) {
            zahl_tmp = zahlenfolge[i];
            ziffer_gefunden = 0;
            zähler_für_jede_ziffer = 0;

            do {
                ziffer = zahl_tmp % 10;
                if (ziffer == liste_mit_gemeinsamen_ziffern[j]) {
                    ziffer_gefunden = 1;
                }
                zahl_tmp = zahl_tmp / 10;
                zähler_für_jede_ziffer++;
            } while (zahl_tmp != 0);

            if (ziffer_gefunden == 0) {
                liste_mit_gemeinsamen_ziffern[j] = -1;
            }
        }

        counter_für_gemeinsame_ziffern = 0;
        for (int i = 0; i < 10; i++) {
            if (liste_mit_gemeinsamen_ziffern[i] != -1) {
                counter_für_gemeinsame_ziffern++;
            }
        }

        if (counter_für_gemeinsame_ziffern > 1) {
            end_index = i;
        } else {

            if (end_index - start_index > max_len) {
                start_index_max_seq = start_index;
                end_index_max_seq = end_index;
                max_len = end_index - start_index;
            }
            start_index = i;

            for (int j = 0; j < 10; j++) liste_mit_gemeinsamen_ziffern[j] = j;

            // neue reihe anfangen
            for (int j = 0; j < 10; j++) {
                zahl_tmp = zahlenfolge[i];
                ziffer_gefunden = 0;
                zähler_für_jede_ziffer = 0;

                do {
                    ziffer = zahl_tmp % 10;
                    if (ziffer == liste_mit_gemeinsamen_ziffern[j]) {
                        ziffer_gefunden = 1;
                    }
                    zahl_tmp = zahl_tmp / 10;
                    zähler_für_jede_ziffer++;
                } while (zahl_tmp != 0);

                if (ziffer_gefunden == 0) {
                    liste_mit_gemeinsamen_ziffern[j] = -1;
                }
            }
        }
        if (end_index - start_index > max_len) {
            start_index_max_seq = start_index;
            end_index_max_seq = end_index;
            max_len = end_index - start_index;
        }
    }

    //Ergebnis wird ausgegeben
    cout << "Die längste Subsequenz ist: ";
    for (int i = start_index_max_seq; i <= end_index_max_seq; i++) {
        cout << zahlenfolge[i] << ", ";
    }
}

int main() {
    teilaufgabe_a();
    teilaufgabe_b();
    system("pause");
    return 0;
}