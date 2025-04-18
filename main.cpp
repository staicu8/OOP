#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
#include <cstddef>


#include "Hotel.h"
#include "TipCamera.h"
#include "Client.h"
#include "Angajat.h"

void clearInputBuffer() {

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


void afiseazaMeniu() {
    std::cout << "\n========== Meniu Gestiune Hotel (Simplificat C++98) ==========\n";
    std::cout << " 1. Adauga Camera\n";
    std::cout << " 2. Adauga Client\n";
    std::cout << " 3. Adauga Angajat\n";
    std::cout << " 4. Creeaza Rezervare\n";
    std::cout << " 5. Anuleaza Rezervare\n";
    std::cout << " 6. Marcheaza Rezervare ca Platita\n";
    std::cout << " 7. Afiseaza Toate Camerele\n";
    std::cout << " 8. Afiseaza Camerele Libere\n";
    std::cout << " 9. Afiseaza Camerele Ocupate\n";
    std::cout << "10. Afiseaza Clientii\n";
    std::cout << "11. Afiseaza Angajatii\n";
    std::cout << "12. Afiseaza Toate Rezervarile\n";
    std::cout << "13. Afiseaza Rezervarile unui Client (dupa CNP)\n";
    std::cout << "14. Calculeaza si Afiseaza Venit Total\n";
    std::cout << "15. Afiseaza Detalii Hotel \n";
    std::cout << " 0. Iesire\n";
    std::cout << "============================================================\n";
    std::cout << "Alegeti o optiune: ";
}

int main() {
    std::cout << std::fixed << std::setprecision(2);

    Hotel hotelPrincipal("Staicu's Hotel", "Strada Grozavesti", 5);
    std::cout << "Bun venit la sistemul de gestiune pentru " << hotelPrincipal.getNume() << "!" << std::endl;
    TipCamera tipSingle("Single", 1, false, false);
    TipCamera tipDouble("Double", 2, true, false);
    TipCamera tipApartament("Apartament", 4, true, true);

    hotelPrincipal.adaugaCamera(new Camera(101, 250.00, false, tipSingle, 1));
    hotelPrincipal.adaugaCamera(new Camera(201, 400.00, false, tipDouble, 2));
    hotelPrincipal.adaugaCamera(new Camera(301, 750.00, false, tipApartament, 3));

    hotelPrincipal.adaugaClient(new Client("Popescu", "Ion", "1900101123456", 34));
    hotelPrincipal.adaugaClient(new Client("Ionescu", "Andreea", "2950302654321", 29));

    //Downcasting
    Persoana* cl=new Client("Mircea","Andrei","2219910000121",20);
    hotelPrincipal.adaugaClient(static_cast<Client*> (cl));

    Persoana* ang=new Angajat("Mihai","Raul","200019988271",45,"Barman",7000,10);
    hotelPrincipal.adaugaAngajat(static_cast<Angajat*> (ang));
    hotelPrincipal.adaugaAngajat(new Angajat("Staicu", "Octavian", "1801122000000", 50, "Manager", 8500.00, 20));


    int optiune;
    do {



        afiseazaMeniu();

        while (!(std::cin >> optiune)) {
            std::cerr << "Input invalid. Introduceti un numar: ";
            std::cin.clear();
            clearInputBuffer();
        }
        clearInputBuffer();
        switch (optiune) {
            case 1: { // Adauga Camera
                Camera* pCamNoua = new Camera();
                std::cout << "\n--- Adaugare Camera Noua ---\n";
                std::cin >> (*pCamNoua);
                hotelPrincipal.adaugaCamera(pCamNoua);

                break;
            }
             case 2: { // Adauga Client
                Client* pClientNou = new Client();
                std::cout << "\n--- Adaugare Client Nou ---\n";
                std::cin >> (*pClientNou);

                hotelPrincipal.adaugaClient(pClientNou);


                break;
            }
             case 3: { // Adauga Angajat
                 Angajat* pAngajatNou = new Angajat();
                 std::cout << "\n--- Adaugare Angajat Nou ---\n";
                 std::cin >> (*pAngajatNou);
                  if(!std::cin) {
                    std::cerr << "Eroare la citirea datelor angajatului!" << std::endl;
                    delete pAngajatNou;
                    std::cin.clear();
                    clearInputBuffer();
                 } else {
                    hotelPrincipal.adaugaAngajat(pAngajatNou);

                 }
                 break;
            }
           case 4: { // Creeaza Rezervare
                std::string cnp, dataIn, dataOut; int nrCam = 0, nrZile = 0; // Initializam numerele
                std::cout << "\n--- Creare Rezervare ---\n";
                std::cout << "CNP client: ";

               std::cin >> cnp;
                clearInputBuffer();

                std::cout << "Nr camera: ";

                std::cin >> nrCam;
                clearInputBuffer();

                std::cout << "Data In (YYYY-MM-DD): ";
                std::cin >> dataIn;
                clearInputBuffer();

                std::cout << "Data Out (YYYY-MM-DD): ";
                 std::cin >> dataOut;
                clearInputBuffer();
                std::cout << "Nr zile: ";
               std::cin >> nrZile;
                clearInputBuffer();


                int idRez = hotelPrincipal.creeazaRezervare(cnp, nrCam, dataIn, dataOut, nrZile);
                if (idRez == -1) {
                     std::cout << "Crearea rezervarii a esuat (verificati datele introduse)." << std::endl;
                } else {
                     const Rezervare* r = hotelPrincipal.gasesteRezervare(idRez);
                     if(r != 0) std::cout << "\nRezervare creata:\n" << *r << std::endl;
                 }
                break;
            }
            case 5: { // Anuleaza Rezervare
                int idRez = 0;
                std::cout << "\n--- Anulare Rezervare ---\nID Rezervare: ";
              std::cin >> idRez;
                clearInputBuffer();

                if (!hotelPrincipal.anuleazaRezervare(idRez)) {
                    std::cout << "Anularea rezervarii a esuat." << std::endl;
                } else {
                    std::cout << "Rezervare ID " << idRez << " anulata.\n";
                }
                break;
            }
            case 6: { // Marcheaza Platita
                int idRez = 0;
                std::cout << "\n--- Marcare Platita ---\nID Rezervare: ";
               std::cin >> idRez;
                clearInputBuffer();
                Rezervare* r = hotelPrincipal.gasesteRezervare(idRez);
                if (r != 0) {
                    r->setPlatita(true);
                    std::cout << "Rezervare ID " << idRez << " marcata ca platita.\n";
                } else {
                    std::cout << "Rezervare ID " << idRez << " negasita.\n";
                }
                break;
            }

            case 7: hotelPrincipal.afisareCamere(); break;
            case 8: hotelPrincipal.afisareCamereLibere(); break;
            case 9: hotelPrincipal.afisareCamereOcupate(); break;
            case 10: hotelPrincipal.afisareClienti(); break;
            case 11: hotelPrincipal.afisareAngajati(); break;
            case 12: hotelPrincipal.afisareRezervari(); break;
            case 13: {
                std::string cnp;
                std::cout << "\n--- Afisare Rezervari Client ---\nCNP: ";
                std::cin>>cnp;
                clearInputBuffer();
                hotelPrincipal.afisareRezervariClient(cnp);
                break;
            }


             case 14: {
                 double venit = hotelPrincipal.calculeazaVenitTotal();
                 std::cout << "\n--- Venit Total Actual ---\n" << venit << " RON\n------------------------\n";
                 break;
             }
             case 15: std::cout << "\n--- Detalii Hotel  ---\n" << hotelPrincipal << "\n---------------------------\n"; break;
            case 0:
                std::cout << "Iesire din program...\n";
                break;
            default:
                std::cout << "Optiune invalida. Incercati din nou.\n";
                break;
        }


    } while (optiune != 0);

    std::cout << "Programul s-a incheiat." << std::endl;
    return 0;
}