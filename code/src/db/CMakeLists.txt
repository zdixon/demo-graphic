project(db)

include_directories(
      ${MYSQL_INCLUDE_DIR}
      ${MYSQL_INCLUDE_CPPCONN_DIR}
      ${MYSQL_LIBRARY}
  )
  
set(db_headers DBHandler.h)
set(db_sources DBHandler.cpp)
set(db_files ${db_headers} ${db_sources})

add_library(db ${db_files})

install(TARGETS db
  LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
	ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)

install(FILES ${db_headers}
  DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
