project(ds)

include_directories(
      ${GLM_INCLUDE_DIR}
  )

set(ds_headers Dimension.h)
set(ds_sources Dimension.cpp)
set(ds_files ${ds_headers} ${ds_sources})

add_library(ds ${ds_files})

install(TARGETS ds
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
	ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

install(FILES ${ds_headers}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

