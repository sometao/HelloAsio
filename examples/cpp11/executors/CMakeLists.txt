

set(THIS_MODULE "Ex11")


######################################
#  exp Information
######################################
message(" ===================== ${THIS_MODULE} Information ======================")
message(CMAKE_SOURCE_DIR         	    =  ${CMAKE_SOURCE_DIR})
message(PROJECT_SOURCE_DIR            =  ${PROJECT_SOURCE_DIR})
message(CMAKE_INCLUDE_PATH            =  ${CMAKE_INCLUDE_PATH})
message(CMAKE_LIBRARY_PATH            =  ${CMAKE_LIBRARY_PATH})
message(PROJECT_SOURCE_DIR            =  ${PROJECT_SOURCE_DIR})
message(CMAKE_BUILD_TYPE              =  ${CMAKE_BUILD_TYPE})


foreach(module_target 
	"actor"
	"bank_account_1"
	"bank_account_2"
)
  
  set(target_name "${THIS_MODULE}_${module_target}")
 
  message(" ${THIS_MODULE}: add target [${target_name}]")

	add_executable(${target_name} "${module_target}.cpp")

	target_include_directories( ${target_name}  
		PRIVATE 
			${PROJECT_SOURCE_DIR}/include
	)


	target_link_libraries( ${target_name}  
		PRIVATE 
			${CMAKE_THREAD_LIBS_INIT}
			${CMAKE_DL_LIBS}
	)


endforeach(module_target)
