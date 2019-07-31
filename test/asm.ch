int exit()
{
    @asm
    ; i can do this
    mov eax,6 ; sys_exit
    mov ebx,0 ; supposed to exit with code 0
    int 0x80
    @end
}

entry()
{
    exit()
}