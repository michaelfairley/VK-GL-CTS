#include "tcuMyglPlatform.hpp"

#include "gluRenderContext.hpp"
#include "gluContextFactory.hpp"
#include "gluRenderConfig.hpp"
#include "glwFunctions.hpp"
#include "tcuRenderTarget.hpp"
#include "egluNativeDisplay.hpp"
#include "eglwLibrary.hpp"
#include "eglwEnums.hpp"

namespace tcu {
  class MyglRenderContext: public glu::RenderContext {
  public:
    MyglRenderContext(const glu::RenderConfig& config)
      : type(config.type)
      , renderTarget (0, 0, tcu::PixelFormat(0,0,0,0), 0, 0, 0) {

    }

    ~MyglRenderContext() {}

    const glw::Functions& getFunctions() const {
      return functions;
    }

    const tcu::RenderTarget& getRenderTarget() const {
      return renderTarget;
    }

    void postIterate() {}

    glu::ContextType getType() const {
      return type;
    }

  private:
    const glu::ContextType type;
    glw::Functions functions;
    tcu::RenderTarget renderTarget;
  };

  class MyglContextFactory: public glu::ContextFactory {
  public:
    MyglContextFactory() : glu::ContextFactory("mygl", "Mygl Context") {}

    glu::RenderContext* createContext(const glu::RenderConfig& config,
                                      const tcu::CommandLine& cmdLine,
                                      const glu::RenderContext* sharedContext) const {
      return new MyglRenderContext(config);
    }
  };

  class MyglDisplay: public eglu::NativeDisplay {
  public:
    MyglDisplay(): eglu::NativeDisplay(CAPABILITY_GET_DISPLAY_LEGACY),
      library("libmygl.dylib") {

    }

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
    m_contextFactoryRegistry.registerFactory(new MyglContextFactory());
    m_nativeDisplayFactoryRegistry.registerFactory(new MyglDisplayFactory());
  }

  MyglPlatform::~MyglPlatform() {}
}

tcu::Platform* createPlatform() {
  return new tcu::MyglPlatform();
}
