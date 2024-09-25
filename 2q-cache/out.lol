Insert summary cache size in pages (note that approximately 50%% of it will go to A1 and the rest to Am) : Insert number of requests : Now insert 7 numbers that will represent page numbers to look up:
Now chill out and enjoy the testing)
a1 : [end]
a1_map : [end]
am : [end]
am_map : [end]

Test start
0
a1 : [3, end]
a1_map : [<3, 0>, end]
am : [end]
am_map : [end]

0
a1 : [2, end]
a1_map : [<2, 0>, end]
am : [end]
am_map : [end]

0
a1 : [1, end]
a1_map : [<1, 0>, end]
am : [end]
am_map : [end]

0
a1 : [2, end]
a1_map : [<2, 0>, end]
am : [end]
am_map : [end]

0
a1 : [3, end]
a1_map : [<3, 0>, end]
am : [end]
am_map : [end]

0
a1 : [1, end]
a1_map : [<1, 0>, end]
am : [end]
am_map : [end]

1
a1 : [end]
a1_map : [end]
am : [1, end]
am_map : [<1, 0>, end]


Now lets compare it to an ideal cache
-------------------------
requests : [3, 2, 1, 2, 3, 1, 1, end]
cache : [end]
cache_map : [end]
dist_map : [(4)<1, {2, 5, 6, 4294967295, end}>, (3)<2, {1, 3, 4294967295, end}>, (3)<3, {0, 4, 4294967295, end}>, end]
dist_set : [<3, {0, 4, 4294967295, end}>, <2, {1, 3, 4294967295, end}>, <1, {2, 5, 6, 4294967295, end}>, end];
-------------------------
Test start
0
-------------------------
requests : [3, 2, 1, 2, 3, 1, 1, end]
cache : [3, end]
cache_map : [<3, 0>, end]
dist_map : [(4)<1, {2, 5, 6, 4294967295, end}>, (3)<2, {1, 3, 4294967295, end}>, (2)<3, {4, 4294967295, end}>, end]
dist_set : [<2, {1, 3, 4294967295, end}>, <1, {2, 5, 6, 4294967295, end}>, <3, {4, 4294967295, end}>, end];
-------------------------
0
-------------------------
requests : [3, 2, 1, 2, 3, 1, 1, end]
cache : [2, 3, end]
cache_map : [<2, 0>, <3, 1>, end]
dist_map : [(4)<1, {2, 5, 6, 4294967295, end}>, (2)<2, {3, 4294967295, end}>, (2)<3, {4, 4294967295, end}>, end]
dist_set : [<1, {2, 5, 6, 4294967295, end}>, <2, {3, 4294967295, end}>, <3, {4, 4294967295, end}>, end];
-------------------------
0
-------------------------
requests : [3, 2, 1, 2, 3, 1, 1, end]
cache : [2, 3, end]
cache_map : [<2, 0>, <3, 1>, end]
dist_map : [(3)<1, {5, 6, 4294967295, end}>, (2)<2, {3, 4294967295, end}>, (2)<3, {4, 4294967295, end}>, end]
dist_set : [<2, {3, 4294967295, end}>, <3, {4, 4294967295, end}>, <1, {5, 6, 4294967295, end}>, end];
-------------------------
1
-------------------------
requests : [3, 2, 1, 2, 3, 1, 1, end]
cache : [2, 3, end]
cache_map : [<2, 0>, <3, 1>, end]
dist_map : [(3)<1, {5, 6, 4294967295, end}>, (1)<2, {4294967295, end}>, (2)<3, {4, 4294967295, end}>, end]
dist_set : [<3, {4, 4294967295, end}>, <1, {5, 6, 4294967295, end}>, <2, {4294967295, end}>, end];
-------------------------
1
-------------------------
requests : [3, 2, 1, 2, 3, 1, 1, end]
cache : [2, 3, end]
cache_map : [<2, 0>, <3, 1>, end]
dist_map : [(3)<1, {5, 6, 4294967295, end}>, (1)<2, {4294967295, end}>, (1)<3, {4294967295, end}>, end]
dist_set : [<1, {5, 6, 4294967295, end}>, <2, {4294967295, end}>, end];
-------------------------
0
-------------------------
requests : [3, 2, 1, 2, 3, 1, 1, end]
cache : [2, 3, end]
cache_map : [<2, 0>, <3, 1>, end]
dist_map : [(2)<1, {6, 4294967295, end}>, (1)<2, {4294967295, end}>, (1)<3, {4294967295, end}>, end]
dist_set : [<1, {6, 4294967295, end}>, <2, {4294967295, end}>, end];
-------------------------
0
-------------------------
requests : [3, 2, 1, 2, 3, 1, 1, end]
cache : [1, 3, end]
cache_map : [<1, 0>, <3, 1>, end]
dist_map : [(1)<1, {4294967295, end}>, (1)<2, {4294967295, end}>, (1)<3, {4294967295, end}>, end]
dist_set : [<2, {4294967295, end}>, end];
-------------------------
