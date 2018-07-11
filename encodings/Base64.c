#include <openssl/bio.h>
#include <openssl/evp.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include 'Base64.h' 

// Encoder Base64
// Codifica a string de entrada em base64 
int Base64Encode(const char* message, char** buffer){
	BIO *bio, *b64; 
	FILE* stream; 
	int encodedSize = 4*ceil((double)strlen(message)/3); 
	*buffer = (char *)malloc(encodedSize+1); 
	
	stream = fmemopen(*buffer, encodedSize+1, "w"); 
	b64 = BIO_new(BIO_f_base64()); 
	bio = BIO_new_fp(stream, BIO_NOCLOSE); 
	
	// Ignora newlines - escreve tudo em uma linha
	BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); 
	
	BIO_write(bio, message, strlen(message));
	BIO_flush(bio);
	BIO_free_all(bio); 
	
	fclose(stream); 
	return(0); //sucesso
}

// Decoder Base64
// Calcula o tamanho da string base64 decodificada
int calcDecodeLength(const char* b64input){
	int len = strlen(b64input); 
	int padding = 0; 
	
	
	if(b64input[len-1] == '=' && b64input[len-2] == '='){
		padding = 2; // dois ultimos caracteres sao '='
	}else if (b64input[len-1] == '='){
		padding = 1; // o ultimo caractere eh '='
	}
	return (int)len*0.75 - padding;
}

// Decodifica a string codificada em base64 
int Base64Decode(char* b64message, char** buffer){
	BIO *bio, *b64; 
	int decodeLen = calcDecodeLength(b64message); 
	int len = 0; 
	
	*buffer = (char*)malloc(decodeLen+1); 
	FILE* stream = fmemopen(b64message, strlen(b64message), "r");
	
	b64 = BIO_new(BIO_f_base64()); 
	bio = BIO_push(b64, bio); 
	BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Nao use newlines para flush buffer
	len = BIO_read(bio, *buffer, strlen(b64message)); 
	
	// Pode testar aqui, se len == decodeLen - senao, retornar um erro
	(*buffer)[len] = '\0'; 
	
	BIO_free_all(bio); 
	fclose(stream); 
	
	return (0); // sucesso
}

int main(){
	// Codifica em base64 
	Char* base64EncodeOutput; 
	Base64Encode("Hello World", &base64EncodeOutput); 
	printf("Output base64 : %s\n", base64EncodeOutput); 
	
	// Decodifica base64 
	char* base64DecodeOutput; 
	Base64Decode("SGVsbG8gV29ybGQ=", &base64DecodeOutput); 
	printf("Output: %s", base64DecodeOutput); 
	
	return (0); // sucesso
}
