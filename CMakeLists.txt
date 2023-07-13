cmake_minimum_required(VERSION 3.14)

include(cmake/prelude.cmake)

project(
    mylibfaustembedded
    VERSION 0.1.0
    DESCRIPTION ""
    HOMEPAGE_URL ""
    LANGUAGES CXX
)

include(cmake/project-is-top-level.cmake)
include(cmake/variables.cmake)

# ---- Declare executable ----
add_compile_definitions(_GLIBCXX_USE_CXX11_ABI=0)
add_executable(mylibfaustembedded_exe source/main.cpp)
add_executable(mylibfaustembedded::exe ALIAS mylibfaustembedded_exe)
target_link_libraries(mylibfaustembedded_exe PUBLIC ${PROJECT_SOURCE_DIR}/lib/libfaustwithllvm.a)

set_property(TARGET mylibfaustembedded_exe PROPERTY OUTPUT_NAME mylibfaustembedded)

target_compile_features(mylibfaustembedded_exe PRIVATE cxx_std_11)

target_include_directories(
    mylibfaustembedded_exe ${warning_guard}
    PUBLIC
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/source>"
    "$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/faust/architecture>"
)

# ---- Install rules ----

if(NOT CMAKE_SKIP_INSTALL_RULES)
  include(cmake/install-rules.cmake)
endif()

# ---- Developer mode ----

if(NOT mylibfaustembedded_DEVELOPER_MODE)
  return()
elseif(NOT PROJECT_IS_TOP_LEVEL)
  message(
      AUTHOR_WARNING
      "Developer mode is intended for developers of mylibfaustembedded"
  )
endif()

include(cmake/dev-mode.cmake)
