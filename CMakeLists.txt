cmake_minimum_required (VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project (Stack2Huffman)

set(SRC ${PROJECT_SOURCE_DIR}/src/)
set(010 ${SRC}010_stack_i/)
set(011 ${SRC}011_stack_s/)
set(012 ${SRC}012_queue_s/)
set(020 ${SRC}020_stack_t/)
set(021 ${SRC}021_queue_t/)
set(022 ${SRC}022_deque_t/)
set(030 ${SRC}030_stack_sp/)
set(040 ${SRC}040_stack_f/)
set(041 ${SRC}041_queue_f/)
set(042 ${SRC}042_deque_f/)
set(043 ${SRC}043_stack_fv2/)
set(044 ${SRC}044_queue_fv2/)
set(045 ${SRC}045_deque_fv2/)
set(050 ${SRC}050_stack_sf/)
set(051 ${SRC}051_queue_sf/)
set(052 ${SRC}052_deque_sf/)
set(060 ${SRC}060_stack/)
set(061 ${SRC}061_queue/)
set(062 ${SRC}062_deque/)
set(070 ${SRC}070_list/)
set(080 ${SRC}080_vector/)
set(090 ${SRC}090_bin_tree_simple/)
set(100 ${SRC}100_bin_tree/)
set(110 ${SRC}110_bin_tree_sort/)
set(120 ${SRC}120_red_black_tree/)
set(121 ${SRC}121_set/)
set(122 ${SRC}122_pair/)
set(123 ${SRC}123_map/)
set(140 ${SRC}140_red_black_tree_multi/)
set(141 ${SRC}141_multiset/)
set(142 ${SRC}142_multimap/)
set(150 ${SRC}150_priority_queue/)
set(160 ${SRC}160_huffman_tree/)
set(170 ${SRC}170_hash_array_simple/)
set(180 ${SRC}180_hash_array/)
set(181 ${SRC}181_hash_array_v2/)
set(182 ${SRC}182_unordered_set/)
set(183 ${SRC}183_unordered_map/)
set(190 ${SRC}190_hash_array_multi/)
set(191 ${SRC}191_unordered_multiset/)
set(192 ${SRC}192_unordered_multimap/)

set(SLD ${SRC}Misc_sld/)
set(VEC ${SRC}Misc_vec/)
set(TST ${SRC}Misc_tests/)
set(GEX ${SRC}Misc_gexception/)
set(TEST ${SRC}test/)

include_directories(${011})
include_directories(${012})
include_directories(${020})
include_directories(${021})
include_directories(${022})
include_directories(${050})
include_directories(${051})
include_directories(${052})
include_directories(${060})
include_directories(${061})
include_directories(${062})
include_directories(${070})
include_directories(${080})
include_directories(${090})
include_directories(${100})
include_directories(${110})
include_directories(${120})
include_directories(${121})
include_directories(${122})
include_directories(${123})
include_directories(${140})
include_directories(${141})
include_directories(${142})
include_directories(${150})
include_directories(${180})
include_directories(${181})
include_directories(${190})

include_directories(${SLD})
include_directories(${GEX})
include_directories(${TST})
include_directories(${VEC})


add_library(Misc_gex ${GEX}gexception.cpp)


add_executable(010_StackI ${010}stack_i.h
                          ${010}stack_i.cpp
                          ${010}main.cpp
)

add_executable(011_StackS ${011}stack_s.h
                          ${011}stack_s.cpp
                          ${011}main.cpp
)

add_executable(012_QueueS ${012}queue_s.h
                          ${012}queue_s.cpp
                          ${012}main.cpp
)


add_executable(020_StackT ${020}stack_t.hpp
                          ${020}main.cpp
)

add_executable(021_QueueT ${021}queue_t.hpp
                          ${021}main.cpp
)

add_executable(022_DequeT ${022}deque_t.hpp
                          ${022}main.cpp
)
target_link_libraries(022_DequeT Misc_gex)


add_executable(030_StackSP ${030}stack_sp.hpp
                           ${030}main.cpp
)                          
target_link_libraries(030_StackSP Misc_gex)


add_executable(040_StackF ${040}stack_f.hpp
                          ${040}main.cpp
)
target_link_libraries(040_StackF Misc_gex)


add_executable(041_QueueF ${041}queue_f.hpp
                          ${041}main.cpp
)
target_link_libraries(041_QueueF Misc_gex)




add_executable(042_DequeF ${042}deque_f.hpp
                          ${042}main.cpp
)
target_link_libraries(042_DequeF Misc_gex)


add_executable(043_StackFv2 ${043}stack_fv2.hpp
                            ${043}main.cpp
)
target_link_libraries(043_StackFv2 Misc_gex)

add_executable(044_QueueFv2 ${044}queue_fv2.hpp
                            ${044}main.cpp
)
target_link_libraries(044_QueueFv2 Misc_gex)

add_executable(045_DequeFv2 ${045}deque_fv2.hpp
                            ${045}main.cpp
)
target_link_libraries(045_DequeFv2 Misc_gex)


add_executable(050_StackSF ${050}stack_sf.hpp
                           ${050}main.cpp
)
target_link_libraries(050_StackSF Misc_gex)

add_executable(051_QueueSF ${051}queue_sf.hpp
                           ${051}main.cpp
)
target_link_libraries(051_QueueSF Misc_gex)

add_executable(052_DequeSF ${052}deque_sf.hpp
                           ${052}main.cpp
)
target_link_libraries(052_DequeSF Misc_gex)


add_executable(060_Stack ${060}stack.hpp
                         ${060}main.cpp
)
target_link_libraries(060_Stack Misc_gex)

add_executable(061_Queue ${061}queue.hpp
                         ${061}main.cpp
)
target_link_libraries(061_Queue Misc_gex)

add_executable(062_Deque ${062}deque.hpp
                         ${062}main.cpp
)
target_link_libraries(062_Deque Misc_gex)


add_executable(070_List ${070}list.hpp
                        ${070}main.cpp
)
target_link_libraries(070_List Misc_gex)


add_executable(080_Vector ${080}vector.hpp
                          ${080}main.cpp
)
target_link_libraries(080_Vector Misc_gex)


add_executable(090_BinTreeSimple ${090}bin_tree_s.hpp
                                 ${090}main.cpp
)
target_link_libraries(090_BinTreeSimple Misc_gex)


add_executable(100_BinTree ${100}bin_tree.hpp
                           ${100}main.cpp
)
target_link_libraries(100_BinTree Misc_gex)


add_executable(Misc_vec ${VEC}vec.hpp
                        ${VEC}main.cpp
)               
target_link_libraries(Misc_vec Misc_gex)


add_executable(110_BinTreeSort ${110}bin_tree_sort.hpp
                               ${110}main.cpp
)
target_link_libraries(110_BinTreeSort Misc_gex)


add_executable(120_RedBlackTree ${120}red_black_tree.hpp
                                ${120}main.cpp
)
target_link_libraries(120_RedBlackTree Misc_gex)


add_executable(121_Set ${121}set.hpp
                       ${121}main.cpp
)
target_link_libraries(121_Set Misc_gex)
                                         

add_executable(122_Pair ${122}pair.hpp
                        ${122}main.cpp
)
target_link_libraries(122_Pair Misc_gex)

                                        
add_executable(123_Map ${123}map.hpp
                       ${123}main.cpp
)
target_link_libraries(123_Map Misc_gex)


add_executable(140_RedBlackTreeMulti ${140}red_black_tree_multi.hpp
                                     ${140}main.cpp
)
target_link_libraries(140_RedBlackTreeMulti Misc_gex)


add_executable(141_MultiSet ${141}multiset.hpp
                            ${141}main.cpp
)
target_link_libraries(141_MultiSet Misc_gex)


add_executable(142_MultiMap ${142}multimap.hpp
                            ${142}main.cpp
)
target_link_libraries(142_MultiMap Misc_gex)


add_executable(150_PriorityQueue ${150}priority_queue.hpp
                                 ${150}main.cpp
)
target_link_libraries(150_PriorityQueue Misc_gex)
        
        
add_executable(160_HuffmanTree ${160}huffman_tree.hpp
                               ${160}main.cpp
)
target_link_libraries(160_HuffmanTree Misc_gex)
        
        
add_executable(170_HashArraySimple ${170}hash_array_s.hpp
                                   ${170}main.cpp
)     
target_link_libraries(170_HashArraySimple Misc_gex)

             
add_executable(180_HashArray ${180}hash_array.hpp
                             ${180}main.cpp
)
target_link_libraries(180_HashArray Misc_gex)
              
add_executable(181_HashArrayV2 ${181}hash_array_v2.hpp
                               ${181}main.cpp
)
target_link_libraries(181_HashArrayV2 Misc_gex)
              
add_executable(182_UnorderedSet ${182}unordered_set.hpp
                                ${182}main.cpp
)
target_link_libraries(182_UnorderedSet Misc_gex)
              
add_executable(183_UnorderedMap ${183}unordered_map.hpp
                                ${183}main.cpp
)
target_link_libraries(183_UnorderedMap Misc_gex)
              
            
add_executable(190_HashArrayMulti ${190}hash_array_multi.hpp
                                  ${190}main.cpp
)
target_link_libraries(190_HashArrayMulti Misc_gex)

add_executable(191_UnorderedMultiset ${191}unordered_multiset.hpp
                                     ${191}main.cpp
)
target_link_libraries(191_UnorderedMultiset Misc_gex)
              
add_executable(192_UnorderedMultimap ${192}unordered_multimap.hpp
                                     ${192}main.cpp
)
target_link_libraries(192_UnorderedMultimap Misc_gex)


add_executable(Misc_sld ${SLD}sld.hpp
                        ${SLD}main.cpp
)


add_executable(Misc_tests ${TST}main.cpp
                          ${TST}stack_tests.hpp
                          ${TST}queue_tests.hpp
                          ${TST}deque_tests.hpp
                          ${TST}list_tests.hpp
                          ${TST}vector_tests.hpp
                          ${TST}bin_tree_tests.hpp
                          ${TST}hash_array_tests.hpp
)
target_link_libraries(Misc_tests Misc_gex)


add_executable(test ${TEST}main.cpp
)
target_link_libraries(test Misc_gex)


