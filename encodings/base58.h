/*
* Base58 encoding is used for encoding byte arrays into human-typable strings.  
* It avoids the characters that loook the same (O-0, l-1) in some fonts, and the signs present in base64. 
* The benefits for encoded-addresses are: 
* - A string with non-alphanumeric characters is not as easily accepted as an account number.
* - E-mail usually won't line-break if there's no punctuation to break at.
* - Doubleclicking selects the whole number as one word if it's all alphanumeric.
*
* Source info: https://en.bitcoin.it/wiki/Base58Check_encoding
*/
