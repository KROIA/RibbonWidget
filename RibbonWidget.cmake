## description: simple ribbon widget for QT applications
include(FetchContent)

# Define the git repository and tag to download from
set(LIB_NAME RibbonWidget)
set(GIT_REPO https://github.com/KROIA/RibbonWidget.git)
set(GIT_TAG main)

FetchContent_Declare(
    ${LIB_NAME}
    GIT_REPOSITORY ${GIT_REPO}
    GIT_TAG        ${GIT_TAG}
)

set(${LIB_NAME}_NO_EXAMPLES True)
set(${LIB_NAME}_NO_UNITTESTS True)
message("Downloading dependency: ${LIB_NAME} from: ${GIT_REPO} tag: ${GIT_TAG}")
FetchContent_MakeAvailable(${LIB_NAME})

# Add this library to the specific profiles of this project
list(APPEND DEPENDENCIES_FOR_SHARED_LIB ${LIB_NAME}_static)
list(APPEND DEPENDENCIES_FOR_STATIC_LIB ${LIB_NAME}_static)
list(APPEND DEPENDENCIES_FOR_STATIC_PROFILE_LIB ${LIB_NAME}_static_profile) # only use for static profiling profile

