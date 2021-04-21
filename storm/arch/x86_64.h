/* Target x86_64 */

#define MACHINE_STACK_ELEMENT_SIZE 8

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
    "\tmov rsp, rbp\n" \
    "\tpop rbp\n"      \
    "\tret\n"

#define MACHINE_RETURNZERO \
    "\txor eax, eax\n" \
    "\tmov rsp, rbp\n" \
    "\tpop rbp\n"      \
    "\tret\n"

#define MACHINE_ADD \
    "\tpop rax\n"   \
    "\tadd qword [rsp], rax\n"

#define MACHINE_SUB \
    "\tpop rax\n"   \
    "\tsub qword [rsp], rax\n"

#define MACHINE_MUL \
    "\tpop rax\n"   \
    "\tpop rcx\n"   \
    "\tmul rcx\n"   \
    "\tpush rax\n"

#define MACHINE_DIV    \
    "\tpop rcx\n"      \
    "\tpop rax\n"      \
    "\txor rdx, rdx\n" \
    "\tdiv rcx\n"      \
    "\tpush rax\n"

#define MACHINE_MODULO    \
    "\tpop rcx\n"      \
    "\tpop rax\n"      \
    "\txor rdx, rdx\n" \
    "\tdiv rcx\n"      \
    "\tpush rdx\n"

#define MACHINE_ISEQUAL              \
    "\txor ecx, ecx\n"               \
    "\tpop rax\n"                    \
    "\tpop rcx\n"                    \
    "\tcmp rcx, rax\n"               \
    "\tsete cl\n"                    \
    "\tpush rcx\n"

#define MACHINE_ISGREATER              \
    "\txor ecx, ecx\n"               \
    "\tpop rax\n"                    \
    "\tpop rcx\n"                    \
    "\tcmp rcx, rax\n"               \
    "\tsetg cl\n"                    \
    "\tpush rcx\n"

#define MACHINE_ISLESS              \
    "\txor ecx, ecx\n"               \
    "\tpop rax\n"                    \
    "\tpop rcx\n"                    \
    "\tcmp rcx, rax\n"               \
    "\tsetl cl\n"                    \
    "\tpush rcx\n"

#define MACHINE_ISGREATEROREQUAL              \
    "\txor ecx, ecx\n"               \
    "\tpop rax\n"                    \
    "\tpop rcx\n"                    \
    "\tcmp rcx, rax\n"               \
    "\tsetge cl\n"                    \
    "\tpush rcx\n"

#define MACHINE_ISLESSOREQUAL              \
    "\txor ecx, ecx\n"               \
    "\tpop rax\n"                    \
    "\tpop rcx\n"                    \
    "\tcmp rcx, rax\n"               \
    "\tsetle cl\n"                    \
    "\tpush rcx\n"

#define MACHINE_IF      \
    "\ttest rax, rax\n" \
    "\tjz .__l%d\n"

#define MACHINE_INTLABEL \
    ".__l%d:\n"

#define MACHINE_WHILE   \
    "\ttest rax, rax\n" \
    "\tjz .__l%d\n"

#define MACHINE_ENDWHILE \
    "\tjmp .__l%d\n"

#define MACHINE_POKE8        \
    "\tpop rax\n"            \
    "\tpop rcx\n"            \
    "\tmov byte [rcx], al\n" \
    "\tpush rax\n"

#define MACHINE_POKE16       \
    "\tpop rax\n"            \
    "\tpop rcx\n"            \
    "\tmov word [rcx], ax\n" \
    "\tpush rax\n"

#define MACHINE_POKE32         \
    "\tpop rax\n"              \
    "\tpop rcx\n"              \
    "\tmov dword [rcx], eax\n" \
    "\tpush rax\n"

#define MACHINE_POKE64         \
    "\tpop rax\n"              \
    "\tpop rcx\n"              \
    "\tmov qword [rcx], rax\n" \
    "\tpush rax\n"

#define MACHINE_PEEK8        \
    "\tpop rcx\n"            \
    "\txor rax, rax\n"       \
    "\tmov al, byte [rcx]\n" \
    "\tpush rax\n"

#define MACHINE_PEEK16       \
    "\tpop rcx\n"            \
    "\txor rax, rax\n"       \
    "\tmov ax, word [rcx]\n" \
    "\tpush rax\n"

#define MACHINE_PEEK32         \
    "\tpop rcx\n"              \
    "\txor rax, rax\n"         \
    "\tmov eax, dword [rcx]\n" \
    "\tpush rax\n"

#define MACHINE_PEEK64 \
    "\tpop rcx\n"      \
    "\tpush qword [rcx]\n"

#define MACHINE_CDECL                                                                        \
    "cdecl:\n"                                                                               \
    "\tpush rbx\n"                                                                           \
    "\tmov rbx, qword [rsp + 16]\n" /* arg count in rbx */                                    \
    "\tmov rax, qword [rsp + rbx*8 + 24]\n" /* rax contains the function's address */        \
    "\tlea rbx, [rsp + rbx*8 + 16]\n"   /* rbx points to top of args */                       \
    "\tmov rdi, qword [rbx]\n"                                                               \
    "\tsub rbx, 8\n"                                                                         \
    "\tmov rsi, qword [rbx]\n"                                                               \
    "\tsub rbx, 8\n"                                                                         \
    "\tmov rcx, qword [rbx]\n"                                                               \
    "\tsub rbx, 8\n"                                                                         \
    "\tmov rdx, qword [rbx]\n"                                                               \
    "\tsub rbx, 8\n"                                                                         \
    "\tmov r8, qword [rbx]\n"                                                                \
    "\tsub rbx, 8\n"                                                                         \
    "\tmov r9, qword [rbx]\n" /* TODO support more than 6 args */                            \
    "\ttest rsp, 1111b\n"                                                                    \
    "\tjnz .align16\n"                                                                       \
    "\tcall rax\n"                                                                           \
    "\tret\n"                                                                                \
    "\t.align16:\n"                                                                          \
    "\tsub rsp, 8\n"                                                                         \
    "\tcall rax\n"                                                                           \
    "\tadd rsp, 8\n"                                                                         \
    "\tpop rbx\n"                                                                            \
    "\tret\n"

#define MACHINE_FUNCTION_CALL \
    "\tcall %s\n"             \
    "\tadd rsp, %d\n"         \
    "\tpush rax\n"

#define MACHINE_CREATE_FRAME \
    "\tpush rbp\n"           \
    "\tmov rbp, rsp\n"

#define MACHINE_ALLOCATE_STACK \
    "\tsub rsp, %zu\n"

#define MACHINE_GLOBAL_VAR \
    "%s: dq 0\n"

#define MACHINE_PUSH_INTEGER \
    "\tpush %ld\n"

#define MACHINE_PUSH_GLOBAL \
    "\tpush qword [rel %s]\n"

#define MACHINE_PUSH_LOCAL \
    "\tpush qword [rbp+(%d)]\n"

#define MACHINE_PUSH_ADDROF_GLOBAL \
    "\tlea rax, [rel %s]\n"        \
    "\tpush rax\n"

#define MACHINE_PUSH_ADDROF_LOCAL \
    "\tlea rax, [rbp+(%d)]\n"     \
    "\tpush rax\n"

#define MACHINE_ASSIGN_GLOBAL \
    "\tpop rax\n"             \
    "\tmov qword [rel %s], rax\n"

#define MACHINE_ADD_AND_ASSIGN_GLOBAL \
    "\tpop rax\n"             \
    "\tadd qword [rel %s], rax\n"

#define MACHINE_SUB_AND_ASSIGN_GLOBAL \
    "\tpop rax\n"             \
    "\tsub qword [rel %s], rax\n"

#define MACHINE_ASSIGN_LOCAL \
    "\tpop rax\n"            \
    "\tmov qword [rbp+(%d)], rax\n"

#define MACHINE_ADD_AND_ASSIGN_LOCAL \
    "\tpop rax\n"            \
    "\tadd qword [rbp+(%d)], rax\n"

#define MACHINE_SUB_AND_ASSIGN_LOCAL \
    "\tpop rax\n"            \
    "\tsub qword [rbp+(%d)], rax\n"

#define MACHINE_POP_RESULT \
    "\tpop rax\n"

#define MACHINE_LITERAL_LABEL_BEGIN \
    "__literal%d: db \""

#define MACHINE_LITERAL_LABEL_END \
    "\", 0\n"

#define MACHINE_LITERAL_HEX \
    "\", 0x%x, \""
