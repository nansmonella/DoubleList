# DoubleList

Multiple data structures are often interlinked or merged to perform complicated tasks. A double list represents two distinct lists over the same group of elements. To be more precise, at any time, a double list D can be viewed as a pair of ordered sequences:
D = (⟨r1,r2,...,rn⟩,⟨b1,b2,...,bn⟩) where the sequences ⟨ri⟩ and ⟨bi⟩ are permutations of each other.

Since the red and the blue lists are defined on the same collection of elements, they are not independent. One cannot update the red list without updating the blue list and vice versa. If an element is removed from the red list, it should also be removed from the blue list. If an element is inserted into the red list, then it should also be inserted into the blue list. The position of insertion, however, may differ for each list.

This project does the implemention of a double list that consists of two non-circular singly linked lists. Since the values stored in both linked lists are identical, the double list uses a single set of nodes to represent both lists at the same time. (That is, the double list does not create two nodes for each element.) To be able to represent two lists with a single copy of nodes, the double list nodes have two separate next pointers, one for the red list and one for the blue list. Similarly, the main structure maintains two head pointers, one for each list.
