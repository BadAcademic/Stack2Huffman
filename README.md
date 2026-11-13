# C++ Data Structures Course

Source code for a hands-on C++ course on data structures: from stack and queue
to binary trees, red-black trees, a Huffman coder and hash tables. Every lesson
is a small program with its own data structure implementation.

[Русская версия](README.ru.md)

## About

This repository contains the code shown in the course videos. The course is
still in development: some lessons may be incomplete, and the code is written
for teaching clarity first and production robustness second.

## Requirements

- **Visual Studio 2022 or 2026** with the *Desktop development with C++* workload
- **CMake 3.20 or newer** (CMake 4.2+ is required for the `Visual Studio 18 2026` generator)
- C++20 (the project sets `CMAKE_CXX_STANDARD 20`)

The code targets MSVC (Windows). GCC/Clang builds are not supported.

## Building

Generate the build files and build every lesson:

```bat
cmake -B build -G "Visual Studio 18 2026"
cmake --build build --config Debug
```

Use `-G "Visual Studio 17 2022"` with CMake 3.21+ for Visual Studio 2022; the
`Visual Studio 18 2026` generator requires CMake 4.2+.

Build a single lesson by its target name:

```bat
cmake --build build --config Debug --target 160_HuffmanTree
```

Executables are placed in `build\Debug\`. Each lesson is a standalone
executable; the `Misc_gex` static library provides the shared `gexception`
class and is linked into the lessons that use it.

## Lessons

| Folder | Topic | CMake target |
|---|---|---|
| `010_stack_i` | Stack: separate `.h`/`.cpp` implementation | `010_StackI` |
| `011_stack_s` | Stack on a static array | `011_StackS` |
| `012_queue_s` | Queue on a static array | `012_QueueS` |
| `020_stack_t` | Template stack | `020_StackT` |
| `021_queue_t` | Template queue | `021_QueueT` |
| `022_deque_t` | Template deque | `022_DequeT` |
| `030_stack_sp` | Stack that grows on demand | `030_StackSP` |
| `040_stack_f` | Fast stack (raw memory) | `040_StackF` |
| `041_queue_f` | Fast queue (raw memory) | `041_QueueF` |
| `042_deque_f` | Fast deque (raw memory) | `042_DequeF` |
| `043_stack_fv2` | Fast stack, version 2 | `043_StackFv2` |
| `044_queue_fv2` | Fast queue, version 2 | `044_QueueFv2` |
| `045_deque_fv2` | Fast deque, version 2 | `045_DequeFv2` |
| `050_stack_sf` | Static fast stack | `050_StackSF` |
| `051_queue_sf` | Static fast queue | `051_QueueSF` |
| `052_deque_sf` | Static fast deque | `052_DequeSF` |
| `060_stack` | Final stack implementation | `060_Stack` |
| `061_queue` | Final queue implementation | `061_Queue` |
| `062_deque` | Final deque implementation | `062_Deque` |
| `070_list` | Singly/doubly linked list | `070_List` |
| `080_vector` | Dynamic array (`vector`) | `080_Vector` |
| `090_bin_tree_simple` | Simple binary tree | `090_BinTreeSimple` |
| `100_bin_tree` | Binary tree | `100_BinTree` |
| `110_bin_tree_sort` | Tree sort | `110_BinTreeSort` |
| `120_red_black_tree` | Red-black tree | `120_RedBlackTree` |
| `121_set` | Set on a red-black tree | `121_Set` |
| `122_pair` | `pair` container | `122_Pair` |
| `123_map` | `map` on a red-black tree | `123_Map` |
| `140_red_black_tree_multi` | Multi red-black tree | `140_RedBlackTreeMulti` |
| `141_multiset` | Multiset | `141_MultiSet` |
| `142_multimap` | Multimap | `142_MultiMap` |
| `150_priority_queue` | Priority queue | `150_PriorityQueue` |
| `160_huffman_tree` | Huffman tree and encoder | `160_HuffmanTree` |
| `170_hash_array_simple` | Simple hash table | `170_HashArraySimple` |
| `180_hash_array` | Hash table | `180_HashArray` |
| `181_hash_array_v2` | Hash table, version 2 | `181_HashArrayV2` |
| `182_unordered_set` | `unordered_set` | `182_UnorderedSet` |
| `183_unordered_map` | `unordered_map` | `183_UnorderedMap` |
| `190_hash_array_multi` | Multi hash table | `190_HashArrayMulti` |
| `191_unordered_multiset` | `unordered_multiset` | `191_UnorderedMultiset` |
| `192_unordered_multimap` | `unordered_multimap` | `192_UnorderedMultimap` |

## Project layout

```
src/
  010_stack_i … 192_unordered_multimap   one folder per lesson
  Misc_gexception/   gexception exception class (static library Misc_gex)
  Misc_sld/          helper header used by the demos
  Misc_tests/        shared test templates
  Misc_vec/          small dynamic-array helper
  test/              scratch target
CMakeLists.txt       single build configuration for all targets
```

## Notes

- The Huffman lesson (`160_huffman_tree`) reads a `big_data.txt` word list from
  its working directory for the encode demo. That file is not part of the
  repository — supply your own.
- Visual Leak Detector (`src/vld/`) is a third-party tool and is not included.

## License

MIT. Copyright (c) 2026 BadAcademic. See [LICENSE](LICENSE).
