
#include "bfd.h"
#include <unistd.h> //Need it for the write function 
#include <string.h> 


/*number, where the character string will be stored, the width of the hex string*/
void convert_int_to_hex(int number, char * buffer, int width){
    const char *hex_digits = "0123456789abcdef";

    int index = width -1; 
    buffer[index + 1] = '\0';  //Add the \0 terminator to the string 

    while(index >= 0) //As long as there is still width to fill
    {
        buffer[index] = hex_digits[number % 16]; //Match to hex equivalent 
        number /= 16; 
        index--;  //Decrement index to get one length closer to zero 
    }
	for(int x = 0; x <= index; x++) //Fulfing the remaining width with zeros 
    {
        buffer[x] = '0'; 
    }
}



int print_section_info(bfd *abcd, asection *sect, void *obj)
{
    int len; 
    char buffer[1024]; /*Just manually define the buffer size of type character*/


   // len = snprintf(buffer, sizeof(buffer), "Section name: %s\n",sect->name);
    /*snprintf inputs (Where to store the string, max number of charactes that can be stored, formatting)*/
    //if(len >= sizeof(buffer) || len <= 0)
        //return 1;  
    //write(1, buffer, len); /*File Descriptor, pointer to written data, numOfBytes need to be written to the FiLeD*/ 


    write(1, "Section Name: ", 14); 
    write(1, sect->name, strlen(sect->name)); 
    write(1, "\n", 1);  

    convert_int_to_hex(sect->size, buffer, 8);
    write(1, "Cooked Size: 0x", 15);
    write(1, buffer, 8); 
    write(1, "\n", 1); 

    convert_int_to_hex(sect->vma, buffer, 16);
    write(1, "VMA: ", 5); 
    write(1, buffer, 16); 
    write(1, "\n", 1); 

    convert_int_to_hex(sect->filepos, buffer, 8);
    write(1, "Section Address: 0x ", 20); 
    write(1, buffer, 8); 
    write(1, "\n", 1); 

    

return 0; 

}
