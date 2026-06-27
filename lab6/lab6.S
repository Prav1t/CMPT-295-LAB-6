.text

    .globl strlen_mine
strlen_mine:
    xorq    %rax, %rax #counter rax = 0 
.Lmine_loop:
    cmpb    $0, (%rdi) #checks is current byte == '\0'?
    je      .Lmine_done  #if yes then done
    incq    %rax  #counter++
    incq    %rdi #move to next byte
    jmp     .Lmine_loop
.Lmine_done:
    ret



    .globl strlen_utf8
strlen_utf8:
    xorq    %rax, %rax #counter rax = 0 
.Lutf8_loop:
    movzbq  (%rdi), %rcx  #load current 
    cmpq    $0, %rcx #check for null terminator
    je      .Lutf8_done #if yes then done

   
    movq    %rcx, %rdx
    andq    $0xC0, %rdx #keeping only top two bits
    cmpq    $0x80, %rdx  #checks if it is a continuation byte
    je      .Lutf8_skip #if yes dont count it and skip

    incq    %rax #count it if leading byte
.Lutf8_skip:
    incq    %rdi #move to next byte
    jmp     .Lutf8_loop
.Lutf8_done:
    ret