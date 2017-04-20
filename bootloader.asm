NOOP ;Do nothing
COPY 0x0000000000000042,0x0000000000000001 ;Copy data from address 0x42 to address 0x01
PRNT 0x41 ;Print data at address 41
PRNT 0x42 ;Print data at address 42
PRNT 0x43 ;Print data at address 43
PRNT 0x01 ;Print data at address 1
STOR 0x100,0xDEADBEEF
PRNT 0x100
;JUML 0x41
STOP ;Stop
