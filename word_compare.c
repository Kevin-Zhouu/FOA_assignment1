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

int all_to_lower(word_t w);
/* If you wish to add further #defines, put them below this comment,
   then prototypes for the functions that you add

   The only thing you should alter above this line is to complete the
   Authorship Declaration
*/
#define TRUE 1;
#define FALSE 0;

typedef char paragraph_t[MAX_PARA_LEN + 1];
int get_paragraph(paragraph_t cur_paragraph, int *word_count, int *cur_para_match_count, int cur_para_limit);
int is_keyword(word_t word);
int word_compare(word_t word_a, word_t word_b);
/****************************************************************/
/* main program controls all the action
 */
int num_keywords;
char *keywords[10];
int word_compare(word_t keyword, word_t word_a);
int main(int argc, char *argv[])
{

    char keyword[] = "feet";

    char word[] = "feet.";
    int result = word_compare(keyword, word);
    printf("is keyword: %d\n", result);

    return 0;
}
/* Determines whether a given word matches the given keyword
    in a case-insensitive manner.
    Returns 1 if the word matches the keyword, 0 otherwise
    */
int word_compare(word_t keyword, word_t word_a)
{
    int is_keyword = FALSE;
    int strlen_keyword = strlen(keyword);
    int strlen_word = strlen(word_a);
    // Case 1: two words have same length
    if (strlen_keyword == strlen_word)
    {
        int result = strncasecmp(keyword, word_a, strlen_keyword);
        if (result == 0)
        {
            is_keyword = TRUE;
        }
    }
    // Case 2: if the last char is non-alphanumerical
    printf("last char:%c\n", *(word_a + strlen(word_a) - 1));
    printf("result:%d", strncasecmp(keyword, word_a, strlen_word - 1) == 0);
    if (!isalnum(*(word_a + strlen(word_a) - 1)))
    {
        int result = (strncasecmp(keyword, word_a, strlen_word - 1) == 0);
        if (result == 0)
        {
            is_keyword = TRUE;
        }
    }
    return is_keyword;
}

// algorithms are fun!