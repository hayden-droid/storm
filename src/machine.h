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

#endif
