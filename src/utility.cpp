#include <echelon/utility.hpp>

#include <echelon/hdf5/dataspace.hpp>

namespace echelon
{

object_type get_object_type(hid_t obj_id)
{
    H5O_info_t obj_info;
    H5Oget_info(obj_id, &obj_info);

    if (obj_info.type == H5O_TYPE_GROUP)
        return object_type::group;
    else if (obj_info.type == H5O_TYPE_DATASET)
    {
        hdf5::dataspace space(H5Dget_space(obj_id));

        if(H5Sget_simple_extent_type(space.id()) == H5S_SCALAR)
            return object_type::scalar_dataset;
        else
            return object_type::dataset;
    }
    else
    {
        //If we can't determine the type of an HDF5 object simply signal this to the user code.
        //This might be handy, if we want to introspect HDF5 files, which were not written with echelon.
        //For example we could use this to deal with future object types, which are not handled by echelon yet.
        //When we have a better overview of all use cases of get_object_type, we should consider to throw an
        //appropriate exception instead, to force the user to deal with this case. As of now I am not sure,
        //if this is a normal or an exceptional use case.
        return object_type::unknown;
    }
}

}
