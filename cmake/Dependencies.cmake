# lodepng
list(APPEND DEPENDENCIES lodepng)

# imgui
list(APPEND DEPENDENCIES imgui)

# nativefiledialog-extended (https://github.com/btzy/nativefiledialog-extended#cmake-projects)
list(APPEND DEPENDENCIES nfd)
add_subdirectory(${DEPENDENCIES_DIR}/nativefiledialog-extended)

# zstd (https://github.com/facebook/zstd/tree/dev/build/cmake)
list(APPEND DEPENDENCIES libzstd_static)
set(ZSTD_DIR ${DEPENDENCIES_DIR}/zstd)
set(ZSTD_BUILD_PROGRAMS OFF CACHE BOOL "" FORCE)
set(ZSTD_BUILD_STATIC ON CACHE BOOL "" FORCE)
set(ZSTD_BUILD_SHARED OFF CACHE BOOL "" FORCE)
include_directories(SYSTEM ${ZSTD_DIR}/lib)
add_subdirectory(${ZSTD_DIR}/build/cmake)

# lz4 (https://github.com/lz4/lz4/tree/dev/build)
list(APPEND DEPENDENCIES lz4_static)
set(LZ4_DIR ${DEPENDENCIES_DIR}/lz4)
set(LZ4_BUILD_CLI OFF CACHE BOOL "" FORCE)
set(LZ4_BUNDLED_MODE ON CACHE BOOL "" FORCE)
include_directories(SYSTEM ${LZ4_DIR}/lib)
add_subdirectory(${LZ4_DIR}/build/cmake)

# fmt (https://fmt.dev/latest/usage.html#usage-with-cmake)
list(APPEND DEPENDENCIES fmt::fmt)
add_subdirectory(${DEPENDENCIES_DIR}/fmt)

