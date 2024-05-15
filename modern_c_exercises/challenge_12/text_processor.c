/*For a text processor, can you use a doubly linked list to store text?
The idea is to represent a “blob” of text through a struct that contains a string (for the text) and pointers to preceding and following blobs.
Can you build a function that splits a text blob in two at a given point?
One that joins two consecutive text blobs?
One that runs through the entire text and puts it in the form of one blob per line?
Can you create a function that prints the entire text or prints until the text is cut off due to the screen size?*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct text_blob text_blob;
struct text_blob {
    text_blob* next;
    text_blob* prev;
    char* text;
};

/*pure function to create a text blob*/
text_blob tb_create(text_blob* prev, text_blob* next, char* text) {
    text_blob blob = {
        .next = next, 
        .prev = prev,
        .text = text,
    };

    return blob;
}

/*wrapper for create to work with pointers*/
text_blob* tb_init(text_blob* blob, text_blob* prev, text_blob* next, char* text) {
    if (blob) 
        *blob = tb_create(next, prev, text);
    return blob;
}

/*to zero a text blob*/
void tb_zero(text_blob* blob) {
    *blob = (text_blob){0};
}

/*print text of linked blobs till end of chain*/
void tb_print(text_blob* blob) {
    size_t num = 1;
    while (blob) {
        printf("Blob %zu: \"%s\"\n", num, blob->text);
        ++num;
        blob = blob->next;
    }
    printf("\n");
}

/*count the nodes till you hit null pointer*/
size_t tb_count(text_blob* blob) {
    size_t count = 0;
    while (blob) {
        blob = blob->next;
        ++count;
    }
    return count;
}


/* TODO: figure out to stop losing the string to the function scope deallocate */
text_blob tb_split(text_blob blob, char* to_split, size_t split_point) {
}

int main(void) {
    char* text = "this is main text.";
}
