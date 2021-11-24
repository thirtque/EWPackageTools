# lodepng
set(LODEPNG_DIR ${DEPENDENCIES_DIR}/lodepng)

add_library(lodepng STATIC)

target_compile_definitions(lodepng PRIVATE LODEPNG_NO_COMPILE_DISK)

target_sources(lodepng
        PRIVATE
        ${LODEPNG_DIR}/lodepng.cpp
        )

target_include_directories(lodepng
        PUBLIC ${LODEPNG_DIR}
        )
