#include "program.cpp"

int main() {
    int opcja = 0;
    interfejs();
    while (opcja != 4) {
        opcja = MenuProgramu();
        switch (opcja) {
            case 1:
                calka();
                break;
            case 2:
                definicja();
                break;
            case 3:
                wyswietlHistorie();
                break;
            case 4:
                koniec();
                break;
            default:
                error();
                break;
        }
    }
    return 0;
}
