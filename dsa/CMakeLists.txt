


#add_library(dsa    #SHARED
#    src/reverse/reverse.h
#)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# common function
#add_executable(dsa-test_sum src/sum/test_sum.cpp)
#target_link_libraries(dsa-test_sum dsa)
#add_executable(dsa-test_max src/max/test_max.cpp)
#target_link_libraries(dsa-test_max dsa)
#add_executable(dsa-bubblesort src/bubblesort/bubble.cpp)
#add_executable(dsa-fibonacci src/fibonacci/fibonacci.cpp)

# Vector
add_executable(dsa-test_vector test/test_Vector.cpp)
target_link_libraries(dsa-test_vector dsa_core)

## List
#add_executable(dsa-test_list src/List/test_List.cpp)

### Stack
#add_executable(dsa-test_stack src/Stack/test_Stack.cpp)
#add_executable(dsa-stack_convertion src/Stack/stack_convertion.cpp)
#add_executable(dsa-stack_nest src/Stack/stack_nest.cpp)

### Queue
#add_executable(dsa-test_queue src/Queue/test_Queue.cpp)

### Tree
#add_executable(dsa-test_BinTree src/BinTree/test_BinTree.cpp)
#add_executable(dsa-test_BST src/BST/test_BST.cpp)
#add_executable(dsa-test_AVL src/AVL/test_AVL.cpp)
#add_executable(dsa-test_Splay src/Splay/test_Splay.cpp)
#add_executable(dsa-test_BTree src/BTree/test_BTree.cpp)
#add_executable(dsa-test_RedBlack src/RedBlack/test_RedBlack.cpp)

## Graph
#add_executable(dsa-test_graph src/Graph/test_Graph.cpp)
##target_link_libraries(dsa-test_graph dsa)

## Bitmap
#add_executable(dsa-test_Bitmap src/Bitmap/test_Bitmap.cpp)

## Hashtable
#add_executable(dsa-test_Hashtable src/Hashtable/test_Hashtable.cpp)

## PQ
##add_executable(dsa-test_PQ src/PQ/test_PQ.cpp)

## string
#add_executable(dsa-test_string_match src/StringMatch/test_StringMatch.cpp)

## sort & selection
#add_executable(dsa-test_sort_and_selection src/sort_and_selection/test_sort_and_selection.cpp)
