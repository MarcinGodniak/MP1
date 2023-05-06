#ifndef MP1_CAR_H
#define MP1_CAR_H

#include "Vehicle.h"
#include <boost/serialization/export.hpp>

class Car : public Vehicle{
private:
    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & boost::serialization::base_object<Vehicle>(*this);
        ar & type_.brand_;
        ar & type_.model_;
    }

public:
    struct CarType {
        std::string brand_;
        std::string model_;
    };

private:
    //atrybut zlozony
    CarType type_;
public:
    [[nodiscard]] const CarType &getType() const;

public:
    Car();
    Car(const Car&);
    Car(std::string licensePlate, uint64_t price, CarType type);

    //Przesłonięcie
    [[nodiscard]] std::string Print() const override;
};

BOOST_CLASS_EXPORT_KEY(Car)

#endif //MP1_CAR_H
