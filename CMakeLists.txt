cmake_minimum_required(VERSION 3.12)
project(EngineGL)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(freetype_GL)
include_directories(src)
include_directories(src/audio)
include_directories(src/graphics)
include_directories(src/graphics/buffer)
include_directories(src/graphics/layer)
include_directories(src/Maths)
include_directories(src/utils)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)



add_executable(EngineGL
        freetype_GL/distance-field.c
        freetype_GL/distance-field.h
        freetype_GL/edtaa3func.c
        freetype_GL/edtaa3func.h
        freetype_GL/freetype-gl.h
        freetype_GL/opengl.h
        freetype_GL/platform.c
        freetype_GL/platform.h
        freetype_GL/texture-atlas.c
        freetype_GL/texture-atlas.h
        freetype_GL/texture-font.c
        freetype_GL/texture-font.h
        freetype_GL/utf8-utils.c
        freetype_GL/utf8-utils.h
        freetype_GL/vec234.h
        freetype_GL/vector.c
        freetype_GL/vector.h
        src/audio/sound.cpp
        src/audio/sound.h
        src/audio/sound_manager.cpp
        src/audio/sound_manager.h
        src/graphics/buffer/buffer.cpp
        src/graphics/buffer/buffer.h
        src/graphics/buffer/index_buffer.cpp
        src/graphics/buffer/index_buffer.h
        src/graphics/buffer/vertex_array.cpp
        src/graphics/buffer/vertex_array.h
        src/graphics/layer/group.cpp
        src/graphics/layer/group.h
        src/graphics/layer/layer.cpp
        src/graphics/layer/layer.h
        src/graphics/batch_renderer_2_d.cpp
        src/graphics/batch_renderer_2_d.h
        src/graphics/font.cpp
        src/graphics/font.h
        src/graphics/font_manager.cpp
        src/graphics/font_manager.h
        src/graphics/label.cpp
        src/graphics/label.h
        src/graphics/renderable_2_d.h
        src/graphics/renderer_2_d.h
        src/graphics/shader.cpp
        src/graphics/shader.h
        src/graphics/sprite.cpp
        src/graphics/sprite.h
        src/graphics/texture.cpp
        src/graphics/texture.h
        src/graphics/window.cpp
        src/graphics/window.h
        src/Maths/Mat4.cpp
        src/Maths/Mat4.h
        src/Maths/maths.h
        src/Maths/Vec2.cpp
        src/Maths/Vec2.h
        src/Maths/Vec3.cpp
        src/Maths/Vec3.h
        src/Maths/Vec4.cpp
        src/Maths/Vec4.h
        src/utils/file_utils.cpp
        src/utils/file_utils.h
        src/utils/image_load.cpp
        src/utils/image_load.h
        src/utils/string_utils.cpp
        src/utils/string_utils.h
        src/utils/Timer.h
        src/engine_gl.h
        main.cpp Game.h Game.cpp Pipe.cpp Pipe.h myLayer.h)

target_link_libraries(EngineGL freeimage GLEW glfw3 GL X11 Xi Xrandr Xxf86vm Xinerama Xcursor rt m pthread dl freetype gorilla openal)
