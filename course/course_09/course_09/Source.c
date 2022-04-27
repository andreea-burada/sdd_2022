// test curs - 25 mai 11:00 sala 0435 (1p)

/*
			--- Course 09 ---

 - heap or priority queue
 - uses arrays but also some char. from trees (complete binary trees)
 - heap = specialized tree-based data structure that satisfies: if A parent of B 
		-> between A and B - semnatic relation of total order applied

 - if values of children lower than the parent -> MAX heap
 - if values of children higher than the parent -> MIN heap

 - queue as array -> array 0 1 2 3 4 -> 0 - get; 4 - put
	-> we go from left to right when we insert/extract
	-> we use two indexes: left and right or first and last

 - full binary tree = all parents have 2 children except the leaves
 - complete binary tree = the last level does not necesarily have all the leaves
 						-> complete binary trees are completed from left to right
						-> when deleting from binary trees we go from right to left

 --- decendent formulas ---
 left desc = 2 * i + 1
 right desc = 2 * i + 2

 --- parent formula --- 
 (i - 1) / 2	(partea intreaga)

 - liniarization of a binary tree -> putting element after element, taken level by level
 - in a MAX/MIN heap the MAX/MIN values can be accessed with constant (O(1)) complexity

 - priority queues -> HEAP SORT

 --- priority queue specific functions ---

 insert - put
 extract - get
 max/min - peek
 increasePriority

 - finding a MAX in a MIN heap -> extracting all of the elements -> the last one will be the MAX (O(n) complexity)
 - finding a MIN in a MAX heap -> extracting all of the elements -> the last one will be the MIN (O(n) complexity)

 */