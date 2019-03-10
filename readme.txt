Extra Credit:
- Metadata size: 2 Bytes
we bit shifted and masked in order to store data. Since the memory array is 4096 bytes, we need a minimum of 12 bits (2^12=4096) to store the size. the 12 rightmost bits store the size bits and the left most bit is the in use bit. if the block hs been given to the user by malloc then the in use bit will be 1 else, if the block is free the in use bit is 0. Were using 16 bits however, we really only need 13 bits, however, the extra 3 bits that are wasted do not make much of a difference in terms of space usage. the 3 bits will take some time to add up to a significant amount of bytes. Keeping the extra 3 bits help storing and accessing data easier because it makes up 2 blocks of the array. 

Metadata structure: | 1 000 1111| 11110000|  
					  ^     ^
			in use bits     starting of the size bits


Free:
- Algorithm:
	- Traversing:

- Fragmentation:
	Upon every free, when the right block to free is found, I check if:
		
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


