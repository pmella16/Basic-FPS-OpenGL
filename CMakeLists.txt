# CMake entry point
cmake_minimum_required (VERSION 3.5)

project (Showcase)

find_package(OpenGL REQUIRED)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()



# Compile external dependencies 
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 NEW)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")
include(CreateLaunchers)
include(MSVCMultipleProcessCompile) # /MP

if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)



include_directories(
	external/glfw-3.1.2/include/GLFW/
	external/glm-0.9.7.1/
	external/glew-1.13.0/include/
	.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	glfw
	GLEW_1130
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

# User FPSGame
add_executable(FPSGame 
	FPSGame/FPSGame.cpp
	FPSGame/Map.cpp
	FPSGame/Minimap.cpp
	FPSGame/FPSGame.h
	FPSGame/Map.h
	FPSGame/Minimap.h
	FPSGame/Shaders/MapFragmentShader.fragmentshader
	FPSGame/Shaders/MapVertexShader.vertexshader
	FPSGame/Shaders/SunFragmentShader.fragmentshader
	FPSGame/Shaders/SunVertexShader.vertexshader
	FPSGame/Shaders/MiniMapFragmentShader.fragmentshader
	FPSGame/Shaders/MiniMapVertexShader.vertexshader
	common/shader.cpp
	common/shader.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/texture.cpp
	common/texture.hpp
	
)
target_link_libraries(FPSGame
	${ALL_LIBS}
)
# Xcode and Visual working directories
set_target_properties(FPSGame PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/FPSGame/")
#create_target_launcher(FPSGame WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/FPSGame/")



SOURCE_GROUP(common REGULAR_EXPRESSION ".*/common/.*" )
SOURCE_GROUP(shaders REGULAR_EXPRESSION ".*/.*shader$" )

if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )

add_custom_command(
   TARGET FPSGame POST_BUILD
   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/FPSGame${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/FPSGame/"
   )


elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )

