
# Find Packages
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)

# Get Sources
file(GLOB SOURCE_FILES "*.cpp" )

foreach( FILE ${SOURCE_FILES} )

    # Gxet Filename
    get_filename_component( FILENAME ${FILE} NAME_WE )
    
    # Create Test
    add_executable( ${FILENAME} ${CORE_SOURCE_FILES} ${FILE} )

    # Common Includes
    target_include_directories( ${FILENAME} PRIVATE
                        ${CMAKE_SOURCE_DIR}/include
                        ${GLUT_INCLUDE_DIR}
                        ${OPENGL_INCLUDE_DIR} )
    
    # Link
    target_link_libraries( ${FILENAME} ${PROJECT_BINARY_DIR}/src/libglutFramework.a
                ${OPENGL_LIBRARIES}
                ${GLUT_LIBRARIES} 
                ${GLEW_LIBRARIES} )

    # Install
    install( TARGETS ${FILENAME} RUNTIME 
             DESTINATION ${CMAKE_SOURCE_DIR}/bin )
    
endforeach()
