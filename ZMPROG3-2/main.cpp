#include <iostream>
#include <memory>
#include <string>

// Klasa bazowa Robot (interfejs robota)
class Robot {
public:
    virtual void operacja() const = 0; // Wirtualna metoda do wykonywania operacji
    virtual ~Robot() = default;       // Wirtualny destruktor
};

// Klasa RobotPodstawowy (konkretny robot)
class RobotPodstawowy : public Robot {
public:
    void operacja() const override
    {
        std::cout << "Robot porusza sie." << std::endl;
    }
};

// Klasa abstrakcyjna RobotDekorator (dekorator)
class RobotDekorator : public Robot {
protected:
    std::unique_ptr<Robot> robot; // WskaŸnik na dekorowany obiekt (robot)

public:
    // Konstruktor przyjmuj¹cy wskaŸnik na bazowego robota
    explicit RobotDekorator(std::unique_ptr<Robot> r) : robot(std::move(r)) {}

    // Wywo³anie operacji bazowego robota
    void operacja() const override {
        robot->operacja();
    }
};

// Klasa RobotKamera ---> dodawanie kamery
class RobotKamera : public RobotDekorator {
public:
    explicit RobotKamera(std::unique_ptr<Robot> r) : RobotDekorator(std::move(r)) {}

    void operacja() const override {
        robot->operacja(); // Wywo³anie operacji bazowego robota
        std::cout << "Robot ma kamere." << std::endl;
    }
};

// Klasa RobotTemp --> dodawanie temperatury
class RobotTemp : public RobotDekorator {
public:
    explicit RobotTemp(std::unique_ptr<Robot> r) : RobotDekorator(std::move(r)) {}

    void operacja() const override {
        robot->operacja(); // Wywo³anie operacji bazowego robota
        std::cout << "Robot ma czujnik temperatury." << std::endl;
    }
};

// Klasa RobotHIFI --> dodawanie systemu hifi
class RobotHIFI : public RobotDekorator {
public:
    explicit RobotHIFI(std::unique_ptr<Robot> r) : RobotDekorator(std::move(r)) {}

    void operacja() const override {
        robot->operacja(); // Wywo³anie operacji bazowego robota
        std::cout << "Robot ma system Hi-FI." << std::endl;
    }
};

int main() {
    int x;
    // Wyswietlanie menu informacyjnego
    std:: cout << "Menu: "<< std::endl << "1. Kamera"<< std::endl << "2. Termometr"<< std::endl << "3. Hi-Fi" <<std::endl  << "4. Pakiet Luxury - wszystko" <<std::endl;
    std:: cout << "Co chcesz dodac: " ;
    // Wpisujemy wybor
    std:: cin >> x;
    // Tworzenie podstawowego robota
    std::unique_ptr<Robot> robot = std::make_unique<RobotPodstawowy>();

    //Switch case do wybrania opcji: 1-Kamera, 2-Termometr, 3-Hihi, 4 - wszystko do tesu.
    switch(x)
    {

        case 1:
            // Dodanie kamery
            robot = std::make_unique<RobotKamera>(std::move(robot));
        break;
        case 2:
            // Dodanie czujnika temperatury
            robot = std::make_unique<RobotTemp>(std::move(robot));
        break;
        case 3:
            // Dodanie hiFI
            robot = std::make_unique<RobotHIFI>(std::move(robot));
        break;
        case 4:
            std:: cout << "Luxury:" << std::endl;
            robot = std::make_unique<RobotKamera>(std::move(robot));
            robot = std::make_unique<RobotTemp>(std::move(robot));
            robot = std::make_unique<RobotHIFI>(std::move(robot));
        break;
    }
    // Wywo³anie operacji (robot z wszystkimi funkcjonalnoœciami)
    robot->operacja();

    return 0;
}
