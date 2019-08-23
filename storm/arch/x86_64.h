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
    "\tpop rbx\n"      \
    "\tret\n"

#define MACHINE_RETURNZERO \
    "\txor eax, eax\n" \
    "\tmov rsp, rbp\n" \
    "\tpop rbp\n"      \
    "\tpop rbx\n"      \
    "\tret\n"

#define MACHINE_ADD \
    "\tpop rax\n"   \
    "\tadd qword [rsp], rax\n"

#define MACHINE_SUB \
    "\tpop rax\n"   \
    "\tsub qword [rsp], rax\n"

#define MACHINE_MUL \
    "\tpop rax\n"   \
    "\tpop rbx\n"   \
    "\tmul rbx\n"   \
    "\tpush rax\n"

#define MACHINE_DIV    \
    "\tpop rbx\n"      \
    "\tpop rax\n"      \
    "\txor rdx, rdx\n" \
    "\tdiv rbx\n"      \
    "\tpush rax\n"

#define MACHINE_MODULO    \
    "\tpop rbx\n"      \
    "\tpop rax\n"      \
    "\txor rdx, rdx\n" \
    "\tdiv rbx\n"      \
    "\tpush rdx\n"

#define MACHINE_ISEQUAL              \
    "\txor ecx, ecx\n"               \
    "\tpop rax\n"                    \
    "\tpop rbx\n"                    \
    "\tcmp rbx, rax\n"               \
    "\tsete cl\n"                    \
    "\tpush rcx\n"

#define MACHINE_ISGREATER              \
    "\txor ecx, ecx\n"               \
    "\tpop rax\n"                    \
    "\tpop rbx\n"                    \
    "\tcmp rbx, rax\n"               \
    "\tsetg cl\n"                    \
    "\tpush rcx\n"

#define MACHINE_ISLESS              \
    "\txor ecx, ecx\n"               \
    "\tpop rax\n"                    \
    "\tpop rbx\n"                    \
    "\tcmp rbx, rax\n"               \
    "\tsetl cl\n"                    \
    "\tpush rcx\n"

#define MACHINE_ISGREATEROREQUAL              \
    "\txor ecx, ecx\n"               \
    "\tpop rax\n"                    \
    "\tpop rbx\n"                    \
    "\tcmp rbx, rax\n"               \
    "\tsetge cl\n"                    \
    "\tpush rcx\n"

#define MACHINE_ISLESSOREQUAL              \
    "\txor ecx, ecx\n"               \
    "\tpop rax\n"                    \
    "\tpop rbx\n"                    \
    "\tcmp rbx, rax\n"               \
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
    "\tpop rbx\n"            \
    "\tmov byte [rbx], al\n" \
    "\tpush rax\n"

#define MACHINE_POKE16       \
    "\tpop rax\n"            \
    "\tpop rbx\n"            \
    "\tmov word [rbx], ax\n" \
    "\tpush rax\n"

#define MACHINE_POKE32         \
    "\tpop rax\n"              \
    "\tpop rbx\n"              \
    "\tmov dword [rbx], eax\n" \
    "\tpush rax\n"

#define MACHINE_POKE64         \
    "\tpop rax\n"              \
    "\tpop rbx\n"              \
    "\tmov qword [rbx], rax\n" \
    "\tpush rax\n"

#define MACHINE_PEEK8        \
    "\tpop rbx\n"            \
    "\txor rax, rax\n"       \
    "\tmov al, byte [rbx]\n" \
    "\tpush rax\n"

#define MACHINE_PEEK16       \
    "\tpop rbx\n"            \
    "\txor rax, rax\n"       \
    "\tmov ax, word [rbx]\n" \
    "\tpush rax\n"

#define MACHINE_PEEK32         \
    "\tpop rbx\n"              \
    "\txor rax, rax\n"         \
    "\tmov eax, dword [rbx]\n" \
    "\tpush rax\n"

#define MACHINE_PEEK64 \
    "\tpop rbx\n"      \
    "\tpush qword [rbx]\n"

#define MACHINE_CDECL                                                                        \
    "cdecl:\n"                                                                               \
    "\tmov rbx, qword [rsp + 8]\n" /* arg count in rbx */                                    \
    "\tmov rax, qword [rsp + rbx*8 + 16]\n" /* rax contains the function's address */        \
    "\tlea rbx, [rsp + rbx*8 + 8]\n"   /* rbx points to top of args */                       \
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
    "\tret\n"

#define MACHINE_FUNCTION_CALL \
    "\tcall %s\n"             \
    "\tadd rsp, %d\n"         \
    "\tpush rax\n"

#define MACHINE_CREATE_FRAME \
    "\tpush rbx\n"           \
    "\tpush rbp\n"           \
    "\tmov rbp, rsp\n"

#define MACHINE_ALLOCATE_STACK \
    "\tsub rsp, %d\n"

#define MACHINE_GLOBAL_VAR \
    "%s: dq 0\n"

#define MACHINE_PUSH_INTEGER \
    "\tpush %ld\n"

#define MACHINE_PUSH_GLOBAL \
    "\tpush qword [%s]\n"

#define MACHINE_PUSH_LOCAL \
    "\tpush qword [rbp+(%d)]\n"

#define MACHINE_PUSH_ADDROF_GLOBAL \
    "\tpush %s\n"

#define MACHINE_PUSH_ADDROF_LOCAL \
    "\tlea rax, [rbp+(%d)]\n"     \
    "\tpush rax\n"

#define MACHINE_ASSIGN_GLOBAL \
    "\tpop rax\n"             \
    "\tmov qword [%s], rax\n"

#define MACHINE_ASSIGN_LOCAL \
    "\tpop rax\n"            \
    "\tmov qword [rbp+(%d)], rax\n"

#define MACHINE_POP_RESULT \
    "\tpop rax\n"

#define MACHINE_LITERAL_LABEL_BEGIN \
    "__literal%d: db \""

#define MACHINE_LITERAL_LABEL_END \
    "\", 0\n"

#define MACHINE_LITERAL_HEX \
    "\", 0x%x, \""
