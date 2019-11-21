if(MSVC AND NOT "${MSVC_VERSION}" LESS 1400)
	add_definitions( "/MP" )
endif()


add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

### GLFW ###

add_subdirectory (glfw-3.1.2)

include_directories(
	glfw-3.1.2/include/GLFW/
	glew-1.13.0/include/
	SOIL/src/
)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(OPENGL_LIBRARY
	${OPENGL_LIBRARY}
	-lGL -lGLU -lXrandr -lXext -lX11 -lrt
	${CMAKE_DL_LIBS}
	${GLFW_LIBRARIES}
)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
set(OPENGL_LIBRARY
	${OPENGL_LIBRARY}
	${CMAKE_DL_LIBS}
	${GLFW_LIBRARIES}
)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

### GLEW ###

set(GLEW_SOURCE
	glew-1.13.0/src/glew.c
)

set(GLEW_HEADERS
)


add_library( GLEW_1130 STATIC
	${GLEW_SOURCE}
	${GLEW_INCLUDE}
)

target_link_libraries(GLEW_1130
	${OPENGL_LIBRARY}
	${EXTRA_LIBS}
)

### SOIL ###

set(SOIL_SOURCE
	SOIL/src/SOIL.c
	SOIL/src/image_DXT.c
	SOIL/src/image_helper.c
	SOIL/src/stb_image_aug.c
	SOIL/lib/libSOIL.a
	)

set(SOIL_HEADERS
	SOIL/src/SOIL.h
	SOIL/src/image_DXT.h
	SOIL/src/image_helper.h
	SOIL/src/stb_image_aug.h
	)

add_library(SOIL STATIC
	${SOIL_SOURCE}
	${SOIL_HEADERS}
	)

target_link_libraries(SOIL
	${OPENGL_LIBRARY}
	${EXTRA_LIBS}
)