#include "bfd.h" //The BFD libary 


//This is the callback function for the map_over_section loop 
//Takes a pointer of

#include <unistd.h>
#include "header.h" //The header.h has the function prototypes that are in the static librbary 
#include <stdlib.h>
#include <dlfcn.h>
#include <fcntl.h>


#define RDTSC(var)                                              \
{                                                             \
    uint32_t var##_lo, var##_hi;                                \
    asm volatile("lfence\n\trdtsc" : "=a"(var##_lo), "=d"(var##_hi));     \
    var = var##_hi;                                             \
    var <<= 32;                                                 \
    var |= var##_lo;                                            \
}

//Convert float to string 
void convert_float_str(double number, char * buffer, int decimalPlace){
    if(decimalPlace < 0) decimalPlace = 0; //Error handling

	long long intPart = (long long) number; //Trunactes the decimals 
    int i = 0; 
	
	while (intPart!= 0) {
        buffer[i++] = intPart % 10 +  '0'; //Converting to Assci Character 
		intPart = intPart / 10;
	}

	//Reverse 
    for(int j = 0; j < i / 2; j++) //Preincrement
    {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1]; 
        buffer[i - j - 1] = temp; 
    }

    //Now decimal Point handling
    if(decimalPlace > 0)
    {
        buffer[i++] = '.';
        double fractionalPart = number - (long long)number;
        for (int j = 0; j < decimalPlace; j++) {
            fractionalPart *= 10;
            int digit = (int)fractionalPart % 10;
            buffer[i++] = digit + '0';
        }
    }
    buffer[i] = '\0'; // Terminate

}



int main(int argc, char **argv)
{//char pointer Argv array argv[0] - programs name, argv[1] - path to bianry file, argv[2] = dlFlag] 
//argc is the Argument counte

    int fd; //File Descriptor 
    if(argc != 3) //Should pass in two arguments 
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
    
    int dl_flagType = 0; 
    unsigned long long start, finish; 
    float time; //For timer 

    if(strcmp(argv[2], "RTLD_LAZY") == 0){ //Getting the section argument and checking the type using cmp function 
        dl_flagType = RTLD_LAZY; 
        fd = open("getsections_d1_RTLD_LAZY.time.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
    }

    if(strcmp(argv[2], "RTLD_NOW") ==0){
        dl_flagType = RTLD_NOW; 
        fd = open("getsections_d1_RTLD_NOW.time.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
    }
    RDTSC(start); //Start timing function 
    void *handle = dlopen("./libobjdata.so", dl_flagType);  //Get a pointer to the librabry 
    RDTSC(finish); //Finish timing function 
    time = ((float)(finish - start)/2200000000) * 1000;  //CPU Base Clock Speed is 2.2 GHZ.
    
    if(!handle) //If file fails to open and dlopen returns null 
        return 1; 
    //Creating Buffer
    char buffer[40]; 
    //convert float to string buffer
    convert_float_str(time, buffer, 6); 

    //FileDescriptor open file using low programing language
    
    if(fd != -1) //Success code 
    {
        write(fd, buffer, strlen(buffer)); 
        write(fd, "\n", 1); //Writting a new line 
        close(fd); 
    }
    else 
        return 1;
   

    //Function pointer 
    //A function pointer named print_section_ptr that expects a void return type with the three following parametrs listed 
    void (*print_section_ptr)(bfd *, asection *, void *); 

    /*dlysm looks up the function symbol in "" shared librabry pointed by handle returns void pointer 
    whcih then is derfrenced... double casting happening here*/
    *(void **) (&print_section_ptr) = dlsym(handle, "print_section_info"); 

    const char *error = dlerror(); 
    if(error) //If error is not null it means an error message is present (Will evalute to true) if there is error message
        return 1; 
    


    bfd_map_over_sections(abcd, print_section_ptr, NULL); //Calling print_section_info function from objsect 

    return 0; 
}