
#include "query.h"

#include <cassert>

#include <scm/gl_core/render_device.h>
#include <scm/gl_core/render_device/opengl/gl3_core.h>
#include <scm/gl_core/render_device/opengl/util/assert.h>
#include <scm/gl_core/render_device/opengl/util/error_helper.h>

namespace scm {
namespace gl {

query::query(render_device& in_device)
  : render_device_child(in_device),
    _gl_query_id(0),
    _gl_query_type(0)
{
    const opengl::gl3_core& glapi = in_device.opengl3_api();

    glapi.glGenQueries(1, &_gl_query_id);
    if (0 == _gl_query_id) {
        state().set(object_state::OS_BAD);
    }

    gl_assert(glapi, leaving query::query());
}

query::~query()
{
    const opengl::gl3_core& glapi = parent_device().opengl3_api();

    assert(0 != _gl_query_id);
    glapi.glDeleteQueries(1, &_gl_query_id);
    
    gl_assert(glapi, leaving query::~query());
}

void
query::begin(const render_context& in_context) const
{
    const opengl::gl3_core& glapi = in_context.opengl_api();
    assert(0 != query_id());
    assert(0 != query_type());

    glapi.glBeginQuery(query_type(), query_id());

    gl_assert(glapi, leaving query::begin());
}

void
query::end(const render_context& in_context) const
{
    const opengl::gl3_core& glapi = in_context.opengl_api();
    assert(0 != query_id());
    assert(0 != query_type());

    glapi.glEndQuery(query_type());

    gl_assert(glapi, leaving query::end());
}

unsigned
query::query_id() const
{
    return (_gl_query_id);
}

unsigned
query::query_type() const
{
    return (_gl_query_type);
}

} // namespace gl
} // namespace scm