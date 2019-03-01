//main: if first (2? 4?) bytes arent set to key, set key, and set the first piece of metadata.
/*split method: see how much data user is requesting
at first instance of a space big enough
                      check if metadata has been set after space for allocation
                      if not, set metadata, taking the value originally stored for size of currblock-size of space being allocated
                      ->if too small for metadata+2 bytes, return the whole thing to user
                      update size bits
                      -->if space is bigger than requested

                      --> check to see if  */
