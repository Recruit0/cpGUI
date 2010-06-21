cmake_minimum_required( VERSION 2.6 )
   
find_package(SFML REQUIRED
	COMPONENTS
		Graphics
	)

set (SAMPLE_1_SOURCES
	cpGUI-example.cpp
)

include_directories(
	${SFML_INCLUDE_DIR}
	../include
)

add_executable (
	cpGUI-example
	WIN32
	${SAMPLE_1_SOURCES}
)

target_link_libraries ( cpGUI-example
	${SFML_LIBRARY}
	cpGUI
)

