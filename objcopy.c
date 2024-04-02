//Starting
#include <elf.h> //ELF header structure 

//Standard librabry headers 
#include <stdlib.h> 

#include <unistd.h> 
#include "bfd.h"
#include <string.h>
#include <dlfcn.h>
#include <fcntl.h>

//New Call Back Function that specifcally looks for the .text section 
void find_text_section(bfd *abcd, asection *sect, void *obj)
{
    if(strcmp(sect->name, ".text") == 0)//If section name is .text
    {
        void *buffer = malloc(bfd_section_size(sect)); //Allocating memory of .text section sie 
        int fd = ("text-output", O_WRONLY | O_CREAT | O_APPEND, 0644); 

        if(fd!=-1)
        {
            //File, section, where contents be copied, start at 0 (copying whole section), end at the end of the section 
            bfd_get_section_contents(abcd, sect, buffer, 0, bfd_section_size(sect)); 
            write(fd, buffer, bfd_section_size(sect)); 
            close(fd);  
        }
        else
        {
            bfd_perror("Error Opening file Writing File");
        }
        
        
        
        
        free(buffer); 
        
    }
}

int main(int argc, char **argv)
{
    //Error checking 
    if(argc!=2)
        return 1; 
    
    bfd_init(); //To use BFD
    bfd *elfFile = bfd_openr(argv[1], NULL);
    //Check if scuessly open 
    if (elfFile == NULL){
        bfd_perror("Error Opening File"); 
        return 1; 
    }
    //Check if the pointer is of acceptable object file 
    if(!bfd_check_format(elfFile, bfd_object))
    {
        bfd_perror("Unsupported File"); 
        bfd_close(elfFile); 
        return 1; //Same as above. Returing 1 indictaes failed exit status 
    }
    
    bfd_map_over_sections(elfFile, find_text_section, NULL);

    bfd_close(elfFile);

    return 0; 
   
    
}