#include "Car.h"

std::string Car::Print() const {
    return "Car: type: " + type_.brand_ + " " + type_.model_ + " , " + Vehicle::Print();
}

Car::Car() = default;

Car::Car(const Car &c)
: Vehicle(c),
type_(c.type_)
{

}

const Car::CarType &Car::getType() const {
    return type_;
}

Car::Car(std::string licensePlate, uint64_t price, Car::CarType type) : Vehicle(std::move(licensePlate), price),
                                                                                      type_(std::move(type)) {}

BOOST_CLASS_EXPORT_IMPLEMENT(Car)