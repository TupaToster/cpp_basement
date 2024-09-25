Insert summary cache size in pages (note that approximately 50%% of it will go to A1 and the rest to Am) : Insert number of requests : No insert 7 numbers that will represent page numbers to look up:
Now chill out and enjoy the testing)
0
a1 : [1, end]
a1_map : [<1, 0>, end]
am : [end]
am_map : [end]

0
a1 : [2, 1, end]
a1_map : [<2, 0>, <1, 1>, end]
am : [end]
am_map : [end]

0
a1 : [3, 2, 1, end]
a1_map : [<3, 0>, <2, 1>, <1, 2>, end]
am : [end]
am_map : [end]

1
a1 : [3, 2, end]
a1_map : [<3, 0>, <2, 1>, end]
am : [1, end]
am_map : [<1, 0>, end]

1
a1 : [3, end]
a1_map : [<3, 0>, end]
am : [2, 1, end]
am_map : [<2, 0>, <1, 1>, end]

1
a1 : [3, end]
a1_map : [<3, 0>, end]
am : [1, 2, end]
am_map : [<2, 1>, <1, 0>, end]

1
a1 : [3, end]
a1_map : [<3, 0>, end]
am : [2, 1, end]
am_map : [<2, 0>, <1, 1>, end]


Now lets compare it to an ideal cache-------------------------
requests : [1, 2, 3, 1, 2, 1, 2, end]
cache : [end]
cache_map : [end]
dist_map : [<3, {2, 4294967295, end}>, <2, {1, 4, 6, 4294967295, end}>, <1, {0, 3, 5, 4294967295, end}>, end]
dist_set : [<3, {2, 4294967295, end}>, <2, {1, 4, 6, 4294967295, end}>, <1, {0, 3, 5, 4294967295, end}>, end];
-------------------------
