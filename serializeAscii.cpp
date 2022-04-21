#include <iostream>
#include <cctype>
#include <sstream>
#include <bitset>

/***
Program to serialize and deserialize the ascii values from 1 to 255, OR all possible values in an unsigned char.

This seems a simple task since the values could be stored in an unsigned char,serialized using stringstream and deserialized again.
However storing the values as a stream of unsigned chars, doesnt seem to work.

The solution is to have extra padding bits, storing the values as unsigned shorts, 
deserializing and converting them back to unsigned chars.
***/

int main()
{
    unsigned char arr[256];
    unsigned char asciiArr[256];

    std::stringstream ss; 

    for(int i=1;i<=255;++i) {
        arr[i] = i;
#if 0
        ss << arr[i] << ' ';
#else
        ss << static_cast<unsigned short>(arr[i]) << ' ';
#endif
    }   

    for(int i=1;i<=255;++i)
    {   
#if 0
        ss >> asciiArr[i];
#else
        unsigned short value=0;
        ss >> value;
        asciiArr[i] = static_cast<unsigned char>(value);
#endif
        std::cout << "arr[" << i << "]:" << std::bitset<8>(arr[i]) << ", asciiArr[" << i << "]:" << std::bitset<8>(asciiArr[i]) << std::endl;
        std::cout << "arr[" << i << "]:" << arr[i] << ", asciiArr[" << i << "]:" << asciiArr[i] << std::endl;

        if(arr[i] != asciiArr[i])
            std::cout << "asciiArr[" << i << "] != asciiArr[" << i << "]" << std::endl;
    }   

   return 0;    
}
