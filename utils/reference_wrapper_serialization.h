#ifndef MP1_REFERENCE_WRAPPER_SERIALIZATION_H
#define MP1_REFERENCE_WRAPPER_SERIALIZATION_H

#include <functional>

/////////////////////////////////////////////////
//https://stackoverflow.com/questions/30286437/reference-wrapper-to-abstract-class-serialization-in-boost
// Allow serialization of `reference_wrapper`
namespace boost { namespace serialization {
        template<class Ar, class T> void save_construct_data(Ar & ar, std::reference_wrapper<T> const * t, unsigned) {
            T const * p = &t->get();
            ar << p;
        }
        template<class Ar, class T> void load_construct_data(Ar & ar, std::reference_wrapper<T> * t, unsigned) {
            T* p = nullptr;
            ar >> p;
            ::new(t) std::reference_wrapper<T>(*p);
        }

        template <class Ar, typename T> inline void serialize(Ar &, std::reference_wrapper<T>&, unsigned) { }
    } }

#endif //MP1_REFERENCE_WRAPPER_SERIALIZATION_H
