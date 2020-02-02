# Harvard CS50x 2020 Problem Set 1

This problem set consist of 3 questions (1 optional ones), kindly refer to this link for more info: https://cs50.harvard.edu/x/2020/psets/2/

- [x] **Readability**: Problem statement looks at how input text can be graded using Coleman-Liau index
- [x] **Caesar**: creates encrypted messages by getting users to input integar key (number of 'steps' to shift alphabetical words) and desired string to output an encrypted message.  

Eg. 

./caesar 5 

| plain_text | H | E | L | L | O | ! |
|------------|---|---|---|---|---|---|
| cipher_text| M | J | Q | Q | T | ! |


- [x] **Substitution**: creates encryped messages by getting users to input the encryption key (26 alphabets) and desired message to output an encrypted message. The 26 letter key is jumbled up but its position relative to the alphabets (in order) determines the encrypted message. 

Eg.

./substituition JTREKYAVOGDXPSNCUIZLFBMWHQ

| plain_text | A | B | C | D | E | ! |
|------------|---|---|---|---|---|---|
| cipher_text| J | T | R | E | K | ! |
