/* Target i386 */
#define MACHINE_STACK_ELEMENT_SIZE 4

#define MACHINE_SECTION_TEXT \
    "\nsection .text\n"

#define MACHINE_SECTION_DATA \
    "\nsection .data\n"

#define MACHINE_GLOBAL_REF \
    "global %s\n"

#define MACHINE_EXTERN_REF \
    "extern %s\n"

#define MACHINE_NEW_LABEL \
    "%s:\n"

#define MACHINE_RETURN \
    "\tmov esp, ebp\n" \
    "\tpop ebp\n"      \
    "\tret\n"

#define MACHINE_ADD \
    "\tpop eax\n"   \
    "\tadd dword [esp], eax\n"

#define MACHINE_SUB \
    "\tpop eax\n"   \
    "\tsub dword [esp], eax\n"

#define MACHINE_MUL \
    "\tpop eax\n"   \
    "\tpop ebx\n"   \
    "\tmul ebx\n"   \
    "\tpush eax\n"

#define MACHINE_DIV    \
    "\tpop ebx\n"      \
    "\tpop eax\n"      \
    "\txor edx, edx\n" \
    "\tdiv ebx\n"      \
    "\tpush eax\n"

#define MACHINE_ISEQUAL              \
    "\tpop eax\n"                    \
    "\tpop ebx\n"                    \
    "\tcmp eax, ebx\n"               \
    "\tpushfd\n"                     \
    "\tand dword [esp], 1 << 6\n" \
    "\tshr dword [esp], 6\n"

#define MACHINE_IF      \
    "\ttest eax, eax\n" \
    "\tjz .__l%d\n"

#define MACHINE_INTLABEL \
    ".__l%d:\n"

#define MACHINE_WHILE   \
    "\ttest eax, eax\n" \
    "\tjz .__l%d\n"

#define MACHINE_ENDWHILE \
    "\tjmp .__l%d\n"

#define MACHINE_POKE8        \
    "\tpop eax\n"            \
    "\tpop ebx\n"            \
    "\tmov byte [ebx], al\n" \
    "\tpush eax\n"

#define MACHINE_POKE16       \
    "\tpop eax\n"            \
    "\tpop ebx\n"            \
    "\tmov word [ebx], ax\n" \
    "\tpush eax\n"

#define MACHINE_POKE32         \
    "\tpop eax\n"              \
    "\tpop ebx\n"              \
    "\tmov dword [ebx], eax\n" \
    "\tpush eax\n"

#define MACHINE_POKE64 \
    "\tnop\n"

#define MACHINE_PEEK8        \
    "\tpop ebx\n"            \
    "\txor eax, eax\n"       \
    "\tmov al, byte [ebx]\n" \
    "\tpush eax\n"

#define MACHINE_PEEK16       \
    "\tpop ebx\n"            \
    "\txor eax, eax\n"       \
    "\tmov ax, word [ebx]\n" \
    "\tpush eax\n"

#define MACHINE_PEEK32 \
    "\tpop ebx\n"      \
    "\tpush dword [ebx]\n"

#define MACHINE_PEEK64 \
    "\tnop\n"

#define MACHINE_CDECL \
    "\tnop\n"

#define MACHINE_FUNCTION_CALL \
    "\tcall %s\n"             \
    "\tadd esp, %d\n"         \
    "\tpush eax\n"

#define MACHINE_CREATE_FRAME \
    "\tpush ebp\n"           \
    "\tmov ebp, esp\n"

#define MACHINE_ALLOCATE_STACK \
    "\tsub esp, %d\n"

#define MACHINE_GLOBAL_VAR \
    "%s: dd 0\n"

#define MACHINE_PUSH_INTEGER \
    "\tpush %ld\n"

#define MACHINE_PUSH_GLOBAL \
    "\tpush dword [%s]\n"

#define MACHINE_PUSH_LOCAL \
    "\tpush dword [ebp+(%d)]\n"

#define MACHINE_PUSH_ADDROF_GLOBAL \
    "\tpush %s\n"

#define MACHINE_PUSH_ADDROF_LOCAL \
    "\tlea eax, [ebp+(%d)]\n"     \
    "\tpush eax\n"

#define MACHINE_ASSIGN_GLOBAL \
    "\tpop eax\n"             \
    "\tmov dword [%s], eax\n"

#define MACHINE_ASSIGN_LOCAL \
    "\tpop eax\n"            \
    "\tmov dword [ebp+(%d)], eax\n"

#define MACHINE_POP_RESULT \
    "\tpop eax\n"

#define MACHINE_LITERAL_LABEL_BEGIN \
    "__literal%d: db \""

#define MACHINE_LITERAL_LABEL_END \
    "\", 0\n"

#define MACHINE_LITERAL_HEX \
    "\", 0x%x, \""
