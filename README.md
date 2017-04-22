# ELEC2204 - 2204 CPU Emulator

## Usage
### Assembler
`assembler <input assembly file> <output binary file>`

### Emulator
#### Configuration
In `default.cfg`

| Variable      | Type    | Description                                               | 
|---------------|---------|-----------------------------------------------------------| 
| bootLoader    | String  | The path to the programme binary for the emulator to load | 
| registerCount | Integer | The number of general purpose CPU registers               | 
| ramAddress    | Integer | The first memory address of the RAM                       | 
| ramSize       | Integer | The size of the RAM, in 64 bit words                      | 

#### Running
Just run `2204`

#### Debugging
Set the `CPU_DEBUG` macro accordingly in `cpu.h`. Refer to BUILDING.md on how to compile.

## Instruction set
| Mnemonic | Description                                                                                                                          | Value | Operands | Size [words] | Argument 1           | Argument 2            | Argument 3          | 
|----------|--------------------------------------------------------------------------------------------------------------------------------------|-------|----------|--------------|----------------------|-----------------------|---------------------| 
| NOOP     | No operation                                                                                                                         | 0x00  | 0        | 1            |                      |                       |                     | 
| COPY     | Copy data from one address to another                                                                                                | 0x01  | 2        | 3            | Source address       | Destination address   |                     | 
| STOP     | Stop the CPUs operation                                                                                                              | 0x02  | 0        | 1            |                      |                       |                     | 
| PRNT     | Prints the hex value at the specified address                                                                                        | 0x03  | 1        | 2            | Source address       |                       |                     | 
| JUML     | Jump to the specified address                                                                                                        | 0x04  | 1        | 2            | Destination address  |                       |                     | 
| STOR     | Store data at the specified address                                                                                                  | 0x05  | 2        | 3            | Destination address  | Data                  |                     | 
| FREE     | Free the specified length of RAM                                                                                                     | 0x06  | 2        | 3            | Start address        | Length                |                     | 
| ADDA     | "Add the values of two addresses, store in the third address"                                                                        | 0x07  | 3        | 4            | Left operand address | Right operand address | Result address      | 
| SUBA     | Subtract the value at the second address from the value at the first address. Store the result in the third address.                 | 0x08  | 3        | 4            | Left operand address | Right operand address | Result address      | 
| PRND     | Prints the decimal value at the specified address                                                                                    | 0x09  | 1        | 2            | Source address       |                       |                     | 
| ORAD     | Bitwise OR the values of the first and second addresses. Store the result in the third                                               | 0x0A  | 3        | 4            | Left operand address | Right operand address | Result address      | 
| ANDA     | Bitwise AND the values of the first and second addresses. Store the result in the third                                              | 0x0B  | 3        | 4            | Left operand address | Right operand address | Result address      | 
| NOTA     | Bitwise NOT the value of the first address. Store the result in the second                                                           | 0x0C  | 2        | 3            | Operand address      | Result address        |                     | 
| NNDA     | Bitwise NAND the values of the first and second addresses. Store the result in the third                                             | 0x0D  | 3        | 4            | Left operand address | Right operand address | Result address      | 
| NORA     | Bitwise NOR the values of the first and second addresses. Store the result in the third                                              | 0x0E  | 3        | 4            | Left operand address | Right operand address | Result address      | 
| XORA     | Bitwise XOR the values of the first and second addresses. Store the result in the third                                              | 0x0F  | 3        | 4            | Left operand address | Right operand address | Result address      | 
| JEQA     | "If the values at the first two addresses are equal, jump to the specified address"                                                  | 0x10  | 3        | 4            | Left operand address | Right operand address | Destiantion address | 
| JEQP     | "If the values at the first two addresses are equal, jump the specified number of addresses forward"                                 | 0x11  | 3        | 4            | Left operand address | Right operand address | Destiantion address | 
| JGTP     | "If the value at the first address is greater than the value at the second address, jump the specified number of addresses forward"  | 0x12  | 3        | 4            | Left operand address | Right operand address | Destiantion address | 
| JLTP     | "If the value at the first address is less than the value at the second address, jump the specified number of addresses forward"     | 0x13  | 3        | 4            | Left operand address | Right operand address | Destiantion address | 
| JEQN     | "If the values at the first two addresses are equal, jump the specified number of addresses backward"                                | 0x14  | 3        | 4            | Left operand address | Right operand address | Destiantion address | 
| JGTN     | "If the value at the first address is greater than the value at the second address, jump the specified number of addresses backward" | 0x15  | 3        | 4            | Left operand address | Right operand address | Destiantion address | 
| JLTN     | "If the value at the first address is less than the value at the second address, jump the specified number of addresses backward"    | 0x16  | 3        | 4            | Left operand address | Right operand address | Destiantion address | 
| MULA     | "Multiple the values of two addresses, store in the third address"                                                                   | 0x17  | 3        | 4            | Left operand address | Right operand address | Result address      | 
| DIVA     | Divide the value at the first address by the value at the second address. Store the result in the third address                      | 0x18  | 3        | 4            | Left operand address | Right operand address | Result address      | 
| MODA     | Divide the value at the first address by the value at the second address. Store the modulus in the third address                     | 0x19  | 3        | 4            | Left operand address | Right operand address | Result address      | 
