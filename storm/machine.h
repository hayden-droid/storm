#ifndef __MACHINE_H__
#define __MACHINE_H__

#ifdef TARGET_i386

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
        "\tpop ebp\n" \
        "\tret\n"

    #define MACHINE_ADD \
        "\tpop eax\n" \
        "\tadd dword [esp], eax\n"

    #define MACHINE_SUB \
        "\tpop eax\n" \
        "\tsub dword [esp], eax\n"

    #define MACHINE_MUL \
        "\tpop eax\n" \
        "\tpop ebx\n" \
        "\tmul ebx\n" \
        "\tpush eax\n"

    #define MACHINE_DIV \
        "\tpop eax\n" \
        "\tpop ebx\n" \
        "\txor edx, edx\n" \
        "\tdiv ebx\n" \
        "\tpush eax\n"

    #define MACHINE_ISEQUAL \
        "\tpop eax\n" \
        "\tpop ebx\n" \
        "\tcmp eax, ebx\n" \
        "\tpushfd\n" \
        "\tand dword [esp], ~(1 << 6)\n" \
        "\tshr dword [esp], 6\n"

    #define MACHINE_IF \
        "\ttest eax, eax\n" \
        "\tjz .__l%d\n"

    #define MACHINE_INTLABEL \
        ".__l%d:\n"

    #define MACHINE_WHILE \
        "\ttest eax, eax\n" \
        "\tjz .__l%d\n"

    #define MACHINE_ENDWHILE \
        "\tjmp .__l%d\n"

    #define MACHINE_POKE8 \
        "\tpop eax\n" \
        "\tpop ebx\n" \
        "\tmov byte [ebx], al\n" \
        "\tpush eax\n"

    #define MACHINE_POKE16 \
        "\tpop eax\n" \
        "\tpop ebx\n" \
        "\tmov word [ebx], ax\n" \
        "\tpush eax\n"

    #define MACHINE_POKE32 \
        "\tpop eax\n" \
        "\tpop ebx\n" \
        "\tmov dword [ebx], eax\n" \
        "\tpush eax\n"

    #define MACHINE_POKE64 \
        "\tnop\n"

    #define MACHINE_PEEK8 \
        "\tpop ebx\n" \
        "\txor eax, eax\n" \
        "\tmov al, byte [ebx]\n" \
        "\tpush eax\n"

    #define MACHINE_PEEK16 \
        "\tpop ebx\n" \
        "\txor eax, eax\n" \
        "\tmov ax, word [ebx]\n" \
        "\tpush eax\n"

    #define MACHINE_PEEK32 \
        "\tpop ebx\n" \
        "\tpush dword [ebx]\n"

    #define MACHINE_PEEK64 \
        "\tnop\n"

    #define MACHINE_FUNCTION_CALL \
        "\tcall %s\n" \
        "\tadd esp, %d\n" \
        "\tpush eax\n"

    #define MACHINE_CREATE_FRAME \
        "\tpush ebp\n" \
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
        "\tlea eax, [ebp+(%d)]\n" \
        "\tpush eax\n"

    #define MACHINE_ASSIGN_GLOBAL \
        "\tpop eax\n" \
        "\tmov dword [%s], eax\n"

    #define MACHINE_ASSIGN_LOCAL \
        "\tpop eax\n" \
        "\tmov dword [ebp+(%d)], eax\n"

    #define MACHINE_POP_RESULT \
        "\tpop eax\n"

    #define MACHINE_LITERAL_LABEL_BEGIN \
        "__literal%d: db '"

    #define MACHINE_LITERAL_LABEL_END \
        "', 0\n"

#endif

#ifdef TARGET_x86_64

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
        "\tpop rbp\n" \
        "\tret\n"

    #define MACHINE_ADD \
        "\tpop rax\n" \
        "\tadd qword [rsp], rax\n"

    #define MACHINE_SUB \
        "\tpop rax\n" \
        "\tsub qword [rsp], rax\n"

    #define MACHINE_MUL \
        "\tpop rax\n" \
        "\tpop rbx\n" \
        "\tmul rbx\n" \
        "\tpush rax\n"

    #define MACHINE_DIV \
        "\tpop rax\n" \
        "\tpop rbx\n" \
        "\txor rdx, rdx\n" \
        "\tdiv rbx\n" \
        "\tpush rax\n"

    #define MACHINE_ISEQUAL \
        "\tpop rax\n" \
        "\tpop rbx\n" \
        "\tcmp rax, rbx\n" \
        "\tpushfq\n" \
        "\tand qword [rsp], ~(1 << 6)\n" \
        "\tshr qword [rsp], 6\n"

    #define MACHINE_IF \
        "\ttest rax, rax\n" \
        "\tjz .__l%d\n"

    #define MACHINE_INTLABEL \
        ".__l%d:\n"

    #define MACHINE_WHILE \
        "\ttest rax, rax\n" \
        "\tjz .__l%d\n"

    #define MACHINE_ENDWHILE \
        "\tjmp .__l%d\n"

    #define MACHINE_POKE8 \
        "\tpop rax\n" \
        "\tpop rbx\n" \
        "\tmov byte [rbx], al\n" \
        "\tpush rax\n"

    #define MACHINE_POKE16 \
        "\tpop rax\n" \
        "\tpop rbx\n" \
        "\tmov word [rbx], ax\n" \
        "\tpush rax\n"

    #define MACHINE_POKE32 \
        "\tpop rax\n" \
        "\tpop rbx\n" \
        "\tmov dword [rbx], eax\n" \
        "\tpush rax\n"

    #define MACHINE_POKE64 \
        "\tpop rax\n" \
        "\tpop rbx\n" \
        "\tmov qword [rbx], rax\n" \
        "\tpush rax\n"

    #define MACHINE_PEEK8 \
        "\tpop rbx\n" \
        "\txor rax, rax\n" \
        "\tmov al, byte [rbx]\n" \
        "\tpush rax\n"

    #define MACHINE_PEEK16 \
        "\tpop rbx\n" \
        "\txor rax, rax\n" \
        "\tmov ax, word [rbx]\n" \
        "\tpush rax\n"

    #define MACHINE_PEEK32 \
        "\tpop rbx\n" \
        "\txor rax, rax\n" \
        "\tmov eax, dword [rbx]\n" \
        "\tpush rax\n"

    #define MACHINE_PEEK64 \
        "\tpop rbx\n" \
        "\tpush qword [rbx]\n"

    #define MACHINE_FUNCTION_CALL \
        "\tcall %s\n" \
        "\tadd rsp, %d\n" \
        "\tpush rax\n"

    #define MACHINE_CREATE_FRAME \
        "\tpush rbp\n" \
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
        "\tlea rax, [rbp+(%d)]\n" \
        "\tpush rax\n"

    #define MACHINE_ASSIGN_GLOBAL \
        "\tpop rax\n" \
        "\tmov qword [%s], rax\n"

    #define MACHINE_ASSIGN_LOCAL \
        "\tpop rax\n" \
        "\tmov qword [rbp+(%d)], rax\n"

    #define MACHINE_POP_RESULT \
        "\tpop rax\n"

    #define MACHINE_LITERAL_LABEL_BEGIN \
        "__literal%d: db '"

    #define MACHINE_LITERAL_LABEL_END \
        "', 0\n"

#endif

#endif
