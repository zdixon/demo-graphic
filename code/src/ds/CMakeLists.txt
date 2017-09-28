project(ds)

include_directories(
      ${GLM_INCLUDE_DIR}
      ${MYSQL_INCLUDE_DIR}
      ${MYSQL_INCLUDE_CPPCONN_DIR}
      ${MYSQL_LIBRARY}
  )

set(ds_headers Dimension.h CubeCell.h Cube.h InterfaceData.h) 
set(ds_sources Dimension.cpp CubeCell.cpp Cube.cpp)
set(ds_files ${ds_headers} ${ds_sources})

add_library(ds ${ds_files})

install(TARGETS ds
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
	ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

install(FILES ${ds_headers}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

