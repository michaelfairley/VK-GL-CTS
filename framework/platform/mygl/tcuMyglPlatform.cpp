#include "tcuMyglPlatform.hpp"

#include "glwFunctions.hpp"
#include "tcuRenderTarget.hpp"
#include "egluNativeDisplay.hpp"
#include "eglwLibrary.hpp"
#include "eglwEnums.hpp"
#include "egluGLContextFactory.hpp"

namespace tcu {
  class MyglDisplay: public eglu::NativeDisplay {
  public:
    MyglDisplay(): eglu::NativeDisplay(CAPABILITY_GET_DISPLAY_LEGACY),
#if DE_OS == DE_OS_OSX
      library("libmygl.dylib")
#elif DE_OS == DE_OS_UNIX
      library("libmygl.so")
#else
#error Need to define filename for platform
#endif
    {}

    const eglw::Library& getLibrary (void) const {
      return library;
    }

    eglw::EGLNativeDisplayType getLegacyNative (void) {
      return EGL_DEFAULT_DISPLAY;
    }

  private:
    eglw::DefaultLibrary library;
  };

  class MyglDisplayFactory: public eglu::NativeDisplayFactory {
  public:
    MyglDisplayFactory(): eglu::NativeDisplayFactory("mygl", "Mygl Display", eglu::NativeDisplay::CAPABILITY_GET_DISPLAY_LEGACY) {}

    eglu::NativeDisplay* createDisplay(const eglw::EGLAttrib*) const {
      return new MyglDisplay();
    }
  };


  MyglPlatform::MyglPlatform() {
    m_nativeDisplayFactoryRegistry.registerFactory(new MyglDisplayFactory());
    m_contextFactoryRegistry.registerFactory(new eglu::GLContextFactory(m_nativeDisplayFactoryRegistry));
  }

  MyglPlatform::~MyglPlatform() {}
}

tcu::Platform* createPlatform() {
  return new tcu::MyglPlatform();
}
