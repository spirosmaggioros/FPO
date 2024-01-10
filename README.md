# Polynomials representation using AVL Trees
We present a data structure based on AVL Trees , used for polynomial representation , which allows insertion to be performed in $O(logn)$. This structure is mostly used for sparse polynomials as experimental results showed that it has a much lower space complexity than other data structures used to store polynomials.

# Theory
Polynomials exists everywhere, from computer science , biology , cryptography , to
physics and robotics.They are used in calculus and numerical analysis to approximate 
other complex functions.Polynomials are also useful in algebra and algebraic geometry as 
they are used to construct polynomial rings and algebraic varieties. 
There exists many balanced trees having a worst case behavior of O(logn) for opera-
tions such as Search , Insert and Delete in a tree of n nodes. AVL trees were introduced by 
Adel’son-Vel’skii and Landis (1962) , they are a special kind of binary tree that is strongly 
balanced.That means that the heights of the two child subtrees of any node differ by at 
most one.That will ensure as that the insertion will take at most O(logn) time as the 
tree remain balanced at every insertion or deletion.Insertions and deletions may require 
the tree to be rebalanced by one or more tree rotations.Taking advantage of those proper- 
ties , we can create a tree-like structure for polynomial representation , which is strongly 
balanced and sorted with no further operations.Polynomials can be represented in many 
ways , using dynamic arrays or linked lists.Every data structure has it’s advantages and 
drawbacks , but , when it comes to sparse polynomials , experimental results showed that 
using AVL trees , execution time is significantly reduced.

