   .text 
	.globl	square
square:
.PROLOGsquare : 
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $40,   %rsp
    movq    %rdi, -16(%rbp) 

.square : 
	movq  -16(%rbp), %rax
	mulq  -16(%rbp)
	movq  %rax, -24(%rbp)
	movq  $-8,-32(%rbp)
	movq  %rbp, %rax
	addq  -32(%rbp), %rax
	movq  %rax, -32(%rbp)
	movq  -32(%rbp), %rax
	movq  -24(%rbp), %r10
	movq  %r10, (%rax)
        jmp  .EPILOGsquare 
.LBB_square_1 : 
        jmp  .EPILOGsquare 
.EPILOGsquare : 
	movq  -8(%rbp), %rax
    addq    $40,   %rsp
    popq   %rbp
    retq
	.globl	main
main:
.PROLOGmain : 
    pushq   %rbp
    movq    %rsp, %rbp
    subq    $264,   %rsp
    movq    %rdi, -16(%rbp) 

.main : 
	movb  $-104,-24(%rbp)
	movq  $0,-120(%rbp)
	movq  $-112,-128(%rbp)
	movq  %rbp, %rax
	addq  -128(%rbp), %rax
	movq  %rax, -128(%rbp)
	movq  -128(%rbp), %rax
	movq  -120(%rbp), %r10
	movq  %r10, (%rax)
        jmp  .LBB_main_1 
.LBB_main_1 : 
	movq  $10,-136(%rbp)
	movq  -112(%rbp), %rax
	cmpq  -136(%rbp), %rax
        setl  %cl 
        andb  $1, %cl 
	movq  $0, -144(%rbp)
	movb  %cl, -144(%rbp)
        cmpq   $0, -144(%rbp) 
        je  .LBB_main_3 
        jmp  .LBB_main_2 
.LBB_main_2 : 
	movb  $8,-152(%rbp)
	movq  -112(%rbp), %rax
	mulq  -152(%rbp)
	movq  %rax, -160(%rbp)
	movq  -160(%rbp), %rax
	addq  -24(%rbp), %rax
	movq  %rax, -168(%rbp)
	movq  %rbp, %rax
	addq  -168(%rbp), %rax
	movq  %rax, -168(%rbp)
	movb  $97,-176(%rbp)
	movq  -168(%rbp), %rax
	movb  -176(%rbp), %dl
	movb  %dl, (%rax)
	movb  $8,-184(%rbp)
	movq  -112(%rbp), %rax
	mulq  -184(%rbp)
	movq  %rax, -192(%rbp)
	movq  -192(%rbp), %rax
	addq  -24(%rbp), %rax
	movq  %rax, -200(%rbp)
	movq  %rbp, %rax
	addq  -200(%rbp), %rax
	movq  %rax, -200(%rbp)
	movq  -200(%rbp) , %rax
	movb  (%rax), %dl
	movb  %dl, -208(%rbp)
        movq    -208(%rbp), %rdi
        call putchar@PLT
	movb  $10,-216(%rbp)
        movq    -216(%rbp), %rdi
        call putchar@PLT
	movq  $1,-224(%rbp)

	movq  -112(%rbp),%rax
	movq  %rax,-232(%rbp)

	movq  -112(%rbp), %rax
	addq  -224(%rbp), %rax
	movq  %rax, -240(%rbp)

	movq  -240(%rbp),%rax
	movq  %rax,-112(%rbp)

        jmp  .LBB_main_1 
.LBB_main_3 : 
	movq  $0,-248(%rbp)
	movq  $-8,-256(%rbp)
	movq  %rbp, %rax
	addq  -256(%rbp), %rax
	movq  %rax, -256(%rbp)
	movq  -256(%rbp), %rax
	movq  -248(%rbp), %r10
	movq  %r10, (%rax)
        jmp  .EPILOGmain 
.LBB_main_4 : 
        jmp  .EPILOGmain 
.EPILOGmain : 
	movq  -8(%rbp), %rax
    addq    $264,   %rsp
    popq   %rbp
    retq
