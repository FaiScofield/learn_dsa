cmake_minimum_required(VERSION 2.8)

project(learn_dsa)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug)
ENDIF()

MESSAGE("Build type: " ${CMAKE_BUILD_TYPE})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


include_directories(${PROJECT_SOURCE_DIR}/include)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
add_library(algo    SHARED
    include/MGraph.h
    include/BinaryTree.h
    include/HashTable.h
    include/KdTree.h

    src/graph/MGraph.cpp
    src/tree/binaryTree.cpp

)

add_library(dsa    SHARED
    dsa/src/sum/sum.cc
    dsa/src/max/max.cc

    dsa/src/Vector/Vector.h
    dsa/src/List/List.h
    dsa/src/List/ListNode.h
    dsa/src/Stack/Stack.h
    dsa/src/Queue/Queue.h
    dsa/src/BinTree/BinTree.h
    dsa/src/BinTree/BinNode.h
    dsa/src/Graph/Graph.h
    dsa/src/Graph/GraphMatrix.h
    dsa/src/Bitmap/Bitmap.h
    dsa/src/BST/BST.h
    dsa/src/AVL/AVL.h
    dsa/src/Splay/Splay.h
    dsa/src/BTree/BTNode.h
    dsa/src/BTree/BTree.h
    dsa/src/RedBlack/RedBlack.h
    dsa/src/Hashtable/Hashtable.h
    dsa/src/Entry/Entry.h
#    dsa/src/PQ/PQ.h
#    dsa/src/PQ/PQ_List.h
#    dsa/src/PQ/PQ_LeftHeap.h
#    dsa/src/PQ/PQ_ComplHeap.h
    dsa/src/StringMatch/StringMatch.h
    dsa/src/StringMatch/showStringMatch.h
    dsa/src/sort_and_selection/sort_and_selection.h

    dsa/src/UniPrint/print.h
#    dsa/_share/Increase.h
)

add_subdirectory(dsa)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# tree
add_executable(addTree src/tree/addTree.cpp)
target_link_libraries(addTree algo)
add_executable(test_KdTree src/tree/test_KdTree.cpp)
target_link_libraries(test_KdTree algo)


#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
#add_executable(prim src/graph/prim.cpp)
#add_executable(dijkstra src/graph/dijkstra.cpp)
#add_executable(floyd src/graph/floyd.cpp)
add_executable(chessboard src/graph/chessboard.cpp)
add_executable(eraseUnorderContainer src/eraseUnorderContainer.cpp)


# other
add_executable(LCS src/LongestCommonSubsequence.cpp)


# leetcode
add_executable(70-ClimbingStairs src/leetcode/70-ClimbingStairs.cpp)
add_executable(706-DesignHashMap src/leetcode/706-DesignHashMap.cpp)
add_executable(778-SwimInRisingWater src/leetcode/778-SwimInRisingWater.cpp)