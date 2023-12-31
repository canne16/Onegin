#include "lib.cpp"


#ifndef DEBUG
    #define RELEASE
#endif


int main(int argc, char* argv[])
{

    // Preparing files
    FILE* input  = NULL;
    FILE* output = fopen("output.txt", "w");

    if (checkargs(argc, argv) == NO_FILENAME)
        assert("No input file proceeded\n");

    if (( input = fopen(argv[1], "r")) == NULL)
    {
        printf("Cannot open file.\n");
        return OPEN_FILE_ERROR;
    }

    // Initializing buffer,
    struct stat file_info = {};
    fstat( fileno(input), &file_info );

    const size_t buf_len = file_info.st_size / sizeof(char);
          char*  buf     = (char*) calloc(buf_len + 1, sizeof(char));          // 1 byte if file dosn't end with '\n'


    // Reading file into buffer
    size_t     read_len   = fread(buf, sizeof(char), buf_len, input);
    size_t     rows_count = countrows(buf, read_len);

    Text_info* Text       = (Text_info*) calloc(1, sizeof(Text_info));
    create_text(Text, rows_count);

    assert( !read_text(buf, read_len, Text) );


    // Sorting data
    #ifdef DEBUG
        const int data_size = 20;
        int** data = (int**) calloc(data_size, sizeof(int*));
        assert(data);
        srand(time(NULL));

        for (int i = 0; i < data_size; i++)
        {
            data[i] = (int*) calloc(1,sizeof(int));
            *data[i] = rand() % 20;
            //printf("%d ", *data[i]);
        }

        Sort(data, data_size, sizeof(int*), (int (*) (const void* a, const void* b)) int_comp);

        test_sort(data, data_size);
    #else
        Sort(Text->text, Text->row_num, sizeof(char*), (int (*)(const void*, const void*)) str_bkw_comp);

        // Printing sorted data
        print_text_to_file(Text, output);
    #endif
    // Clearing memory

    fclose(input);
    fclose(output);
    free_text(Text);
    free(buf);

    return MEOW;
}

