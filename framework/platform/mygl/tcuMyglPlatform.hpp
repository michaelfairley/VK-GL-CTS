#include "tcuDefs.hpp"
#include "tcuPlatform.hpp"
#include "gluPlatform.hpp"
#include "egluPlatform.hpp"

namespace tcu
{

  class MyglPlatform : public tcu::Platform, private glu::Platform, private eglu::Platform {
  public:
    MyglPlatform ();
    ~MyglPlatform ();

    const glu::Platform& getGLPlatform() const {
      return static_cast<const glu::Platform&>(*this);
    }

    const eglu::Platform& getEGLPlatform (void) const {
      return static_cast<const eglu::Platform&>(*this);
    }

  };

}
