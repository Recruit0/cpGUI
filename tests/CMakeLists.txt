cmake_minimum_required( VERSION 2.6 )
   
find_package(SFML REQUIRED
	COMPONENTS
		Graphics
	)

set (TEST_1_SOURCES
	main.cpp
)

include_directories(
	${SFML_INCLUDE_DIR}
	../include
)

add_executable (
	cpGUI-test
	WIN32
	${TEST_1_SOURCES}
)

target_link_libraries ( cpGUI-test
	${SFML_LIBRARY}
	cpGUI
)

