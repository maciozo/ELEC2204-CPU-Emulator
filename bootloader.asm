NOOP ;Do nothing
COPY 0x42, 0x01 ;Copy data from address 0x42 to address 0x01
PRNT 0x41 ;Print data at address 41
STOR 0x02, 1000 ;Store 1000 in address 2    
STOR 0x03, 234 ;Stpre 234 in address 3
ADDA 0x02, 0x03, 0x102 ;*0x102 = 1000 + 234
PRND 0x102 ;Should print 1234
COPY 0x102, 0x03 ;Copy 1234 to 0x03
FREE 0x102, 1 ;Free 0x102 for writing
SUBA 0x03, 0x02, 0x102 ;*0x102 = 1234 - 1000
PRND 0x102 ;Should print 234
ORAD 0x02, 0x03, 0x103 ;*0x103 = 1000 | 1234 = 2042?
PRND 0x103 ;Should print 2042, I think
ANDA 0x02, 0x03, 0x104 ;*0x104 = 1000 & 1234 = 192?
PRND 0x104 ;Should print 192, I think
NOTA 0x02, 0x105 ;*0x105 = ~1000 = 0xFFFFFC17?
PRNT 0x105 ;Should print 0xFFFFFC17
NNDA 0x02, 0x03, 0x106 ;*0x106 = ~(1000 & 1234) = 0xFFFFFF3F?
PRNT 0x106 ;Should print 0xFFFFFF3F
NORA 0x02, 0x03, 0x107 ;*0x107 = ~(1000 | 1234) = 0xFFFFF805?
PRNT 0x107 ;Should print 0xFFFFF805
XORA 0x02, 0x03, 0x108 ;*0x108 = 1000 ^ 1234 = 1850?
PRND 0x108 ;Should print 1850
STOR 0x04, 1000 ;Store 1000 in address 2
JEQA 0x02, 0x04, 0x8E ;If 1000 == 1000, jump to 0x8F
STOR 0x05, 9090909090909090 ;Should be skipped
PRND 0x05 ;Should be skipped
PRND 0x03 ;Should print 1234
STOR 0x05, 9090909090909090 ;Store 9090909090909090 in address 5
JEQP 0x01, 0x02, 3 ;If 1 == 1000, jump 2 addresses forward
PRND 0x05 ;Should print 9090909090909090
JEQP 0x02, 0x02, 3 ;If 1000 == 1000, jump 2 addresses forward
PRND 0x02 ;Should be skipped
PRND 0x05 ;Should print 9090909090909090
STOP ;Stop
