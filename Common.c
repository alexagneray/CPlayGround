#include "Common.h"

const char* g_CmdLabel [] =
{
    "Join",
    "Tell",
    "Leave"
};

const char* g_OutcomeLabel[] =
{
    "Success.",
    "An error occured.",
    "Unknown error.",
    "The element already exists.",
    "The argument is invalid.",
    "An internal error occured.",
    "Given file has a wrong type.",
    "The file has not been opened, use file_open(...)."
};

void print_outcome(EOC eoc)
{
    printf("%s\n", OUTCOMEGETLABEL(eoc));
}