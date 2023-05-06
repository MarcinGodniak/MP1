#include "Vehicle.h"

std::ostream& operator<< (std::ostream &out, const Vehicle & car)
{
    return out << "("
              << car.Print()
            <<")";

}

//static
std::optional<std::reference_wrapper<Vehicle>> Vehicle::GetFreeVehicle()
{
    std::optional<std::reference_wrapper<Vehicle>> ret;
    for ( const auto & c: Vehicle::GetExtension()) {
        if(!c->borrowed_to_.has_value()) {
            return *c;
        }
    }
    return ret;
}

std::string Vehicle::Print() const {
    return "license plate: " + license_plate_ + ", ";
}

const std::string &Vehicle::getLicensePlate() const {
    return license_plate_;
}

uint64_t Vehicle::getPrice() const {
    return price_;
}

const std::optional<std::reference_wrapper<const Client>> &Vehicle::getBorrowedTo() const {
    return borrowed_to_;
}

const std::vector<std::reference_wrapper<const Client>> &Vehicle::getPastRenters() const {
    return past_renters_;
}

Vehicle::Vehicle(std::string licensePlate, uint64_t price)
: license_plate_(std::move(licensePlate)),
price_(price)
{}

Vehicle::Vehicle(std::string licensePlate, uint64_t price, const Client& renter)
: license_plate_(std::move(licensePlate)),
  price_(price),
  borrowed_to_(renter)
  {}

Vehicle::Vehicle(const Vehicle &v) = default;
Vehicle::Vehicle() = default;

