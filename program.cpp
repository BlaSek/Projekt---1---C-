#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <cstdlib>
using namespace std;

void wyczyscEkran()
{
    system("cls");
}
void interfejs()
{
    cout << "*************************************************" << endl;
    cout << "Program obliczajacy calke zlozona metoda trapezow" << endl;
    cout << "*************************************************" << endl;
}
void definicja()
{
cout << "**********************************************************************************************************************************" << endl;
cout << "Metoda trapezow daje dosc dokladne wyniki calkowania, szczegolnie przy duzej dokladnosci podzialu danego przedzialu na N trapezow.\nPolega ona na podzieleniu obszaru calkowanego na N trapezow (przedzialow), ktorych pola na koncu sumuje sie."<<endl;
cout << "**********************************************************************************************************************************" << endl;
}
int error()
{
    wyczyscEkran();
    cout << "Niepoprawna opcja. Program konczy dzialanie." << endl;
    return 0;
}
int koniec()
{
    wyczyscEkran();
    cout << "Zakonczono dzialanie programu." << endl;
    return 0;
}
int opcja()
{
    int opcja;
    cin >> opcja;
    return opcja;
}
int MenuProgramu()
{
    int opcja;
    do {
        cout << "Prosze o wybranie jednej opcji z ponizszej listy:" << endl;
        cout << "1 = Przejdz do opcji obliczania calki." << endl;
        cout << "2 = Wyswietl na czym polega metoda trapezow." << endl;
        cout << "3 = Wyswietl historie calkowanych funkcji." << endl;
        cout << "4 = Zakoncz program" << endl;
        cout << "*************************************************" << endl;
        cout << "Wybrana opcja = ";
        cin >> opcja;
        if (opcja < 1 || opcja > 4)
        {
            wyczyscEkran();
            cout << "\nNieprawidlowy wybor. Prosze podac poprawna opcje.\n"
                 << endl;
        }
        else if (opcja == 2)
        {
            wyczyscEkran();
            definicja();
            cout << "Wybierz opcje:" << endl;
            cout << "3 = Wroc do menu glownego." << endl;
            cout << "4 = Zakoncz program." << endl;
            cin >> opcja;
            if (opcja == 3)
            {
                wyczyscEkran();
                return MenuProgramu();
            }
            else if (opcja == 4)
            {
                return koniec();
            }
            else
            {
                return error();
            }
        }
    } while (opcja < 1 || opcja > 4);
    return opcja;
}
int wybierzCalke()
{
    int opcja;
    cout << "***********************************" << endl;
    cout << "Wybierz funkcje do obliczenia calki" << endl;
    cout << "1. x+2" << endl;
    cout << "2. x^2" << endl;
    cout << "3. x^2+2" << endl;
    cout << "4. (x+2)*pierwiastek(x^2+2)" << endl;
    cout << "5. sin(x)" << endl;
    cout << "6. cos(x)" << endl;
    cout << "***********************************" << endl <<endl;
    cout << "Wybrana funkcja = ";
    cin >> opcja;
        if (opcja < 1 || opcja > 6)
        {
            wyczyscEkran();
            cout << "\nNieprawidlowy wybor. Prosze podac poprawna opcje.\n" << endl;
            return wybierzCalke();
        }else
        {
        return opcja;
        }
}
void wyswietlHistorie()
{
    ifstream plik("wyniki.txt");
    if (plik.is_open())
        {
        string linia;
        while (getline(plik, linia))
        {
            cout << linia << endl;
        }
        plik.close();
        } else
    {
        cout << "Nie udalo sie otworzyc pliku 'wyniki.txt'." << endl;
    }
}
double ktoraFunkcja(double x, int opcja)
{
    switch(opcja)
    {
        case 1:
            return x + 2;
        case 2:
            return pow(x, 2);
        case 3:
            return pow(x, 2) + 2;
        case 4:
            return (x+2)*sqrt(pow(x,2)+2);
        case 5:
            return sin(x);
        case 6:
            return cos(x);
        default:
            return 0;
    }
}
    double pole(int opcja, int dokladnosc, double x1, double x2)
    {
    double wysokosc = (x2 - x1) / (double)dokladnosc; //wys pojedynczego trapezu
    double sumaTrapezow = 0;
    double PrawaKrawedz = 0, LewaKrawedz = ktoraFunkcja(x1, opcja);
    int i = 0;
    while (i <= dokladnosc)
        {
        PrawaKrawedz = ktoraFunkcja(x1 + wysokosc*i, opcja);
        sumaTrapezow = sumaTrapezow + (LewaKrawedz + PrawaKrawedz);
        LewaKrawedz = PrawaKrawedz;
        i++;
        }
    return (sumaTrapezow*wysokosc)/2 ;
    }
string nazwaWielomianu(int opcja)
{
    switch(opcja)
    {
        case 1:
            return "x + 2";
        case 2:
            return "x^2";
        case 3:
            return "x^2 + 2";
        case 4:
            return "(x+2)*pierwiastek(x^2+2)";
        case 5:
            return "sin(x)";
        case 6:
            return "cos(x)";
        default:
            return "Nieznany wielomian";
    }
}
void zapiszWynik(int opcja, int dokladnosc, double x1, double x2, double wynik)
{
    ofstream file;
    file.open("wyniki.txt", ios_base::app);
    file << "*****************************************************" << endl;
    file << "Wynik dla wielomianu " << opcja << ": " << nazwaWielomianu(opcja) << endl;
    file << "Wartosc calki zaokraglona do czesci dziesietnych:" << fixed << setprecision(1) << wynik << endl;
    file << "Przedzial <x1 ; x2>: [" << x1 << " ; " << x2 << "]" << endl;
    file << "Dokladnosc(ilosc trapezow w calkowaniu): " << dokladnosc << endl;
    file.close();
}
int calka()
{
    int opcja, opcja2, dokladnosc;
    double x1, x2;
    do {
        wyczyscEkran();
        opcja = wybierzCalke();
        if (opcja > 0 && opcja < 10)
            {
            cout << "****************************************************************" << endl;
            cout << "Podaj przedzial <x1 ; x2> (Warunek: x1<x2):" << endl;
            cout << "(x1) = ";
            cin >> x1;
            cout << "(x2) = ";
            cin >> x2;
            if (x1 >= x2)
            {
                cout << "****************************************************************" << endl;
                cout << "Podano nieprawidlowy przedzial." << endl;
                cout << "Czy chcesz wrocic do poczatku?" << endl;
                cout << "1 = Tak \t 2 = Nie." << endl;
                cin >> opcja2;
            } else {
                cout << "Podaj dokladnosc N (Warunek: N = liczba calkowita wieksza od 0):" << endl ;
                cout << "Dokladnosc (N) = ";
                cin >> dokladnosc;
                if (dokladnosc <= 0)
                {
                    cout << "Podano nieprawidlowa wartosc podzialu." << endl;
                    cout << "Wpisz prawidlowa wartosc." << endl;
                    cout << "Dokladnosc (N) = ";
                    cin >> dokladnosc;
                }
                double wynik = pole(opcja, dokladnosc, x1, x2);
                cout << "Wartosc calki zaokraglona do czesci dziesietnych: " << fixed << setprecision(1) << wynik << endl;
                cout << "Czy chcesz zapisac wynik do pliku 'wyniki.txt'? (1 = Tak, 2 = Nie): ";
                cin >> opcja2;
                if (opcja2 == 1)
                {
                    zapiszWynik(opcja, dokladnosc, x1, x2, wynik);
                    cout << "Wynik zostal zapisany do pliku 'wyniki.txt'." << endl;
                }
                cout << "Czy chcesz wrocic do poczatku?" << endl;
                cout << "1 = Tak \t 2 = Nie." << endl;
                cout << "Wybor = ";
                cin >> opcja2;
            }
        } else {
            wyczyscEkran();
            cout << "Niepoprawny wybor. Wybierz ponownie poprawna opcje." << endl;
            cout << "Wybor = ";
            cin >> opcja;
        }
    } while (opcja2 != 2);
    cout << "**************************************************" << endl;
    cout << "\nProgram zakonczyl dzialanie.\nWyniki zapisano do pliku 'wyniki.txt'." << endl;
    cout << "**************************************************" << endl;
    return 0;
}
