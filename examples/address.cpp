/*
 Creating a Base58Check-encoded bitcoin address from a private key.
 Code from Mastering Bitcoin, by Andreas M. Antonopoulos (O'Reilly), chapter 4 
 page 75,76. 
 Exemple only. Not to be used in implementation. 
 Date : April 14th 2016 
*/

#include <bitcoin/bitcoin.hpp> 

int generate_address(){
	
	//Private secret key
	bc::ec_secret secret; 
	bool success = bc::decode_base16(secret, 
		"038109007313a5807b2eccc082c8c3fbb988a973cacf1a7df9ce725c31b14776"); 

	assert(success); 
	//Get public key 
	bc::ec_point public_key = bc::secret_to_public_key(secret); 
	std::cout<< "Public key: " << bc::encode_hex(public_key) << std::endl; 

	//Create bitcoin address 
	//Normally can use: 
	//  bc::payment_address payaddr; 
	//  bc::set_public_key(payaddr, public_key); 
	//  const std::string address = payaddr.encoded(); 

	//Compute hash of public key for P2PKH 
	const bc::short_hash hash = br::bitcoin_short_hash(public_key);

	bc::data_chunk unencoded_address; 

	// Reserve 25 bytes
	//  [ version  : 1  ]
	//  [ hash     : 20 ]
	//  [ checksum : 4  ]
	unencoded_address.reserve(25); 

	//Version byte, 0 is normal BTC address (P2PKH)
	unencoded_address.push_back(0); 

	//Hash data 
	bc::extend_data(unencoded_address, hash); 

	//Checksum is computed by hashing data, and adding 4 bytes from hash
	bc::append_checksum(unencoded_address); 

	//Finally we must encode the result in Bitcoin's base58 encoding
	assert(unencoded_address.size() == 25); 

	const std::string address = bc::encode_base58(unencoded_address); 

	std::cout << "Address: " << address << std::endl; 

	return 0;  
}
