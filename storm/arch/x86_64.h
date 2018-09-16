
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

#define MACHINE_ISEQUAL              \
    "\tpop rax\n"                    \
    "\tpop rbx\n"                    \
    "\tcmp rax, rbx\n"               \
    "\tpushfq\n"                     \
    "\tand qword [rsp], ~(1 << 6)\n" \
    "\tshr qword [rsp], 6\n"

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
    "\tpop r12\n"                      /* put the return address in r10 */                   \
    "\tpop rcx\n"                      /* put the number of arguments to be passed in rcx */ \
    "\tmov rax, qword [rsp + rcx*8]\n" /* rax contains the function's address */             \
    "\tlea rbx, [rsp + rcx*8 - 8]\n"   /* rdi points to top of args */                       \
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
    "\t.back:\n"                                                                             \
    "\tpush rcx\n"                                                                           \
    "\tpush r12\n"                                                                           \
    "\tret\n"                                                                                \
    "\t.align16:\n"                                                                          \
    "\tsub rsp, 8\n"                                                                         \
    "\tcall rax\n"                                                                           \
    "\tadd rsp, 8\n"                                                                         \
    "\tjmp .back\n"

#define MACHINE_FUNCTION_CALL \
    "\tcall %s\n"             \
    "\tadd rsp, %d\n"         \
    "\tpush rax\n"

#define MACHINE_CREATE_FRAME \
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
