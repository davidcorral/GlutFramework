
# Find Packages
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

# Find Files
file(GLOB SOURCE_FILES "*.cpp" )

set( LIB_NAME glutFramework )
add_library( ${LIB_NAME} STATIC ${SOURCE_FILES} )

# Common Includes
target_include_directories( ${LIB_NAME} PRIVATE
                            ${CMAKE_SOURCE_DIR}/include
                            ${GLUT_INCLUDE_DIR}
                            ${OPENGL_INCLUDE_DIR} )

# Install
install( TARGETS ${LIB_NAME}
         ARCHIVE DESTINATION ${CMAKE_SOURCE_DIR}/lib )
