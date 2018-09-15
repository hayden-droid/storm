/* Target subleq */

/*
This backend generates dubu-assembler code. You can get the assembler software
from https://owo.codes/noxim/dubu-assembler
*/

#define MACHINE_STACK_ELEMENT_SIZE 8

#define MACHINE_SECTION_TEXT \
    "\nTXT\n"

#define MACHINE_SECTION_DATA \
    "\nDAT\n"

#define MACHINE_GLOBAL_REF \
    "GBL %s\n"

#define MACHINE_EXTERN_REF \
    "EXT %s\n"

#define MACHINE_NEW_LABEL \
    "LBL %s\n"

#define MACHINE_RETURN \
    "\tRET\n"

// pop 2 values off stack, add and push them back
#define MACHINE_ADD \
    "\tADD\n"

// pop 2 values off stack, sub TOS from NOS and push to stack
#define MACHINE_SUB \
    "\tSUB\n"

// pop 2 values, mul and push
#define MACHINE_MUL \
    "\tMUL\n"

// pop 2 values, div and push
#define MACHINE_DIV \
    "\tDIV\n"

// pop 2 values, compare their equality and push 1 if they are same else 0
#define MACHINE_ISEQUAL \
    "\tEQL\n"

#define MACHINE_IF \
    "\tJNZ #%d\n"

#define MACHINE_INTLABEL \
    "LBL #%d\n"

#define MACHINE_WHILE \
    "\tJNZ #%d\n"

#define MACHINE_ENDWHILE \
    "\tJMP #%d\n"

// pop TOS and NOS, then write to the location NOS the 8 least significant bits
// of TOS. Push TOS back to stack
#define MACHINE_POKE8 \
    "\tPK1\n"

#define MACHINE_POKE16 \
    "\tPK2\n"

#define MACHINE_POKE32 \
    "\tPK4\n"

#define MACHINE_POKE64 \
    "\tPK8\n"

#define MACHINE_PEEK8 \
    "\tPE1\n"

#define MACHINE_PEEK16 \
    "\tPE2\n"

#define MACHINE_PEEK32 \
    "\tPE4\n"

#define MACHINE_PEEK64 \
    "\tPE8\n"

#define MACHINE_CDECL \
    "\tNOP\n"

// label name and number of bytes to shift the stack
#define MACHINE_FUNCTION_CALL \
    "\tCAL %s %d\n"

#define MACHINE_CREATE_FRAME \
    "\tCSF\n"

#define MACHINE_ALLOCATE_STACK \
    "\tALL %d\n"

#define MACHINE_GLOBAL_VAR \
    "GBV %s\n"

#define MACHINE_PUSH_INTEGER \
    "\tPSV %ld\n"

#define MACHINE_PUSH_GLOBAL \
    "\tPSG %s\n"

#define MACHINE_PUSH_LOCAL \
    "\tPSL %d\n"

#define MACHINE_PUSH_ADDROF_GLOBAL \
    "\tPAG %s\n"

#define MACHINE_PUSH_ADDROF_LOCAL \
    "\tPAL %d\n"

#define MACHINE_ASSIGN_GLOBAL \
    "\tWRG %s\n"

#define MACHINE_ASSIGN_LOCAL \
    "\tWRL %d\n"

#define MACHINE_POP_RESULT \
    "\tPPR\n"

#define MACHINE_LITERAL_LABEL_BEGIN \
    "__literal%d \""

#define MACHINE_LITERAL_LABEL_END \
    "\" 0\n"

#define MACHINE_LITERAL_HEX \
    "\" x%x \""
