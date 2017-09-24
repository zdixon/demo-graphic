 # Use this file for compiling the examples.
 
  if(MINVR_FOUND)
    # Redefine the include directories to include MinVR.
    include_directories(
      ${OPENGL_INCLUDE_DIR}
      ${FREEGLUT_INCLUDE_DIR}
      ${FREETYPE_INCLUDE_DIRS}
      ${GLM_INCLUDE_DIR}
      ${GLEW_INCLUDE_DIRS}
      ${MINVR_INCLUDE_DIR}
      ${MYSQL_INCLUDE_DIR}
      ${MYSQL_INCLUDE_CPPCONN_DIR}
  )
  
    # add_executable(main  textureDemoMinVR.cpp)
    add_executable(main main.cpp DemoVRApp.h DemoVRApp.cpp StageController.cpp StageController.h)
    # add_executable(main main.cpp DemoVRApp.h DemoVRApp.cpp)


    target_link_libraries(main bsg db ds adapter
     ${MINVR_LIBRARY}
     ${FREEGLUT_LIBRARY}
     ${OPENGL_LIBRARY}
     ${GLEW_LIBRARY}
     ${FREETYPE_LIBRARIES}
     ${MYSQL_LIBRARY})


  else(MINVR_FOUND)

    message("** No MinVR for you!")
    message("** See instructions and advice on the topic above.")

  endif(MINVR_FOUND)
#endif(PNG_FOUND)


                    
