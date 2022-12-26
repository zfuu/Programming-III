#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define L 256

struct cell {
    char *word;
    struct cell *next;
};
char buf[L];
struct cell *main_list = NULL;


void print_list(struct cell *head) {
    while (head != NULL) {
        printf("%s\n", head->word);
        head = head->next;
    }
}


int get_word(FILE *fp, char buf[]){
    int ch, k = 0;

    while (!isalpha(ch = getc(fp)) && ch != EOF);
    if (ch == EOF) return 0;

    buf[k++] = ch;
    while ((ch = getc(fp)) != EOF && isalpha(ch))
        buf[k++] = ch;
    buf[k] = '\0';
    return 1;
}


// Return the last element of a list. Argument can't be null.
struct cell *get_last_cell(struct cell *head) {
    if (head == NULL) {
        fprintf(stderr, "Can't get the last element of NULL list\n");
        exit(1);
    }

    if (head->next == NULL) return head;
    else return get_last_cell(head->next);
}


// Return the result of joining two lists. The first list can't be NULL.
void join_lists(struct cell *first_list, struct cell *second_list) {
    if (first_list == NULL) {
        fprintf(stderr, "When joining lists the first list can't be NULL\n");
        exit(1);
    }

    get_last_cell(first_list)->next = second_list;
}


// A version of join_lists which handles the first list being NULL by simply
// assigning the second list to it instead. For that it requires that a pointer
// to the first head is provided.
void join_lists2(struct cell **first_head_pointer, struct cell *second_list) {
    if (*first_head_pointer == NULL) *first_head_pointer = second_list;
    else join_lists(*first_head_pointer, second_list);
}


// Append the word to the list as a new cell. If the list itself is empty, the
// new cell becomes the first element in the list.
void list_append(struct cell **head_pointer, char *word) {
    struct cell *new = malloc(sizeof(struct cell));
    new->word = (char *)malloc(strlen(word)+1);
    strcpy(new->word, word);

    join_lists2(head_pointer, new);
}


// Unlink the cell from the following cells. Return the remaining cells.
struct cell *unlink_cell(struct cell *head) {
    struct cell *next = head->next;
    head->next = NULL;
    return next;
}


// Sorts the given list in place.
void sort(struct cell **head_pointer) {
    struct cell *head = *head_pointer;
    if (head == NULL || head->next == NULL) return;

    int cmp;
    // lt and gt are initially empty. head is an element of eq from the start.
    struct cell *lt = NULL, *eq = head, *gt = NULL;
    char *key = head->word;

    // The `head = unlink_cell(head)` call serves two purposes. First, it makes
    // sure that head - which just been joined to one of the other
    // lists(lt/eq/gt) - unlinks from the remaining elements, as they don't
    // necessarily belong to the same group. Second, it makes head point to the
    // next element, so that it can be joined to its appropriate group as well.
    while ((head = unlink_cell(head)) != NULL) {
        cmp = strcmp(head->word, key);

        if (cmp < 0) join_lists2(&lt, head);
        else if (cmp == 0) join_lists(eq, head);
        else join_lists2(&gt, head);
    }

    sort(&lt);
    sort(&gt);
    join_lists2(&lt, eq);
    join_lists(lt, gt);
    *head_pointer = lt;
}


int main(int argc, char *argv[]){

    FILE *fp;

    for (int i = 1; i < argc; i++) {
        if ((fp = fopen(argv[i], "r")) == NULL) {
            fprintf(stderr, "Can't open %s\n", argv[i]);
            continue;
        }

        while (get_word(fp, buf)){
            list_append(&main_list, buf);
        }
        fclose(fp);
    }

    sort(&main_list);
    print_list(main_list);

}
