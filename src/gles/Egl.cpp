#include "gles/Egl.h"
#include "gles/Display.h"
#include "core/Exception.h"
#include <EGL/egl.h>
#include <GLES2/gl2.h>

using namespace nb::gl;

static bool g_initialized = false;
static std::shared_ptr<Display> g_display = nullptr;
static std::shared_ptr<Configure> g_configure = nullptr;
static std::shared_ptr<Camera>	g_camera = std::make_shared<Camera>();

std::string nb::gl::getVersion()
{
	if (!hasInitialized())
		NB_THROW_EXCEPTION("none display init, use egl::init to init display.");

	return eglQueryString(getDisplay()->handle(), EGL_VERSION);
}

std::string nb::gl::getVendor()
{
	if (!hasInitialized())
		NB_THROW_EXCEPTION("none display init, use egl::init to init display.");

	return eglQueryString(getDisplay()->handle(), EGL_VENDOR);
}

void nb::gl::initialize(std::shared_ptr<Display> display, std::shared_ptr<Configure> configure)
{
	if (g_initialized)
		return;

	g_display = display;
	g_configure = configure;
	g_initialized = true;
}

bool nb::gl::hasInitialized()
{
	return g_initialized;
}

std::shared_ptr<Display> nb::gl::getDisplay()
{
	return g_display;
}

std::shared_ptr<Configure> nb::gl::getConfigure()
{
	return g_configure;
}

void nb::gl::setCamera(std::shared_ptr<Camera> camera)
{
	g_camera = camera;
}

std::shared_ptr<Camera> nb::gl::getCamera()
{
	return g_camera;
}

void nb::gl::makeCurrent(std::shared_ptr<Surface> onScreen, std::shared_ptr<Surface> offScreen, std::shared_ptr<Context> context)
{
	if(!hasInitialized())
		NB_THROW_EXCEPTION("none display init, use egl::init to init display.");

	if(!eglMakeCurrent(getDisplay()->handle(), onScreen->handle(), offScreen->handle(), context->handle()))
		NB_THROW_EXCEPTION("eglMakeCurrent fail");
}

void nb::gl::swapBuffers(const Surface *surface)
{
	eglSwapBuffers(getDisplay()->handle(), surface->handle());
}

void nb::gl::viewport(int x, int y, unsigned int width, unsigned height)
{
	glViewport(x, y, width, height);
}
