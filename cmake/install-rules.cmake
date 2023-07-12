install(
    TARGETS mylibfaustembedded_exe
    RUNTIME COMPONENT mylibfaustembedded_Runtime
)

if(PROJECT_IS_TOP_LEVEL)
  include(CPack)
endif()
