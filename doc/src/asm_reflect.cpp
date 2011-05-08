callq  407000 <_ZN3rt25Scene10get_lightsEv>
movaps 0x100(%rsp),%xmm4
mov    %eax,%r12d
mov    0x8(%rbx),%rdi
movaps (%rsp),%xmm3
movaps %xmm4,%xmm5
mulps  0xe576(%rip),%xmm4
dpps   $0xf1,%xmm3,%xmm5
shufps $0x0,%xmm5,%xmm5
mulps  %xmm5,%xmm4
subps  %xmm4,%xmm3
movaps %xmm3,0x20(%rsp)
callq  407000 <_ZN3rt25Scene10get_lightsEv>
