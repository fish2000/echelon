//  Copyright (c) 2012-2013 Christopher Hinz
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef ECHELON_HDF5_DATASET_HPP
#define ECHELON_HDF5_DATASET_HPP

#include <echelon/hdf5/type.hpp>
#include <echelon/hdf5/dataspace.hpp>
#include <echelon/hdf5/property_list.hpp>
#include <echelon/hdf5/object.hpp>
#include <echelon/hdf5/file.hpp>

#include <hdf5.h>
#include <string>

namespace echelon
{
namespace hdf5
{

class object_reference;

class dataset
{
public:
    dataset();
    explicit dataset(hid_t dataset_id_);
    explicit dataset(const object& other);
    dataset(hid_t loc_id, const std::string& name, const type& dtype,
            const dataspace& space, const property_list& lcpl,
            const property_list& dcpl, const property_list& dapl);
    dataset(hid_t loc_id, const std::string& name, const property_list& dapl);
    ~dataset();

    dataset(const dataset& other);
    dataset(dataset&& other);

    dataset& operator=(const dataset& other);
    dataset& operator=(dataset&&);

    void write(const type& mem_type, const dataspace& mem_space,
               const dataspace& file_space, const property_list& xfer_plist,
               const void* buf);
    void read(const type& mem_type, const dataspace& mem_space,
              const dataspace& file_space, const property_list& xfer_plist,
              void* buf) const;

    void write(const void* value);
    void read(void* value) const;

    void set_extent(const std::vector<hsize_t>& dims);

    dataspace get_space() const;

    type datatype() const;
    property_list creation_property_list() const;

    std::string name() const;
    file associated_file() const;

    std::string label(unsigned int index) const;
    void relabel(unsigned int index, const std::string& new_label);

    hid_t id() const;

private:
    hid_t dataset_id_;
};
}
}

#endif
