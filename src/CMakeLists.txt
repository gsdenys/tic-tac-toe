project(tictactoe)

find_package(cdt)

add_contract( tictactoe tictactoe tictactoe.cpp )
target_include_directories( tictactoe PUBLIC ${CMAKE_SOURCE_DIR}/../include )
target_ricardian_directory( tictactoe ${CMAKE_SOURCE_DIR}/../ricardian )