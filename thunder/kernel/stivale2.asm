section .stivale2hdr write

stivale2hdr:
    dq 0
    dq stack.top
    dq 0
    dq 0

section .bss

stack:
    resb 8192
  .top:
