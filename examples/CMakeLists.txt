list(APPEND EXAMPLES
    main1
    main2
    main3
    main4
    main5
    fibonacci
    HoardTest
    loopback
)

find_package(Threads REQUIRED)
foreach(example IN LISTS EXAMPLES)
    add_executable(${example} ${example}.cpp)
    target_link_libraries(${example} Threads::Threads numa)
    
endforeach(example IN LISTS EXAMPLES)




