#ifndef MP1_EXTENSION_OWNING_H
#define MP1_EXTENSION_OWNING_H


#include <list>
#include <functional>
#include <boost/serialization/access.hpp>
#include <filesystem>
#include <boost/archive/text_oarchive.hpp>
#include <fstream>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include "reference_wrapper_serialization.h"



template <typename T>
class ExtensionOwning : public std::enable_shared_from_this<ExtensionOwning<T>>
{
public:
    using container_t = std::list<T*>;
private:
    //used type needs iterators that are not invalidated during push_back and erase
    //would be nice to write some concept / static_assert to check that
    static container_t ext_list_;
    using iterator = container_t::const_iterator;
    iterator it;

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & ext_list_;
    }

    void Register() {
        ext_list_.push_back(static_cast<T*>(this));
        it = std::prev(ext_list_.end());
    }

public:
    static const container_t& GetExtension() {
        return ext_list_;
    }

    explicit ExtensionOwning() {
        Register();
    }

    ExtensionOwning( const ExtensionOwning<T> &) {
        Register();
    }

    virtual ~ExtensionOwning()
    {
        ext_list_.erase(it);
    }

    static void WriteToFile(const std::filesystem::path& path)
    {
        std::ofstream ofs(path);
        boost::archive::text_oarchive oa(ofs);
        oa << ext_list_;
    }

    static void ReadFromFile(const std::filesystem::path& path)
    {
        std::ifstream ifs(path);
        boost::archive::text_iarchive ia(ifs);

        //those will self create and register
        //so we use tmp container to trigger deserialization
        container_t tmp;
        ia >> tmp;
    }

};

template <typename T>
typename ExtensionOwning<T>::container_t ExtensionOwning<T>::ext_list_ = {};

#endif //MP1_EXTENSION_OWNING_H
