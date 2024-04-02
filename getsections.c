#include "bfd.h" //The BFD libary 

//This is the callback function for the map_over_section loop 
//Takes a pointer of
#include <unistd.h>
#include "header.h" //The header.h has the function prototypes that are in the static librbary 
#include <stdlib.h>


/*jx is unsigned int but in hexadecimal format 
      08 is format specifer for 8 hexadecimal values 
      Section address = File off (objdump)
    */


int main(int argc, char **argv)
{
    if(argc!=2)
        return 1;

    bfd_init();
    bfd *abcd = bfd_openr(argv[1], NULL); 

    //Checking if pointer is NULL. For pointers in C if pointer is Null, it will return false in conditionals
    if (abcd == NULL){
        bfd_perror("Error Opening File"); 
        return 1; 
    }

    
    //Check if the pointer is of acceptable object file 
    if(!bfd_check_format(abcd, bfd_object))
    {
        bfd_perror("Unsupported File"); 
        bfd_close(abcd); 
        return 1; //Same as above. Returing 1 indictaes failed exit status 
    }


    bfd_map_over_sections(abcd, print_section_info, NULL); //Calling print_section_info function from objsect


    bfd_close(abcd); 

    return 0; 
}
