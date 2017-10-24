# CMakeFile for qphelper library.

# PNG support enabled by default.
add_definitions(-DQP_SUPPORT_PNG)

set(QPHELPER_SRCS
	qpCrashHandler.c
	qpCrashHandler.h
	qpDebugOut.c
	qpDebugOut.h
	qpInfo.c
	qpInfo.h
	qpTestLog.c
	qpTestLog.h
	qpWatchDog.c
	qpWatchDog.h
	qpXmlWriter.c
	qpXmlWriter.h)

set(QPHELPER_LIBS
	debase
	depool
	dethread
	deutil
	${PNG_LIBRARY}
	)

if (DE_OS_IS_UNIX OR DE_OS_IS_QNX)
	# For vsnprintf()
	add_definitions(-D_XOPEN_SOURCE=600)
endif ()

if (DE_OS_IS_WIN32 AND DE_COMPILER_IS_MSC)
	set(QPHELPER_LIBS ${QPHELPER_LIBS} DbgHelp)
endif ()

add_library(qphelper STATIC ${QPHELPER_SRCS})
target_link_libraries(qphelper ${QPHELPER_LIBS})

# Should qpInfo.c attempt to include qpReleaseInfo.inl
set(USE_RELEASE_INFO_FILE OFF)

if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/qpReleaseInfo.inl")
	set(USE_RELEASE_INFO_FILE ON)
endif ()

if (USE_RELEASE_INFO_FILE)
	add_definitions(-DDEQP_USE_RELEASE_INFO_FILE)
endif ()
