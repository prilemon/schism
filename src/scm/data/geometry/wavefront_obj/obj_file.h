
#ifndef SCM_DATA_OBJ_FILE_H_INCLUDED
#define SCM_DATA_OBJ_FILE_H_INCLUDED

#include <cstdlib>

#include <map>
#include <string>
#include <vector>

#include <scm/core/ptr_types.h>
#include <scm/core/math/math.h>

#include <scm/core/platform/platform.h>
#include <scm/core/utilities/platform_warning_disable.h>

namespace scm {
namespace data {

struct __scm_export(data) wavefront_material
{
    wavefront_material();

    float           _Ns;
    float           _Ni;
    math::vec4f_t   _Ka;
    math::vec4f_t   _Kd;
    math::vec4f_t   _Ks;
    float           _d;
}; // struct wavefront_material

struct wavefront_object_triangle_face
{
    unsigned    _vertices[3];
    unsigned    _normals[3];
    unsigned    _tex_coords[3];        
}; // struct wavefront_object_triangle_face

struct wavefront_object_group
{
    wavefront_object_group() : _num_tri_faces(0) {}

    std::size_t                                 _num_tri_faces;
    scm::core::shared_array<wavefront_object_triangle_face>  _tri_faces;

    std::string                                 _name;
    std::string                                 _material_name;

}; // struct wavefront_object_group

struct wavefront_object
{
    wavefront_object() {}

    typedef std::vector<wavefront_object_group> group_container;

    group_container::iterator                   add_new_group();
    group_container::iterator                   add_new_group(const std::string& /*name*/);

    group_container                             _groups;

    std::string                                 _name;
}; // struct wavefront_object

struct wavefront_model
{
    wavefront_model() : _num_vertices(0),
                        _num_normals(0),
                        _num_tex_coords(0) {}

    typedef std::vector<wavefront_object>               object_container;
    typedef std::map<std::string, wavefront_material>   material_container;

    object_container::iterator                  add_new_object();
    object_container::iterator                  add_new_object(const std::string& /*name*/);

    object_container                            _objects;

    std::size_t                                 _num_vertices;
    std::size_t                                 _num_normals;
    std::size_t                                 _num_tex_coords;

    scm::core::shared_array<math::vec3f_t>      _vertices;
    scm::core::shared_array<math::vec3f_t>      _normals;
    scm::core::shared_array<math::vec2f_t>      _tex_coords;

    material_container                          _materials;


}; // struct wavefront_model

} // namespace data
} // namespace scm

#include <scm/core/utilities/platform_warning_enable.h>

#endif // SCM_DATA_OBJ_FILE_H_INCLUDED