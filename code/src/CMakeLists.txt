 # Use this file for compiling the examples.
 
  if(MINVR_FOUND)
    # Redefine the include directories to include MinVR.
    include_directories(
      ${OPENGL_INCLUDE_DIR}
      ${FREEGLUT_INCLUDE_DIR}
      ${GLM_INCLUDE_DIR}
      ${GLEW_INCLUDE_DIRS}
      ${MINVR_INCLUDE_DIR}
      ${MYSQL_INCLUDE_DIR}
      ${MYSQL_INCLUDE_CPPCONN_DIR}
      ${MYSQL_LIBRARY}
  )
  
    add_executable(main main.cpp DemoVRApp.h DemoVRApp.cpp)

    target_link_libraries(main bsg ds db
     ${MINVR_LIBRARY}
     ${FREEGLUT_LIBRARY}
     ${OPENGL_LIBRARY}
     ${GLEW_LIBRARY})

  else(MINVR_FOUND)

    message("** No MinVR for you!")
    message("** See instructions and advice on the topic above.")

  endif(MINVR_FOUND)
#endif(PNG_FOUND)


                    
