1. I would write proper exception handlers for each type of possible error (Memory allocation, wrong inputs etc).
2. I would closely hanlde exceptions. 
3. I would optimize and instead of shared_ptr use raw pointers to reduce memory usage. 
4. I would fine tune MultiMap.h in MultiMap to handle the memory usage (replaced list with dumb implementation).
5. I assumed when we delete entries by the name, we delete only one (first searched entry). Otherwise the code can be adapted to support multiple names. 
6. I would write regex that validates inputs email.
7. I would add a register of cities and town and in the case if city or the town doesn't appear, I would prompt the error. 
8. Optimization with regards to writing to sstream and then just write all the entries on the disk. 