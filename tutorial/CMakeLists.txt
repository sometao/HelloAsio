

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



foreach(target_module t1 t2 t3 t3a t4 t5 d1 d2 d3 d4 d5 d6 d7)

	add_executable(${target_module} "${target_module}.cpp")

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
