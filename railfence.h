#pragma once
#include <cmath>
#include <iostream>

struct railfence_cipher {

  private:
    uint key;
  
  public:
    
	railfence_cipher(size_t key) {
		this->key = key;
	}

  std::string * encrypt(std::string);
  std::string * decrypt(std::string *);

};

