#include "bfd.h" //The BFD libary 

#include <unistd.h>
#include "header.h" //The header.h has the function prototypes that are in the static librbary 
#include <stdlib.h>
//Hello

int main(int argc, char **argv){
    bfd_init();
    if(argc!=2)
        return 1;

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

    getsymb(abcd); //Caling the getsymb function from objsym
    bfd_close(abcd); 
    return 0; 
}