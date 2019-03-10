Extra Credit:
- Metadata size: 2 Bytes


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
			- combine with previous block if previous block's set bit is 0  (update size of prev to be prev size + curr sie+ 2 for metadata block )
			- do nothing if previous block is in use
		
		- Prev block is not null and Next block is not null
			- check if next block's set bit block is 0, if it is then combine current and next and set current's set bit to 0. 


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



