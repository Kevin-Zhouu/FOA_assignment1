/* Program to generate term-biased snippets for paragraphs of text.

   Skeleton program written by Alistair Moffat, ammoffat@unimelb.edu.au,
   August 2022, with the intention that it be modified by students
   to add functionality, as required by the assignment specification.

   Student Authorship Declaration:

   (1) I certify that except for the code provided in the initial skeleton
   file, the  program contained in this submission is completely my own
   individual work, except where explicitly noted by further comments that
   provide details otherwise.  I understand that work that has been developed
   by another student, or by me in collaboration with other students, or by
   non-students as a result of request, solicitation, or payment, may not be
   submitted for assessment in this subject.  I understand that submitting for
   assessment work developed by or in collaboration with other students or
   non-students constitutes Academic Misconduct, and may be penalized by mark
   deductions, or by other penalties determined via the University of
   Melbourne Academic Honesty Policy, as described at
   https://academicintegrity.unimelb.edu.au.

   (2) I also certify that I have not provided a copy of this work in either
   softcopy or hardcopy or any other form to any other student, and nor will I
   do so until after the marks are released. I understand that providing my
   work to other students, regardless of my intention or any undertakings made
   to me by that other student, is also Academic Misconduct.

   (3) I further understand that providing a copy of the assignment
   specification to any form of code authoring or assignment tutoring service,
   or drawing the attention of others to such services and code that may have
   been made available via such a service, may be regarded as Student General
   Misconduct (interfering with the teaching activities of the University
   and/or inciting others to commit Academic Misconduct).  I understand that
   an allegation of Student General Misconduct may arise regardless of whether
   or not I personally make use of such solutions or sought benefit from such
   actions.

   Signed by: Shiyuan Zhou
   Dated:     8 Sep 2022

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>

/* you may need to delete this next line on some platforms
   in order to get it to compile; if you end up doing that
   make sure you put it back before you submit to the
   Gradescope system, because it is required there */
#include <strings.h>

/* maximum number of characters per word */
#define MAX_WORD_LEN 23
/* maximum number of words per paragraph */
#define MAX_PARA_LEN 10000

/* return code from get_word if end of paragraph found */
#define PARA_END 1
/* return code from get_word if a word successfully found */
#define WORD_FND 2

/* terminating punctuation that may follow a word */
#define TERM_PUNCT ".,;:!?"
/* terminating punctuation that needs dots added */
#define NEEDS_DOTS ",;:"
/* the string the separates paragraphs */
#define PARA_SEPARATOR "\n\n"
/* insertion characters to indicate "bold" */
#define BBOLD "**"
/* length of those characters when wrapped around a word */
#define BBOLD_LEN (2 * strlen(BBOLD))
/* insertion characters to indicate omitted text */
#define DDOTS "..."

/* maximum words in any output snippet */
#define MAX_SNIPPET_LEN 30
/* minimum words in any output snippet */
#define MIN_SNIPPET_LEN 20
/* maximum length of output lines */
#define MAX_OUTPUT_LINE 72

/* maximum terms allowed on command line */
#define MAX_TERMS 50
/* signal for no match between word and query term */
#define NO_MATCH (-1)

typedef char word_t[MAX_WORD_LEN + 1];
int get_word(word_t w, int limit);
/* If you wish to add further #defines, put them below this comment,
   then prototypes for the functions that you add

   The only thing you should alter above this line is to complete the
   Authorship Declaration
*/

typedef char paragraph_t[MAX_PARA_LEN + 1];
int get_paragraph(paragraph_t, int *, int);
/****************************************************************/
/* main program controls all the action
 */
int main(int argc, char *argv[])
{

    for (int i = 1; i < argc; i++)
    {
        printf("Keyword: %s\n", argv[i]);
    }

    word_t cur_paragraph;
    int para_num = 1;

    int cur_code = 0;
    int cur_para_word_count = 0;
    while ((cur_code = get_paragraph(cur_paragraph, &cur_para_word_count, MAX_PARA_LEN)))
    {
        if (cur_code == PARA_END || cur_code == EOF)
        {
            // stage 1:
            printf("======= Stage 1 [para %d; %d words]\n", para_num, cur_para_word_count);
            para_num += 1;
            cur_para_word_count = 0;

            printf("%s\n", cur_paragraph);
            if (cur_code == EOF)
            {
                printf("EOF\n");
                return 0;
            }
            // stage 2: compute
        }
    }

    return 0;
}

int get_paragraph(paragraph_t cur_paragraph, int *word_count, int cur_para_limit)
{

    printf("get para:\n");
    word_t cur_word;
    int cur_code = 0;
    // int cur_word_index = 0;
    while ((cur_code = get_word(cur_word, MAX_WORD_LEN)) != EOF)
    {

        if (cur_code == PARA_END)
        {

            *cur_paragraph = '\0';
            return PARA_END;
        }
        else
        {
            printf("Word found: %s\n", cur_word);
            strcpy(cur_paragraph, cur_word);
            // cur_paragraph[cur_word_index + 1] = ' ';

            // printf("paragraph index: %d\n", cur_word_index);

            // printf("paragraph: %s\n", cur_paragraph);

            cur_paragraph += (strlen(cur_word) + 1);

            *word_count += 1;

            *(cur_paragraph - 1) = ' ';
        }
        // printf("word: %s\n", cur_word);
    }

    return EOF;
}
/****************************************************************/

/* extract a single word out of the standard input, but not
   more than "limit" characters in total. One character of
   sensible trailing punctuation is retained.
   argument array W must be limit+1 characters or bigger
*/
int get_word(word_t cur_word, int cur_word_limit)
{

    printf("reading:\n");
    int cur_char;
    // int new_line_count = 0;
    /* first, skip over any non alphanumerics */
    while ((cur_char = getchar()) != EOF && !isalnum(cur_char))
    {
        // printf("while loop: cur_char value:%d", cur_char);
        if (cur_char == '\n' && (cur_char = getchar()) == '\n')
        {
            printf("para end");

            return PARA_END;
        }
    }
    if (cur_char == EOF)
    {
        return EOF;
    }
    /* ok, first character of next word has been found */
    *cur_word = cur_char;
    cur_word += 1;
    cur_word_limit -= 1;
    while (cur_word_limit > 0 && (cur_char = getchar()) != EOF && isalnum(cur_char))
    {
        /* another character to be stored */
        *cur_word = cur_char;
        cur_word += 1;
        cur_word_limit -= 1;
    }
    /* take a look at that next character, is it a sensible trailing
       punctuation? */
    if (strchr(TERM_PUNCT, cur_char) && (cur_word_limit > 0))
    {
        /* yes, it is */
        *cur_word = cur_char;
        cur_word += 1;
        cur_word_limit -= 1;
    }

    /* now close off the string */
    *cur_word = '\0';
    return WORD_FND;
}

// algorithms are fun!