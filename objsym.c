#include "bfd.h" //The BFD libary 
#include <stdio.h> 

//This is the callback function for the map_over_section loop 
//Takes a pointer of
#include <stdio.h>
#include <unistd.h>
#include "header.h" //The header.h has the function prototypes that are in the static librbary 
#include <stdlib.h>
#include <string.h> 
/*number, where the character string will be stored, the width of the hex string*/
void convert_int_to_hex_objsym(int number, char * buffer, int width){
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

int getsymb(bfd *abcd){
    
        long storage_needed = bfd_get_symtab_upper_bound(abcd);
        char buffer [storage_needed];  //Creating a buffer of size upper_bound 

        if(storage_needed > 0)
        {
            asymbol **symbol_table = (asymbol**)malloc(storage_needed); // Assigning storage of pointer type asymbol
            long num_of_symbols = bfd_canonicalize_symtab(abcd, symbol_table); //The number of symbols exist in the symbol table

            for(long x = 0; x < num_of_symbols; x++)
            {
                asymbol *symbol = symbol_table[x]; //Pointer to each element of symbol tale 
                bfd_vma symbol_address = bfd_asymbol_value(symbol);  //Getting the address 

                unsigned int address = (unsigned int)symbol_address;  //Convert symbol_address to int type 
                write(1, symbol->name, strlen(symbol->name)); //Writting symbol name
                write(1, ": ",2); 
                convert_int_to_hex_objsym(address, buffer, 16);  //Convert into Hex 
                write(1, buffer, 16); 
                write(1, "\n", 1); 


                /*
                int len = snprintf(buffer, sizeof(buffer), "%s: %016llx\n", name, (unsigned long long)symbol_address); 
                if(len >= sizeof(buffer) || len < 0)
                    return 1; 
                write(1, buffer, len); */ 

            }
            free(symbol_table); 

            }
        return 0; 
}