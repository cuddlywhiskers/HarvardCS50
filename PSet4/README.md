# Harvard CS50x 2020 Problem Set 4

This [problem set](https://cs50.harvard.edu/x/2020/psets/4/) consists of 3 questions.

First two problem statements attempt to create a code that reads, filters and output an image depending on user's desired filter choice. 

- [x] **filter** (less): create four different filter - grayscale, sepia, reflect, blur
- grayscale: creates black-scale image by adjusting each pixel to the avg RBG of that pixel. 
- sepia: applies sepia by by adjusting each pixel with a specific formula 
- reflect: projects a mirror image of the picture by 'swaping' each pixel. 
- blur: blurs an image by taking the average RGB values of 8 other neighbouring pixels around each pixel. 
--- 

- [x] **filter** (more): create four different filter - grayscale, reflect, blur, edges
- grayscale: creates black-scale image by adjusting each pixel to the avg RBG of that pixel. 
- reflect: projects a mirror image of the picture by 'swaping' each pixel. 
- blur: blurs an image by taking the average RGB values of 8 other neighbouring pixels around each pixel. 
- edges: detects edges of an image and creates boundary between one object with another. 
---

- [x] **recover**: recover JPEGs photo found in raw card format. 

`recover.c` attempts to recover deleted photos using pointers, file pointers (fopen, fread)! However, not all info in the raw card are jpeg, the code then breaks the card into 512 byte chunks and search for jpeg headers. A new jpg file is then created in memory and written into file. Subsequent jpeg files are created and info from raw card are continously written until all jpeg files were recovered. 
