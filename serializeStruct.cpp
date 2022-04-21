#include <iostream>
#include <sstream>
#include <cstring>

const int SIZE = 12;

/***
A Program to serialize a complex user defined struct into a stringstream based byte stream.

. The program serializes the sample MyStruct, and compares the values after deserialization.
. The program also creates a new string object extracting it from the stringstream, creates a new stream object using this string.
. It provides the functionality to compare each element of the MyStruct original and deserialized objects.
***/

struct MyStruct
{
    int         IntData;
    float       FloatData;
    char        charData[SIZE];

    unsigned char Char1Bits1:3;
    unsigned char Char1Bits2:1;
    unsigned char Char1Bits3:4;

    unsigned char Char2Bits1:4;
    unsigned char Char2Bit2:1;
    unsigned char Char2Bit3:1;
    unsigned char Char2Bit4:1;
    unsigned char Char2Bit5:1;

    std::string StringData;
};

void PrintMyStruct(MyStruct const & myThing)
{
    std::cout << "IntData : " << myThing.IntData << std::endl;
    std::cout << "FloatData : " << myThing.FloatData << std::endl;

    unsigned char value = 0;
    value = static_cast<unsigned char>(myThing.Char1Bits1); std::cout << "Char1Bits1:" << value << std::endl;
    std::cout << "Char1Bits2 :" << static_cast<unsigned char>(myThing.Char1Bits2) << std::endl;
    std::cout << "Char1Bits3 :" << static_cast<unsigned char>(myThing.Char1Bits3) << std::endl;
    std::cout << "Char2Bits1 :" << static_cast<unsigned char>(myThing.Char2Bits1) << std::endl;
    std::cout << "Char2Bit2 :" << static_cast<unsigned char>(myThing.Char2Bit2) << std::endl;
    std::cout << "Char2Bit3 :" << static_cast<unsigned char>(myThing.Char2Bit3) << std::endl;
    std::cout << "Char2Bit4 :" << static_cast<unsigned char>(myThing.Char2Bit4) << std::endl;
    std::cout << "Char2Bit5 :" << static_cast<unsigned char>(myThing.Char2Bit5) << std::endl;

    std::cout << "charData : " << myThing.charData << std::endl;
    std::cout << "StringData : " << myThing.StringData << std::endl;
}

void PopulateMyStruct(MyStruct & myThing)
{
    myThing.IntData = 42;
    myThing.FloatData = 0.123;
    strcpy(myThing.charData,"aBCDeghryte");

    myThing.Char1Bits1 = static_cast<unsigned char>(7);
    myThing.Char1Bits2 = static_cast<unsigned char>(1);
    myThing.Char1Bits3 = static_cast<unsigned char>(14);
    myThing.Char2Bits1 = static_cast<unsigned char>(12);
    myThing.Char2Bit2 = static_cast<unsigned char>(1);
    myThing.Char2Bit3 = static_cast<unsigned char>(0);
    myThing.Char2Bit4 = static_cast<unsigned char>(0);
    myThing.Char2Bit5 = static_cast<unsigned char>(1);

    myThing.StringData = "My_String_Test with additional spaces";
}

std::stringstream serialize (const MyStruct & my)
{
    std::stringstream ss;

    ss << my.IntData << ' ' << my.FloatData << ' ';

    /// Serialize the C style string
    ss << SIZE;
    std::cout << "Writing SIZE: " << SIZE << std::endl;
    for(int i=0;i<SIZE;++i) {
        ss << my.charData[i];
    }
    ss << ' ';

    /// Serialize the bit values

    ss << static_cast<unsigned short>(my.Char1Bits1) << ' ';
    ss << static_cast<unsigned short>(my.Char1Bits2) << ' ';
    ss << static_cast<unsigned short>(my.Char1Bits3) << ' ';
    ss << static_cast<unsigned short>(my.Char2Bits1) << ' ';
    ss << static_cast<unsigned short>(my.Char2Bit2) << ' ';
    ss << static_cast<unsigned short>(my.Char2Bit3) << ' ';
    ss << static_cast<unsigned short>(my.Char2Bit4) << ' ';
    ss << static_cast<unsigned short>(my.Char2Bit5) << ' ';

    /// Serialize the string
    const int size = my.StringData.size();
    std::cout << "Writing size: " << size << std::endl;
    ss << size;
    for(int i=0;i<size;++i) {
///        std::cout << "cstr[" << i << "]:" << my.str.at(i) << std::endl;
        ss << my.StringData.at(i);
    }
    ss << ' ';

    return ss;
}

MyStruct deserialize (std::stringstream & ss)
{
    MyStruct my;

    /// Deserialze the PODs
    ss
    >> my.IntData
    >> my.FloatData;

    /// Deserialize the C style strings
    int size;
    ss >> size;
    std::cout << "SIZE read: " << size << std::endl;

    ss >> std::noskipws;
    for(int i=0; i<size; ++i)   {
        ss >> my.charData[i];
    }
    ss >> std::skipws;

    /// Deserialize the bit values
    unsigned short value = 0;

    ss >> value; my.Char1Bits1 = static_cast<unsigned char>(value);
    value = 0;
    ss >> value; my.Char1Bits2 =  static_cast<unsigned char>(value);
    value = 0;
    ss >> value; my.Char1Bits3 =  static_cast<unsigned char>(value);
    value = 0;
    ss >> value; my.Char2Bits1 =  static_cast<unsigned char>(value);
    value = 0;
    ss >> value; my.Char2Bit2 =  static_cast<unsigned char>(value);
    value = 0;
    ss >> value; my.Char2Bit3 =  static_cast<unsigned char>(value);
    value = 0;
    ss >> value; my.Char2Bit4 =  static_cast<unsigned char>(value);
    value = 0;
    ss >> value; my.Char2Bit5 =  static_cast<unsigned char>(value);
    value = 0;

    /// Deserialize the String
    size = 0;
    ss >> size;
    std::cout << "size read: " << size << std::endl;

    char str[size];

    my.StringData = "";
    ss >> std::noskipws;

    for(int i=0;i<size;++i) {
        char c;
        ss >> c;
        my.StringData += c;
///        std::cout << "c: " << c << ", my.str:" << my.str << std::endl;
    }
    ss >> std::skipws;

    return my;
}

void compare(const MyStruct & my1, const MyStruct & my2)
{
    if(my1.IntData != my2.IntData)
        std::cout << "my1.IntData != my2.IntData" << std::endl;

    if(my1.FloatData != my2.FloatData)
        std::cout << "my1.FloatData != my2.FloatData" << std::endl;

    if(strcmp(my1.charData,my2.charData))
        std::cout << "strcmp(my1.charData,my2.charData)" << std::endl;

    if(my1.Char1Bits1 != my2.Char1Bits1)
        std::cout << "my1.Char1Bits1 != my2.Char1Bits1" << std::endl;

    if(my1.Char1Bits2 != my2.Char1Bits2)
        std::cout << "my1.Char1Bits2 != my2.Char1Bits2" << std::endl;

    if(my1.Char1Bits3 != my2.Char1Bits3)
        std::cout << "my1.Char1Bits3 != my2.Char1Bits3" << std::endl;

    if(my1.Char2Bits1 != my2.Char2Bits1)
        std::cout << "my1.Char2Bits1 != my2.Char2Bits1" << std::endl;

    if(my1.Char2Bit2 != my2.Char2Bit2)
        std::cout << "my1.Char2Bit2 != my2.Char2Bit2" << std::endl;

    if(my1.Char2Bit3 != my2.Char2Bit3)
        std::cout << "my1.Char2Bit3 != my2.Char2Bit3" << std::endl;

    if(my1.Char2Bit4 != my2.Char2Bit4)
        std::cout << "my1.Char2Bit4 != my2.Char2Bit4" << std::endl;

    if(my1.Char2Bit5 != my2.Char2Bit5)
        std::cout << "my1.Char2Bit5 != my2.Char2Bit5" << std::endl;

    if(my1.StringData != my2.StringData)
        std::cout << "my1.StringData != my2.StringData" << std::endl;

    std::cout << "MyStruct " << &my1 << " and " << &my2 << " are equal" << std::endl;
}

int main()
{
    MyStruct my;
    PopulateMyStruct(my);

    std::cout << "///////////////////////////// Initial values, before serializing ////////////////////////////// " << std::endl;
    PrintMyStruct(my);

    std::stringstream ss;
    ss = serialize(my);

    std::string ssStr(ss.str());

    std::cout << "ss.str(): " << ss.str() << "ss.str().len:" << ss.str().length() << std::endl;
    std::cout << "ssStr: " << ssStr << "ssStr.len:" << ssStr.length() << std::endl;

    MyStruct myStruct = deserialize(ss);
    std::cout << "///////////////////////////// Values, after deserializing ////////////////////////////// " << std::endl;
    PrintMyStruct(myStruct);

    std::cout << "///////////////////////////// Comparing Values my, myStruct ////////////////////////////// " << std::endl;
    compare(my, myStruct);

    std::stringstream ss1(ssStr);
    MyStruct mySt1 = deserialize(ss1);

    std::cout << "///////////////////////////// Comparing Values my, mySt1 ////////////////////////////// " << std::endl;
    compare(my, mySt1);
    std::cout << "///////////////////////////// Comparing Values myStruct, mySt1 ////////////////////////////// " << std::endl;
    compare(myStruct, mySt1);

    return 0;
}
