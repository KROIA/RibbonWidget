
# This functions creates a default example project using the given library
# Function name: exampleMaster
# Params: PARENT_LIBRARY_NAME   Name of the library. Example: JsonDatabase
#         PROFILING_NAME        Name of the macro that defines that the profiler is enabled. Example: JD_PROFILING
#         QT_ENABLE             Enables QT modules. ON if QT is used, otherwise OFF
#         QT_DEPLOY             Deploys the compiled file to the compile output path and the install path. ON / OFF
#         QT_MODULES            Defines which QT modules are required. 
#                                     set(QT_MODULES
#                                         Core
#                                         # Widgets
#                                         # Gui
#                                         # Network
#                                         # Add any other required modules here
#                                     )
#         ADDITIONAL_SOURCES    Additional source files that should be added to the project. Example: "Application icon"
#         ADDITIONAL_LIBRARIES  Additional libraries that should be added to the project.
#         INSTALL_BIN_PATH      Specifies the install path. Example: "${CMAKE_INSTALL_PREFIX}/bin"
function(exampleMaster 
			PARENT_LIBRARY_NAME 
			PROFILING_NAME 
			QT_ENABLE 
			QT_DEPLOY 
			QT_MODULES
            ADDITIONAL_SOURCES
            ADDITIONAL_LIBRARIES
            INSTALL_BIN_PATH)

			
set(PARENT_LIBRARY_STATIC ${PARENT_LIBRARY_NAME}_static)
set(PARENT_LIBRARY_STATIC_PROFILE ${PARENT_LIBRARY_STATIC}_profile)

# Set the project name to the same as the folder name this file is contained in
cmake_path(GET CMAKE_CURRENT_SOURCE_DIR FILENAME PROJECT_NAME)   
string(REPLACE " " "_" ProjectId ${PROJECT_NAME})

# Change the project name if it gets compiled with profiler enabled
if(${PROFILING_NAME})
    set(PROJECT_NAME ${PROJECT_NAME}_profile)
    message("Profiling is enabled for ${PROJECT_NAME}")
else()
    message("Profiling is disabled for ${PROJECT_NAME}")
endif()
project(${PROJECT_NAME})



# QT settings
if(QT_ENABLE)
    find_package(Qt5Widgets REQUIRED)

    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    #set(CMAKE_AUTOUIC ON)

    find_package(Qt5 REQUIRED COMPONENTS ${QT_MODULES})
endif()
# end QT settings

include_directories(inc)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Get all source files
FILE_DIRECTORIES(H_FILES *.h)
FILE_DIRECTORIES(CPP_FILES *.cpp)


set(SOURCES 
	${H_FILES}
	${CPP_FILES})

if(QT_ENABLE)
    # Search for QT specific files
    FILE_DIRECTORIES(UI_FILES *.ui)    
    FILE_DIRECTORIES(RES_FILES *.qrc)    

    qt5_wrap_cpp(CPP_MOC_FILES ${H_FILES})
    qt5_wrap_ui(UIS_HDRS ${UI_FILES})
    qt5_add_resources(RESOURCE_FILES ${RES_FILES})

    list(APPEND DEFINES QT_ENABLED)
    # Check if QT_MODULES contains Widgets
    list(FIND QT_MODULES "Widgets" _index)
    if(NOT ${_index} EQUAL -1)
        list(APPEND DEFINES QT_WIDGETS_ENABLED)
    endif()

    set(SOURCES ${SOURCES}
	    ${CPP_MOC_FILES}
	    ${UIS_HDRS}
        ${RESOURCE_FILES})

    # Link the QT modules to your executable
    foreach(MODULE ${QT_MODULES})
        set(QT_LIBS ${QT_LIBS} Qt5::${MODULE})
    endforeach()

endif()

add_executable(${PROJECT_NAME} ${SOURCES} ${ADDITIONAL_SOURCES})


if(${PROFILING_NAME})
    if(NOT TARGET ${PARENT_LIBRARY_STATIC_PROFILE})
        message("ERROR: Target: PARENT_LIBRARY_STATIC_PROFILE does not exist")
        message("ERROR: Target: Make shure you have added the dependency: easy_profiler.cmake and set(EASY_PROFILER_IS_AVAILABLE ON)")
    endif()
    target_link_libraries(${PROJECT_NAME} ${PARENT_LIBRARY_STATIC_PROFILE} ${QT_LIBS} ${ADDITIONAL_LIBRARIES})
else()
    target_link_libraries(${PROJECT_NAME} ${PARENT_LIBRARY_STATIC} ${QT_LIBS} ${ADDITIONAL_LIBRARIES})
endif()

list(APPEND DEFINES BUILD_STATIC)
target_compile_definitions(${PROJECT_NAME} PUBLIC ${DEFINES})

install(TARGETS ${PROJECT_NAME} DESTINATION "${INSTALL_BIN_PATH}")

if(QT_ENABLE AND QT_DEPLOY)
   DEPLOY_QT(${PROJECT_NAME} "${INSTALL_BIN_PATH}")
   DEPLOY_QT(${PROJECT_NAME} "$<TARGET_FILE_DIR:${PROJECT_NAME}>") # Also deploy on the compile output path
endif()

endfunction()