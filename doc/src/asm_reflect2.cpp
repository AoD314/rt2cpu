xmm4 = rsp[0x100]
xmm3 = *rsp
xmm5 = xmm4
xmm4 = xmm4 * rip[0xe576]
xmm5 = dot (xmm5, xmm3)
xmm5 = (xmm5[0], xmm5[0], xmm5[0], xmm5[0])
xmm4 = xmm4 * xmm5
xmm3 = xmm3 - xmm4
rsp[0x20] = xmm3
