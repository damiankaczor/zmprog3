#include <iostream>
#include <cmath>

// Zmienne do wproawdzania z reki
int x,y;
// Klasa RobotStary (uklad prostokatny)
class RobotStary {
public:
    virtual void idzDo(double x, double y) {
        std::cout << "RobotStary: Ide do punktu (" << x << ", " << y << ") w ukladzie prostokatnym.\n";
    }
    virtual ~RobotStary() = default;
};

// Klasa RobotNowy (dane z katem)
class RobotNowy {
public:
    void idzDo(double kat, double odleglosc) {
        std::cout << "RobotNowy: Ide pod katem " << kat << " stopni na odleglosc " << odleglosc << ".\n";
    }
};

// Klasa AdapterRobota (dziedzicz¹ca po RobotStary)
class AdapterRobota : public RobotStary {
private:
    RobotNowy* robotNowy; // Obiekt nowego robota

public:
    // Konstruktor przyjmuj¹cy wskaŸnik na obiekt RobotNowy
    AdapterRobota(RobotNowy* nowyRobot) : robotNowy(nowyRobot) {}

    // Nadpisana metoda idzDo - przelicza wspó³rzêdne prostok¹tne na katy
    void idzDo(double x, double y) override {
        double kat = atan2(y, x) * (180.0 / M_PI); // Zamiana na stopnie
        double odleglosc = sqrt(x * x + y * y);    // Obliczenie odleg³oœci
        robotNowy->idzDo(kat, odleglosc);
    }
};

int main() {
    // Tworzenie instancji RobotNowy
    RobotNowy nowyRobot;

    // Tworzenie instancji AdapterRobota
    AdapterRobota adapter(&nowyRobot);

    // ----OKNO CMD
    std::cout << "Podaj mi dokad mam isc: [x y] ";
    std::cin >> x >> y;
    adapter.idzDo(x, y); // Punkt liczony dla uzytkownika
    std::cout << "Punkt wyliczony na sztywno: " << std::endl;
    adapter.idzDo(-5.0, 12.0); // Punkt (-5, 12)

    return 0;
}
