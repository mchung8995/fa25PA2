## Entry 1 

**What I tried:** 
I tried to implement the minheap structure to manage the nodes based on their frequency.

**What broke:** 
When I tried to build the tree the nodes were not combining correctly, the smallest ones were not coming first
and the output would produce incorrect results.

**Why it happened:** 
When I look back through the code I used the wrong formula, I had parenthesis around the pos+1 and pos+2
instead of leaving them open. the math was wrong so sometimes larger weights were "smaller".

**Fix:** 
I corrected the math and double checked that in both heap functions nodes were being properly compared, and also
when two nodes were equal I made it so a<b so there is a method in terms of how they got organized.

**Proof it works:** 
After fixing the downheap function the nodes were in the correct order and showing the proper output of correct
combining from smallest to largest.

---
## Entry 2

**What I tried:**
I was building the generateCodes function which uses a stack to perform a iterative dfs on the tree. Everytime
it moves to the left it adds a 0 and when it moves to the right it adds a 1 and when it gets to the leaf node it 
stores the final path as the letters code.

**What broke:**
When I ran the program it would print out "Create x leaf nodes", but that was it there was no code that was outputed
Where there were supposed to print the characters and the code it was left blank.

**Why it happened:**
In generateCodes I had if(root==1) and not if(root==-1) so in the function it would skip valid trees and in the
double if statement in the same function the code that pushes the children to the left and right in the stack
was nested into the wrong if loop and because of that the function would never reach the leaf nodes and would not
display the correct output.

**Fix:**
I correct the root==1 to root==-1 and nested the else block into the correct if loop.

**Proof it works:**
After fixing it when rerunning the program it would display the correct characters and code

---
## Entry 3

**What I tried:**
When testing program with different inputs in the input.txt, I testing multiple things such as an input with
the same characters such as aaaa.

**What broke:**
When inputting only one type of character the program would build one leaf node but nothing would be encoded
because there was no branches since all the nodes were equal

**Why it happened:**
In the generateCodes function it only created code following the paths from the root to the leaves but since
there was only one type of character there were no paths since the tree only had one node

**Fix:**
Added a special case check that when there is only one type of character it would assign that character a 0 so 
when the program was ran it would still output properly

**Proof it works:**
When running the program the correct character and code were outputted

---
## Entry 4

**What I tried:**
When building the buildEncodingTree function I was following the huffman method by taking the two smallest nodes
and make the children of the new parent node then inserting that parent back into the heap until there was only
one root node. To mark parent nodes that didnt represent any letters I assigned them with charArr[curr] = '\\0'.

**What broke:**
When compiling it would get and out an incorrect amount of leaf nodes and print a bunch of characters and codes
that were not part of the input.txt.

**Why it happened:**
Instead of double backslashing it was only supposed to be one. In C++ that means a multicharacter constant so it
would produce a higher integer value rather than what is supposed to be smaller values so the code would be values
such 1100 and 1011 etc.

**Fix:**
I fixed the \\0 to \0.

**Proof it works:**
After making the changed and rerunning the program it would create the correct amount of leaf nodes and print
the correct characters and code.

---
