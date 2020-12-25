## (WIP) Left-leaning red-black tree implementation (Sedgewick 2008)
Uses C++17 (e.g. for `std::optional`)

Compile with `cmake` or e.g.

```
$ g++ -std=c++17 -O3 red_black_tree.cpp -o red_black_tree
$ ./red_black_tree
Test of a left-leaning red-black tree implementation
----------------
Basic check: 
- Fill tree with 16 random elements
- Print tree
RedBlackTree (r=right child, l=left child)
296
├r(blk)── 17180
|     ├r(blk)── 18642
|     └l(red)── 8191
|          ├r(blk)── 16469
|          └l(blk)── 8167
|               └l(red)── 3060
└l(red)── -5820
     ├r(blk)── -164
     |     ├r(blk)── -22
     |     └l(blk)── -4765
     └l(blk)── -8713
          ├r(blk)── -6052
          └l(red)── -18097
               ├r(blk)── -18009
               └l(blk)── -19628

----------------
Performance check: 
- Execute N initial put operations with random data
- Calculate how fast further put operations are by executing 1000 more
- Multiply N by 10

1000 initial puts with random keys took 0.427872 ms
1000 more puts took 0.503796 ms (0.503796 us/put)
---
10000 initial puts with random keys took 6.19506 ms
1000 more puts took 0.783496 ms (0.783496 us/put)
---
100000 initial puts with random keys took 99.7787 ms
1000 more puts took 1.13429 ms (1.13429 us/put)
---
1000000 initial puts with random keys took 1867.83 ms
1000 more puts took 2.41446 ms (2.41446 us/put)
---
10000000 initial puts with random keys took 32514.5 ms
1000 more puts took 3.8344 ms (3.8344 us/put)
---
^C
```

