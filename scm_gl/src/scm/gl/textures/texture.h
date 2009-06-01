
#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED

#include <boost/noncopyable.hpp>

#include <scm/core/pointer_types.h>

#include <scm/gl/opengl.h>

#include <scm/core/platform/platform.h>
#include <scm/core/utilities/platform_warning_disable.h>

namespace scm {
namespace gl {

class __scm_export(ogl) texture
{
public:
    class binding_guard : boost::noncopyable
    {
    public:
        binding_guard(unsigned /*target*/, unsigned /*binding*/);
        virtual ~binding_guard();
    private:
        int             _save_active_texture_unit;
        int             _save_texture_object;
        unsigned        _binding;
        unsigned        _target;
    };

public:
    texture(const gl::texture& tex);
    virtual ~texture();

    const gl::texture&              operator=(const gl::texture& rhs);

    void                            bind(int /*texunit*/ = -1) const;
    void                            unbind() const;

    void                            parameter(GLenum pname, int param);
    void                            parameter(GLenum pname, float param);

    int                             target() const;
    int                             binding() const;
    unsigned                        id() const;
    int                             last_error() const;

protected:
    texture(const GLenum target, const GLenum binding);

private:
    void                                checked_lazy_generate_texture_id() const ;

protected:
    GLenum                              _last_error;

private:
    GLenum                              _texture_target;
    GLenum                              _texture_binding;

    mutable scm::shared_ptr<GLuint>     _texture_id;

    mutable int                         _occupied_texture_unit;
}; // class texture

} // namespace gl
} // namespace scm

#include <scm/core/utilities/platform_warning_enable.h>

#endif // TEXTURE_H_INCLUDED
