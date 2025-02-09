set(VCPKG_TARGET_ARCHITECTURE x86)
set(VCPKG_CRT_LINKAGE static)
set(VCPKG_LIBRARY_LINKAGE static)
set(VCPKG_CXX_FLAGS_DEBUG "-D_SECURE_SCL=0 -D_HAS_ITERATOR_DEBUGGING=0" CACHE STRING "")
set(VCPKG_C_FLAGS_DEBUG "-D_SECURE_SCL=0 -D_HAS_ITERATOR_DEBUGGING=0" CACHE STRING "")
set(CMAKE_CXX_FLAGS_DEBUG "${VCPKG_CRT_LINK_FLAG_PREFIX}d /Z7 /Ob0 /Od /RTC1 ${VCPKG_CXX_FLAGS_DEBUG}" CACHE STRING "")
set(CMAKE_C_FLAGS_DEBUG "${VCPKG_CRT_LINK_FLAG_PREFIX}d /Z7 /Ob0 /Od /RTC1 ${VCPKG_C_FLAGS_DEBUG}" CACHE STRING "")
