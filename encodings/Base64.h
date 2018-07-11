// Base64.h
// Codificador Base64
int Base64Decode(const char* message, char** buffer); 
int Base64Decode(char* b64message, char** buffer); 
int calcDecodeLength(const char* b64input); 
