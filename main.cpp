#include <iostream>
#include "Car.h"

void PrintMenu()
{
    std::cout << " 1 Generate new Car" << std::endl;
    std::cout << " 2 Print Car extension " << std::endl;
    std::cout << " 3 Save Car extension " << std::endl;
    std::cout << " 4 Load Car extension " << std::endl;
}

std::string gen_random(const int len) {
    static const char alphanum[] =
            "0123456789"
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (int i = 0; i < len; ++i) {
        tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
}

Car* GenerateCar()
{
    Car::CarType type;
    type.model_ = gen_random(5);
    type.brand_ = gen_random(6);
    std::string licence_plate = gen_random(10);
    std::uint64_t price = 100;
    return new Car(std::move(licence_plate), price, std::move(type));
}

void PrintCarExtension( std::ostream& os) {
    auto cars = Car::GetExtension();
    for (const auto & c : cars) {
        os << *c << std::endl;
    }
}

int main() {
    //std::vector<Car> current_cars;
    srand (time(NULL));
    GenerateCar();
    auto car2 = &Vehicle::GetFreeVehicle().value().get();
    delete car2;

    while(true) {
        PrintMenu();
        int option;
        std::cin >> option;

        switch (option) {
            case 1: {
                auto car = GenerateCar();
                std::cout <<" Generated Car: " << *car << std::endl;
                //current_cars.emplace_back(std::move(car));
                break;
            }
            case 2: {
                std::cout <<" Car extension: " << std::endl;
                PrintCarExtension(std::cout);
                break;
            }
            case 3: {
                Vehicle::WriteToFile("test");
                std::cout <<" Car extension Saved. " << std::endl;
                break;
            }
            case 4: {
                Vehicle::ReadFromFile("test");
                std::cout <<" Car extension Loaded. " << std::endl;
                break;
            }

        }
    }

}