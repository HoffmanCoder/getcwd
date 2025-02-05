void print_cur_dir(size_t size) {
    char * buffer = (char *)alloca(size);
    if (getcwd(buffer, size) == NULL) {

        perror("getcwd");
        exit(EXIT_FAILURE);
    }
    else {
        printf("Current working directory: %s\n", buffer);
    }
}


int main(){

    print_cur_dir(1024);
    return 0;
 }
     
