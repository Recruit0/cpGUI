cmake_minimum_required( VERSION 2.6 )
   
find_package(SFML REQUIRED
	COMPONENTS
		Graphics
		Window
		System
	)

set (SOURCES
	button.cpp
	check_box.cpp
	gui.cpp
	menu.cpp
	text_box.cpp
)

include_directories(
	${SFML_INCLUDE_DIR}
	../include
)

add_library (
	cpGUI
	${SOURCES}
)

target_link_libraries ( cpGUI
	${SFML_LIBRARY}
)

