# CMakeList.txt : CMake project for CMake_wxWidgets_openGL

cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
cmake_policy(SET CMP0141 NEW)
set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("CMake_wxWidgets_openGL")

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base gl)

# Include wxWidgets macros and definitions
include(${wxWidgets_USE_FILE})

# Add the executable target with WIN32 option for a GUI application
add_executable(CMake_wxWidgets_openGL WIN32 CMake_wxWidgets_openGL.cpp)

# Ensure the correct subsystem is used
set_target_properties(CMake_wxWidgets_openGL PROPERTIES
    WIN32_EXECUTABLE YES
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
set_property(TARGET CMake_wxWidgets_openGL PROPERTY CXX_STANDARD 20)
endif()

# Link wxWidgets libraries
target_link_libraries(CMake_wxWidgets_openGL ${wxWidgets_LIBRARIES} ${OPENGL_gl_LIBRARY})