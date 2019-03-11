Extra Credit:
- Metadata size: 2 Bytes
The meta data was sorted in chars because the chars are guaranteed to be a single byte. We are using two chars to store all of the metadata (). 
we bit shifted and masked in order to store data. Since the memory array is 4096 bytes, we need a minimum of 12 bits (2^12=4096) to store the size. Since the key takes up 2 bytes and metadata blocks take up 2 bytes, the most we can allocate in one block is 4092, therefore, 2^12 fits our requirements in terms of bits. The 12 rightmost bits store the size bits and the left most bit is the in use bit. If the block has been given to the user by malloc then the in use bit will be 1 else, if the block is free the in use bit is 0. Were using 16 bits however, we really only need 13 bits, however, the extra 3 bits that are wasted do not make much of a difference in terms of space usage. The 3 bits will take some time to add up to a significant amount of bytes. Keeping the extra 3 bits help storing and accessing data easier because it makes up 2 blocks of the array. 

Metadata structure: | 1 000 1111| 11110000|  
					  ^     ^
			in use bits     starting of the size bits

Bit shifting and Masking:
Methods:
setInUse - takes in a byte and the bit you want to set the in use bit to
getbit - takes in the byte and the position of bit to extract and returns the value of the bit at that position. used to check the inuse bit
getsizebits - removes the in use bit and returns the size bits from the given byte. 
bin2int - takes in pointers to high and low bytes and converts it into an integer. used for bit add to find the new sum size after combining blocks
splitbin - takes in an integer and divides the bits into two chars to set the size of the metadata



Malloc
- Algorithm:

	- Traversing: mallocTraverse
		-Traverses through the array, checking size bits and in use bits until it reaches a block the same size as or larger than the amount of space requested that isn't in use. If such a block is found, splitblock is called, otherwise an insufficient memory message is displayed.                  

	- Splitting Blocks: splitBlock 
		- How many bytes to give back to user:
			*If the space found is the exact same size as the amount of memory requested by the user, return just that, without altering the blocks adjacent to it.
			*If the space found is larger than the amount being malloced by the user, and has enough space to store metadata plus 2 bytes of memory, the block is split into a block the same size as the size requested, and the in use bit is flipped. The adjacent block's size is set to that of the original block - user requested size, with an in use bit set to zero.
			*If the space found is larger than the user requested size, but fewer than 4 bytes larger (2 metadata bytes + 2 data bytes), the whole block is returned to the user, without splitting.
			
		- Setting in use bits: In use bits are set using the get bit method, specifically to set a block to 'in use' status, or if a block is being split, to 'not in use'.
	
	- Error Checkings
		- size input validity: Checked for a request larger than 4092 bytes (the size of the array, minus the key bytes and the first metadata block) in the main 'mymalloc' function, and for requests less than or equal to zero (because obviously neither a negative malloc nor a malloc of size zero can occur)
	
Free:
- Algorithm:
	- Traversing: 
	I start at the first metadata (&mem[2]) and move to (metadata size +2) and continue until I find the pointer given in by the user or the current pointer to the meta data is greater than the pointer received. Traverses by comparing pointers and accessing size bits in order to move to the next metadata.


- Fragmentation:
	Upon every free, when the right block to free is found, I try to combine any free blocks surrounding the current block. I check if:
		
		- Current block is the only block in the whole memory (mallocd blocksize is 4092 bytes)
			-> Just change set bit to 0
		
		- Curr is first block -> prev is null but next is not
			- combine with next block if next block is not inuse 
			set currents inuse bit to 0
			- just change set bit of current block to 0 if next block is in use
		
		- Curr is last block -> next is null
			- combine with previous block if previous block's set bit is 0  
			update size of prev to be prev size + curr size+ 2 for metadata block 
			- do nothing if previous block is in use
		
		- Prev block is not null and Next block is not null
			-check if next block's set bit block is 0, if it is then combine current and next by changing the size bits of current to currentsize+nextsize+2 and set current's set bit to 0. 
			- check if previous block's inuse bit is 0 if it is 0 combine by updating prev block size to prevsize+currentsize+2
			change current block inuse bit to 0 


- Error Checks:

If any of the following errors were encountered with the pointer received, the error message was returned. 
	- if pointer given is null
	
	- if key is not initialized --> first two bytes should equal 11474 (a predefined key)
			means that no pointers have been mallocd yet
	
	- if pointer is outside the array length/bounds 
			pointer is not mallocd by mymalloc
	
	- if pointer given does not point to the starting of a block of data --> Checked by seeing if address of pointer given matched address of metadata+2

	| metadata byte 1 | metadata byte 2 | blocks 	of 		data  |
										^     				^
				where pointer should be pointing  		where pointer is pointing
									^
if pointer sent in doesnt = address | of above pointer, then return error 


Findings:
	We are able to confirm that our version of malloc and free works because after the workloads were completed, when the first block's size was printed out, it equaled 4092, which is the amount memory we started out with. 
	
	The workloads helped verify that we are able to deal with extremely small mallocs of 1 byte. We are able to give the user exactly what they ask for. Freeing the one byte pointers showed immediately that free worked. When printing out addresses of the pointers given by malloc showed that each of the 50 pointers were of the same address because they were freed after the malloc call. 
	For B, the workload tested free's fragmentation algorithms. By freeing pointers one by one, we are required to combine the blocks if we want to return to the original free block of 4092. 
	C verified that free wont work on not mallocd array. Shows that program can handle what is asked for regardless of when
	For D, mallocing random bytes tested malloc's ability to take in any given request for bytes and evaluate it. If the request can be fulfilled, malloc sent back a pointer. 
	The workloads helped us find errors in our code. In one space the wrong parametor was sent in. 
