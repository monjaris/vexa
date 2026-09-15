if(PLUTOVG_ENABLE_IMAGE_WRITE)
   add_executable(smiley smiley.c)
   target_link_libraries(smiley plutovg)
endif()
