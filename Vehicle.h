#ifndef MP1_VEHICLE_H
#define MP1_VEHICLE_H

#include "utils/Extension_owning.h"
#include "Client.h"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <cmath>
#include <optional>

class Vehicle : public ExtensionOwning<Vehicle>
{
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & license_plate_;
    }

    //atrybut klasowy
    static constexpr double VAT = 0.23;

    std::string license_plate_;
    std::uint64_t price_;

    //atrybut opcjonalny
    std::optional<std::reference_wrapper<const Client>> borrowed_to_;

    //atrybut powtarzalny
    std::vector<std::reference_wrapper<const Client>> past_renters_;

public:
    Vehicle();
    Vehicle(const Vehicle& v);
    Vehicle(std::string licensePlate, uint64_t price);
    Vehicle(std::string licensePlate, uint64_t price, const Client& renter);

    [[nodiscard]] const std::string &getLicensePlate() const;

    [[nodiscard]] std::uint64_t getPrice() const;

    [[nodiscard]] const std::optional<std::reference_wrapper<const Client>> &getBorrowedTo() const;

    [[nodiscard]] const std::vector<std::reference_wrapper<const Client>> &getPastRenters() const;

    //atrybut wyliczalny
    [[nodiscard]] std::uint64_t GetFullPrice() const {
        return std::round(price_ * (1+ VAT));
    }

    //Przeciążenie
    [[nodiscard]] std::uint64_t GetFullPrice(double discount) const {
        return std::max(std::uint64_t {0}, static_cast<std::uint64_t>(std::round(price_ * (1-discount) * (1+ VAT))));
    }

    //metoda klasowa
    static std::optional<std::reference_wrapper<Vehicle>> GetFreeVehicle();

    //Przesłonięcie
     [[nodiscard]] virtual std::string Print() const;

};

std::ostream& operator<< (std::ostream &out, const Vehicle& c);

#endif //MP1_VEHICLE_H
