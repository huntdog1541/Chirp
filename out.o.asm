section .text 
global _start
_start: 
push ebp
mov ebp, esp
mov dword  [ebp-4],39483
mov dword  [ebp-8],39483
mov dword  [ebp-12],39483
mov dword  [ebp-16],39483
mov esp, ebp
pop ebp
ret 0 

