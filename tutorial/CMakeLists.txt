


add_executable(tutorial1 "t1.cpp")

add_executable(tutorial2 "t2.cpp")

add_executable(tutorial3 "t3.cpp")

add_executable(tutorial4 "t4.cpp")

add_executable(tutorial5 "t5.cpp")


######################################
#  tutorial Information
######################################
message(" ===================== tutorial Information ======================")
message(CMAKE_SOURCE_DIR         	    =  ${CMAKE_SOURCE_DIR})
message(PROJECT_SOURCE_DIR            =  ${PROJECT_SOURCE_DIR})
message(CMAKE_INCLUDE_PATH            =  ${CMAKE_INCLUDE_PATH})
message(CMAKE_LIBRARY_PATH            =  ${CMAKE_LIBRARY_PATH})
message(PROJECT_SOURCE_DIR            =  ${PROJECT_SOURCE_DIR})
message(CMAKE_BUILD_TYPE              =  ${CMAKE_BUILD_TYPE})



foreach(target_module tutorial1 tutorial2 tutorial3 tutorial4 tutorial5)

	target_include_directories( ${target_module}  
		PRIVATE 
			${PROJECT_SOURCE_DIR}/include
	)


	target_link_libraries( ${target_module}  
		PRIVATE 
			${CMAKE_THREAD_LIBS_INIT}
			${CMAKE_DL_LIBS}
	)


endforeach(target_module)
